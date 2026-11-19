Abbiamo visto la comunicazione tramite [[Communication in DS - RPC |RPC]]. Essi presentano ancora alcune forme di *accoppiamento* tra le entità coinvolte.
- *Accoppiamento temporale:* Il chiamante e il chiamato devono essere entrambi attivi e disponibili durante l'interazione.
- *Accoppiamento spaziale:* Il chiamante deve conoscere come raggiungere il destinatario della richiesta, direttamente o attraverso un meccanismo di localizzazione.

Per riderre queste forme di accoppiamento viene introdotta la *comunicazione persistente orientata ai messaggi*, realizzata attraverso i *Message-Oriented Middleware*. Un MOM è un middleware di comunicazione che consente alle applicazioni distribuite di scambiarsi messaggi attraverso un'infrastruttura intermedia, capace di conservarli temporaneamente fino alla loro consegna o elaborazione.

![[momvsrpc.png]]

Il MOM agisce quindi come intermediario tra:
- **Producer:** componente che genera e invia messaggi.
- **Consumer:** componente che riceve ed elabora messaggi.
Il middleware si occupa delal gestione dei messaggi, riducendo le dipendenze tra i due componenti.

**VANTAGGI:**
L'obiettivo principale dei MOM è ottenere un *accoppiamento debole (loose coupling)* tra i componenti di un sistema distribuito.
1. *Disaccoppiamento temporale:* Producer e consumer non devono necessariamente essere attivi contemporaneamente. Il middleware può conservare un messaggio o renderlo disponibile al consumer in un momento successivo.
2. *Disaccoppiamento spaziale:* Il producer non deve necessariamente conoscere l'indirizzo del consumer. È sufficiente che conosca la destinazione logica del messaggio, ad esempio una coda o un topic.
3. *Disaccopiamento della sincronizzazione:* Il producer può inviare un messaggio senza dover attendere che il consumer completi l'elaborazione.

Questi vantaggi portano a migliorare le *prestazioni, la scalabilità e l'affidabilità*.

## Pattern di comunicazione nei MOM

I MOM supportano principalmente due pattern di comunicazione:
- **Message Queue:** i messaggi vengono inseriti in una coda e ciascun messaggio viene consegnato a un singolo consumer (comunicazione *one-to-one*).
- **Pub/Sub:** I producer pubblicano messaggi associati a determinati argomenti (*topic*), che vengono distribuiti ai consumer interessati (comunicazione *one-to-many*).

### Message Queue Pattern

Rappresenta un modello di comunicazione nel quale i producer inviano messaggi a una coda, nella quale vengono successivamente prelevati dai consumer. I messaggi vengono conservati nella coda finché non vengono recuperati da un consumer.

La caratteristica fondamentale è che *ogni messaggio viene consegnato a un solo consumer*, anche quando più consumer sono collegati alla stessa cosa.


![[queue.png]]

**Casi d'uso**
- *Task scheduling:* i procuder inseriscono attività in una coda e i worker le eseguono.
- *Load balancing:* le attività vengono distribuite tra più consumer, evitando che un singolo componente debba elaborarle tutte.
- *Logging e tracing:* i componenti inviano messaggi relativi a eventi e operazioni, che vengono raccolti ed elaborati da un servizio dedicato.

**API**

| Operazione         | Comportamento      | Descrizione                                                                 |
| ------------------ | ------------------ | --------------------------------------------------------------------------- |
| `put(message)`     | Non bloccante      | Inserisce un messaggio nella coda                                           |
| `get()`            | Bloccante          | Attende che la coda contenga un messaggio e lo recupera                     |
| `poll()`           | Non bloccante      | Controlla la coda e recupera un messaggio se disponibile                    |
| `notify(callback)` | Basato su callback | Registra una funzione richiamata automaticamente quando arriva un messaggio |

### Publis/Subscribe Pattern

Rappresenta un modello di comuncazione asincrona nel quale i producer, chiamati *publisher*, pubblicano messaggi che vengono distribuiti ai consumer, chiamati *subscriber*, interessati a riceverli.

Il Pub/Sub supporta una comunicazione *one-to-many*, nella quale uno stesso messaggio può essere ricevuto da più subscriber.

**Topic**
I messaggi vengono generalmente organizzati in categorie logiche chiamate *topic*. Un subscriber può sottoscrivere uno o più topic, indicando al sistema quali messaggi desidera ricevere. Quando un publisher pubblica un messaggio su un topic, il sistema Pub/Sub lo distribuisce a tutti i subscriber che hanno una sottoscrizione corrispondente.

![[pubsub.png]]

I subscriber possono sottoscrivere un topic specificando anche dei *filtri*, in modo da ricevere soltanto i messaggi che soddisfano determinate condizioni.

**VANTAGGI**
Il Pub/Sub permette un elevato grado di disaccoppiamento tra i componenti. I publisher non devono conoscere i subscriber e non devono gestire direttamente la distribuzione dei messaggi.
Il sistema Pub/Sub può anche essere distribuito su più nodi per migliorare la scalabilità.

I principali casi d'uso sono:
- *Evento notification:* notificare eventi a più componenti interessati.
- *Multicasting:* distribuire uno stesso messaggio a più destinatari.

**API**

- `publish(message)`:
- `subscribe(filter_expr, notify_cb, expiry)`
- `notify_cb(sub_handle, message)`
- `unsubscribe(sub_handle)`

## Funzionalità dei MOM

Le principali funzionalità sono:
- *Disponibilità dei componenti:* gestione della consegna dei messaggi attraverso differenti *delivery semantic e models*.
- *Addresing e routing:* individuazione dei destinatari e instradamento dei messaggi verso le destinazioni corrette.
- *Trasformazione dei messaggi:* conversione dei formati e instradamento basato sul contenuto attraverso un *message broker*.

