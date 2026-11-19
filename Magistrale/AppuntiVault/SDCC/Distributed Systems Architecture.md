
Possiamo descrivere un sistema distribuito in due modi:

1. **Software Architecture:** descrive l'architettura logica, ossia le componenti che costituiscono l'applicazione, quali responsabilità hanno e come interagiscono tra di loro.
2. **System Architecture:** descrive come l'architetuttura software è concretamente realizzata sulle risorse disponibili, includendo il *deployment*.

## Software Architecture

Uno **stile architetturale** è un insieme di scelte progettuali che definsce come organizzare le componenti e le loro interazioni. Definiamo infatti come
- **Componente:** l'unità modulare con un'interfaccia ben definita (es. servizio che gestisce gli ordini);
- **Connettore:** il meccanismo che permette ai componenti di comunicare tra loro (es. chimate HTTP, code di messaggi, etc...).

Un componente può essere sostituito con un'altra implementazione a patto che questa mantenga un'interfaccia compatibile con gli altri componenti.
Lo stile architetturale stabilisce inoltre quali componenti possono interagire, quali dati si scambiano e come sono configurati nel loro insieme.

Ci sono 3 famiglie di stili architetturali: **a livelli**, **orientata ai servizi** e **publish-subscribe**.

### Layered Style

Nello stile *layered*, i componenti sono organizzati a livelli, ognuno con responsabilità specifiche. Nel modello tradizionale un livello superiore usa i servizi di un livello inferiore.
- la richiesta scende a livelli sottostanti;
- il risultato sale al chiamante.

Il vantaggio più grande è la *separazione delle responsabilità*: ogni livello si concentra su un compito ed espone agli altri ciò che serve tramite un'interfaccia.

Esistono varianti dove le chiamate possono essere fatte saltando alcuni livelli, possono esserci chiamte senza risposta immediata (one-way call) e comunicazioni verso l'alto (upcall).

Nelle applicazioni, la suddivisione tradizionale è la seguente:
- **Presentation Layer:** gestisce l'interfaccia utente e la presentazione dei dati.
- **Business Logic Layer:** gestisce la logica di business e le regole dell'applicazione.
- **Persistence Layer:** gestisce l'accesso ai dati conservati.
- **Database Layer:** rappresenta il livello più basso, dove i dati sono effettivamente memorizzati. Permette quindi di memorizzare e interrogare i dati.

Persistence Layer e Database Layer sono distinti perché il primo contiene il codice che accede ai dati, mentre il secondo è proprio il sistema che li conserva.
**NOTA:** questi sono livelli logici, non devono essere eseguiti in macchine diverse! Inoltre in alcune implementazioni alcuni livelli possono essere accorpati.

### Service Oriented Style

L'applicazione è vista come una raccolta di entità separate, *ciscuna delle quali incapsula un servizio*. Ogni entità realizza una funzione ed espone un'interfaccia attraverso cui gli altri componenti possono utilizzarla, nascondendo l'implementazione interna.

Vediamo ora 3 tipologie principali: a Oggetti, a Microservizi e RESTful. Ovviamente queste tipologie possono anche combinarsi.

#### Object Based Style

Ogni componente è un oggetto che contiene dati e offre metodi per operarvi. Ciò permette di applicare i principi della OOP, ossia:
- *Incapsulamento:* i dati sono nascosti e accessibili solo tramite metodi pubblici.
- *Information Hiding:* i dettagli sono nascosti.
- *Riuso:* gli oggetti possono essere riutilizzati in contesti diversi.

In questo senso si cita il riutilizzo di sistemi **legacy**: un componente può essere integrato in un nuovo sistema senza modificarne l'implementazione, purché l'interfaccia sia compatibile.

La comunicazione tra oggetti può avvenire tramite **RPC Remote Procedure Call**: un componente richiede l'esecuzione di una procedura su un altro processo, eventualmente su un'altra macchina. Il meccanismo nasconde parte dei dettagli della comunicazione, ma la chiamata resta soggetta a latenza e possibili errori di rete.

#### Microservices Based Style

L'applicazione viene scomposta in servizi relativamente piccoli, autonomi e dedicati a responsabilità specifiche. Questi comunicano tramite API ben definite.
Con questo stile si vuole che questi servizi siano *loosely coupled*: si cerca di limitare le dipendenze tra i servizi. Questo implica le seguente proprietà fondamentali:
- possibilità di sviluppare e distribuire i servizi separatamente;
- possibilità di aggiornarli senza ridistribuire tutta l'applicazione;
- possibilità di scalare ciascun servizio in base al carico.

Per esempio se consideriamo un e-commerce sviluppato con microservizi, se il numero di ordini cresce si può scegliere di scalare solo il servizio degli ordini, senza toccare il resto dell'applicazione.

Ovviamente l'indipendenza resta limitata, in quanto un servizio dovrà quasi sempre dipendere dalle risposte o dai dati di un altro.
Inoltre è sconsigliato dividere troppo in quanto si rischia di aumentare solo la complessità.

#### RESTful Based Style

*REST (Representational State Transfer)* è uno stile architetturale per sistemi distribuiti dove *i componenti possono operare attraverso un'interfaccia uniforme e stateless*. Negli esempi che vedremo, viene utilizzato *HTTP*.

Una risorsa può essere un utente, una recensione, un documento o un oggetto conservato nel cloud. Le risorse sono identificate tramite *URI (Uniform Resource Identifier)*, mentre un *URL (Uniform Resource Locator)* è un tipo di URI che indica anche come localizzare e accedere alla risorsa.

L’interfaccia uniforme permette di interagire con risorse diverse attraverso operazioni e convenzioni comuni. I messaggi devono fornire informazioni sufficienti per essere interpretati, tramite contenuto e metadati.

Con *stateless* si intende che ogni richiesta deve contenere le informazioni necessarie a comprenderla ed eseguirla, senza che il server debba ricordare il contesto delle precedenti richieste del client. Questo non implica che il server non conserva dati: un server può conservare utenti, ordini e recensioni in un database. Ciò che non deve essere indispensabile è mantenere conversazioni precedenti per interpretare le richieste successive (no sessione).

Ripassiamo le operazioni REST con metodi HTTP:

- **GET**: recupera una risorsa senza modificarla;
- **PUT**: crea o sostituisci lo stato della risorsa all'URI specificato;
- **POST**: crea una nuova risorsa o invia dati al server per elaborazione;
- **DELETE**: rimuove la risorsa all'URI specificato.
### Decoupling

Quando un componente chiama direttamente un altro, possono nascere dipendenze; deve conoscere il suo indirizzo, verificare la disponibilità e infine rimanere bloccato attendendo la risposta.

Queste dipendenze tra componenti definiscono forme di accoppiamento tra componenti (*coupling*). Per ridurle si introduce un *intermediario*, per esempio una coda o un sistema di messaggistica.
In questo modo si ha una separazione tra *computazione* e *coordinazione*.

**Proprietà del Decoupling**:
- *Space Decoupling:* i componenti non devono conoscere l'identità reciproca; I componenti infatti conoscono solo il punto di comunicazione comune (ad esempio una coda di messaggi). Il principale vantaggio risiede nel fatto che un componente può essere sostitui/aggiornato/replicato/spostato senza che gli altri ne conoscano la nuova collocazione.
- *Time Decoupling:* i componenti non devono essere attivi nello stesso momento; L'intermediario però deve essere in grado di conservare il messaggio in modo che il mittente possa inviarlo anche qunado il destinatario è inattivo. Il vantaggio principale è che sia mittente che destinatario possono essere disponibili in momenti diversi.
- *Syncronization Decoupling:* i componenti non devono attendersi reciprocamente, restando bloccati. Infatti mentre aspettano una risposta possono continuare a lavorare su altro task.

**Interazione sincrona e asincrona:**
- *Sincrona:* Il chiamante invoca una procedura bloccante. Rimane in attesa finché non riceve la risposta per poter andare avanti con il task.
- *Asincrona:* La presenza di un intermediario (coda di messaggi o un MOM) permette al mittente di continuare il suo task mentre attende la risposta dal destinatario. Il mittente riceve il messaggio dall'intermediario, elabora il messaggio e invia la risposta al mittente tramite l'intermediario.

