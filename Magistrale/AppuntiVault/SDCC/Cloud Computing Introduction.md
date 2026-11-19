**DEF:** Il *Cloud Computing* è un paradigma di elaborazione che permette di accdere, attraverso la rete, a risorse computazionali e servizi forniti da infrastrutture remote.
- *Cloud:* rappresenta simbolicamente la rete Internet;
- *Computing:* comprende attività di elaborazione (computation), memorizzazione dei dati (storage) e coordinamento (coordination).

L'idea fondamentale è il passaggio da un modello di elaborazione basato su un singolo server o data center a un modello in cui le risorse e i servizi sono accessibili attraverso Internet, permettendo alle applicazioni di sfruttare risorse distribuite, anziché dipendere esclusivamente da una sola macchina.

Per capire meglio il concetto, possiamo considerare un'applicazione che offre un determinato servizio di streaming.
1. *Soluzione Classica:* Server Multithread, i thread gestiscono in contemporaneamente le richieste degli utenti. Viene quindi sfruttato il *parallelismo multicore*. Una soluzione di questo tipo è molto complessa in quanto è necessario gestire la concorrenza e presenta molti limiti (es. scalabilità limitata).
2. *Soluzione Cloud-native:* Inceve di utilizzare un unico server multithread, viene realizzato un server single-threaded, istanziato separatamente per ogni utente ed eseguito all'interno di un *container*. Poichè ogni istanza gestisce un unico utente, riduce la complessità della concorrenza, se un'istanza dell'applicazione si arresta, gli altri container continuano l'esecuzione normalmente. Infine questa soluzione è molto scalabile in quanto basta aumentare i numero di istanze.

Per quanto riguarda la *scalabilità*, esistono due strategie:
- *Scale Up:* aumenta le risorse disponibili su una singola macchina.
- *Scale Out:* aumenta la capacità complessiva distribuendo il lavoro tra più istanze o istanze.

![[cloudscaling.png]]

**Problema Principale del Cloud Computing: Large-Scale Systems:** Le applicazioni devono essere in grado di:
- *Gestire milioni di richieste al secondo,* garantendo tempi di risposta adeguati anche in presenza di un elevato numero di utenti.
- *Gestire foti variazioni del carico di lavoro*;
- *Memorizzare enormi quantità di dati,* anche dell'ordine degli exabyte: $1 \text{ EB } = 10^{18} \text{ byte}$.

Oltre al problema della disponibilità delle risorse, il sistema deve essere in grado di *gestirle e adattarle dinamicamente alle esigenze del sistema*.

**DEF:** Per *scalability* intendiamo la capacità di un sistema di gestire un carico di lavoro crescente attraverso un opportunno aumento delle risorse disponibili.

### Paradigmi pre-Cloud Computing

1. **Utility Computing:** L'idea nasce già negli anni 60', quando alcuni ricercatori avevano immaginato un futuro in cui le risorse sarebbero state accessibili attraverso una rete. In questo modello le risorse computazionali vengono fornite come servizi di cui l'utente ne può usufruire pagando in funzione del loro utilizzo.
2. **Grid Computing:** Paradigma del calcolo distribuito che permette di condividere e coordinaer risorse computazionali appartenenti a sistemi differenti, spesso distribuiti geograficamente e amministrati da organizzazioni diverse.
3. **Autonomic Computing:** Paradigma che mira alla realizzazione di sistemi informatici capaci di *gestirsi automaticamente*, riducendo la necessità di intervento umano.
4. **Software as a Service (SaaS):** Modello di distribuzione del software in cui le applicazioni vengono rese disponibili agli utenti attraverso Internet. 

Il 2006 viene considerato l'anno della nascita del cloud computing. In quell'anno, *Amazon* iniziò a commercializzare risorse computazionali e di memorizzazione come servizi accessibili attraverso Internet. L'idea di base consisteva nello sfruttare le risorse infrastrutturali disponibili per offrirle a clienti esterni, permettnedo loro di *noleggiare capacità computazionale e spazio di archiviazione*.

Vengono quindi introdotti due servizi fondamentali:
- *Amazon EC2:* Servizio che permette di ottenere capacità computazionale attraverso istanze di VM, configurabili in base alle esigenze dell'utente.
- *Amazon S3:* Servizio che permette di memorizzare e recuperare dati (drive).