### Delivery Semantics

- *At-most-once delivery:* ogni messaggio viene consegnato al massimo una volta. Il middleware non effettua una nuova consegna se il messaggio viene perso. Questa semantica non garantisce quindi che tutti i messaggi raggiungano il destinatario.
- *At-least-once delivery:* il middleware cerca di garantire che ogni messaggio venga consegnato almeno una volta. Per ottenere questo comportamento viene utilizzato un meccanismo di conferma (*ACK*). Il problema principale è che la *mancata ricezione di un ACK non implica necessariamente che il messaggio non sia stato ricevuto*. Per evitare che le duplicazioni provochino errori, il consumer dovrebbe essere *idempotente*.
- *Exactly-once delivery:* ha come obiettivo di garantire che ogni messaggio venga consegnato esattamento una volta. Questo risultato può essere ottenuto combinando meccanismi di *deduplicazione, consumer idempotenti, storage persistente*.

**Timeout-based Delivery**
Meccanismo che permette di realizzare una consegna *at-least-once*, cercando di riderre il rischio che più consumer elaborino contemporaneamente lo stesso messaggio.
- *visibility timeout:* quando un consumer recupera un messaggio, questo non viene immediatamente eliminato dalla coda, ma viene contrasegnato con *invisilble* per un intervallo di tempo. Durante questo periodo, gli altri consumer non possono recuperare lo stesso messaggi.

**Transaction-based Delivery**
Questo meccanismo utilizza le transazioni per coordinare la ricezione e la rimozione dei messaggi dalla coda. L'obiettivo è garantire che un messaggio venga eliminato soltanto dopo che è stato ricevuto ed elaborato correttamente dal consumer.

Ricordiamo che una transazione è definita dalle proprietà *ACID*.
- *Commit:* la transazione termina correttamente e il messaggio viene eliminato definitivamente.
- *Rollback:* la transazione fallisce e il messaggio rimane nella coda, permettendo una successiva elaborazione.

### Delivery Models: Push vs Pull

Definiscomo come i consumer recuperano i messaggi.

![[pushpull.png]]

- *Push:* il middleware gestisce attivamente la consegna dei messaggi.
- *Pull:* il consumer decide quando richiedere nuovi messaggi.

### Message Routing

Il MOM si occupa dell'*instradamento dei messaggi* attraverso componenti chiamati *Queue Manager*. Un QM gestisce le code e permette la comunicazione tra applicazione e altri QM.

I QM formano una *rete overlay* e l'instradamento all'interno di questa rete avviene tramite tabelle di routing locali ai QM che associa i nomi delle code alle rispettive posizioni.
- *Static overlay:* le tabelle di routing vengono configurate e gestite manualmente.
- *Dynamic overlay:* le tabelle di routing vengono configurate e gestite dinamicamente.

### Message Broker

Un altro problema dei sistemi distribuiti è l'*eterogeneità delle applicazioni*. Componenti sviluppati con linguaggi e tecnologie differenti possono utilizzare formati di dati incompatibili tra loro.

Viene quindi introdotto il *Message Broker*, un componente intermedio che facilita l'interazione tra producer e consumer. Svolge:
- *Message Transformation:* trasforma i messaggi da un formato a un altro, utilizzando un insieme di regole di conversione.
- *Content-based Routing:* può decidere a quali destinatari inoltrare un messaggio in base al suo contenuto o al suo tipo.

## Amazon Simple Queue Service (SQS)

Servizio di messaggistica cloud gestito da AWS, progettato per fornire code di messaggi affidabili e scalabili.

L'obiettivo principale è quello di *disaccoppiare i componenti di un'applicazione distribuita* permettendo di operare in modo indipendente e asincrono.

### Architettura

Le code di messaggi sono completamente gestite da AWS e vengono distribuite su più server SQS. I messaggi vengono replicati su più server all'interno di una zona AWS.

SQS utilizza un modello di consegna *pull-based*.

Questa architettua consente di ottenere: *scalabilità, alata dispobilitià e disaccoppiamento*.

### Gestione dei messaggi

In SQS, una coda rappresenta un luogo di memorizzazione temporaneo, non un archivio permanente. Ogni messaggio viene conservato per un periodo configurabile, chiamato *message retention period* che può arrivare fino a 14 giorni.
Una volta recuperato ed elaborato correttamente, il messaggio deve essere eliminato esplicitamente dal consumer.

SQS implemeta il meccanismo di *timeout-based delivery*.
1. Un producer inserisce un messaggio nella coda.
2. Un consumer recupera il messaggio attraverso un'operazione di ricezione.
3. Il messaggio rimane nella coda, ma diventa temporaneamente invisibile agli altri consumer.
4. Se il consumer completa corretamente l'elaborazione, elimina il messaggio.
5. Se l'elaborazione fallisce e il messaggio non viene eliminato, alla scadenza del *visibility timeout* torna visibile e può essere recuperato nuovamente.
Un aspetto importante è che *ricevere un messaggio non significa eliminarlo*. In SQS, il recupero e l'eliminazione sono due operazioni distinte, proprio per permettere il recupero dei messaggi in caso di errore.

### Polling e tipologie di code

SQS supporta due modalità di polling:
- *Short Polling:* la richiesta interroga soltanto un sottoinsieme dei server SQS, di conseguenza si possono avere risposte vuote anche quando il messaggio richiesto è presente nella coda.
- *Long Polling:* la richiesta interroga tutti i server SQS e può rimanere in attessa dell'arrivo di nuovi messaggi.