I messaggi inoltre possono essere consegnati in 2 modi diversi:
- *Pull:* Il destinatario deve chiedere/prelevare il messaggio dall'intermediario.
- *Push:* L'intermediario invia al destinatario il messaggio.

Il decoupling porta con se un costo, quello dell'intermediario, un'infrastruttura che *introduce elaborazione, trasferimenti, memorizzazione e gestione aggiuntivi portando cosi ad aumentare latenza e costo complessivo*.

Gli stili basati su comunicazione indiretta sono principalmente 3: *Event-Driven*, *Data-Oriented*, *Publish-Subscribe*.

#### Event-Driven

I componenti comunicano attraverso **eventi**, dove un evento rappresenta un cambiamento di stato significativo per l'applicazione.
Per questo stile le componenti comunicano attraverso un *event bus*: alcune componenti *pubblicano gli eventi*, altre si *iscrivono per ricevere quelli di interesse*, e il bus si occupa di inoltrare le notifiche.

La comunicazione è *anonima tra mittente e destinatario, asincrona e multicast*. Questo implica che valgono il *decoupling spaziale, di sincronizzazione*. Per quanto riguarda il *decoupling temporale*, dipende dall'event bus. Se l'event bus è in grado di mantenere gli eventi finché i destinatari non sono pronti allora vale anche il decoupling temporale. Nel modello di base non è previsto che il bus conservi gli eventi, quindi in generale questo stile non offre decoupling temporale.

#### Data-Oriented

In questo stile i componenti comunicano attraverso uno *spazio dati condiviso*. Un componente deposita il dato mentre l'altro lo recupera: non occorre quindi comunicazione diretta tra i due.

Le operazioni principali sono: `write, read, take, readIfExists, takeIfExists`. Poichè `take` rimuove il dato, se più componenti lo leggono, solo una lo otterrà, quindi è necessario gestire la *concorrenza*.

Si parla inoltre di *spazio passivo*, il quale risponde solo alle operazioni dei componenti e *spazio attivo*, il quale può effettuare operazioni di push quando i dati diventano disponibili.

Questo tipo di comunicazione offre *decoupling spaziale* e *temporale*. Al contrario il *decoupling di sincronizzazione* dipende dalle API e dal meccanismo di notifica. Uno spazio passivo può comportare che un mittente resti bloccato in attesa di un dato da parte del destinatario. Invece uno spazio attivo con giusta implementazione delle notifiche può garantire questo decoupling.

#### Publish-Subscribe Stye

Nel modello *pub/sub* esistono due ruoli:

- *Publisher*: colui che produce e pubblica eventi
- *Subscriber*: colui che si iscrive per ricevere eventi di interesse

Uno stesso componente può svolgere entrambi i ruoli. Esiste un *Middleware pub/sub* che mantiene le iscrizioni e gestisce la distribuzione. Questo implica che il publisher non deve individuare tutti i destinatari: pubblica l'evento e affida al middleware la consegna.
Con questo stile si ottengono *tutti i decoupling*: spaziale perché sub e pub non devono conoscersi, temporale perché il middleware può *conservare* gli eventi finché i destinatari non sono pronti, e di sincronizzazione perché il mittente può proseguire senza attendere la risposta del destinatario.

Si noti come logicamente Data-Oriented attivo e pub/sub sono la stessa cosa, la differenza sta nell'implementazione.

Affinchè questo stile funzioni, bisogna definire dei modelli si *subscribe*.
Esistono due modelli principali per far sì che il Middleware decida quali eventi consegnare a ciascun subscriber: *Topic Based* e *Content Based*.

- **Topic Based**: gli eventi appartengono a degli argomenti (topic) e i subscriber si iscrivono a uno o più topic. Il middleware inoltra gli eventi ai subscriber iscritti al topic corrispondente. Questo modello è semplice e veloce, poiché è sufficiente confrontare il topic dell'evento con quelli a cui il subscriber è iscritto per capire se inoltrarglielo. Tuttavia offre anche una selezione relativamente poco espressiva: un subscriber riceverà tutti gli eventi di un topic, anche quelli che non lo interessano.
- **Content Based** invece il subscriber può specificare *filtri più complessi* basati sul contenuto dell'evento (es. `categoria = "elettronica" AND prezzo < 100`). Il middleware deve verificare per ogni subscriber se l'evento soddisfa il filtro prima di inoltrarlo. Questo modello è molto più espressivo *ma rende anche costoso il matching, comportando quindi problemi di scalabilità all'aumentare del numero di subscriber e della complessità dei filtri*.

In pratica quindi il Topic Based è il modello più diffuso in quanto più adatto a sistemi orientati a throughput (i.e. molti eventi al secondo) elevati, come vedremo con Kafka.  
In questo caso quindi *compromesso tra espressività e scalabilità*.

In generale, **non esiste uno stile architetturale migliore per tutte le applicazioni**. La scelta oltre a dipendere dai requisiti specifici dell'applicazione (es. requisiti di performance, di sicurezza, ecc.) dipende anche dai **requisiti non funzionali** come costi, scalabilità ed elasticità, prestazioni, tolleranza ai guasti, manutenibilità, facilità di uso e riuso etc...

Un sistema reale può anche **combinare più stili architetturali assegnandoli alle parti per le quali sono più adatti**.

Ad esempio per la parte di API esposte al client uno stile possibile è il REST, per le elaborazioni che vengono avviate periodicamente in base alla disponibilità dei dati invece uno stile candidato è Event-Driven o Pub/Sub, per la comunicazione interna potrei realizzare le componenti come microservizi facendoli interagire tramite RPC, per l'analisi e raccolta di log invece uno stile Data-Oriented con spazio attivo può essere più adatto.
## System Architecture

Finora abbiamo descritto l'organizzazione logica dei componenti, ora invece andiamo a considerare la loro organizzazione fisica incluso il *deployment*. Vederemo quindi:
- quali componenti eseguire,
- come collegarli correttamente,
- su quali nodi collocarli (per nodo intendiamo una macchina fisica o virtuale).
Nel dettaglio vedremo architetture *centralizzare, decentralizzare, ibride*.
### Client-Server

Nel modello client-server i server offrono i servizi, mentre i client ne richiedono l'utilizzo.

L'approccio tipico è il *request-reply*: il client invia una richiesta al server e attende la risposta, quindi spesso comunicazione sincrona e bloccante (evidente dipendenza del client dal server: se il server non risponde, il client resta bloccato).

Per *centralizzato* non intendiamo una sola macchina "fisica" bensì una singola componente "logica", in questo caso il server, che può ovviamente essere eseguito su più macchine fisiche.

#### Tier vs Layer

- *Layer:* Rappresenta la separazione delle responsabilità a livello di codice e architettura software (livello logico). I moduli sono organizzati in modo che ciascuno svolga un compito ben delimitato: presentation, business logic e persistance.
- *Tier:* Indica la separazione dei processi o delle macchine fisiche/virtuali che eseguono effettivamente quei layer. Un tier corrisponde a un nodo di calcolo autonomo con proprio spazio di memoria, CPU e confine di rete.

**NOTA:** I Layer definiscono _cosa fa_ il software; i Tier definiscono _dove gira_ fisicamente il software. Tre layer logici possono girare tutti su un solo tier, su due tier o su tre o più tier distinti.

Nelle architetture **Two-Tier** (due soli nodi fisici: Client e Server) con **tre layer logici** (Presentation, Business Logic, Persistence), la suddivisione delle responsabilità determina il peso computazionale del client:

1. *Thin Client:* Il client gestisce solo una porzione minimale del _Presentation Layer_ mentre il server centralizza la parte restante della presentazione, l'intero _Business Logic Layer_ e il _Persistence Layer_ (es. terminali SSH).
2. *Standard Client:* Il client gestisce interamente il _Presentation Layer_ e una parte del _Business Logic Layer_ . Il server esegue la logica di business principale e l'intero _Persistence Layer_ (es. app mobile moderna).
3. *Fat Client:* Il client si fa carico per intero sia del _Presentation Layer_ sia del _Business Logic Layer_. Il server funge quasi esclusivamente da nodo dati per il _Persistence Layer_ (es. applicazione gestionale in locale).

L'architettura tradizionle 3-Tier presenta un tier per ogni layer:
1. Client - Presentation Layer
2. Application Server - Business Logic Layer
3. Database Server - Persistence Layer