|Paradigma|Caratteristica distintiva|
|---|---|
|Distributed Computing|Cooperazione tra sistemi autonomi e generalmente eterogenei|
|Cluster Computing|Nodi strettamente accoppiati, percepiti come un unico sistema|
|Grid Computing|Condivisione di risorse tra organizzazioni e domini amministrativi differenti|
|Cloud Computing|Risorse e servizi forniti on demand, con garanzie di servizio|

È importante osservare che questi paradigmi non sono necessariamente alternativi o mutuamente esclusivi.

### Definizioni

Nel corso degli anni sono state proposte diverse definizioni di Cloud Computing, ciascuna delle quali pone l'attenzione su aspetti differenti del paradigma.

**DEF (Ambrust):** Il Cloud Computing comprende sia le applicazioni distribuite come servizi attraverso Internet, sia i sistemi hardware che software presenti nei data center che permettono di erogare tali servizi. Le caratteristiche fondamentali sono: *Illusione di risorse computazionali infinite, eliminazione degli investimenti iniziali, pagamento in base all'utilizzo*.

**DEF (NIST):** Il NIST definisce il Cloud Computing come un modello che permette l'accesso, attraverso la rete, a un insieme condiviso di risorse computazionali configurabili (reti, server, storage, applicazioni e servizi).
La caratteristica principale è che queste risorse possono essere allocate e rilasciate rapidamente su richiesta, con un intervento gestionale minimo senza l'interazione diretta con il fornitore.

**DEF (Vaquero):** Il Cloud Computing consise in un ampio insieme di risorse virtualizzate, facilmente accessibili e utilizzabili. Il modello prevede generalmente un pagamento basato sull'utilizzo (definito tramite *SLA*).

### Caratteristiche

1. *On-demand self-service:* capacità dell'utente di richiedere e ottenere autonomamente risorse computazionali, senza dover interagire direttamente con Cloud Provider. Questo meccanismo permette di ridurre i tempi necessari per ottenere nuove risorse e rende più flessibile la gestione dell'infrastruttura.
2. *Broad network access:* indica che le risorse Cloud sono accessibili attraverso la rete, utilizzando meccanismi standard. I servizi Cloud espongono quindi *interfacce pubblicate*, sotto forma di API.
3. *Elasticity:* capacità di aumentare o diminuire rapidamente le risorse computazionali disponibili in funzione delle variazioni del carico di lavoro (scale out/scale in).
4. *Resource pooling:* consiste nel raggruppamento delle risorse computazionali del Cloud Provider all'interno di un insieme condiviso, dal quale vengono allocate le risorse necessarie ai diversi utenti. Questo modello è strettamente legato al concetto di *multi-lenancy*, ossia la possibilità di servire più utenti, o *tenant*, utilizzando la stessa infrastruttura hardware.
5. *Resource virtualization:* meccanismo attraverso cui le risorse fisiche vengono astratte e presentare agli utenti sotto forma di risorse virtuali (potenza di calcolo, memoria, storage, banda di rete).
6. *Pay-per-use:* modello economico in cui il costo del servizio dipende dall'utilizzo delle risorse Cloud. Questo approccio permette di evitare grandi investimenti inziali per l'acquisto di hardware. Il vantaggio principale consiste nel poter sostenere costi proporzionati alle risorse consumate, anziché dover acquistare anticipatamente un'infrastruttura dimensionata per il carico massimo previsto.
7. *Measured service:* indica che il Cloud Provider misura l'utilizza delle risorse attraverso specifiche metriche. Queste misurazioni permettono di determinare il consumo delle risorse e, quando previsto dal modello tariffario, calcolare il costo da addebitare all'utente.

**NOTA:** La scalability indica la capacità di un sistema di sostenere un carico crescente aumentando le risorse, mentre l'elasticity pone l'attenzione sulla rapidità e sulla capacità di adattare le risorse alle variazioni del carico, anche quando questo diminuisce.

## Modelli di Deployment

I modelli di deployment descrivono le modalità con cui un'infrastruttura Cloud viene distribuita, resa disponibile e gestita.
In particolare, permettono di distinguere le infrastrutture in base a:
- *Accessibilità:* chi può utilizzare le risorse Cloud.
- *Proprietà e gestione:* chi possiede e ammnistra l'infrastruttura.
- *Localizzazione:* dove si trovano fisicamente le risorse.
- *Costi e isolamento:* quali vantaggio e limitazioni derivano dal modello adottato.

