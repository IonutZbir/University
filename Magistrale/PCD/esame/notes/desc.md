# Wallet Bitcoin Go

Repository contenente il progetto per l'esame di Principles of Cryptocurrency Design.

L'obiettivo del progetto è quello di progettare un wallet Bitcoin in Golang da zero. I principali problemi da affrontare sono sicuramente la gestione e la generazione delle chiavi private e degli indirizzi Bitcoin, la generazione di transazioni e infine la connessione con il nodo Bitcoin per permettere di inserire la transazione nella blockchain.

- https://pkg.go.dev/github.com/btcsuite/btcutil
- https://github.com/btcsuite/btcd

## 1. Chiavi Private e Derivazione Indirizzi Bitcoin

Generazione e memorizzazione della chiave privata master. Per questa sezione si farà riferimento a:

- https://github.com/iancoleman/bip39
- https://github.com/bitcoin/bips/tree/master/bip-0039 - https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki
- https://github.com/bitcoin/bips/tree/master/bip-0032 - https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki
- https://www.secg.org/sec2-v2.pdf

La generazione di chiavi private Bitcoin secondo gli standard BIP prevede la creazione di una frase seed composta da 12 o 24 parole (BIP39), il suo inserimento in un generatore di chiavi master (BIP32) e la derivazione di indirizzi specifici.

### 1.2 Derivazione degli Indirizzi

Per la derivazione degli indirizzi si segue lo standard definito in BIP32/44/84.
BIP44 definisce una convenzione di indici da applicare alle stesse funzioni DeriveChild.

A partire dalla master key si crea un albero di derivazione di chiavi. Un percorso all'interno dell'albero segue il seguente schema:

```
m / purpose' / coin_type' / account' / change / address_index
``` 

Si parte dalla master key $m$ e si chiama la funzione `masterKey.DeriveChild(idx)`. Ogni "/" rappresenta una chiamata alla funzione `DeriveChild()`. L'apice `'` o `h` significa **hardened**, cioè si deve sommare `HardenedOffset` $(2^{31})$ ad `idx` prima di chiamare la funzione.

| Livello   | Path  | Valore indice | Hardened? | Chiamata                                  |
|-----------|-------|---------------|-----------|-------------------------------------------|
| purpose   | `44'` | 44            | sì        | `master.DeriveChild(44 + HardenedOffset)` |
| coin_type | `0'`  | 0             | sì        | `.DeriveChild(0 + HardenedOffset)`        |
| account   | `0'`  | 0             | sì        | `.DeriveChild(0 + HardenedOffset)`        |
| change    | `0`   | 0             | no        | `.DeriveChild(0)`                         |
| index     | `0`   | 0             | no        | `.DeriveChild(0)`                         |

```go
master, err := NewMasterKey(seed)
if err != nil {
    return err
}

// m/44'
purpose, err := master.DeriveChild(44 + HardenedOffset)
if err != nil {
    return err
}

// m/44'/0'
coinType, err := purpose.DeriveChild(0 + HardenedOffset)
if err != nil {
    return err
}

// m/44'/0'/0'
account, err := coinType.DeriveChild(0 + HardenedOffset)
if err != nil {
    return err
}

// m/44'/0'/0'/0  (external chain, per ricevere)
externalChain, err := account.DeriveChild(0)
if err != nil {
    return err
}

// m/44'/0'/0'/0/0  (primo indirizzo)
addrKey, err := externalChain.DeriveChild(0)
if err != nil {
    return err
}

pubKey, err := privToCompressedPub(addrKey.Key)
if err != nil {
    return err
}

address := DeriveLegacyAddress(pubKey, false) // false = mainnet
fmt.Println(address) // "1..."
```

Chiamando poi `addrKey.Key` (32 byte, privata) ootteremo la chiave per firmare la transazione che spenderà da quel'indirizzo.

Quindi questo procedimento genera un albero fatto in questo modo:
```
                        m (master)
                            |
                    44' ────┼──── altri rami possibili (49', 84', ...)
                            |
                    0' ─────┼──── (altri coin_type se supportassi altre coin)
                            |
                    0' ─────┼──── (altri account: 1', 2', ...)
                            |
              ┌─────────────┴─────────────┐
              0                            1
        (external chain)            (internal chain)
              |                            |
      ┌───────┼───────┐            ┌───────┼───────┐
      0       1       2 ...        0       1       2 ...
   (indirizzo (indirizzo         (resto)  (resto)
    di ricez.) di ricez.)
```

## 2. Memorizzazione su Disco

## 3. Generazione Transazioni

- https://github.com/bitcoin/bips/blob/master/bip-0141.mediawiki
- https://github.com/bitcoin/bips/blob/master/bip-0143.mediawiki
- https://github.com/bitcoin/bips/blob/master/bip-0144.mediawiki

## 4. Inserimento su Blockchain e Collegamento al Nodo

## Scenario consigliato: nodo per tutto, mempool.space solo come "vista"/backup

Il tuo nodo Bitcoin Core via RPC può fare **tutto** quello che ti serve per il wallet:

| Operazione | RPC method |
|---|---|
| Query UTXO di un indirizzo | `scantxoutset` (se non hai `-txindex`) o `listunspent` (se è wallet-aware) |
| Fee estimation | `estimatesmartfee <conf_target>` |
| Broadcast | `sendrawtransaction "<hex>"` |
| Verifica conferma | `gettransaction` / `getrawtransaction` con verbose |
| Stato mempool | `getmempoolentry <txid>` |

Se il tuo nodo **non ha `-txindex=1`** attivo, `scantxoutset` per recuperare UTXO di un indirizzo arbitrario è lento (scansiona tutto l'UTXO set on-demand). In quel caso mempool.space API è comodo come **complemento** solo per le query di UTXO/address history, mantenendo il tuo nodo per broadcast e fee estimation (dati più affidabili/diretti, zero terze parti nel path critico).

## Setup ibrido pratico per il tuo wallet Go

```
┌─────────────────────────────────────┐
│         Wallet Go                    │
├───────────────┬───────────────────────┤
│  Query UTXO    │  mempool.space API    │  (comodo, indicizzato, veloce)
│  (address→utxo)│  GET /api/address/{a}/utxo
├───────────────┼───────────────────────┤
│  Fee estimate  │  tuo nodo RPC         │  (dato diretto dalla tua mempool)
│                │  estimatesmartfee     │
├───────────────┼───────────────────────┤
│  Broadcast tx  │  tuo nodo RPC         │  (privacy: non esponi la tx
│                │  sendrawtransaction   │   a un servizio terzo prima
│                │                       │   che sia in mempool)
└───────────────┴───────────────────────┘
```





## RIASSUNTO

1. Genera/importa mnemonic (BIP39) → seed
2. Deriva master key (BIP32)
3. Deriva account key m/84'/0'/0', poi un paio di indirizzi fissi (indice 0, 1)
4. Mostra gli indirizzi all'utente ("manda fondi qui per testare")
5. Query al nodo: quali UTXO ci sono su questi indirizzi? (listunspent o scantxoutset)
6. L'utente specifica: destinatario + importo
7. Costruisci tx (seleziona UTXO semplice, calcola resto)
8. Firma con BIP143
9. sendrawtransaction al nodo