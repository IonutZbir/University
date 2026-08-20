# BIP necessari per costruire e firmare transazioni

## Core

**Nessun BIP formale per la tx legacy** — il formato transazione originale di Bitcoin non è nemmeno un BIP, è nel codice originale. Ma se vuoi supportare SegWit (consigliato oggi, quasi tutti i wallet lo fanno):

- **BIP141** — SegWit: definisce il nuovo formato di serializzazione con `marker`, `flag` e campo `witness` separato
- **BIP143** — Nuovo algoritmo di sighash per input SegWit (risolve i problemi di malleabilità e quadratic hashing del vecchio sighash)
- **BIP144** — Serializzazione peer-to-peer dei dati witness

## Opzionali ma utili

- **BIP69** — Ordinamento canonico (lessicografico) di input/output — non obbligatorio, ma buona pratica per privacy
- **BIP125** — Replace-By-Fee (RBF), se vuoi permettere di aumentare la fee di una tx non confermata (basta settare `nSequence < 0xfffffffe`)
- **BIP174 (PSBT)** — Se in futuro vuoi supportare firma multi-dispositivo/hardware wallet; per un wallet "banale" **puoi saltarlo**

---

# Quali Implementare

### Opzione A — Solo Legacy P2PKH (più facile da capire)
```
BIP39 (mnemonic) → BIP32 (chiavi) → BIP44 path m/44'/0'/0'/0/i
→ indirizzo "1..." → transazione legacy classica
```
Il sighash legacy è concettualmente più semplice: serializzi l'intera tx sostituendo lo scriptSig dell'input che stai firmando con lo scriptPubKey dell'UTXO che spendi, appendi `SIGHASH_ALL` (4 byte), fai doppio SHA256, firmi con ECDSA su secp256k1, codifichi la firma in DER + byte sighash type.

### Opzione B — Native SegWit P2WPKH (consigliata, non molto più complessa)
```
BIP39 → BIP32 → BIP84 path m/84'/0'/0'/0/i
→ indirizzo "bc1..." → transazione SegWit (BIP141+BIP143)
```
Vantaggi: fee più basse (witness discount), sighash BIP143 evita il problema del quadratic hashing, ed è lo standard de facto oggi.

---

## Struttura essenziale di una transazione da implementare

1. **Selezione UTXO** — scegli gli input da spendere
2. **Costruzione output** — destinatario + eventuale change
3. **Serializzazione** — version(4) + [marker+flag se SegWit] + input count + inputs + output count + outputs + [witness se SegWit] + locktime(4)
4. **Calcolo sighash** per ogni input (BIP143 se SegWit)
5. **Firma ECDSA** (o Schnorr se in futuro vuoi Taproot/BIP340, ma per ora niente)
6. **Costruzione scriptSig/witness** finale
8. **Broadcast** (via RPC a un nodo, o API tipo Blockstream/mempool.space)

---

1. **Coin Selection:** Questa è la parte più complessa per creare una transazione, ossia capire quali UTXO scegliere per creare gli input. Gli wallet professionali, come Bitcoin Wallet, Electrum utilizzano algoritmi tipo Branch and Bound. Per questo progetto, si è scelto un approccio Greedy, ossia, dato un indirizzo, si ordinano le UTXO in ordine crescente. (spiegare poi meglio i vantaggi e gli svantaggi di tutto ciò)


## Librerie Go di riferimento (anche solo da leggere, non necessariamente da usare)

Il pacchetto **`btcsuite/btcd`** (in particolare `btcec`, `btcutil`, `txscript`, `wire`) è lo standard de facto in Go per Bitcoin — anche se vuoi implementare tutto "da zero" per scopo didattico, vale la pena guardare il loro codice sorgente per capire le convenzioni di serializzazione byte-per-byte, specialmente per BIP143.