### 1. Public Cloud

Rappresenta un modello di deployment in cui l'infrastruttura Cloud viene resa disponibile per l'utilizzo da parte del pubblico. Le risorse sono fornite da un Cloud Provider, che si occupa della gestione e del funzionamento dell'infrastruttura.

**Caratteristiche Principali:**
- *Infrastruttura:* disponibile per l'utilizzo pubblico, generalmente secondo un modello *multi-tenant*, in cui più clienti condividono la stessa infrastruttura fisica.
- *Proprietà e gestione:* l'infrastruttura può essere posseduta, gestita e amministrata da un'organizzazione privata, accademica, governativa o da una loro combinazione.
- *Localizzazione:* le risorse fisiche si trovano presso le strutture del Cloud Provider.
- *Costi:* i servizi possono essere gratuiti oppure a pagamento.

*Esempio:* Amazon Web Services.

### 2. Private Cloud

Chiamato anche *Enterprise Cloud*, è un modello di deployment in cui l'infrastruttura Cloud viene destinata all'utilizzo esclusivo di una singola organizzazione.
Il modello adottato a livello di organizzazione è *single-tenant*. Questo non significa che l'infrastruttura venga utilizzata da un solo utente: una stessa organizzazione può infatti comprendere più unità aziendali o gruppi di utenti che condividono le risorse.

**Caratteristiche Principali:**
- *Infrastruttura:* riservata esclusivamente a una singola organizzazione.
- *Proprietà e gestione:* può essere posseduta, amministrata e gestita dall'organizzazione stessa, da una terza parte oppure da una combinazione delle due.
- *Localizzazione:* può trovarsi sia presso le strutture dell'organizzazione (on-premises) oppure presso strutturne estene (off-premises).

I principali vantaggi sono: *maggiore sicurezza* e *maggiore personalizzazione* mentre i svantaggi sono: *maggiori costi* e *scalabilità più complessa*.

### 3. Hybrid Cloud

Modello di deployment che combina due o più infrastrutture Cloud distine, generalmente Public Cloud e Private Cloud.

Le infrastrutture che compongono un Hybrid Cloud:
1. Mantengono la propria identità e autonomia.
2. Sono collegate attraverso tecnologie strandardizzate o proprietarie.
3. Permettono, in una certa misura, la portabilità dei dati e delle applicazioni tra gli ambienti.

Ad esempio, un'organizzazione potrebbe utilizzare un Private Cloud per memorizzare dati sensibili e un Public Cloud per eseguire applicazioni che richiedono una capacità computazionale variabile.

**Vantaggi:**
- *Bilanciamento tra utilizzo delle risorse e costi:* la combinazione tra public e private cloud permette di distribuire i carichi di lavoro.
- *Riduzione del Vendor Lock-in:* riduce il rischio di forte dipendenza da un determinato fornitore di servizi, permettendo di distribuire applicazioni e dati tra infrastrutture differenti.
- *Maggiore flessibilità:* permette di differenziare la distribuzione delle applicazioni e dei dati in base a esigenze specifiche (privacy, disponibilità, prestazioni).

**NOTA:** ll Cloud Bursting è una tecnica utilizzata nei sistemi Hybrid Cloud per gestire dinamicamente gli aumenti del carico di lavoro.

Il principio consiste nell'utilizzare il Public Cloud per ottenere capacità computazionale aggiuntiva quando le risorse del Private Cloud non sono più sufficienti. 

1. Carico ordinario: le richieste vengono gestite dall'infrastruttura privata.
2. Picco di carico: il Private Cloud raggiunge la propria capacità massima.
3. Cloud Bursting: il carico eccedente viene trasferito al Public Cloud, che mette a disposizione risorse aggiuntive.

![[cloudbursting.svg | 700]]
**Svantaggi:**
- *Complessità operativa*;
- *Sicurezza:* l'utilizzo di più infrastrutture può aumentare la *superficie di attacco*.
- *Prestazioni:* la comunicazione tra infrastrutture Cloud differenti può introdurre ritardi aggiuntivi.
- *Troubleshooting:* Individuare problemi può diventare difficile quando un'applicazione dipende da componenti distribuiti.
- *Costi aggiuntivi:* l'integrazione di più infrastrutture può richidere investimenti maggiori.

