# Protocolli a suddivisione del canale

# Protocolli ad accesso causale

## Slotted ALOHA

Slotted ALOHA è uno dei più semplici algoritmi di acceso casuale ad un canale per trasmissioni multiple.

- Tutti i frame hanno la stessa dimensione.
- Il tempo è diviso in slot temporali uguali, pari al tempo di trasmissione di un frame.
- I nodi cominciano la trasmissione solo all'inizio degli slot.
- I nodi sono sicronizzati in modo tale che tutti sappiano quando iniziano i slot.
- Se due nodi trasmettono in contemporanea nello stesso slot, tutti i nodi rilevano l'evento prima del termine dello slot.

Sia $p$ una probabilità, ovvero un numero tra 0 e 1. Allora le operazioni dei nodi in slotted ALOHA sono:

1. Quando un nodo ha un nuovo frame da spedire, attende fino all'inizio dello slot successivo e poi trasmette l'intero frame.
2. **Se non si verifica una collisione**, l'operazione ha avuto successo, quindi non occorre effettuare una ritrasmissione e il nodo può predisporre l'invio di un nuovo frame.
3. **Se si verifica una collisione**, il nodo la rileva prima della terminazione dello slot e ritrasmette con probalità $p$ il suo frame durante gli slot successivi, fino a quando l'operazione non ha successo.

Per capire meglio il concetto di **ritrasmissione con probabilità $p$** possiamo immaginare che il nodo lanci una moneta truccata: l'evento testa corrisponde alla ritrasmissione, che si verifica con probabilià $p$, quello croce corrisponde a "salta questo slot e lancia di nuovo la moneta in quello successivo". Questo accade con probabilità $(1 - p)$. I nodi coinvolti nella collisione lanciano le proprie monete indipendentemente gli uni dagli altri.

### Vantaggi

1. Quando c'è un solo nodo attivo, esso continua a trasmettere frame a massima velocità.
2. Fortemente decentralizzato in quanto ciascun nodo rileva le collisioni e decide indipendentemente dagli altri quando ritrasmettere.
3. Molto semplice.

### Svantaggi

1. Se ci sono collisioni, esse portano a sprecare slot.
2. Un grande numero di slot risulterà inutilizzato, in quanto la ritrasmissione è probabilistica.

### Efficienza

**L'efficienza** di un protocollo di accesso multiplo che fa uso di slot temporali è definita come la frazione di slot riusciti in presenza di un elevato numero di nodi attivi che hanno sempre un elevato numero di frame da trasmettere.

Dopo tanti calcoli che non sto qua a fare perché non me va, otteniamo che l'effienza massima di slotted ALOHA è $\frac{1}{e} = 0.37$. Vale a dire che quando un gran numero di nodi ha molti pacchetti da trasmettere, allora solo il **$37\%$** degli slot compie lavoro utile.

## ALOHA

La prima versione di slotted ALOHA, fu ALOHA puro, che non faceva utilizzo degli slot ed era fortemente decentralizzato. Dunque appena arriva un frame il nodo lo trasmette immediatamente e integralmente nel canale broadcast. Se il frame va in collisione allora lo ritrasmette immediatamente con probabilità $p$.

L'efficienza di questo protocollo è $\frac{1}{2e} = 0.18$ esattamente la metà di slotted ALOHA.

## CSMA: Carrier Sense Multiple Access

Se in ALOHA e slotted ALOHA i nodi prendono la decione di trasmettere indipendentemente dall'attività degli altri nodi collegati in broadcast (analogia: maleducato che parla sopra ad altre persone senza preoccuparsi che stiano conversando tra di loro), i protocolli CSMA e CSMA/CD si basano su due regole fondamentali:

1. *Ascoltare prima di parlare*, nel mondo delle reti questo prende il nome di **rilevamento della portante (carrier sens)**, ovvero un nodo ascolta il canale prima di trasmettere. Se il canale sta già trasmettendo un frame allora si mette in attesa, altrimenti se il canale è libero inizia la trasmissione (CSMA).
2. *Se qualcun altro comincia a parlare insieme a voi, smettere di parlare*, nel mondo delle reti questo prende il nome di **rilevamento della collisione (collisione detection)**. Se un nodo osserva che un altro nodo sta trasmettendo un frame che interferisce col suo, arresta la propria trasmissione (CSMA/CD).