SQS mette a disposizione due tipologie di code:
- *Standard Queue:* l'ordine di consegna è *best-effort*, i messaggi possono essere consegnati in ordine diverso da quello di arrivo e inoltre sono possibili duplicazioni.
- *FIFO Queue:* garantisce la consegna ordinata dei messaggi evitando duplicazioni. Presentano però un throughput inferiore rispetto alle code standard.

### API

- *Gestione delle code:* `CreateQueue, ListQueues, DeleteQueue, SetQueueAttributes, GetQueueAttribute`.
- *Gestione dei mesaggi:*
	- `SendMessage`: inserisce un messaggio nella coda. La dimensione massima è 1MB. Per messaggi più grandi, si può memorizzare il messaggio su S3 e inviare solo il link della risorsa.
	- `ReceiveMessage:` Permette di recuperare uno o più messaggi fino a 10 per richiesta.
	- `DeleteMessage, ChangeMessageVisibility`.

### Esempio

Servizio di elaborazione fotografie.

![[sqsesempio.png]]

**Funzionamento:**
1. L'utente carica una fotografia attraverso il front-end.
2. Il front-end salva l'immagine in un bucket S3.
3. Il front-end invia un messaggio alla coda SQS contenente il riferimento all'immagine.
4. Una delle istanze EC2 recupera il messaggio.
5. Il worker scarica l'immagine da S3 ed esegue l'elaborazione richiesta, ad esempio un ridimensionamento.
6. Se l'elaborazione termina correttamente, il worker elimina il messaggio dalla coda.

Il sistema può utilizzare un gruppo di istanze EC2 con *autoscaling*.
L'utilizzo di SQS introduce diversi vantaggi:
- *Disaccoppiamento:* il front-end non deve attendere che la fotografia venga elaborata.
- *Load balancing:* le richieste vengono distribuite tra più worker.
- *Fault tolerance:* se un worker fallisce, un altro può recuperare il messaggio e ripetere l'elaborazione.
- *Scalabilità:* il numero di worker può essere adattato dinamicamente al carico.

## Apache Kafka

Apache Kafka è una piattarforma open-source e distribuita di *event streaming*, progettata per gestire flussi continui di eventi.

Svolge tre operazioni fondamentali:
- *Publish/Subscribe:* pubblicare eventi e permettere ai consumer di sottoscrivere i relativi flussi.
- *Persistent Storage:* memorizzare gli eventi in maniera duratura e affidabile.
- *Stream Processing:* elaborare flussi di eventi.

Le sue principali caratteristiche sono:
- *Scalabilità orizzontale:* possibilità di distribuire il carico tra più nodi.
- *Fault tolerance:* capacità di continuare a funzionare in presenza di guasti.
- *High Throughput:* capacità di gestire quantità molto elevate di eventi, anche nell'ordine dei miliardi.
- *Durabilità:* conservazione persistente degli eventi.

### Architettura Generale

L'architettura di Kafka è composta da 4 elementi fondamentali:
- **Producer:** applicazioni che pubblicano eventi.
- **Topic:** categorie logiche nelle quali vengono organizzati gli eventi.
- **Broker:** server che ricevono e memorizzano gli eventi.
- **Consumer:** applicazioni che leggono ed elaborano gli eventi.

Un insieme di broker costituisce un *Kafka Cluster*, che può essere distribuito su più data center o regioni cloud.
Il producer non invia direttamente i messaggi ai consumer, ma li pubblica in un topic gestito dal cluster.
I consumer possono sottoscrivere i topic di interesse e leggere gli eventi indipendentemente dagli altri consumer.
Un topic può avere zero, uno oppure più consumer.

### Topic, Log e Partition

Kafka organizza gli eventi in all'interno di *topic*. Un topic rappresenta una categoria logica lla quale i producer possono pubblicare eventi. Per ogni topic, il cluster Kafka mantiene un *partitioned log* cioè un log suddiviso in più partizioni.

- **Log append-only:** Un log è una struttura dati costituita da una sequenza totalmente ordinata di record. In Kafka, il log è *append-only:* i nuovi eventi vengono aggiunti alla fine della sequenza e quelli già presenti non vengono modificati. Ogni partizione si comporta quindi in maniera simili ad un *commit log*.
- **Partition:** Un topic viene suddivisono in un numero predefinito di partizioni. Ogni partizione contiene una sequenza ordinata e immutabile di record. Le partizione rappresentano l'*unità fondamentale di parallelismo* di Kafka.
- **Offset:** Ogni record all'interno di una partizione possiede un *offset*, cioè un identificatore numerico che indica la posizione del record nel log. Gli offset sono crescenti e identificano univocamente un record all'intenro della relativa partizione (tipo gli indici nelle liste). Gli offset sono relativi alla singola partizione, non dell'intero topic. Per identificare un record è quindi necessario conoscere almeno `(Topic, Partition, Offset)`. 

![[kafkapartitions.png]]

**NOTA:** Le partizioni permettono di suddividere il carico di lavoro tra più nodi e consumer. Questo consente di eseguire letture e scritture in parallelo, aumentando la capacità complessiva del sistema.

### Partizionamento e scalabilità

Le partizioni di un topic possono essere distribuite su più broker. Questa scelta permette di aumentare la scalabilità orizzontale del cluster.

![[kafkabrokercluster.png]]

Questa organizzazione permette:
- A più producer di scrivere contemporaneamente su partizioni differenti;
- A più consumer di leggere contemporaneamente da partizioni differenti.
- Di distribuire il carico di I/O tra più broker.

### Replication e Fault Tolerance

Per garantire tolleranza ai guasti, Kafka permette di replicare le partizioni su più broker. Ogni partizione può avere:
- *Un leader:* replica principale che gestisce le operazioni di scrittura e, di default anche di lettura.
- *Zero o più follower:* repliche che copiano i dati del leader e fungono da backup.

**Leader Based Replication**

