# Domande è risposte

## Domanda
1. Descrivere il problema della congestione, in particolare:
   - Cosa si intende per congestione;
   - Quali sono i sintomi della congestione;
   - Che relazione c'è con il controllo di flusso;
   - Quali sono i principali approcci al controllo della congestione;
   - Qual'é l'implementazione del controllo della congestione TCP;

## Risposta

Il fenomeno della congestione avviene quando tante sorgenti provano ad inviare dati a velocità elevate causando ritardi e perdita di pacchetti. Non bisogna confondere controllo del flusso e congestione in quanto:

- Congestione: Tanti mittenti che trasmettono tanti segmenti ad un velocità elevata.
- Controllo di flusso: Un unico mittente che trasmette segmenti troppo veloci per un unico destinatario.

Ci sono due tipi approcci al controllo della congestione:

1. *Controllo della congestione end-to-end*: Il livello di rete non offre nessun servizio di congestione per il livello di trasporto, il quale per poter dedurre l'esistenza della congestione deve far affidamento sui dispositivi periferici, ovvero deve osservare e analizzare le loro perdite e ritardi.
2. *Controllo della congestione assisito dalla rete*: In questo caso i dispositivi, quali i router inviano al mittente feed-back, tramite dei pacchetti chiamati *chokepacket* avvisandoli della congestione, oppure i router inviano al mittene la propria frequenza di trasmissione.

TCP classico utilizza il controllo della congestione end-to-end limitando la frequenza di trasmissione introducendo una nuova variale `cwnd`, che rappresenta la *finestra di congestione*.
$$LastByteSent - LastByteAcked \leq \min\{cwnd, rwnd\}$$
Sappiamo dal controllo di flusso che, affinché il mittente non mandi in overflow il buffer del destinatario, deve valere la seguente relazione:
$$LastByteSent - LastByteAcked \leq rwnd$$
Dove $LastByteSent$ rappresenta l'ultimo byte inviato, $LastByteAcked$ rappresenta l'ultimo byte per cui si è avuto un ACK, dunque la differenza rappresenta la quantità di dati inviati per cui non si è avuto ancora un ACK. $rwnd$ è la finestra di ricezione del destinatario.

In TCP il controllo della congestione è implementato in questo modo:

- **Slow Start**: Quando si stabilisce una connessione TCP, $cwnd$ viene posto a 1 MSS e viene incrementato ogni volta che arriva un ACK. Inoltre vengono spediti due segmenti ad ogni incremento. Quindi la velocità di trasmissione parte lentamente, per poi crescere in maniera esponenziale. Questo incremento esponenziale giunge a termine quando avviene un time out, ovvero una perdita di un pacchetto, in quanto $cwnd$ viene reimpostato a 1 MSS e la variabile $ssthresh$ viene impostata a $\frac{cwnd}{2}$, ovvero al valore dimezzato del ultima misura della congestione. Quando $cwnd == ssthresh$ si passa in Congestione Avoidance.
- **Congestion Avoidance**: In questo stato si passa da un incremento esponenziale ad uno lineare, quindi ad ogni RTT incrementa di uno $cwnd$. Quando arriva un timeout, si comporta esattamente come Slow Start, ovvero $cwnd$ viene reimpostato a 1 MSS e la variabile $ssthresh$ viene impostata a $\frac{cwnd}{2}$ e passa in Fast Recovery.
- **Fast Recovery**: In questo stato ogni volta che riceve un ACK duplicato per il pacchetto che ha causato il timeout incrementa di uno $cwnd$, poi quando gli arriva l'ACK di quel pacchetto, ovvero quando il pacchetto perso o che ha causato il timeout è arrivato, ritorna in Congestion Avoidance. Se invece arriva un altro timeout va in Fast Recovery.

## Domanda

2. Qual'è il ruolo del livello di trasporto e quali sono le differenze tra UDP e TCP.

## Risposta

## Domanda

3. Discurere del protocollo HTTP in particolare: 
   - Come viene utilizzato e qual'è il suo ruolo;
   - Messaggio di richiesta;
   - Messaggio di risposta;

## Risposta

## Domanda

4. Dire cosa si intende per "traduzione dei domini in indirizzi IP"

## Risposta

## Domanda

5. Cosa si intende per piano di dati?

## Risposta

## Domanda

6. Come viene implementato in TCP il controllo della congestione assistito dalla rete? (ECN)

## Risposta

## Domanda

7. Cosa si intende per inoltro basato sull'indirizzo di destinazione?

## Risposta

## Domanda

8. Cosa si intende per inoltro generalizzato?

## Risposta

## Domanda

9. Qual'è l'architettura del router?

## Risposta

## Domanda

10. Quali sono i compiti principali che svolge il router?

## Risposta
