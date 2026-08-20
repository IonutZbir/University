
**Perché il broadcast dal tuo nodo e non da mempool.space?** Se trasmetti tramite un'API terza, quel servizio "vede" la tua transazione (e quindi il tuo indirizzo/pattern di spesa) prima ancora che sia sulla rete P2P. Se hai un nodo tuo, ha più senso fare `sendrawtransaction` direttamente lì — nessuna fuga di privacy verso terzi, e la tx entra comunque nella rete P2P globale.

## In Go, per l'RPC verso il tuo nodo

```go
import "github.com/btcsuite/btcd/rpcclient"

connCfg := &rpcclient.ConnConfig{
    Host:         "127.0.0.1:8332",
    User:         "tuouser",
    Pass:         "tuapassword",
    HTTPPostMode: true,
    DisableTLS:   true, // solo se locale/rete fidata
}
client, err := rpcclient.New(connCfg, nil)
```

```go
package broadcast

import (
    "fmt"
    "github.com/btcsuite/btcd/btcutil"
    "github.com/btcsuite/btcd/chaincfg/chainhash"
    "github.com/btcsuite/btcd/rpcclient"
    "github.com/btcsuite/btcd/wire"
)

func BroadcastViaNode(client *rpcclient.Client, rawTxHex string) (*chainhash.Hash, error) {
    txBytes, err := hex.DecodeString(rawTxHex)
    if err != nil {
        return nil, fmt.Errorf("decode hex: %w", err)
    }

    var msgTx wire.MsgTx
    if err := msgTx.Deserialize(bytes.NewReader(txBytes)); err != nil {
        return nil, fmt.Errorf("deserialize tx: %w", err)
    }

    txHash, err := client.SendRawTransaction(&msgTx, false) // false = non permettere high fees senza check
    if err != nil {
        return nil, fmt.Errorf("sendrawtransaction: %w", err)
    }

    return txHash, nil
}
```

```go
package broadcast

import (
    "bytes"
    "fmt"
    "io"
    "net/http"
)

func BroadcastViaMempoolSpace(rawTxHex string, testnet bool) (string, error) {
    baseURL := "https://mempool.space/api/tx"
    if testnet {
        baseURL = "https://mempool.space/testnet/api/tx"
    }

    resp, err := http.Post(baseURL, "text/plain", bytes.NewBufferString(rawTxHex))
    if err != nil {
        return "", fmt.Errorf("http post: %w", err)
    }
    defer resp.Body.Close()

    body, err := io.ReadAll(resp.Body)
    if err != nil {
        return "", fmt.Errorf("read response: %w", err)
    }

    if resp.StatusCode != http.StatusOK {
        return "", fmt.Errorf("mempool.space rejected tx (status %d): %s", resp.StatusCode, string(body))
    }

    // mempool.space risponde col txid in plain text nel body
    return string(body), nil
}
```

```go
func BroadcastToBoth(nodeClient *rpcclient.Client, rawTxHex string, testnet bool) {
    var wg sync.WaitGroup
    wg.Add(2)

    var nodeTxHash *chainhash.Hash
    var nodeErr error
    var mempoolTxID string
    var mempoolErr error

    go func() {
        defer wg.Done()
        nodeTxHash, nodeErr = BroadcastViaNode(nodeClient, rawTxHex)
    }()

    go func() {
        defer wg.Done()
        mempoolTxID, mempoolErr = BroadcastViaMempoolSpace(rawTxHex, testnet)
    }()

    wg.Wait()

    if nodeErr != nil {
        fmt.Printf("⚠️  Nodo fallito: %v\n", nodeErr)
    } else {
        fmt.Printf("✅ Nodo: txid = %s\n", nodeTxHash.String())
    }

    if mempoolErr != nil {
        fmt.Printf("⚠️  mempool.space fallito: %v\n", mempoolErr)
    } else {
        fmt.Printf("✅ mempool.space: txid = %s\n", mempoolTxID)
    }
}
```

Una volta costruita e firmata la transazione (serializzata in formato hex), va **trasmessa alla rete** perché possa essere inclusa in un blocco. Bitcoin non ha un endpoint centrale "giusto" a cui inviare: basta raggiungere un nodo ben connesso che la ripropaghi ai suoi peer (gossip P2P), finché non arriva ai miner.

## Perché usare sia il nodo che mempool.space

Avendo a disposizione un nodo Bitcoin Core proprio, ha senso usarlo come canale principale di broadcast (`sendrawtransaction` via RPC), e aggiungere mempool.space come canale secondario/ridondante. Vantaggi di questo approccio ibrido:

- **Ridondanza**: se un canale è temporaneamente irraggiungibile, l'altro garantisce comunque la propagazione
- **Verifica incrociata**: entrambe le fonti dovrebbero restituire lo stesso `txid` (essendo deterministico dall'hash della tx) — utile come sanity check in fase di sviluppo
- **Privacy**: broadcastare prima dal proprio nodo evita di esporre la transazione a un servizio terzo prima che sia effettivamente in rete; mempool.space resta un fallback/conferma

## Nota pratica

Se si invia a entrambi i canali, è normale che il secondo tentativo risponda con un errore tipo *"transazione già nota"* (es. `txn-already-known`) — non è un fallimento reale, ma la conseguenza attesa del fatto che la tx è già stata propagata dal primo canale. Va gestito come caso non critico, non come errore vero.

## Riepilogo endpoint utili

| Azione | Nodo (RPC) | mempool.space (REST) |
|---|---|---|
| Broadcast | `sendrawtransaction` | `POST /api/tx` |
| Verifica conferma | `gettransaction` | `GET /api/tx/{txid}` |
| Stato mempool | `getmempoolentry` | (dashboard pubblica) |