Il numero totale di repliche di una partizione, includendo il leader, viene chiamato *replication factor*.

![[kafkareplication.png]]

Il leader è quindi responsabile dell'odinamento delle scritture all'intenro della partizione. I producer inviano i messaggi ai leader, mentre i followe replicano i dati del leader. I follower possono essere:
- *In-sync:* repliche sufficientemente aggiornate rispetto al leader.
- *Out-of-sync:* repliche che hanno accumulato un ritardo rispetto al leader.

Le ripliche aggiornano le proprie partizioni facendo *pull* sul leader, ossia sono lo a richiedere di volta in volta se ci sono aggiornamenti.

Se il leader fallisce, Kafka può eleggere un nuovo leader tra le repliche in-sync disponibili. Con un replication factor pari a $N$, il sistema può teoricamente tollerare fino a $N - 1$ guasti di broker, senza perdere tutte le copie di una partizione, purché le repliche necessarie siano aggiornate e disponibili.

**Load Balancing**

Per evitare che un singolo broker gestisca tutte le operazioni, Kafka distribuisce la leadership delle partizioni. Ogni broker può quindi essere leader di alcune partizioni e follower di altre.

**Coordinamento Broker**

I broker devono mantere una visione coerente dello stato del cluster, comprendente: broker attivi, topic e partizioni, leader delle partizioni, configurazione del cluster.

Il coordinamento viene gestito da un *controller*, supportato da un algoritmo di consenso basato su *Raft*.

### Kafka Producers

I producer rappresentano le sorgenti dei dati e sono responsabili della pubblicazione degli eventi nei topic Kafka. Ogni producer deve determinare a quale partizione inviare un evento. Una volta individuata la partizione, il producer invia il messaggio direttamente al broker che ne gestisce il leader, senza passare attraverso un livello intermedio di routing.

Kafka supporta diverse strategie:
- *Key-based partitioning:* Ogni evento contiene una chiave (*partition key*), ad esempio un identificatore utente o ordine. La partizione viene scelta applicando una funzione hash alla chiave. Questo permette di indirizzzare eventi con la stessa chiave alla stessa partizione.
- *Sticky partitioning:* Quando gli eventi non possiedono una chiave, il producer può scegliere questo metodo. Il producer invia più messaggi consecutivi alla stessa partizione fino al completamento di un batch.
- *Custom partitioning:* Strategie personalizzate per decidere come distribuire gli eventi tra le partizioni.

### Kafka Consumers

I consumer sono i componenti che leggono ed elaborano gli eventi pubblicati nei topic.
Kafka utilizza un modello di consegna **pull-based**. Sono i consumer quindi a richiedere esplicitamente i nuovi eventi ai broker.

**Perché Pull?** 
Nel modello push, il broker dovrebbe gestire direttamente la consegna degli eventi ai consumer. Questo richiederebbe di considerare:
- Le differenti capacità di elaborazione dei consumer.
- La velocità di trasmissione dei messaggi.
- Il momento più opportuno per inviare i dati.
- Mantenere una mappatura `messaggi -> consumer`.

Nel modello pull, invece, è il consumer a controllare quando e quanti eventi recuperare. Questo *riduce il carico di gestione sui broker* e permette ai consumer di adattare la velocità di lettua alle proprie capacità. Questa è una scelta architetturale per migliorare la *scalabilità* e le *prestazioni* di Kafka.

In assenza di eventi, il consumer continuerà ad interrogare i broker senza ottenere nuovi dati.

**Gestione degli offset**

Ogni consumer tiene traccia della propria posizione di lettura attraverso un offset. Consumer differenti possono leggere la stessa partizione mantenendo offset diversi.

![[kafkaoffset.png]]

**Fault tolerance dei consumer**
Per permettere il recupero dopo un guasto, Kafka memorizza gli offset confermati (*committed offsets*) in un topic speciale chiamato: `__consumer_offsets`.
Quando un consumer elabora gli eventi, può registrare il proprio progesso attraveso un commit dell'offset. Se il consumer subisce un crash, può recuperare l'ultimo offset confermato e riprendere la lettura (la scelta di quando effettuare il commit definisce le diverse strategie di delivery semantics).

### Message Retention \& Storage

A differenza dei sistemi basati su code dove i messaggi vengono eliminati dopo essere stati elaborati, in Kafka i messaggi non vengono eliminati ma conservati su disco all'interno di file chiamati *log segments*. Il momento in cui avviene il trasferimento è controllato da una *log flush policy*.

Ci deve essere anche un meccanismo per liberare lo spazio su disco. Questo avveiene attraverso una *retention policy*, che stabilisce per quanto tempo o per quale quantità di dati gli eventi devono essere conservati:
- *Time-based retention:* gli eventi vengono conservati per un intervallo di tempo configurabile.
- *Size-based retention:* gli eventi vengono conservati fino al raggiungimento di una dimensione massima configurata.

La conservazione degli eventi indipendentemente dalla loro lettura permette a più consumer di elaborare gli stessi dati in momenti differenti. Questo rende Kafka particolarmente adatto a sistemi di event streaming, elaborazione di flussi di dati e architetture event-driven.

### Consumer Group

**DEF:** Un *consumer group* è un insieme di consumer che cooperano per leggere ed elaborare gli eventi di un topic e che condividono uno stesso identificatore, *Group ID*.

Dal punto di vista di Kafka, ogni consumer group rappresenta un unico *subscriber logico*.

Le partizioni di un topic vengono distribuite tra i consumer appartenenti allo stesso gruppo, in modo tale che ciascuna partizione sia assegnata a un solo consumer del gruppo in un determinato momento. Di conseguenza:
- Un consumer può leggere da più partizioni.
- Una partizione non viene assegnata contemporaneamente a più consumer dello stesso gruppo.
- Ogni gruppo mantiene i propri offset per ciascuna partizione.
- Consumer apparteneti a gruppi differenti possono leggere gli stessi eventi indipendentemente.