## Modelli di servizio

I *Cloud Service Models* descrivono le diverse modalità con cui un Cloud Provider mette a disposizione risorse e servizi agli utenti.

A differenza dei *Deployment Models*, che definiscono come viene distribuita e gestita un'infrastruttura Cloud, i *Service Models* stabiliscono quali risorse vengono offerte come servizio e quali componenti rimangono sotto il controllo del cliente.

### Infrastructure as a Service (IaaS)

IaaS è un modello in cui il Cloud Provider mette a disposizione risorse infratrutturali virtualizzate come servizi (computazionali, storage, network). L'utente può richidere queste risorse per installare ed eseguire software arbitrario, inclusi sistemi operativi e sistemi.

Nel modello IaaS, il cliente *non ha il controllo dell'infrastruttura Cloud fisica sottostante*, che rimane sotto la responsabilità del provider. Il cliente invece mantiene il controllo su: sistema operativo delle VM, storage e dati, applicazioni installate e alcune componenti di reti (regole firewall).

Il modello IaaS offre quindi un elevato grado di flessibilità, poiché permette all'utente di configurare il proprio ambiente software senza dover acquistare o amministrare direttamente i server fisici.

#### Esempio IaaS: Amazon EC2

EC2 è un servizio IaaS di AWS che permette di creare e utilizzare istanze di VM. L'utente può configurare una VM scegliendo il OS, le risorse computazionali e alcune impostazioni di rete e sicurezza.

### Platform as a Service (PaaS)

PaaS è un modello di servizio in cui il Cloud Provider mette a disposizione una piattaforma per lo sviluppo, la distribuzione e l'esecuzione di applicazioni. A differenza di IaaS, il cliente non deve occuparsi direttamente della gestione dell'infrastruttura e dell'ambiente di esecuzione sottostante.
La piattaforma fornisce infatti un insieme di strumenti e servizi che permettono di *sviluppare, compilare, distribuire, testare ed eseguire applicazioni*.

Nel modello PaaS, il cliente non controlla direttamente l'infrastruttura di rete, i server fisici o virtuali sottostanti, sistemi operativi o storage. Il cliente mantiene invece il controllo sulle *applicazioni distribuite*. 
Il principale vantaggio del PaaS consiste quindi nel permettere agli sviluppatori di concentrarsi sulla logica applicativa, delegando al Cloud Provider la gestione di gran parte dell'infrastruttura.

#### Esempi
1. *Piattaforme per Web Apps:* AWS Elastic Beanstalk, Google App Engine, Azure App Engine;
2. *Piattaforme per applicazioni containerizzate:* AWS Elastic Container Storage, Google Kubernetes Engine, Azure Kubernetes Service.
3. *Serverless Computing \& Function as a Service (FaaS):* Il cliente distribuisce funzioni applicative che vengono eseguite attraverso un'infrastruttura gestita dal provider (AWS Lambda).

#### AWS Elastic Beanstalk

Permette di distribuire e gestire applicazioni senza dover configurare manualmente gran parte dell'infrastruttura necessaria alla loro esecuzione. Supporta applicazioni sviluppate in diversi linguaggi (Go, Java, .NET etc...).

Il funzionamento generale è il seguente:
1. Lo sviluppatore realizza l'applicazione utilizzando uno dei linguaggi supportati.
2. Carica il pacchetto dell'applicazione su Elastic Beanstalk, fornendo alcune informazioni di configurazione.
3. Elastic Beanstalk crea automaticamente l'ambiente necessario all'esecuzione dell'applicazione.
4. Il servizio configura e gestisce le risorse AWS richieste.

In particolare, Elastic Beanstalk può automatizzare:
- *Capacity provisioning:* allocazione delle risorse computazionali.
- *Load balancing:* distribuzione delle richieste tra più istanze.
- *Scaling:* aumento o diminuzione delle risorse in funzione del carico.
- *Health monitoring:* monitoraggio dello stato delle applicazioni.

### Software as a Service (SaaS)

In questo modello il Cloud Provider rende disponibili applicazioni software complete attraverso Internet. L'accesso a tali applicazioni può avvenire tramite interfacce Web oppure API.

Il cliente non ha il controllo dell'infrastruttura Cloud sottostante, inclusi: rete e server, sistemi operativo, storage e funzionalità interne dell'applicazione.