L'architettura però può aggiungere anche altri componenti come cache, load balancer, servizi intermedi di sicurezza (es. WAF Web Application Firewall) etc.. per cui il numero di tier può crescere a $N$.

#### Distribuzione Verticale e Orizzontale

- Nella distribuzione verticale il sistema viene separato in base alle **funzioni logiche distinte** che compongono l'applicazione. Ogni macchina o gruppo di macchine è specializzato nell'eseguire un compito specifico della catena di elaborazione.
- Nella distribuzione orizzontale uno **stesso livello funzionale** viene replicato o suddiviso su più macchine equivalenti che operano in parallelo.

Le due forme possono anche combinarsi: si separano i layer in macchine diverse, ma ognuno o alcuni di essi vengono replicati!

**NOTA:** *Distribuzione verticale* $\neq$ *Vertical scaling* (quest'ultimo indica l'aumento di risorse su un singolo nodo, es. più CPU o RAM).

#### Esempio 1 : Web App with AWS

![[webaws.webp | 500]]

In figura possiamo osservare una web application su AWS a 3 tier. Questa architettura combina sia la distribuzione orizzontale che verticale, infatti
- *Distribuzione Verticale:* suddivisione chiara in 3 livelli fisici isolati (*Web Tier, Application Tier, Database Tier*).
- *Distribuzione Orizzontale:* scalabilità e ridondanza su due zone di disponibilità distinte (*AZ `us-east-1a`* e *AZ `us-east-1b`*) tramite Load Balancer e gruppi di Auto Scaling.

La distribuzione verticale prevede:
- Web Tier: gestisce la parte web e l'inoltro di richieste applicative. Le componenti mostrate sono istanze EC2.
- App Tier: esegue la logica dell'applicazione, di nuovo istanze EC2.
- Database tier: conserva e interroga i dati relazionali, qui si usa un database Amazon RDS.

