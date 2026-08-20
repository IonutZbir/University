## 1. BIP39 — Dalla entropia alla seed

### Step 1: Generazione dell'entropia
Si genera un numero casuale di $ENT$ bit, con $ENT \in \{128, 160, 192, 224, 256\}$ (multiplo di 32). Tipicamente 128 bit → mnemonic da 12 parole, 256 bit → 24 parole.

### Step 2: Checksum
Si calcola:
$$CS = ENT / 32$$
$$\text{checksum} = \text{primi } CS \text{ bit di } SHA256(\text{entropy})$$

I bit di checksum vengono appesi in coda all'entropia:
$$\text{data} = \text{entropy} \| \text{checksum}, \quad |\text{data}| = ENT + CS$$

Questo garantisce che, per 128 bit di entropia, si ottengano $128+4=132$ bit, divisibili in $132/11 = 12$ gruppi da 11 bit.

### Step 3: Mapping alle parole
Ogni gruppo di 11 bit (valore $0$–$2047$) indicizza una parola in una wordlist standardizzata di 2048 parole (es. l'inglese). Il risultato è la **mnemonic phrase**.

Il checksum serve principalmente a rilevare errori di trascrizione/battitura, non è un vero meccanismo crittografico di sicurezza.

### Step 4: Da mnemonic a seed (PBKDF2)
$$\text{seed} = \text{PBKDF2}\big(\text{HMAC-SHA512}, \; \text{password}=\text{mnemonic}, \; \text{salt}=\text{"mnemonic"} \| \text{passphrase}, \; \text{iterazioni}=2048, \; dkLen=64\text{ byte}\big)$$

Punti importanti:
- La **passphrase** opzionale (il cosiddetto "25° parola") viene concatenata al salt: se la ometti, si usa stringa vuota. Cambiare la passphrase produce un wallet completamente diverso, anche con la stessa mnemonic.
- L'output è sempre **512 bit (64 byte)**, indipendentemente dalla lunghezza della mnemonic — questo è il seed che alimenta BIP32.

Nota: la mnemonic **non viene decodificata all'indietro** per ricavare la seed — è un processo unidirezionale via KDF, quindi conoscere la seed non ti dà l'entropia originale né viceversa in modo banale (in realtà l'entropia sì che è recuperabile dalla mnemonic stessa, ma la seed è derivata via PBKDF2 e non invertibile).

---

## 2. BIP32 — Gerarchia deterministica di chiavi (HD Wallet)

- https://github.com/btcsuite/btcd/tree/master/btcutil/hdkeychain

### Step 1: Master key da seed
$$I = \text{HMAC-SHA512}(\text{key}=\text{"Bitcoin seed"}, \; \text{data}=\text{seed})$$
$$I_L = \text{primi 32 byte} = \text{master private key } k_{master}$$
$$I_R = \text{ultimi 32 byte} = \text{master chain code } c_{master}$$

La coppia $(k_{master}, c_{master})$ costituisce la **extended private key** (xprv).

### Step 2: Derivazione dei figli (CKD - Child Key Derivation)
Se vuoi, posso anche scriverti uno script Python che implementa questa pipeline passo-passo (utile se stai lavorando su qualcosa legato a crittografia/sicurezza per il corso), oppure approfondire un punto specifico come la matematica della derivazione su curva ellittica.
Per ogni chiave estesa hai $(k_{par}, c_{par})$. La derivazione del figlio con indice $i$ funziona così:

**Derivazione normale** (non-hardened, $i < 2^{31}$):
$$I = \text{HMAC-SHA512}(c_{par}, \; \text{ser}_P(K_{par}) \| \text{ser}_{32}(i))$$
dove $K_{par}$ è la chiave pubblica del genitore (derivata da $k_{par}$ tramite curva ellittica secp256k1).

**Derivazione hardened** ($i \geq 2^{31}$, notazione $i'$):
$$I = \text{HMAC-SHA512}(c_{par}, \; 0x00 \| \text{ser}_{256}(k_{par}) \| \text{ser}_{32}(i))$$

In entrambi i casi:
$$I_L, I_R = \text{split}(I) \quad \text{(32+32 byte)}$$
$$k_i = (I_L + k_{par}) \mod n \qquad c_i = I_R$$

dove $n$ è l'ordine del gruppo di secp256k1.

**Perché la hardened derivation esiste?** Con la derivazione normale, se qualcuno conosce una chiave pubblica estesa (xpub) e una qualunque chiave privata figlia, può ricavare la chiave privata del genitore (perché $I_L$ dipende solo dalla xpub, nota pubblicamente). La derivazione hardened rompe questa proprietà usando $k_{par}$ (privata) nell'HMAC, quindi è usata tipicamente per i primi livelli del path (account level).

### Step 3: Chiavi pubbliche estese (xpub)
Da $k_i$ si ottiene sempre $K_i = k_i \cdot G$ (moltiplicazione su curva ellittica). È anche possibile derivare direttamente xpub → xpub figli (solo per derivazione normale, non hardened), utile per i "watch-only wallet".

---

## 3. BIP44 — Convenzione sui path

Per organizzare la gerarchia in modo standard tra i vari wallet software, si usa il path:

```
m / purpose' / coin_type' / account' / change / address_index
```

Esempio per Bitcoin, primo account, indirizzo di ricezione #0:
```
m / 44' / 0' / 0' / 0 / 0
```

- `purpose'` = 44' (fisso per BIP44), oppure 49' per BIP49 (P2SH-P2WPKH), 84' per BIP84 (native SegWit bech32)
- `coin_type'` = 0' per Bitcoin mainnet
- `account'` = indice account (0', 1', ...)
- `change` = 0 (indirizzi di ricezione) o 1 (indirizzi di resto/change)
- `address_index` = indice sequenziale dell'indirizzo

---

## 4. Dalla chiave pubblica all'indirizzo Bitcoin

Ottenuta $K_i$ (33 byte, formato compresso), il formato dell'indirizzo dipende dal tipo:

**Legacy (P2PKH, prefisso "1")**
$$\text{hash160} = RIPEMD160(SHA256(K_i))$$
$$\text{address} = \text{Base58Check}(0x00 \| \text{hash160})$$

**SegWit wrapped (P2SH-P2WPKH, prefisso "3", BIP49)**
$$\text{redeemScript} = 0x00 \; 0x14 \; \text{hash160}(K_i)$$
$$\text{address} = \text{Base58Check}(0x05 \| RIPEMD160(SHA256(\text{redeemScript})))$$

**Native SegWit (P2WPKH, prefisso "bc1", BIP84)**
$$\text{address} = \text{Bech32}(\text{hrp}="bc", \; \text{witver}=0, \; \text{hash160}(K_i))$$

---

## Riassunto del flusso completo

```
entropia casuale (128–256 bit)
      │  + checksum (SHA256)
      ▼
mnemonic (12–24 parole)   [BIP39]
      │  + passphrase opzionale, PBKDF2-HMAC-SHA512 (2048 iter)
      ▼
seed (512 bit)
      │  HMAC-SHA512(key="Bitcoin seed", seed)
      ▼
master key (k, c)         [BIP32]
      │  CKD ripetuta secondo path m/44'/0'/0'/0/i   [BIP44]
      ▼
chiave privata/pubblica derivata K_i
      │  hash160 + encoding (Base58Check o Bech32)
      ▼
indirizzo Bitcoin
```