L'utente può generalmente modificare soltanto alcune impostazioni applicative specifiche, come preferenze personali o configurazioni del proprio account.

![[cloudservizi.png]]

Oltre ai tre modelli principali, il Cloud Computing comprende numerosi altri modelli di servizio, generalmente raggruppati sotto il termine Anything as a Service (XaaS).

- Database as a Service (DBaaS): fornitura di database come servizi gestiti.
- Function as a Service (FaaS): esecuzione di funzioni applicative attraverso un'infrastruttura gestita dal provider.
- Monitoring as a Service (MaaS): fornitura di strumenti e servizi per il monitoraggio delle infrastrutture e delle applicazioni.
- Generative AI as a Service (GenAIaaS): accesso a funzionalità e modelli di intelligenza artificiale generativa attraverso servizi Cloud.

## Cloud Pricing, Capacity Planning \& Elasticity

- *Cloud Pricing Models:* i modelli economici attraverso cui i Cloud Provider mettono a disposizione le risorse.
- *Capacity Planning:* il processo di dimensionamento delle risorse necessarie per eseguire un'applicazione.
- *Elasticity:* la capacità di adattare automaticamente le risorse alle variazioni del carico di lavoro.

### Cloud Pricing Models

I Cloud Provider offrono diversi *pricing models*, che si distinguono principalmente per modalità di pagamento, flessibilità e garanzie sulla disponibilità delle risorse.

1. *Pay-per-use / On-demand:* prevede che l'utente paghi in funzione delle risorse Cloud utilizzate. Il principale vantaggio è la *flessibilità* in quanto l'utente può richiedere risorse quando necessario senza dover pianificare anticipatamente un impegno di lungo periodo. Si adatta particolarmente nei casi di: *trafficono non prevedibile, elastic scaling, sviluppo e testing*.
2. *Fixed / Reserved:* prevede un impegno economico prestabilito per l'utilizzo delle risorse Cloud, ad esempio l'utente paga un importo fisso mensile per le risorse riservate. Il principale vantaggio è la possibilità di ottenere *sconti significativi rispetto al modello On-demand*. Questo modello è particolarmente adatto a carichi di lavoro prevedibili e relativamente stabili nel temp.
3. *Dedicated:* prevede l'assegnazione di risorse fisiche dedicate esclusivamente a un determinato cliente. A differenza di un modello basato sulla condivisione delle risorse fisiche, l'utente ottiene hardware dedicato, come un intero server fisico. Il principale vantaggio ovviamente è il massimo isolamento a livello hardware fisico rispetto ad altri clienti, ovviamente a costi molto elevati.
4. *Spot:* permette di utilizzare risorse Cloud a un prezzo variabile spesso molto accesibile. Lo svantaggio fondamentale è che *le risorse Spot possono essere interrotte dal Cloud Provider in qualsiasi momento, spesso con qualche minuto di anticipo.* È adatto a carichi di lavoro capaci di tollerare l'interruzione delle risorse.

### Capacity Planning

**DEF:** Processo attraverso cui si determina il corretto dimensionamento delle risorse informatiche necessarie per eseguire un'applicazione. Le risorse considerate comprendono: Computing, Storage, Memory \& Network.

L'obiettivo è individuare una configurazione capace di sostenere il carico di lavoro previsto, evitando un utilizzo inefficiente delle risorse.

Lo *static provisioning* consiste nell'allocare anticipatamente una quantità prestabilita di risorse, che rimane sostanzialmente fissa durante l'esecuzione dell'applicazione. Questa situazione può portare a:
- *Over-provisioning:* quando le risorse allocate sono superiori a quelle effettivamente necessarie.
- *Under-provisioning:* quando le risorse allocate sono insuffiencienti per sostenere il carico di lavoro.

Il problema dello Static Provisioning è quindi che una capacità fissa difficilmente riesce a seguire un carico di lavoro variabile, causando sprechi oppure carenze di risorse.

Inoltre, definire a priopri il numero di risorse necessarie non è una buna pratica, in quanto si possono verificare:
- *Workload demands:* le richieste necessarie possono variare in modo difficile da prevedere;
- *Dynamic resource performance:* le prestazioni delle risorse possono variare nel tempo.