**Consumer Group e parallelismo**

Consideriamo un topic con 4 partizioni e un consumer group composto da due consumer. Kafka può assegnare due partizioni a ciascun consumer, distribuendo il carico di elaborazione.

Si tratta di una relazione 1:N lato consumer:
- Un singolo consumer può leggere contemporaneamente da più partizioni.
- Ogni partizione, in un dato momento, può essere letta da un solo consumer (all'interno dello stesso consumer group).

Il massimo grado di parallelismo ottenibile all'interno di un consumer group è quindi determinato dal numero di partizioni del topic.
$$
P_{\text{max}} = N_{\text{partizioni}}
$$
Se il numero di consumer supera il numero di partizioni. alcuni consumer rimangono inattivi.

![[kafkaconsumergroup.png]]

Attraverso il meccanismo di consumer group, Kafka può combinare le code e le pub/sub.
- *All'interno dello stesso consumer group - Message Queue:* i consumer si dividono le partizioni e quindi il lavoro. Ogni evento viene assegnato a un solo consumer del gruppo, salvo eventuali rielaborazioni.
- *Tra consumer grup differenti - Pub/Sub:* ciascun gruppo può leggere tutti gli eventi del topic, indipendentemente dagli altri gruppi. 
Questa caratteristica è particolarmente utile nelle architetture a microservizi.
Ogni microservizio può avere un proprio consumer group. Quando si effettua uno *scale-out* di un microservizio, le nuove repliche vengono aggiunte allo stesso gruppo e le partizioni vengono redistribuite.

### Ordinamento degli eventi

Kafka garantisce un *ordinamento totale degli eventi all'interno di ogni singola partizione*, ma non garantisce un ordinamento globale tra partizioni differenti dello stesso topic.

La combinazioe di *per-patitioning* e *key-based partitioning* è sufficiente per molte applicazioni. 
Supponiamo di utilizzare Kafka per gestire gli eventi relativi agli ordini di un e-commerce. Possiamo utilizzare come chiave `order_id`, in modo che tutti gli eventi relativi allo stesso ordine vengano inviati alla stessa partizione.

```
order_id = 101 -> Partition 0

OrderCreated
PaymentReceived
OrderShipped
OrderDelivered
```

Gli eventi relativi allo steso ordine possono essere così letti rispettando la loro sequenza, mentre gli eventi di ordini differenti possono essere elaborati in parallelo.
Si ottiene quindi un compromesso tra *ordinamento e parallelismo*: non è necessario imporre un ordinamento globale se l'applicazione richiede soltanto che siano ordinati gli eventi relativi alla stessa entità.

### Kafka Replication

Kafka replica le partizioni dei topic su più broker utilizzando un modello *leader-follower*, per garantire tolleranza ai guasti e durabilità dei dati.
La replicazione avviene in maniera *asincrona*: i follower recuperano  (*pull* sul leader) periodicamente dal leader i nuovi record, utilizzando gli offset per identificare la propria posizione nel log.

**In-Sync Replicas (ISR)**
Kafka mantiene, per ciascuna partizione, un insieme di repliche chiamato *ISR*, che comprende il leader e i follower sufficientemente aggiornati rispetto al suo log.

L'ISR viene aggiornata dinamicamente, infatti:
- se un follower fallisce o accumula un ritardo eccessivo, viene rimosso;
- se un follower recupera il ritardo, può essere reinserito nell'ISR;
- se il leader fallisce, una replica dell'ISR può essere eletta come nuovo leader.

- *Durabilità:* la durabilità dei record è garantita finché almeno una replica che li conserva rimane disponibile.
- *Replication factor:* rappresenta il numero configurato di repliche.

### Garanzie di Scrittura

Kafka permette di configurare le garanzie relative alle operazioni di scrittura attraverso due parametri fondamentali:
- `acks:` configurato a livello di producer;
- `min.insync.replicas:` configurato a livello di topic o cluster.

Questi parametri permettono di controllare il compromesso tra *latenza, durabilità e disponibilità*.

**Acks**
Il parametro `acks` stabilisce quali e quante repliche devono confermare una scrittura prima che il producer possa considerarla completata correttamente.
- *acks = 0:* Il producer non atttende alcuna conferma da parte del broker. Questo comportamento viene chiamato *fire and forget*. Si ottiene una latenza molto bassa, ma il producer non può sapere se il messaggio è stato effettivamente memorizzato.
- *acks = 1:* Il producer attende soltanto la conferma del leader della partizione. Il leader conferma la scrittura senza attendere che i follower abbiano replicato il record. Se il leader fallisce prima che la replicazione sia avvenuta, il messaggio potrebbe essere perso.
- *acks = all:* Il producer attende che tutte le repliche appartenenti all'ISR abbiano replicato il record. Al producer arriverà un solo ack, ossia quello del leader. Si ottiene una maggiore durabilità, al costo di una latenza superiore.

![[kafkaacks.png]]

**min.insync.replicas**
Utilizzare `acks = all` non significa necessariamente attendere tutte le repliche configurate attraverso il replication factor. Infatti, se l'ISR contiene soltanto il leader, anche `acks = all` potrebbe essere soddisfatto dalla sola replica del leader.
Per risolvere questo problema viene utilizzato il parametro `min.isync.replicas`, che stabilisce la dimensione minima dell'ISR necessaria affinché una scrittura effettuata con `acks = all` venga accettata.
Indicando con \(M\) il valore di `min.insync.replicas`, la condizione necessaria per accettare la scrittura è: $$|ISR|\geq M$$
Se questa condizione non è soddisfatta, il producer riceve un errore.

**Esempio**

Consideriamo un topic configurato con:
```
replication.factor = 3
acks = all
min.insync.replicas = 2
```
In questo caso, ogni scrittura confermata deve essere presente su almeno due repliche.

La configurazione raccomandata nelle slide è `acks = all` con `min.insync.replicas >= 2` e replication factor pari a 3.

### Visibility to Consumers: High Watermark

Poiché la replicazione avviene in maniera asincrona, il leader può contenere record che non sono ancora stati replicati da tutti i follower appartenenti all'ISR.

**Domanda: quali record possono essere letti da consumer?**
Se un consumer potesse leggere un record non ancora replicato e il leader fallisse immediatamente dopo, quel record potrebbe scomparire dal log.

Per evitare ciò, Kafka introduce il concetto di *High Watermark (HW)*.

- *Log End Offset* rappresena l'offset della prossima posizone di scrittura nel log di una replica.
- *High Watermark* rappresent il limite fino al quale i record sono stati confermati $$\text{HW} = \min_{r\ \in \text{ ISR}} \text{LEO}_{r}$$
I consumer possono leggere soltanto i record con $$\text{offset} < \text{HW}$$
![[kafkacommitedmessages.png]]

### Kafka Delivery Semantics

Le garanzie sulla consegna garantite da Kafka dipendono da due aspetti:
- Come il producer pubblica e conferma gli eventi.
- Quando il consumer effettua il commit del proprio offset rispetto all'elaborazione dell'evento.

#### At-most-once

Ogni evento viene elaborato al massimo una volta, ma potrebbe essere perso.
- *Producer:* configurazione senza ritrasmissioni: `acks = 0`.
- *Consumer:* l'offset viene confermato prima di elaborre l'evento.

![[kafkaatmost.png]]

Se il consumer fallisce dopo aver effettuato il commit dell'offset ma prima di elaborare l'evento, al riavvio riprenderà dall'offset sucessivo, non elaborando quindi l'evento.

#### At-most-once

Ogni evento deve essere elaborato almeno una volta, ma sono possibili duplicazioni.
- *Producer:* attende un ack e può ritrasmetter in caso di mancata conferma: `acks = 1`.
- *Consumer:* effettua il commit dell'offset soltanto dopo aver elaborato l'evento.

![[kafkatleast.png]]

Se il consumer fallisce dopo aver elaborato l'evento ma prima di effettuare il commit dell'offset, al riavvio recupererà nuovamente lo stesso evento. Di conseguenza potrebbe elaborare più volte lo stesso messaggio.
Per questo motivo è opportuno utilizzare consumer *idempotenti*.

#### Exactly-once

L'obiettivo è evitare sia la perdita degli eventi sia la duplicazione degli effetti della loro elaborazione. Kafka combina diversi meccanismi:
1. *Conferma delle repliche:* Il producer viene configurato con: `acks=all` e `min.insync.replicas=2` permettendo una maggiore durabilità degli eventi.
2. *Producer idempotente:* Kafka associa agli eventi un identificatore del producer `producerID` e un numero di sequenza `seqNumber`. Queste informazioni permettono al broker di riconoscere eventuali duplicati causati dalle ritrasmissioni del producer.
3. *Transazioni:* Kafka permette di utilizzare transazioni per rendere atomiche le scritture su più partizioni, degli eventi risultanti dell'elaborazione e il commit degli offset degli eventi consumati.

Tuttuavia, Kafka non garantisce un comportamento exactly-once a causa degli effetti esterni. Ad esempio, se durante l'elaborazione viene effettuato un pagamento tramite un servizio esterno oppure viene modificato un database indipendente, anche queste operazioni devono essere opportunamente coordinate o rese idempotenti.

Una soluzione comunemente adottata è *at-least-once delivery con consumer idempotenti*, che offre un buon compromesso tra affidabilità e complessità.

### Kafka Trade-offs

- **Consistency vs Availability:** Poiché Kafka elegge un nuovo leader solo tra le repliche dell'ISR, se il leader fallisce e non è disponibile alcuna replica in-sync, la partizione diventa indisponibile.
- **Lantecy vs Durability:** Attraverso il paramentro `acks`, il producer può scegliere differenti livelli di durabilità. Una maggore durabilità richiede maggiore coordinamento tra le repliche, introducendo un costo in temini di latenza. Allo stesso modo, aumentare `min.insync.replicas` migliora la durabilità, ma aumenta la probabilità che na scrittura venga rifiutata quando alcuni broker sono indisponibili.

### Broker Coordination: KRaft

I broker di un cluster Kafka devono mantenere una visione consistente dello stato globale del sistema. In particolare, devono conoscere quali broker sono attivi, quali topic e partizioni esistono, quali broker sono leader delle partizioni e la configurazione del cluster. 
Il coordinamento (e la scelta del leader) viene effettuato attraverso un *controller*, supportato da un protocollo di consenso distribuito.

**KRaft**
KRaft è il meccanismo di coordinamento utilizzato delle versioni moderne di Kafka e si basa sull'algoritmo di consenso Raft. I metadati del cluster vengono memorizzati in un log interno replicato, mantenuto consistente da un insieme di controller chiamato *controller quorum*.

Raft viene utilizzato per eleggere il controller attivo e mantenere consistente il log dei metadati.

Prima di Kafka 4.0, Kafka poteva utilizzare *Apache ZooKeeper*, un sistema distribuito esterno per la gestione del coordinamento e dei metadati.

L'utilizzo di ZooKeeper introduceva alcuni svantaggi, tra cui la necessità di gestire un sistema aggiuntivo, limitazioni di scalabilità all'aumentare delle partizioni e tempi di failover del controller superiori.

### API

- **Producer API:** Permmete alle applicazioni client di pubblicare eventi all'interno dei topic Kafka.
- **Consumer API:** Permette alle applicazioni client di leggere ed elaborare gli eventi pubblicati nei topic.
- **Connect API:** Permmete di integrare Kafka con sistemi esterni, come database, file system e servizi Cloud. Si hanno 2 tipologie di connector:
	- *Source Connector:* trasferisce dati da un sistema esterno verso Kafka.
	- *Sink Connector:* trasferisce dati da Kafka verso un sistema esterno.
- **Stream API:** Permette di elaborare flussi di eventi in tempo reale. L'idea è leggere un flusso di eventi, applicare una serie di trasformazione e produrre eventualemtne un nuovo flusso di eventi.
- **Admin API:** permette di amministrare il cluster Kafka e le sue risorse.

## Protocolli di Messaggi

Una problematica riguarda il modo in cui le applicazioni interagiscono con questi sistemi: MOM differenti possono utilizzare API, formati dei messaggi e protocolli di comunicazione differenti. Per risolvere questo problema sono stati introdotti i *protocolli di messaggi*, che definiscono la modalità di interazione con un middleware di messaggistica.

Gli obiettivi principali di questi protocolli sono l'indipendenza dalla piattaforma (_platform-agnostic_), l'indipendenza dal produttore del middleware (_vendor-agnostic_) e l'interoperabilità tra implementazioni differenti.

### MQTT

Message Queuing Telemetry Transport è un protocollo di messaggistica binario e leggero, basato sul patterno Pub/Sub.

Viene ampiamente usato nell IoT in quanto progettato per ambienti con risorse limitati.
Nell'IoT i dispositivi producono continuamente dati, i quali devono essere raccolti ed elaborati da altri componenti del sistema. L'utilizzo di un MOM permette di separare i dispositivi che producono i dati dai servizi che li elaborano, avendo come vantaggi.
- *Decoupling:* i sensori non devono conoscere quali servizi elaboreranno le informazioni prodotte.
- *Resilienza:* Poiché i messaggi sono salvati nel MOM, anche se un servizio diventa indisponibile, i dati rimaranno conservati fino al suo ripristino.
- *Gestione del traffico:* Il MOM permettte di assorbire picchi di traffico.

### AMQP

Advanced Message Queuing Protocol definisce le modalità di scambio dei messaggi tra client e broker.

**Alcune Caratteristiche**
- Application level protocol, binary protocol, TCP come trasporto, supporto per TLS e SASL per autenticazione, meccanismi per garanzie di consegna.

AMQP 1.0 è lo standard che definisce il protocollo di comunicazione e il formato dei messaggi, ma non il modello interno del server.

**Architettura**

Nell'architettura di AMQP si hanno 3 attori principali: producer, consumer e broker.

Un *AMQP Container* è un'entità software che ospita uno o più nodi AMQP. Un container può essere sia un'applicazione client sia un message broker.

Un *Node* è un'entità identificabile attraverso un nome o un indirizzo, in grado di produrre, consumare oppure memorizzare messaggi.

Ad esempio, una coda all'interno del broker rappresenta un nodo.

![[rabbitmq.png]]

I produce e il consumer sono quindi applicazioni che ospitano rispettivamente nodi produttori e consumatori, mentre il broker ospita nodi intermedi, come le code.

AMQP organizza la comunicazione secondo tre livelli di astrazione: 

![[rabbitmqconnections.png| 700]]

- *Connection:* rappresenta la connessione di comunicazione tra due container AMQP, normalmente realizzata attraverso TCP.
- *Session:* rappresenta un canale logico di comunicazione bidirezionale contenuto all'interno di una connection. Una connection può ospitare più sessioni.
- *Link:* rappresenta un canale logico unidirezionale tra due nodi, attraverso il quale vengono trasferiti i messaggi. Una sessione può ospitare più link

**Message Flow**

AMQP introduce diversi tipo di operazioni per gestire il trasferimento dei messaggi.
Con `transfer` il messaggio viene trasferito dal mittente al destinatario. Il consumer controlla la velocità con la quale il sender può trasmettere i messaggi mediante un meccanismo chiamato *link credit*. Una volta ricevuto un messaggio, il receiver può comunicare l'esito della consegna attraverso una `disposition`.

Una consegna si dice *settled* quando una parte considera conclusa la gestione della consegna e non ha più bisogno di conservare lo stato. Nel caso di una comunicazione affidabile, il producer attende di conoscere l'esito della consegna da parte del broker, mentre il consumer conferma il messaggio soltanto dopo aver completato la sua elaborazione.

![[rabbitmqmsgflow.png| 700]]

Se il consumer termina la propria esecuzione prima di confermare il messaggio, il broker può consegnarlo nuovamente a un altro consumer.

**Flow Control: Link Credit**

Il link credit è un meccanismo di flow control attraverso il quale il receiver stabilisce quanti messaggi il sender è autorizzato a trasferire su un determinato link.

L'obiettivo è evitare che il sender produca un flusso di messaggi troppo elevato rispetto alla capacità di elaborazione del receiver. Il funzionamento è il seguento:
1. Il receinver concede al sender un certo numero di crediti.
2. Il sender consuma un credito per ogni nuova consegna effettuata.
3. Quando il credito raggiunge zero, il sender non può iniziare nuove consegne.
4. Il receiver può concedere ulteriori crediti man mano che completa l'elaborazione dei messaggi.

![[linkcredit.png]]

La scelta del numero di crediti influenza sia le prestazioni sia la distribuzioe del carico di lavoro.
- *LC = 1:* favorisce una distribuzione più equa del lavoro tra consumer con velocità di elaborazione differenti.
- *LC > 1:* permette di aumentare il throughput, ma può determinare una distribuzione meno equilibrata del carico.

## RabbitMQ

RabbitMQ è un message broker open-source che implementa funzionalità MOM.

**Caratteristiche:**
- Supporta diversi protocolli di messaggistica: AMQP MQTT e STOMP.
- Adotta un modello di consegna Push, ma supporta anche Pull.
- Garantisce un ordinamento FIFO.
- Cross-platform.
- Language-indipendent.

Rispetto a Kafka, RabbitMQ è maggiormente orientato alla consegna dei messaggi e alla loro distribuzione mediante meccanismi di routing.

### Archietettura

- I producer non pubblicano direttamente i messaggi nelle code. Inviano i messaggi ad un'entità intermedia, detti *exchange*, la quale ha il compito di instradarli verso una o più code.

![[rabbitmqbroker.png]]

- *Exchange:* componente del broker che riceve i messaggi dai producer e determina verso quali code instradarli.
- *Queue:* struttura dati nella quale vengono memorizzati i messaggi in attesa di essere consegnati ai consumer.
- *Binding:* collegamento logico tra un exchange e una queue, attraverso il quale vengono definite le regole di instradamento.
- *Routing Key:* informazione associata al messaggio dal producer, che può essere utilizzata dall'exchange per determinare le code di destinazione.

Introduce quindi un ulteriore livello di *disaccoppiamento:* il producer non deve conoscere le code di destinazione, ma soltanto l'exchange verso cui pubblicare e, quando necessario, la routing key da utilizzare.

**Quorum Queue**

Il broker può inoltre essere distribuito su più nodi, formando un *RabbitMQ Cluster*. Questo però non implica che ogni coda sarà replicata, per fare ciò si usano le *Quorum Queues*.

Una *Quorum Queue* è una tipologia di coda:
- *Durable:* progettata per sopravvivere al riavvio del broker.
- *Replicated:* replicata su più nodi del cluster (usa Raft).
- *Fault-tolerant:* in grado di continuare a funzionare in presenza di guasti, purché rimanga disponibile una maggioranza di repliche.

Per ogni Quorum Queue viene individuato un insieme di repliche, costituito da un leader e da divesi follower. Il *leader* gestisce le operazioni effettuate dai producer e dai consumer, mentre i *follower* mantengono una copia replicata dello stato della coda.

La scrittura avviene nel seguente modo: 
- il leader riceve il messaggio è lo registra nel proprio log. 
- Lo replica presso i follower i quali confermano l'avvenuta memorizzazione.
- Quando una maggioranza (quorum) delle repliche ha memorizzato il messaggio, questo viene cosiderato *commited*.
- A questo punto il publisher riceve la conferma della scrittura.

**Fault tolerance**

Se il leader va incontro a un guasto, le repliche eleggono un nuovo leader mediante Raft, purchè sia presente una maggioranza. Se invece non viene raggiunto un quorum, la coda diventa indisponibile.

![[rabbitmqquorum.png]]

**NOTA** le Quorum Queues privilegiano la *consistenza rispetto alla disponibilità*.

### Delivery Semantics

**At-most-once delivery**

Il broker considera il messaggio consegnato senza attendere una conferma esplicita da parte del consumer. Se il consumer va incontro ad un guasto prima di completare l'elaborazione, il messaggio viene perso. Questa modalità riduce l'overhead della comunicazione, ma non è adatta ad applcazioni nelle quali la perdita di un messaggio è inaccettabile.

**At-least-once delivery**

Il consumer deve inviare un ACK esplicito solamente dopo aver completato con successo l'elaborazione del messaggio. Fino ad allora il broker segna il messaggio come *unacknowledged*.
Se il consumer va incontro ad un guasto e la sua connessione viene chiusa prima dell'invio dell'ACK, il broker può reinserire il messaggio nella coda e consegnarlo nuovamente. Si possono però avere *elaborazioni duplicate*. Per questo motivo è necessario progettare consumer idempotenti.

È importante non confondere due differenti meccanismi di conferma.

| Publisher Confirm   | Consumer ACK                                |                                                   |
| ------------------- | ------------------------------------------- | ------------------------------------------------- |
| Mittente            | Broker                                      | Consumer                                          |
| Destinatario        | Producer                                    | Broker                                            |
| Obiettivo           | Confermare la presa in carico del messaggio | Confermare l'avvenuta elaborazione                |
| Nelle Quorum Queues | Dopo il commit sul quorum                   | Dopo l'elaborazione, se configurato correttamente |
| Protegge da         | Perdita durante la pubblicazione            | Perdita durante il consumo                        |

### Use Cases

1. **Message Queue:** rappresenta il caso più semplice: producer invia dei messaggi a una coda, dalla quale vengono successivamente prelevati da un consumer.
2. **Work Queue:** permette di distribuire un insieme di task tra diversi worker, che competono per ricevere i messaggi da una stessa coda. Questo pattern permette di ottenere *load balancing* e scalabilità orizzontale.
3. **Pub/Sub:** permette di consegnare un messagio a molteplici consumer utilizzando più doce collegate allo stesso exchange (*fanout exchange*).
4. **Message Routing:** il producer pubblica un messaggio presso un exchange, il quale seleziona le code di destinazione sulla base delle binding rules e delle routing keys.
5. **RPC:** permette di implementare chiamate a procedura remota. In questo caso vengono utilizzate una coda per le richieste e una coda per le risposte.

**Esempi**
- [[https://www.rabbitmq.com/tutorials/tutorial-one-go-amqp10 |Message Queue]]
- [[https://www.rabbitmq.com/tutorials/tutorial-two-go.html |Work Queue]]

## Multicast Communication

### Gossip Protocols