Si hanno inoltre anche il Bastion Host (per accedere alle istanze private dall'amministrazione) e il NAT Gateway (per permettere alle istanze private di accedere a internet senza esporle direttamente).

Mentre EC2 fornisce le VM, RDS è un servizio di database gestito. Il servizio è IaaS (Infrastructure as a Service): la figura combina le VM amministrate dal cliente con un servizio che nasconde la complessità di gestione del database.

Il percorso è il seguente: l'utente raggiunge il load balancer pubblico, che sceglie un'istanza del web tier. L'istanza a sua volta comunica con un altro LB, stavolta **interno all'application tier**, che sceglie un'istanza applicativa. L'istanza allora esegue la logica e accede a RDS quando servono i dati. I risultati tornano infine all'utente.

La seguente architettura soddisfa le seguenti proprietà:
- **Elasticità**: si ottiene tramite *autoscaling*, il web tier e l'application tier ne hanno due gruppi distinti. Il numero di istanze può quindi aumentare o diminuire in base al carico.
- **Disponibilità**: si ottiene in questo caso tramite più *AZ Availability Zone*. Se un AZ diventa indisponibile, il traffico viene reindirizzato a quello ancora attivo.
- **Sicurezza** attraverso separazione della rete: nell'architettura mostrata si trova infatti una *VPC* (rete virtuale isolata). Mentre il livello web è ancora collocato in subnet pubblico, i livelli applicativi e database sono in subnet private.

#### Esempio 2: Web App Serverless

![[awslambda.png | 500]]

L'esempio illustra un'architettura **Three-Tier completamente Serverless** su AWS. A differenza dell'architettura precedente basata su macchine virtuali (EC2) e database relazionale (RDS), qui non ci sono server fisici o virtuali da configurare, aggiornare o dimensionare manualmente: l'intera infrastruttura è gestita da servizi cloud completamente gestiti (_managed services_) ed eseguiti su richiesta (_on-demand_).

Quindi per serverless si intende che il cliente non deve gestire server fisici e nemmeno gestire ambienti di esecuzione. Se ne occupa il cloud.

Possiamo dire quindi che un modello serverless si avvicina a un modello *PaaS (Platform as a Service)* e nel caso specifico di Lambda a un modello *FaaS (Function as a Service)*, per cui l'astrazione è portata a una singola funzione invocata.

Qui il Presentation Layer è realizzato con i servizi S3, CloudFront e Cognito. Per la logica applicativa API Gateway e Lambda mentre per i dati un database noSQL DynamoDB.

Cognito gestisce l'autenticazione degli utenti, S3 conserva gli asset statici (HTML, CSS, JS) e CloudFront (che è una CDN) li distribuisce geograficamente per ridurre la latenza. S3 si occupa di conservare i contenuti del sito.

Per la logica applicativa il frontend del cliente chiama anzitutto l'API Gateway, che inoltra la richiesta alla funzione Lambda associata. A quel punto la funzione esegue il codice backend. Le funzioni Lambda possono leggere e scrivere dati su DynamoDB, che è un database NoSQL gestito.

**Domanda:** Per quanto riguarda i gruppi di autoscaling? Non sono espliciti in quanto sono gestiti interamente da Lambda. Si introduce infatti il concetto di *cold start*, ossia quando una funzione non viene invocata per un periodo di tempo, l'ambiente di esecuzione viene rimosso. Alla successiva invocazione, il servizio dele allocare un nuovo ambiente e caricare il codice della funzione, richiedendo quindi più tempo.
### P2P

Nei sistemi P2P le funzionalità del sistema vengono realizzate usando usando *risorse distribuite e condivise dai nodi partecipanti*, chiamati *peer*.
Le risorse possono essere di vario tipo: capacità di calcolo, memoria, file etc...

In una rete P2P le caratteristiche fondamentali sono:
- *Simmetria dei ruoli:* un peer è sia client che server. Possono esistere dei peer con ruoli maggiori detti *super-peer.*
- *Decentralizzazione del controllo:* rispetto ad un sistema centralizzato in cui c'è un nodo che assume il controllo, in una rete P2P il controllo è realizzato con la collaborazione di tutti i peer.
- *Ampia distribuzione:* i peer possono essere molti e geograficamente dispersi.
- *Dinamismo:* i peer possono entrare e uscire dal sistema in qualsiasi momento.

**Terminologia:**
- *Membership:* insieme dei peer che appartengono al sistema in un dato momento.
- *Churn:* il continuo ingresso e uscita dei peer, che modifica la membership.

Poichè la stessa informazione risiede su più peer, si ha il concetto di *ridondanza dei dati*, migliorando cosi la disponibilità e la tolleranza ai guasti.
#### P2P Network Challenges

Le principali sfide dei sistemi P2P sono:

- *Eterogeneità delle risorse:* i peer possono differire di hardware, software, memoria, potenza di calcolo e connessione. Un sistema non può quindi fare assunzioni sulle capacità dei peer, ma deve adattarsi a ciò che offre ciascuno.
- *Scalabilità:* le operazioni devono restare efficienti anche quando aumentano i peer. In questo senso ci concentreremo sul *resource lookup*, i.e. come localizzare una risorsa senza interrogare tutti i nodi.
- *Località e interoperabilità:* una risorsa disponibile non è necessariamente vicina al richiedente. Inoltre due nodi possono essere vicini nella struttura logica del sistema ma molto lontani nella rete sottostante (reti overlay).
- *Tolleranza ai guasti e al churn:* i peer possono entrare e uscire in qualsiasi momento. In particolare se un peer sta eseguendo un'operazione e si disconnette, il sistema deve essere in grado di recuperare e continuare l'operazione senza perdere dati o corromperli.
- *Prestazioni e auto-organizzazione:* in assenza di un controllore centrale, i peer devono organizzarsi per gestire le connessioni, distribuire il carico e instradare le richieste.
- *Free-riding:* un free rider usa le risorse del sistema senza contribuire in misura adeguata (es. scarica file senza condividerli). Occorrono meccanismi di incentivo e fairness.
- *Anonimato:* La decentralizzazione non produce automaticamente anonimato: sono necessari meccanismi specifici.  Un esempio è Tor che sfrutta *onion routing*: il messaggio attraversa più intermediari ed è protetto da strati di cifratura. Ogni intermediario rimuove il proprio strato e ottiene solo le informazioni necessarie per inoltrare il messaggio al successivo nodo. In questo modo il mittente e il destinatario restano anonimi.
- *Fiducia e reputazione*: i nodi non sempre si conoscono; un nodo potrebbe fornire informazioni false o risultati errati. Servono quindi meccanismi per valutare l'affidabilità dei peer, a seconda dell'applicazione.
- *Attacchi Sybil:* nel mondo P2P un nodo può creare più identità false (es. esegue tante VM sulla stessa macchina), ciò potrebbe permettergli di avere un'influenza sproporzionata sul sistema (es. controllare la maggioranza dei nodi in un sistema di voto).
- *DDoS e altri comportamenti malevoli:* per difendersi serve verifica, ridondanza e *rate limiting* (limitare la frequenza delle richieste)

**CASO DI STUDIO:** File sharing all'interno di una rete P2P.
Durante quest processo, nella rete avvengono tre operazioni principali:
1. *Bootstaping:* nu nuovo peer deve scoprire aluni peer della rete per iniziare a partecipare. Ciò può avvenire mediante varie tecniche, attraverso una configurazione statica, una lista di peer conservata da sessioni precedenti, nodi che fornisco informazioni su altri nodi etc...
2. *Resource Lookup:* un peer deve essere in grado di localizzare il file desiderato.
3. *Resource Retrieval:* una volta localizzato il file, il peer deve essere in grado di recuperarlo.

### Overlay Routing

**DEF:** Per *overlay network* intendiamo una rete logica costruita sopra una rete di comunicazione sottostante.

![[overlaynet.png | 500]]

Nella figura si osserva una rete overlay definita sopra una rete di comunicazione fisica. Logicamente due nodi sembrano vicini quando in realtà geograficamente si trovano in continenti diversi.

L'*overlay routing* serve quindi a trovare un percorso all'interno della rete overlay che consenta di localizzare una risorsa.
**NOTA:** Da non confondere con il routing IP, infatti nel routing IP si instradano pacchetti verso un indirizzo di destinazione mentre nel lookup P2P si parte dalla risorsa desiderata e si cerca il peer che può fornirla.

La rete overlay deve inoltre supportare *l'ingresso e l'uscita dei peer, inserimento e rimozione delle risorse, identificazione nodi e risorse.*

**DEF:** Definiamo *GUID (Globally Unique Identifier)* come l'identificatore univoco all'interno del sistema.
$$
\text{GUID(peer)} = \texttt{SHA256(metadata)}
$$
Ovviamente il GUID ci fornisce solo un riferimento utilizzabile dal sistema ma non offre la posizione del peer sul quale è presente la risorsa.

L'organizzazione dei nodi e l'instradamento delle richieste dipende fortemente dalla topologia della rete overlay, infatti:
- **Rete Overlay Non Strutturata:** Non impone nessuna topologia della rete overlay. I collegamenti derivano da decisioni locali e dal comportamento dei peer e la ricerca deve adattarsi a un'organizzazione libera.
- **Rete Overlay Strutturata:** La topologia della rete segue delle regole precise per organizzare i nodi. I collegamenti seguono la strutttura scelta e la ricerca può quindi sfruttare la topologia della rete per essere più efficiente.

#### Unstructured Overlay Network

La rete si forma attraverso decisioni locali dei peer. Quando un nuovo nodo entra nella rete, scopre un sottoinsieme di peer con i quali crea un collegamento diventando suoi vicini. Di conseguenza la topologia complessiva deriva dall'insieme delle scelte dei singoli nodi.

Le risorse inoltre non sono assegnate ai nodi attraverso una regola globale di collocazione. Un peer potrebbe semplicemente scelgliere di mettere a disposizione una risorsa (es. file).

**Vantaggi:**
- Semplicità nella modifica della topologia. I peer possono decidere se entrare o uscire dalla rete, aggiungere o rimuovere risorse e adattarsi al *churn*.
- La manutenzione è contenuta in quanto non bisogna ricostruire una topologia rigida.
**Svantaggi:**
- Il lookup di un risorsa può essere costoso richiedendo molti scambi di messaggi.

Analizziamo ora 3 alternative per il routing all'interno delle reti overlay non strutturate. Le informazioni riguardanti i peer si trovano all'inteno di una struttura detta *indice (directory)*.
1. *Centralizzato*. L'indice si trova in uno o pochi *directory server*. Ogni peer comunica al directory server quali risorse mette a disposizione. Quando peer cerca una risorsa chiede al directory server,  che risponde con la lista dei peer che contengono quella risorsa specifica. A questo punto il richiedente sceglie uno dei peer e preleva la risorsa. Si combina in questo modo il *lookup centralizzato* con *trasferimento dati tra peer*. Il principale vantaggio di questo metodo è la semplicità in quanto ogni peer sa a chi chidere per ottenere la risorsa mentre i principali svantaggi sono:
	- Single Point of Failure, in quanto sistema centralizzato;
	- Limiti di scalabilità: il server che gestisce il lookup può diventare un collo di bottiglia;
	- Costo di gestione: necessità di un'entità che gestisca il server.
2. *Ibrdo con super-peer.* Esiste un sottoinsieme di peer (super-peer) con il compito di localizzare le risorse per conto di altri peer.
3. *Decentralizzato.* Non esiste un directory globale a cui fare rivolgersi. Ogni nodo non può mantenere una copia dell'indice di conseguenza l'unico modo per localizzare la risorsa è mediante lo scambio di messaggi tra peer.

Esistono tre 3 meccanismi principali per il lookup decentralizzato: *query flooding, random walk, gossiping*.

##### Query Flooding

Con questo metodo la query viene diffusa in broadcast. Ogni peer che la riceve verifica se possiede la risorsa. In caso affermativo inoltra la risorsa al richiedente altrimenti inoltra la query a tutti i suoi vicini escuso il sender.

Per limitare il numero di messaggi "query" diffusi nella rete si aggiunge un TTL (`time to live`), un contatore che ad ogni hop decrementa di uno finché non arriva a 0 e il messaggio non viene più propagato. Inoltre per evitare cicli, il messaggio contiene anche un GUID in modo tale che ogni peer mantiene una lista di query ricevute. Se riceve una query già ricevuto la scarta.

Costo: $O(N)$ dove $N$ è il numero di peer all'interno della rete overlay.

Una volta trovato il peer con la risorsa, questa deve essere inoltrata al richiedente, che può avvenire in due modi.
1. *Direct Routing:* Il peer che possiede la risorsa la manda direttamente al peer che la richiesta. Per fare ciò ovviamente deve disporre di IP e porta.
2. *Backward Routing:* Il peer che possiede la risorsa la inoltra indietro al peer da cui ha ricevuto la query, che a sua volta la inoltra al peer da cui ha ricevuto la query fino ad arrivare al richiedente. Per fare ciò ogni nodo devere ricordare il GUID del peer da cui ha ricevuto la query. I vantaggi di questo metodo sono:
	- *Privacy:* il peer che risponde non conosce l'identità del peer che ha richiesto la risorsa;
	- *Caching delle risposte:* ogni peer può memorizzare `il nodo X possiede la risorsa Y`. Ovviamente questo caching non è *autoritativo* in quanto il peer X potrebbe aver eliminato la risorsa Y.

Nel caso in cui un nodo del percorso esce dalla rete il protocollo deve prevedere delle alternative come scegliere un altro percorso disponibile, sfruttare altri vicini a cui è arrivata la query etc... .

Tra i **limiti del flooding**:
- *Overhead di comunicazione*: molti messaggi raggiungono nodi che non possiedono la risorsa;
- *Scelta del TTL*;
- *Falsi negativi*: la ricerca può non trovare nulla anche se la risorsa esiste, perché il TTL era troppo basso;
- *Rischi di sicurezza e congestione*: una richiesta viene amplificata dalla propagazione di conseguenza query malevole possono sovraccaricare la rete;
- *Nodi black hole*: nodi che ricevono messaggi ma non li inoltrano (perché sovraccarichi, guasti o malevoli) possono interrompere alcuni rami di ricerca;
- *Topology mismatch*: Un singolo hop dell’overlay può corrispondere a un trasferimento fisico lungo e costoso. Pochi hop logici non garantiscono quindi bassa latenza.
##### Random Walk

Con la **Random Walk** invece si riduce la ramificazione della ricerca.  
Stavolta il nodo iniziale sceglie un solo vicino `u.a.r.` e gli invia la query. Se il vicino non possiede la risorsa allora a sua volta e così via. Anche qui serve una condizione di arresto come un TTL per evitare ricerca indefinita.

Il vantaggio principale è *minore overhead dei messaggi*: ogni passaggio genera un solo inoltro.  
Lo svantaggio è che il percorso potrebbe essere "poco favorevole": può impiegare più tempo a raggiungere la risorsa o esaurire il limite senza trovarla.

Per ottimizzare ciò allora *k-Random Walk*: l'origine avvia percorsi casuali in parallelo ed ogni copia a sua volta sceglie vicini casuali a cui inoltrare la query (o a un solo vicino a seconda della variante). Più è grande più ci avviciniamo al query flooding in termini di complessità di messaggi.

#### Structured Overlay Network

Si impone una topologia rigida della rete, ad esempio anello, albero, ipercubo, mesh etc... In questo modo si può risolvere il problema del lookup in maniera più efficiente.

L'idea è che ogni peer mantiene informazioni su un sottoinsieme specifico degli altri peer, scelto secondo le regole della topologia.
Sfruttando quindi la topologia della rete, il lookup diventa più effciente ma il costo da pagare sta nella manutenzione della rete. Quando un peer esce/entra è necessario modificare i collegamenti in modo da mantenere la topologia della rete.

Nelle reti overlay strutturate, l'accesso efficiente alle risorse è implementato tramite una **Distributed Hash Table (DHT)**, un archivio distribuito chiave-valore in cui sia i peer che i dati condividono il medesimo spazio numerico tramite identificatori univoci (**GUID**) calcolati con funzioni di hash crittografiche. La responsabilità di memorizzare una risorsa ricade sul nodo il cui identificatore risulta matematicamente più vicino al GUID del dato secondo una metrica formale definita dal protocollo. Per garantire la scalabilità del sistema, ciascun peer mantiene una visibilità parziale della rete memorizzando nella propria tabella di routing solo $O(\log N)$ vicini; la procedura di lookup non ricorre a flooding casuali, ma instrada deterministamente la query passo-passo verso il nodo a minor distanza residua dal target, convergendo al peer responsabile in un numero limitato di salti.

#### Distributed Hash Table

Una *Distributed Hash Table (DHT)* è un'astrazione distribuita della classica tabella hash che organizza logicamente le associazioni chiave-valore ($K \rightarrow V$), ripartendone la responsabilità di memorizzazione e recupero tra i diversi nodi (peer) della rete overlay.

- *Tabella hash tradizionale:* data una chiave $K$, una funzione di hash individua direttamente il bucket di memoria locale in cui risiede il valore $V$, garantendo operazioni con costo asintotico medio $O(1)$.
- *DHT:* la coppia $(K, V)$ viene affidata a uno specifico peer responsabile all'interno dell'overlay. Il calcolo dell'hash determina _quale nodo_ è deputato a conservarla, ma non garantisce l'accesso immediato: è necessario *attraversare la rete* attraverso una procedura di routing hop-by-hop. Di conseguenza, il lookup di una DHT non è banalmente $O(1)$, ma richiede in media $O(\log N)$ salti di rete a seconda della topologia.

Le DHT espongono le tre primitive canoniche di un archivio chiave-valore:
- $\text{put}(K, V)$: memorizza l'associazione $(K, V)$ presso il peer competente.
- $\text{get}(K)$: localizza e interroga il peer responsabile per estrarre il valore associato a $K$.
- $\text{remove}(K)$: elimina l'associazione relativa a $K$ dal nodo che la ospita.

All'interno dell'architettura considerata:
- $\texttt{key}(K)$: è il *GUID* ottenuto applicando la funzione di hash crittografica alla risorsa.
- $\texttt{value}(V)$ rappresenta la risorsa stessa oppure un puntatore/riferimento (es. indirizzo IP del nodo sorgente) che indica da dove scaricarla.

La complessità di una DHT deriva dalla necessità di soddisfare contemporaneamente quattro requisiti fondamentali:
1. **Decentralizzazione:** assenza di nodi speciali o coordinatori centrali con visione globale dello stato della rete; ogni decisione di routing si basa esclusivamente sulla topologia logica e su informazioni locali.
2. **Scalabilità:** contenimento dell'overhead di comunicazione e della dimensione delle tabelle di instradamento (al più $O(\log N)$ contatti mantenuti) anche al crescere indefinito dei peer.
3. **Efficienza:** risoluzione delle interrogazioni di ricerca minimizzando la latenza e il numero di hop necessari per convergere al target.
4. **Tolleranza al Churn (Dinamicità):** capacità del sistema di mantenere corretta la topologia e garantire la disponibilità dei dati a fronte di ingressi continui, partenze e disconnessioni improvvise (guasti) dei nodi. 

Poichè i peer sono responsabili di porzioni della tabelle, se un nodo esce, le chiavi di cui era responsabile devono essere riassegnate ad altri peer, mentre se un nodo entra deve ricevere parte di responsabilità per bilanciare il carico. Occorre fare tutto ciò senza che le associazioni della tabella siano continuamente riorganizzate per ogni nuovo ingresso/uscita.
Inoltre bisogna avere repliche e meccanismi di recupero, affinché le associazioni di cui è a conoscenza un peer non vadano perse se il peer si disconnette o si guasta.

Ci sono tre problemi da affrontare durante la progettazione di una DHT:
1. *Evitare concentrazioni di chiavi:* il numero di chiavi gestite dai peer deve essere uguale/simile per tutti. Non ci devono essere peer che gestiscono molte piu chiavi degli altri. Essi possono diventare degli *hotspot*, ossia possono diventare un collo di bottiglia o point of failure. La funzione Hash deve distribuire le chiavi in maniera uniforme tra i peer.
2. *Evitare rimappatura completa.* Vedremo il Consistent Hashing per ciò.
3. *Supportare ricerche per chiave esatta:* Data una chiave, la riceva deve essere esatta e non flessibile.

##### CHORD

Il primo protocollo per progettare una DHT è Chord.
L'architettura di Chrod organizza l'intero spazio degli indirizzi come un *anello logico monodirezionale*.
- I peer e le chiavi ricevono un GUID di $m$ bit, generato tramite hash crittografico (generalmente SHA-1, quindi $m = 160$).
- Lo spazio degli identificatori ha dimensione $2^m$ ed è ordinato in 1 senso crescente: i valori vanno da $0$ a $2^m - 1$ per poi richiudersi ciclicamente su 0 tramite aritmetica modulare $\pmod{2^m}$.
- L'ordinamente segue il senso orario lungo un anello.

**Proprietà:**
- *Efficienza del Lookup:* La risoluzione di una chiave richiede al più $O(\log N)$ messaggi di instradamento, dove $N$ rappresenta il numero di peer.
- *Stato di Routing Limitato:* Ogni peer memorizza riferimenti verso un insieme ristretto di altri nodi ($O(\log N)$ voci nella cosiddetta _finger table_), selezionati secondo intervalli geometrici crescenti sull'anello.
- *Scalabilità:* Al crescere di $N$, il costo computazionale, il consumo di memoria per nodo e il traffico di messaggi aumentano in modo logaritmico, rendendo Chord idoneo a reti di grandissime dimensioni.
- *Robustezza e Gestione del Churn:* Include protocolli periodici di stabilizzazione e liste di successori (_successor lists_) per gestire partenze impreviste, guasti e ingressi simultanei di nodi senza frammentare l'anello logico né perdere l'accesso alle chiavi.

**Regola di Assegnazione:** Una risorsa con chiave $k$ viene assegnata al *primo peer* incontrato in senso orario a partire da $k$, includendo il peer con GUID uguale a $k$, se presente.
Quindi, dato $k$, $\texttt{succ}(k)$ è il peer responsabile di $k$.

Dato un peer $p$, esso gestisce l'insieme di chiavi *successive al predecessore e fino al proprio ID incluso*.
$$
\texttt{keys}_{peer} = (\texttt{pred}(p), p]
$$
La distanza definita pe Chord è la distanza lineare sull'anello: date due chaivi $x$ e $y$, allora la distanza procedendo in senso crescente è:
$$
d(x,y) = y - x \pmod{2^m}
$$
Equivalentemente:
$$
d(x,y) = 
\begin{cases}
y - x &\iff y \geq x \\
2^m + y - x &\iff y < x
\end{cases}
$$

###### Esempio

In figura un esempio di Chord con $m = 4$, dove i pallini pieni rappresentano i peer mentre gli altri le risorse.

![[chord.png]]

In Chord, per organizzare l'assegnazione delle chiavi in modo da limitare i cambiamenti in caso di ingresso/uscita dei peer si utilizza il *Consistent Hashing*. Questo permette che:
- peer e risorse vengono mappati nello stesso spazio di identificatori tramite la stessa funzione hash, spazio che rappresenta un anello logico;
- ogni nodo gestisce un insieme contiguo di chiavi;
- una modifica dei nodi cambia solo alcune assegnazioni.

Con il Consistent Hashing, l'ingresso (uscita) di un peer richiede che solo le chiavi di sua responsabilità vengano rimappate dal suo successore (al suo successore). Tutte le altre chiavi restano assegnate agli stessi peer (*rimappatura limitata*).

Inoltre, se si usa una buona funzione hash, allora è possibile dimostrare che in media il carico sarà approssimativamente bilanciato tra i peer, evitando così che pochi peer gestiscano gran parte delle risorse.

**Lookup:** partendo da un peer qualsiasi, come troviamo quello resposabile della chiave $k$? Possiamo pensare a 2 soluzioni banali:
- Ogni peer conosce il suo successivo. Quando arriva una query, questa avanza per tutto l'anello fino a trovare la risorsa, costo $O(N)$.
- Ogni peer conosce tutti gli altri peer. Data una query, questa verrà indirizzata direttamente al peer che è responsabile della risorsa. Costo di ricerca $O(1)$ mentre costo di memoria $O(N)$.

Chord adotta un compromesso tra queste due idee, una *conoscenza parziale, ma organizzata*. Ogni peer mantiene una *finger table*.
La *finger table* è la tabella di routing di un peer; contiene i riferimenti solo ad alcuni peer, scelti in modo da permettere dalti di ampiezza crescete lungo l'anello (in pratica ogni peer conosce in modo dettagliato i suoi vicini e in modo più rarefatto i peer più lontani).

Ogni peer mantiene quindi una finger table di $m$ righe, costruita nel seguente modo:
$$
\texttt{FT}_{p}[i] = \texttt{succ}(p + 2^{i-1}) \pmod{2^m}, \quad 1 \leq i \leq m
$$
In questo modo ogni nodo conosce $O(\log (N))$ peer.

###### Esempio 

Con $m=3$, la *finger table* del nodo $0$ è:

![[fingertable.png | 500]]

$$
\texttt{FT}_{0}[1] = 1, \quad \texttt{FT}_{0}[2] = 2, \quad \texttt{FT}_{0}[3] = 4
$$

**Algoritmo di Routing:**
Sia $p$ il peer a cui è arrivata la query per la chiave $k$, allora:
1. Se $k \in (\texttt{pred}(p), p]$ allora restuisci $p$.
2. Se $k \in (p, \texttt{succ}(p)]$ allora restituisci $\texttt{succ}(p)$.
3. Altrimenti, $p$ sceglie *il peer più distante* $p'$ *in senso orario che precede strettamente* $k$. La query viene quindi inoltrata a $p'$, il quale ripeterà la procedura ricorsivamente.

Si può facilmente dimostrare che il costo è $\log (N)$.

**Manutenzione Topologia ad Anello**
Per semplificare la manutenzione, ogni peer, oltre a mantenere un riferimento al proprio successore, ne mantiene uno anche al proprio predecessore.

###### Ingresso di un peer
1. *Determina il proprio ID* applicando la funzione hash.
2. *Contatta un peer già esistente* per avviare i looup necessari per inserirsi nell'anello.
3. *Chiede al peer contattato di trovare il suo successore*.
4. Ottiene l'informazione del proprio predecessore dal suo successore e salva i riferimenti.
5. Costruisce la propria finger table: trova i successori delle posizioni $p + 2^i \pmod{2^m}$ per $i = 0, \dots m - 1$ tramite lookup.
6. Riceve infine le chiavi di cui sarà responsabile dal suo successore.

![[nodejoin.png]]

Il nodo 7 entra nella rete. Il suo successore è 9 mentre il predecessore di 9 diventa 7. Il successore di 4 diventa 7. Infine il nodo 9 traferisce le chiave 5 e 6 al nodo 7.

Per quanto rigarda le finger table degli altri peer, l'idea è di utilizzare operazioni periodiche di manutenzione in cui tutte le finger table vengono aggiornate insieme. Questo significa che ci possono essere delle finger table con riferimenti non più valabili.

###### Uscita di un peer (volontaria)

- Il peer deve trasferire al proprio successore le chiavi di cui è responsabile.
- Deve fare aggiornare il riferimento al predecessore del proprio successore.
- Deve fare aggiornare il riferimento al successore del proprio predecessore.

In totale, il costo di manutenzione è $\log^2 (N)$ il che dimostra che nelle reti P2P struttrare la manutenzione della topologia è costosa rispetto a quella nelle reti non strutturare.

Nel caso in cui *un peer si guasta e non notifica la propria uscita* si devono risolvere due problemi:
- riparare le informazioni sull'anello; Per fare ciò si usano le operazioni di manutenzione periodiche menzionate sopra controllando se i peer sono ancora disponibili. Questo avviene tramite meccanismi di *timeout* o *heartbeat*.
- rendere ancora disponibili le informazioni del peer guasto. Per risolvere questo probleme si procede con la *replicazione dei dati*, di modo che se un peer si guasta le chiavi di cui era responsabile non vengano perse. In particolare si replicano le coppie $(k,v). Con $r$ copie totali, una è posta sul peer responabile mentre le altre $r-1$ sui peer successivi.

Questa gestione dei guasti implica che un peer deve conoscere più di un successore. Si parla quindi di *successor list*, la lista dei peer che lo seguono immediatamente sull'anello.
Ovviamente questo viene con un costo in termini di memoria, comunicazione e lavoro di sincronizzazione delle copie.

###### Inserimento, aggiornamento e rimozione di una risorsa

Non è detto che essere *responsabile di una risorsa* significhi che il peer la debba per forza possedere fisicamente, ma anche averne un riferimendo ad essa.

Per inserire una risorsa, prima si determina la sua chiave $k$ con la funzione hash, si esegue il lookup per ottenere il suo responsabile e infine si memorizza presso quel peer la coppia $(k,v)$ dove $v$ o è la risorsa stessa o un suo riferimento.

Per aggiornare o rimuovere l'associazione relativa a una risorsa, si contatta il peer responsabile della sua chiave.  
In tutto ciò, se ci sono copie replicate, queste devono esser gestite coerentemente con l'operazione effettuata.

###### Vantaggi e limiti di Chord

| **Categoria** | **Aspetto**                                       | **Dettagli**                                                                                                                                                |
| ------------- | ------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Vantaggi**  | **Lookup**                                        | Costo di $O(\log N)$ messaggi, scalando in base al numero di peer effet                                                                                     |
|               | **Conoscenza Parziale Organizzata**               | Le tabelle di routing locali ($O(\log N)$ vicini) bastano per instradare le query.                                                                          |
|               | **Load Balancing**                                | L'impiego del consistent hashing distribuisce in modo uniforme sia i nodi che le chiavi lungo l'anello logico.                                              |
|               | **Robustezza e Tolleranza al Churn**              | Mantiene la disponibilità e la connettività di fronte a guasti e ingressi/uscite continui di nodi tramite routine di stabilizzazione e liste di successori. |
| **Limiti**    | **Disallineamento Topologico**                    | La prossimità logica sull'anello non rispecchia la vicinanza fisica nella rete IP sottostante, aumentando la latenza reale.                                 |
|               | **Supporto Esclusivo a Query Esatte**             | Non supporta ricerche complesse, a intervalli (_range queries_), per parole chiave parziali o attributi delle risorse.                                      |
|               | **Complessità di Manutenzione e Stabilizzazione** | La gestione dei puntatori durante frequenti partenze e fallimenti simultanei è critica;                                                                     |
##### KADEMLIA

Vediamo ora un altro protocollo per la progettazione di una DHT nelle reti P2P.

Come in Chord, anche in Kademlia il lookup ha costo $\log (N)$ ed utilizza identificatori ad $m = 160$ bit, calcolati con SHA-1.

La differenza principale rispetto a Chord è la *metrica di distanza.* Kademlia la distanza tra due chiavi $x$ e $y$ è definita come:
$$
d(x, y) = x \oplus y
$$
ossia si applica lo XOR bit a bit tra i due identificatori e si interpreta il risultato come un intero non negativo.
Ad esempio
$$
d(1010, 1100) = 1010 \oplus 1100 = 0110 = 6
$$
Si usa lo XOR perché:
- *veloce da calcolare*;
- *simmetrica:* $d(x, y)  = d(y,x)$.

Un'altra differenza rispetto a Chord è la toplogia dell'overlay. In questo caso la rete è organizzata come un *albero binario*.

L'intero spazio degli identificatori a $m$ bit può essere modellato come un albero binario completo di profondità $m$, dove la radice rappresenta l'universo delle chiavi $[0, 2^m - 1]$, ogni diramazione a sinistra codifica il bit `0` e ogni diramazione a destra il bit `1`. In questa struttura ogni cammino dalla radice a una foglia, letto dal bit più significativo a quello meno significativo, individua in modo univoco il GUID di un peer o di una risorsa.

Dato che nessun nodo può mantenere in memoria l'intero albero da $2^m$ elementi, ciascun peer $p$ organizza la propria tabella di routing decomponendo lo spazio in al più $m$ liste a capienza limitata dette $k$-bucket, dove $k$ (fissato convenzionalmente a 20) rappresenta la dimensione massima di contatti ospitabili per intervallo. Dal punto di vista del peer $p$, la riga $j$-esima della tabella ($j \in [0, m-1]$) raggruppa tutti i nodi che condividono con $p$ un prefisso comune di esattamente $j$ bit iniziali e differiscono tassativamente al bit immediatamente successivo, lasciando del tutto liberi i restanti $m - 1 - j$ bit. In virtù della metrica XOR, questa condizione implica che i nodi del bucket $j$ si trovino a una distanza numerica compresa nell'intervallo $[2^{m-1-j}, 2^{m-j}-1]$, garantendo che all'aumentare dell'indice $j$ la distanza residua da $p$ si dimezzi progressivamente.

Per visualizzare chiaramente il meccanismo, si consideri uno spazio ridotto a $m = 3$ bit con $k = 2$ e un peer di riferimento $p = 010_2$. La sua tabella conterrà tre bucket: il bucket $j = 0$ raccoglie i nodi con $0$ bit iniziali in comune, ovvero quelli che iniziano per `1` (`100`, `101`, `110`, `111`) posti a distanza XOR $[4, 7]$; il bucket $j = 1$ contiene i nodi con $1$ bit in comune che differiscono sul secondo, ossia della forma `00x` (`000` e `001`) a distanza $[2, 3]$; infine, il bucket $j = 2$ include l'unico nodo con 2 bit in comune che differisce solo sul terzo, cioè `011`, posto a distanza unitaria. In questo modo il peer memorizza una campionatura densa dei nodi a lui estremamente vicini e mantiene riferimenti essenziali ma rari per le porzioni più distanti dello spazio.

Il lookup adotta una strategia **iterativa e parallela**, governata da due parametri fondamentali di sistema:

- **$k$ (dimensione del bucket):** Tipicamente pari a 20. È il numero massimo di contatti restituiti da una richiesta o memorizzati in una riga della tabella.
- **$\alpha$ (grado di concorrenza):** Tipicamente pari a 3. Rappresenta il numero di nodi interrogati simultaneamente in parallelo per evitare che un peer lento o non responsivo blocchi la ricerca

1. **Inizializzazione:** Il nodo sorgente $p$ calcola la distanza XOR tra i nodi presenti nella propria tabella di routing e la chiave bersaglio $n$ ($d(x, n) = x \oplus n$). Seleziona gli **$\alpha$ nodi più vicini** a $k$ che conosce e li inserisce in una lista ordinata di candidati (a cui invierà le query).
2. **Interrogazione Asincrona Parallela:** Il nodo $p$ invia in contemporanea una richiesta `FIND_NODE(n)` (o `FIND_VALUE(n)`) a questi $\alpha$ nodi. A differenza di Chord, la query non viene inoltrata a cascata: il nodo ricevente risponde direttamente a $p$.
3. **Elaborazione delle Risposte:** Ciascun nodo interpellato verifica la propria tabella e restituisce a $p$ i **$k$ nodi più vicini a $n$** di cui è a conoscenza (oppure restituisce il payload/file se si tratta di `FIND_VALUE` e lo possiede).
4. **Aggiornamento e Convergenza:** Ricevuti i nuovi indirizzi, $p$ aggiorna la propria lista dei candidati ordinandoli per distanza XOR da $n$. Se tra i nuovi nodi ricevuti ce ne sono di più vicini a $n$ rispetto a quelli precedentemente contattati, $p$ reitera inviando query parallele ai nodi appena scoperti.
5. **Terminazione:** La procedura iterativa si arresta quando tutti i $k$ nodi complessivamente più vicini a $n$ sono stati interrogati senza trovare peer ulteriormente più vicini. A quel punto, $p$ ha isolato il set dei $k$ peer più prossimi alla chiave e memorizza/recupera il dato presso di essi.

Costo: $\log (N)$.
[Kademlia Visual](https://kelseyc18.github.io/kademlia_vis/basics/1/)

#### IPFS

IPFS (InterPlanetary File System) rappresenta un sistema P2P distribuito per memorizzare, individuare e recuperare contenuti su larga scala. La rivoluzione in IPFS sta nel meccanismo per identificare le risorse: invece di basarsi su un indirizzo di posizione in un dato server, se segue un ID basato sul contenuto stesso.

Al contrario del web classico dove la risorsa è identificata da un URL che indica in quale server si trova (URL che può cambiare nel tempo), IPFS utilizza invece un identificatore derivato dal contenuto per cui la richiesta diventa qualcosa del tipo *dato il contenuto identificato da questo ID, quali peer possono fornirmelo*. Non è quindi necessario che il contenuto sia sempre presso lo stesso server.

Per "basato sul contenuto" intendiamo che la risorsa è identificata da un *impronta crittografica*.

In IPFS un file può essere suddiviso in piccoli blocchi detti *chunk*. Ogni blocco è identificato attraverso un *CID (Content Identifier)*, che rappresenta l'hash crittografico del suo contenuto. Se il contenuto cambia anche il CID cambia.
I blocchi sono collegati tra loro tramite riferimenti basati sui loro CID formando un *Merkle DAG*.

Questa struttura a DAG porta i seguenti benefici:
- *Verifica dell'integrità:* quando si riceve un blocco, si può ricalcolare l'hash e confrontarlo con quello atteso nel suo identificatore. In questo modo si può verificare se il blocco è stato corrotto o modificato.
- *Confronto efficiente tra versioni:* per confrontare due strutture non è necessario trasferire tutti i dati ma semplicemente partire dagli ID delle radici.
- *Deduplicazione dei dati:* se due file contengono lo stesso blocco, possono riferirsi allo stesso blocco identificato dal suo CID. Ciò permette di mantenere una sola copia del blocco evitando copie inutili.
- *Download indipendente e in parallelo:* i blocchi possono essere recuperati separatamente, anche da peer diversi e in parallelo.

IPFS usa una variante di Kademlia, adattata alle proprie esigenze, con bucket e lookup paralleli e asincroni.  
Attenzione ovviamente che **la DHT serve a trovare chi possiede il contenuto, ma non a trasferirlo**: per questo vengono utilizzati **provider record**, ossia informazioni che associano un CID ai peer che effettivamente lo possiedono.  
Quindi in generale il peer che viene trovato tramite lookup nella DHT può essere diverso da quello che conserva effettivamente il blocco (es. il peer A conserva il blocco, la DHT arriva a scoprire che A è provider del blocco, quindi sta al richiedente contattarlo separatamente per la fase di retrieval).

Il funzionamento può essere distinto in tre momenti:

1. **Pubblicazione**: un peer dispone del contenuto e annuncia nella DHT di poterlo fornire, l'annuncio rende possibile trovare il provider (non direttamente il contenuto, come detto)
2. **Ricerca del provider**: un altro peer conosce il CID desiderato ed esegue un lookup per scoprire quali peer possono fornirlo. Il risultato è un elenco di peer che hanno annunciato di possedere il contenuto.
3. **Trasferimento**: il richiedente contatta i provider e recupera i blocchi tramite un protocollo retrieval P2P come Bitswap, eventualmente in parallelo.  Dopo averli ricevuti, ne verifica l'integrità calcolando l'hash e confrontandolo con il CID atteso e infine li ricompone secondo la struttura del Merkle DAG per ottenere il file originale.

In tutto ciò due scenari possibili:
- **Rete pubblica**: i peer partecipano ad una rete condivisa, usata per annunciare e cercare contenuti.
- **Rete privata**: IPFS viene usato in un ambiente ristretto, ad es. tra macchine di un'organizzazione. Come al solito è possibile progettare soluzioni ibride

| **Ambito**   | **Caratteristica**            | **Sintesi**                                                                                                                               |
| ------------ | ----------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
| **Vantaggi** | **Decentralizzazione**        | Contenuti distribuiti da molteplici peer, senza dipendenza da server centrali.                                                            |
|              | **Integrità e Versioning**    | I CID garantiscono l'esatta corrispondenza e identificazione univoca del dato.                                                            |
|              | **Efficienza**                | Minori tempi e traffico grazie a caching, riuso dei blocchi e download parallelo.                                                         |
|              | **Anti-censura**              | Architettura distribuita priva di singoli punti di controllo o blocco.                                                                    |
|              | **Accesso LAN**               | Recupero diretto dei dati in rete locale senza transito su Internet.                                                                      |
| **Limiti**   | **Persistenza Non Garantita** | Nessuna conservazione permanente automatica: i dati svaniscono se nessun peer li mantiene attivi (_pinning_).                             |
|              | **Complessità Dati Dinamici** | Ogni modifica muta i CID a cascata, aumentando l'onere di tracciamento delle versioni.                                                    |
|              | **Solo _Exact Match_**        | Ricerca vincolata a corrispondenza esatta dell'hash via DHT; query per filtri, intervalli o parole chiave richiedono indicizzatori terzi. |

### Archietture Ibride

Le architetture ibride di sistemi distribuiti combinano caratteristiche delle architetture centralizzate e decentralizzate. L'obiettivo è sfruttare i vantaggi dei entrmabi i modelli, cercando contemporaneamente di limitarne i svantaggi.

Gli esempi più comuni sono:
- *Super-peer Networks:* alcuni nodi con capacità superiori assumono responsabilità aggiuntive rispetto ai peer ordinari.
- *BitTorrent:* nella modalità basata su tracker, la scoperta dei peer è centralizzata, mentre il trasferimento dei dati è decentralizzato.
- *Blockchain:* l'infrastruttura principale è decentralizzata, ma può essere affiacata da componenti centralizzati o semi-centralizzati.

#### Super-peer Networks

È una rete P2P in cui alcuni nodi, chimati *super-peer*, possiedono maggiori capacità computazionali o di rete e svolgono funzioni aggiuntive per conto dei peer ordinari. Si possono occupare di:
- *Routing:* instradare le richieste verso i nodi appropriati;
- *Indexing:* mantenere informazioni sulle risorse disponibili presso i peer ordinari, facilitandone la ricerca.

L'obiettivo principale è *migliorare le prestazioni della ricerca delle risorse (lookup) mantenendo un certo grado di decentralizzazione*.

La progettazione di una rete super-peer introduce due problemi fondamentali:
1. *Associazione tra peer e super-peer:* L'associazione può essere statica (peer si collega a super-peer prestabilito) o dinamica (il peer può cambiare super-peer). 
2. *Selezione super-peer:* bisogna definire i criteri per cui un peer normale diventi super-peer. Alcuni criteri si basano sulla velocità di banda, sulla disponibilità e la latenza.

#### BitTorrent

È un protocollo P2P utilizzato per la condivisione e il trasferimento di file tra nodi di una rete distribuita.

La caratteristica principale è che un file non deve necessariamente scaricato da un unico server: può essere suddiviso in parti, chiamate *pieces/chunks*, e scaritato in parallelo da più peer.

La scoperta dei peer può avvenire in due modalità:
- *Tracked based:* un server centralizzato (tracker) mantiene informazioni sui peer che partecipano alla condivisione di un file.
- *Trackerless:* I peer vengono individuati attraverso una DHT basatu su Kademlia.

Il funzionamento *Tracked based* è il seguente (rappresenta un'achitettura ibrida):
1. Il client ottiene il `.torrent` che contiene tutti i *metadati necessari per avviare il download*.
2. A questo punto il client utilizza i metadati per contattare il tracker, il quale restituirà al client la lista dei peer disponibili.
3. A questo punto può iniziare il download dei vari chunk dall'*swarm*.

Infine, si hanno due strategie per migliorare l'efficienza e incentivare la cooperazione tra peer.
1. *Rarest Piece First:* consiste nel dare priorità al download dei chunk meno diffusi all'interno dello swarm.
2. *Tit-for-Tat:* l'idea è assegnare la banda di upload tenendo in conto di quanti dati vengono ricevuti dagli altri peer. In questo modo un peer che contribuisce attivamente alla distribuzione dei dati tende a essere favorito rispetto a uno che si limita a scaricare.

#### Blockchain

È una tecnologia che permette di mantenere un registro condiviso di transazioni (*ledger*) replicato tra più nodi di una rete distribuita.

Il problema fondamentale affrontato dalla blockchain riguarda la possibilità di validare e memorizzare transazioni senza affidarsi necessariamente a un'autorità centrale.

- *Validazione:* una transazione risulta legittima se è validata da tutti i nodi all'interno della rete. Una transazione è valida se non è un *double-spending*.
- *Memorizzazione:* le transazioni vengono memorizzate per consentire verifiche successive e altre operazioni.

L'utilizzo delle blockchain non è limitato alle sole crypto, ma anche alla gestione delle identità, tracciamento delle risorse, voto elettronico etc...

La Blockchain è una particolare tipologia di DLT (Distributed Ledger Technology), ossia una tecnologia per la gestione di registri distribuiti in cui i dati vengono condivisi, replicati e sincronizzati trà più partecipanti senza la partecipazione di un coordinatore centrale.

In una blockchain, i peer mantengono una replica locale del registro delle transazioni, secondo le modalità previste dal sistema.

I nodi possono non fidarsi reciprocamente (_untrusted peers_) e alcuni possono essere guasti o malevoli. Per questo motivo, la blockchain utilizza meccanismi crittografici e protocolli di consenso per mantenere una visione coerente del registro tra i peer.

Le transazioni vengono raggruppate in **blocchi (blocks)**, organizzati in una catena append-only.
Ogni blocco è costituito da due componenti principali:
- *Header:* contiene i metadati del blocco, tra cui un riferimento crittografico al blocco precedente.
- *Body:* contiene le transazioni raggruppate nel blocco.

Uno degli aspetti fondamentali della blockchain è stabilire *quale validatore sia autorizzato ad aggiungere il prossimo blocco alla catena*.
Questa decisione viene gestita attraverso un meccanismo di _consenso_.

- *Soluzione centralizzata:* Una singola entità fidata determina quale validatore può aggiungere il prossimo blocco. Questo approccio è semplice da gestire, ma introduce un'autorità centrale e un possibile _single point of failure_.
- *Consenso distribuito: Permissioned Blockchain:* Nelle *permissioned blockchain*, il consenso viene raggiunto da un gruppo relativamente ristretto di server, generalmente preselezionati o autorizzati. Affinchè si possa arrivare ad un consenso deve valere che $$f \leq \left\lfloor \frac{n-1}{3}\right\rfloor$$dove $f$ sono i nodi corrotti e $n$ i nodi totali.
- *Consenso decentralizzato: Permissionless Blockchain:* Nelle **permissionless blockchain**, la partecipazione alla rete non richiede un'autorizzazione preventiva da parte di un'autorità centrale. I meccanismi più usati sono: *Proof-of-Work* utilzzata da Bitcoin e *Proof-of-Stake* utilizzata da Ethereum dove i preponenti dei blocchi sono selezionati in base alla quantità di crypto vincolata come stake.