Si hanno quindi 2 soluzioni:
- *Soluzione Classica: Manual Scaling:* Si stimano il numero di richieste e le risorse necessarie, si modificano manualmente aumentando o diminuendo le risors ein funzione della necessità. Questo approccio è tuttavia poco pratica nei sistemi di grandi dimensioni per via dei lunghi tempi di intervento, la probabilità di errore umana è molto grande e infine può risultare in una soluzione inefficiente in termini di risorse allocate.
- *Soluzione Moderna: Elastic Scaling:* L'auto-scaling è il meccanismo attraverso cui le risorse vengono adattate automaticamente alle variazioni del carico di lavoro.

### Elasiticità

Abbiamo visto quindi che la soluzione migliore nel scalare le risorse all'interno di una sistema è tramite l'autoscaling. Questo meccanismo deriva dalla definizione di *elasticità*:

**DEF:** L'elasticità rappresenta il grado con cui un sistema computazionale riesce ad adattarsi alle variazioni del carico di lavoro, allocando e rilasciando risorse in maniera autonoma, affinché la capacità disponibile corrisponda il più possibile alla domanda corrente.

Da questa definizione si hanno:
- *Adattamento automatico:* le risorse devono variare in funzione del workload;
- *Gestione autonoma:* l'allcazione e il rilascio delle risorse devono avvenire automaticamente;
- *Corrispondenza tra capacità e domanda:* il sistema deve cercare di mantenere la quantità di risorse allocate il più possibile vicina a quella effettivamente necessaria.

I sistemi che *self-adaptive* sono quelli capaci di modificare autonomamente la propria configurazione e il proprio comportamento in risposta ai cambiamenti dell'ambiente operativo.
Nel contesto del Cloud Computing, questo significa poter adattare dinamicamente il numero o la dimnesione delle risorse utilizzate.
Il sistema monitora il carico, decide se modificare le risorse ed esegue le operazioni di scaling necessarie.

Infine, l'elasticità può essere valutata confrontando nel tempo due grandezze:
- *Demand:* quantità di risorse richiesta dal workload;
- *Provisioned capacity:* quantità di risorse allocate dal sistema.
Idealmente, le due grandezze dovrebbero coicidere in ogni istante. Si hanno due metriche:
- *Accuracy:* misura quanto la capacità allocata si discosta dalla domanda effettiva. È data dalla somma $O + U$ dove $O$ è l'area di over-privisioning, nella quale le risorse allocate superano quelle richieste ed $U$ è quella di under-provisioning, nella quale le risorse allocate sono inferiori a quelle richieste. Tale somma rappresenta lo scostamento complessivo tra capacità e domanda nel periodi di osservazioni. Minore è questo scostamento, maggiore è l'accuracy con cui il sistema esegue il workload.
- *Timing:* misura per quanto tempo il sistema rimane in condizioni di over-provisioning o under-provisioning.

## Load Balancing \& Auto-scaling

Per realizzare un sistema elastico non è sufficiente aggiungere o rimuovere istanze dell'applicazione: è necessario anche *distribuire correttamente le richieste tra le istanze disponibili*.

### Load Balancing

Il Load Balancing è una tecnica che permette di distribuire le richieste dei client tra più repliche di un server, con l'obiettivo di bilanciare il carico di lavoro.
Un'appliczione può essere eseguita contemporaneamente su diverse istanze, chiamate *server replicas*. Il LB è il componente responsabile di selezionare la replica alla quale inoltrare ciascuna richiesta.

Il LB dispone di un *Virtual IP*, ovvero di un indirizzo IP virtuale utilizzato come punto di ingresso al servizo. I client inviano le proprie richiste verso il VIP, senza dover conoscere direttamente gli indirizzi IP delle singole repliche.

- *Network LB:* opera al livello di trasporto del modello OSI.
- *Application LB:* opera al livello applicativo.
- *One-way e Two-way LB:* Nel primo caso il LB riceve la richiesta e la inoltra al server selezionta, ma la risposta viene inviata direttamente dal server al client mentre nel secondo caso sia la richiesta che la risposta attraversano il LB.
- *Hardware e Software LB:* il LB è implementato attraverso del hardware dedicato oppure tramite applicazioni che eseguono le funzioni di bilanciamento.
- *Centralized \& Distributed LB:* nel prima coso è realizzato mediante un componente logico centrale mentre nel secondo caso più componenti cooperano per svolgere le funzioni di bilanciamento.