> [!NOTE]  
> 
> In ALOHA e slotted ALOHA questo non era possibile fare, in quanto sono protocolli utilizzati per le connessione wireless, nelle quali non banale osservare che un canale è occupato. CSMA e CSMA/CD sono utilizzati nei collegamenti Ethernet.

Dunque, se si parte dall'idea che se un nodo trasmette gli altri non possono trasmettere perché si verificano comunque delle collisioni? La risposta a questa domanda è il **ritardo di propagazione**.

Supponiamo che un nodo stia iniziando a trasmettere all'istante di tempo $t_{0}$, ma il suo segnale impiega del tempo per arrivare: gli altri nodi potrebbero quindi in certe occasioni rilevare il canale inattivo quando in realtà non lo è.

## CSMA/CD

Osserviamo adesso le operazioni svolte da CSMA/CD dal punto di vista della scheda di rete.

1. La NIC riceve un datagramma dal livello di rete e lo incapsula quindi in un frame.
2. Se il canale risulta libero lo trasmette, altrimenti si mette in attesa finché il canale non si libera e inzia la trasmissione.
3. Verifica la presenza di eventuali segnali provenienti da altre schede di rete.
4. Se la scheda di rete non rivela altri segnali e trasmette l'intero frame allora ha svolto il suo lavoro. Altrimenti se rileva segnali da altre schede di rete (JAM) interrompe la sua trasmissione.
5. Entra in uno stato di wait per un tempo casuale (**tempo di backoff**), per poi ritornare al passo 2.

Ma quanto deve essere questo **tempo di backoff**? Questo tempo viene calcolato dall'algoritmo **binary exponential backoff**. In pratica se viene rilevata l' $n - esima$ collisione, viene scelto un $k$ causale nell'intervallo 
$$\{0,\ 1,\ 2, \dots,\ 2^{n} - 1\}$$
L'intervallo di tempo che deve aspettare è pari al tempo di trasmissione di 512 bit * $k\ s$, ed $n$ è al più 10.


### Efficienza

**L'efficienza di CSMA/CD** è la frazione di tempo media durante la quale i frame sono trasferiti sul canale senza collisioni in presenza di un alto numero di nodi attivi, con un'elevata quantità di frame da inviare.

$$
Efficienza = \frac{1}{1 + \frac{5d_{prop}}{d_{trasm}}}
$$

dove:

- $d_{prop}$ è il massimo ritardo di propagazione tra due schede di rete.
- $d_{trasm}$ è il tempo necessario per trasmettere un frame di dimensione massima.

L'efficienza tende a 1 se:

- $d_{prop}$ tende a 0;
- $d_{trasm}$ tende a infinito;

È un protocollo migliore di ALOHA e slotted ALOHA ma non è applicabile al wireless in quanto non è facile capire se un canale è libero o meno.

# Protocolli a rotazione

L'idea alla base di questi protocolli è quella di estrarre il meglio dai protocolli a suddivisione del canale e ad accesso casuale.
Ci sono due protocolli:

## 1. Protocollo Polling

In questa tipologia di protocollo, esiste un nodo principale, detto controllore che ha il compito di consentire periodimacamente a ciascun client di inviare per un tot tempo un numero di tot frame. In questo modo un client non trasmetterà finché non gli verrà dato il permesso dal controllore.

Il controllore inoltre può aspettare che ciascun client abbia esaurito il proprio turno, oppure in un approccio a rilevamento della portante puo decidere di lasciar trasmenttere un altro client non appena l'altro ha finito.

**Svantaggi**

- Si crea **ritardo di polling**, poiché controllare il traffico spreca banda
- **Throughput minore di R**, in quanto il c'é ritardo di polling
- **Sistema centralizzato**, essendo centrallizato c'é un unico punto di rottura, e in caso di guasto si rompe tutto.

È usato dal bluetooth.

## 1. Protocollo Token passing

In questo protocollo non esiste un nodo centrale ma un frame di controllo detto **token** che circola fra i nodi seguendo un ordine fissato. Chi possiede il token ha il diritto di trasmettere in quel istante di tempo sul canale. È altamente efficiente ma anch'esso non è privo di problemi in quanto ci puo essere la perdita del **token** o la rottura di un nodo.