Inoltre, un elemento fondamentale del LB è il monitoraggio dello stato delle repliche. Questo avviene tramite gli *Health Checks*, ossia dei controlli periodici per verificare lo stato dei server. Qunado un server non risponde a questi controlli significa che non è funzionante e di conseguenza viene escluso dalla distribuzione delle nuove richieste.

Gli obiettivi principali del LB sono:
- *Maximaze Resource Utilization:* massimizzare l'utilizzo delle risorse disponibili;
- *Minimize Response Time:* minimizzare il tempo necessario per rispondere alle richieste dei client;
- *Maximize Throughput:* massimizzare il numero di richieste completate dal sistema nell'unità di tempo.

Le *Load Balancing Policies* sono gli algoritmi utilizzati dal LB per decidere a quale replica assegnare ciascuna richiesta.
- *Stateless Policies:* non richiedono informazioni sullo stato corrente dei server per scegliere la replica.
	- *Random:* Ogni richiesta viene assegnata a un server selezionato casualmente tra quelli disponibili.
	- *Round Robin:* Le richieste vengono assegnate ciclicamente alle repliche disponibil.
- *Server-aware Policies:* prendono in considerazione informazioni relative ai server per effettuare l'assegnazione.
	- *Least Loaded:* ogni nuova richiesta viene assegnata al server che presenta il carico minore.
	- *Weighted Round Robin:* una variante del RR nella quale viene associato a ogni server un peso proporzionale alla sua capacità.
	- *Power of Two Choices:* Per ogni richiesta vengono selezionati casualmente due server. La richiesta viene quindi assegnata al server meno carico tra i due.
- *Client-aware Policies:* utilizzano informazioni relative ai client per decidere a quale server assegnare le richieste.
	- *Hashing:* il server viene selezionato applicando una funzione hash a un'informazione associata al client.
- *Client \& Server-aware Policies:* combinano informazioni relative al client con informazioni sullo stato dei server.

## Service Level Agreements (SLA)

È necessario stabilire quali prestazioni il Cloud Provider si impegna a fornire, come queste vengono misurate e cosa accade quando gli impegni non vengono rispettati.

### Service Level Agreement (SLA)

È un accordo formale, generalmente contrattuale, tra un *Service Provider* e un *Service Consumer*. L'accordo definisce le condizioni relative alla qualità del servizio che il provider si impegna a rispettare. Un SLA è composto da uno o più SLO, cioè condizioni che devono essere soddisfatte da specifiche metrice del servizio.
Un SLO potrebbe richiedere che il tempo medio di risposta sia inferiore o uguale a un secondo $$\bar{T}_{\text{response}} \leq 1 \text{ s}$$
Un SLA cmprende inoltre penalità e/o compensazioni nel caso in cui il provider non rispetti gli obiettivi concordati.

### Service Level Indicator (SLI)

È una metrica misurabile utilizzata per descrivere una determinata porprietà proprietà del servizio (*Availability, Response Time, Throughput*).
### Service Level Objective (SLO)

È una condizione definita su un insieme di SLI. un SLO può consistere, ad esempio, in una soglia applicata a una singola metrica.

Esistono diversi problemi associati agli SLA offerti dai Cloud Provider:
- *Complessità terminologica*
- *Limiti della metrica Availability*
- *Mancanza di SLI relativi di Response Time*
- *Scarsa negoziobilità*

### Cloud Monitoring

È l'insieme delle attività e degli strumenti utilizzati per monitorare e valutare lo stato di salute dei sistemi e dei servizi Cloud.

L'obiettivo è individuare: problemi di prestazioni, interruzioni del servizio e inefficienze nell'utilizzo delle risorse. Per fare ciò si definiscono due tipologie di metriche:
- *System-oriented Metrics:* descrivono lo stato e l'utilizzo delle risorse infrastrutturali (CPU/Disk utilization, memory used etc...). 
- *Application-oriented Metrics:* descrivono il comportamento dell'applicazione e la qualità del servizio percepita dagli utenti (response time, error rate, transaction volume, user interaction).

**ESEMPIO TOOL:** Amazon CloudWatch.

## Data Center

Un Data Center è un'infrastruttura fisica che ospita risorse computazionali, di memorizzazione e di rete. 

Un Warehouse-Scale Computer è un sistema computazionale di grandissime dimensioni, costituito da migliaia di server interconnessi. L'idea fondamentale è che l'intero data center viene considerato come un unico enorme computer.

Un Server Rack è una struttura fisica progettata per ospitare più server e altri dispositivi hardware.

## Edge Computing \& Computing Continuum

Non tutte le applicazioni sono adatte ad essere eseguite nel Cloud. Si hanno infatti
- *Latency-sensitive applications:* applicazioni il cui corretto funzionamento dipende da tempi di risposta molto bassi.
- *Location-aware applications:* applicazioni il cui comportamento dipende dalla posizione geografica degli utenti, dei dispositivi o dei dati.

Il problema della latenza riguardo quindi il tempo di risposta, che può essere dato da:
$$
T_{\text{response}} = T_{\text{network}} + T_{\text{processing}} + T_{\text{other}}
$$
Per applicazioni che richiedono reazioni quasi immediate, il tempo necessario per comunicare con un data center distante può risultare eccessivo.

Per affronare i limiti del Cloud centralizzato, l'idea è spostare parte dell'elaborazione e della memorizzazione verso risorse situate ai margini di Internet, più vicini agli utenti e ai dispositivi. Si individuano i seguenti pagadigmi:

### Edge Computing

**DEF:** Paradigma computazionale che prevede lo spostamento di elaborazione dai data center Cloud centralizzati verso risorse situate in prossimità dei dispositivi periferici.

L'idea quindi è quella di elaborare i dati vicino al luogo in cui vengono generati o utilizzati anziché trasferirli verso un data center remoto.

**DEF:** Gli *Edge Nodes* sono le risorse che vengono utilizzate per l'elaborazione dei dati. Può essere realizzato attraverso dispositivi hardware differenti:
- *IoT/Edge Gateways:* dispositivi che raccolgono dati da sensori e altri dispositivi IoT.
- *Micro-servers:* server di dimnesioni e capacità inferiori rispetto a quelli dei grandi data center.
- *Dispositivi Mobile e Smartphone*.

**Vantaggi:**
- *Riduzione della latenza e della banda*
- *Risparmio energetico*
- *Miglioramento della privacy:* poiché i dati possono essere processati localmente, non c'è necessità che vengano trasmessi verso infrastrutture remote.

Insieme all'edge computing si possono combinare altre tecnologie:
- *Edge Computing + 5G:* Permette di realizzare applicazioni che sfruttano la velocità della tecnologia 5G.
- *Edge AI:* eseguire algoritmi di ML e AI sugli edge nodes. L'obiettivo è eseguire inferenza vicino al luogo in cui vengono prodotti i dati.

**Limiti**
- Risorse computazionali e di memorizzazione limitate.
- Scalabilità complessa.
- Maggiori problemi di sicurezza.
- Mancata standardizzazione.

Una soluzione per affrontare i limiti degli Edge Nodes è quella di spostare parte dell'elaborazione e dello storage verso Cloud più potenti (*Computation Offloading*).

Vediamo ora un'architettura per oganizzare i dispositvi nell'Edge Computing.

Il *Multi-layer Edge Computing* è un architettura nella quale le risorse Edge vengono organizzate in più livelli, caratterizati da capacità computazionali e posizioni differenti.

1. *Far Edge / IoT Devices:* comprende i dispositivi situati più vicino al luogo in cui i dati vengono prodotti o utiizzati.
2. *Near Edge:* comprende risorse computazionali locali, generalmente più potenti rispetto ai dispositivi Far Edge.
3. *Regional Edge:* comprende infrastrutture più grandi, situate a livello regionale. 

### Computing Continuum

**DEF:** Il *Computing Continuum* è un paradigma nel quale risorse computazionali distribuite, dai dispositivi periferici fino ai grandi data center Cloud, vengono integrate all'interno di un'unica infrastruttura logica.

L'obiettivo è superare la distinzione rigida tra Cloud ed Edge Computing, permettendo alle applicazioni di utilizzare risorse collocate a livelli differenti.

Poiché un applicazione potrebbe utilizzare Far Edge per acquisire dati, Near Edge per elaborarli e il Cloud per effettuare anali computazioni costosi, il Computing Continuum ha come obiettivo quello di distribuire dinamicamente l'elaborazione e i dati sui livelli più appropriati.

**DEF:** Per DAG-based application si intendono quelle applicazioni che possono essere descritte come un insieme di operazioni collegate da dipendenze


