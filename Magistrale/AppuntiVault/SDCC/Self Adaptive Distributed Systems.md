
**DEF:** Un sistema software *auto-adattivo* è un sistema in grado di modificare il proprio funzionamento a runtime in risposta a cambiamenti nel *proprio stato interno* o nell'*ambiente esterno in cui opera*.

**DEF:** Per *autonomic computing* indichiamo un paradigma inspirato al sistema nervoso umano per cui alcune funzioni corporee (battito cardiaco, respirazione, digestione) sono regolate automaticamente senza intervento cosciente. Analogamente un sistema informatico autonomo gestisce da solo alcuni aspetti del proprio funzionamento.

### Esempi

1. **Kubernetes:** un sistema di orchestrazione che gestisce applicazioni eseguite in container su un insieme di nodi. Tra le attività di adattamento si hanno: *placement o scheduling* (decidere su quale nodo eseguire un container), *scaling orizzontale* (aumentare o diminuire il numero di istanze di un'applicazione), *verticale* (aumentare o diminuire le risorse per un singolo componente) e *healing* (ricreare su nodi disponibili componenti che erano eseguiti in un nodo ora guasto).
2. **Amazon EC2 Auto Scaling:** un servizio che permette di aumentare o diminuire automaticamente il numero di istanze EC2 in base a regole definite dall'utente, come ad esempio l'utilizzo della CPU o il numero di richieste in coda. *Il sistema adatta automaticamente le risorse per mantenere il comportamento desiderato*.

### Obiettivi nei sistemi self-adaptive

1. **Self-optimization:** ottimizzare prestazioni o uso delle risorse, rispettando gli obiettivi di qualità;
2. **Self-healing:** rivelare, diagnosticare e recupero da guasti;
3. **Self-configuration:** integrare nuovi componenti o modificare automaticamente parametri di configurazione;
4. **Self-protection:** rilevare minacce e reagire per limitare gli effetti.

Affiché il sistema possa raggiungere questi obiettivi, deve essere in grado di conoscere il proprio stato interno *(self-awarness)* e l'ambiente esterno *(self-situation)*. Deve essere in grado di rilevare modifiche riguardo il suo stato e dell'ambiente *(self-monitoring)* e infine riuscere ad adattarsi di conseguenza *(self-adjustment)*.

![[adaptive.png]]

## MAPE

Questo ciclo è organizzato nel modello MAPE:
$$
\text{Monitor} \to \text{Analyze} \to \text{Plan} \to \text{Execute}
$$
Queste 4 fasi si basano poi sulla fase di Knowledge, ossia di conoscenza del sistema.
Si ha quindi:
- *Monitor:* raccoglie i dati dal sitema e dall'ambiente. Può filtrarli, aggregarli e correrarli per ottenere informazioni più utili da analizzare.
- *Analyze:* valuta le informazioni raccolte e determina se è necessario un adattamento. Può usare modelli predittivi, regole o tecniche di ML.
- *Plan:* è il cuore decisionale del ciclo: si sceglie quale azione effettuare per ottenere il cambiamento desiderato.
- *Execute:* applica le azioni pianificate al sistema gestito, usando gli *efettori*.
- *Knowledge:* conserva la conoscenza condivisa necessaria per le varie fasi.

### Monitor

Per progettare questa fase nella miglior maniera possibile è necessario porsi alcune domande:
- *Quando monitorare?* Possiamo monitorare il sistema in modo continuo per tutta la sua esecuzione oppure quando è necessario, ad esempio quando avviene un evento.
- *Cosa monitorare?* Bisogna identificare quali componenti del sistema monitorare, l'utilizzo delle risorse, il carico di lavoro, le performance etc...
- *Come monitorare?* A seconda dell'architettura del sistema (centralizzata/decentralizzata) è necessaria la scelta della tipologia di monitoraggio, che può essere:
	- *Passiva:* si osservano i dati/attività già disponibili senza iniettare nuovo traffico nel sistema;
	- *Attiva:* si iniviano richieste di misurazione per ottenere informazioni più dettagliate.
- *Dove conservare i dati monitorati?* Si posson usare database temporali come InfluxDB, adatti a misure associate nel tempo come utilizzo della CPU. 

### Analyze

In questa fase si utilizzano i dati monitorati nell fase precedenti per analizzarli. Si ha un'analisi *a tempo*, ossia l'analisi avviene ad ogni finestra temporale o *ad evento*.

Si ha infine un'analisi *reattiva*, si reagisce ad un cambiamento già avvento o *proattiva* quando si prevede la necessità futura di adattamento e si prepara l'intervento in anticipo. Il principale motivo di questa scelta è che la creazione di risorse richiede a sua volta del tempo, quindi un intervento proattivo può compesare questo ritardo.

### Plan

È la fase più studiata e difficile da progettare in quanto le tecniche di pianificazione sono numerose. Si ha
- *Ottimizzazione matematica:* con questo approccio si definisce un modello rigoso tramite *variabili decisionali*; una *funzione obiettivo* e *vincoli che le decisioni devono rispettare*. Il vantaggia è che la soluzione é *ottima*, ma non spesso rispecchia alla soluzione ottima reale. In oltre, in molti casi trovare esttamente la soluzione ottima richiede troppo tempo.
- *Euristiche:* un'euristica cerca una soluzione utile con costo computazionale contenuto non garantendo però ottimalità.
- *ML e Reinforcemente Learning:* Si usano tecniche di Machine Learning e RL. Con il RL, il controllore impara a prendere decisione attraverso un'interazione continua con il sistema e l'ambiente, ricevendo un feedback che indica quanto la decisione presa sia stata buona rispetto agli obiettivi ed imparando di conseguenza.

#### Esempio - Container Placement

Il problema del *placement* consiste nel decidere su quali nodi collocare le VM/container che costituiscono le componenti di un'applicazione distribuita in modo da rispettare gli obiettivi di qualità e ottimizzare le risorse.

Questo problema di può ricondurre al *bin packing (knapsack problem)* dove i bin sono i server fisici e gli item sono le VM/container, le *dimensioni dell'item* sono le risorse richieste, e la *capacità del bin* le risorse disponibili sul server.

**GOAL:** Collocare tutti gli oggetti usando il minor numero di server possibile, senza che si superi la capacità di nessuno di essi. Riducendo quindi il numero di server utilizzati si risparmia sulle risorse.

Definiamo
- $I$ l'insieme di oggetti da collocare (le VM/container)
- $n$ il numero di server fisici disponibili
- $s_{i}$ il numero di risorso richieste dall'oggetto $i \in I$
- $B$ la capacità di ogni server (uguale per tutti)

Introduciamo ora le *var. decisionali*
$$
y_{j} = 
\begin{cases}
1 &\iff \text{ server $j$ viene usato}  \\
0 &\text{altrimenti}
\end{cases}
$$
$$
x_{ij} = 
\begin{cases}
1 &\iff \text{oggetto $i$ collocato sul server $j$} \\
0 &\text{altrimenti}
\end{cases}
$$

Definiamo poi la *funzione obiettivo*, che rappresenta il numero di server che si vuole minimizzare
$$
K = \min \sum_{j=1}^n y_{j}
$$
avendo i seguenti vincoli su $K \geq 1$
- Ogni ogetto deve essere collocato su un solo server $$\sum_{j=1}^n x_{ij} = 1\ \forall i \in I$$
- Rispettare le capacità dei server, e usare solo quelli attivi: $$\sum_{i \in I} s_{i} x_{ij} \leq B_{y_{j}}\ \forall j = 1,\dots, n$$
Questo modello matematico è un esempio di PLI, un problema NP-HARD.
In questo senso, per risolverlo in tempo utile, si possono sfruttare diverse *euristiche di placement*.
- **Random**: sceglie un server u.a.r. e verifica che lo spazio sia sufficiente. Se sì inserisci l'oggetto, altrimenti ripeti.
- **Round-Robin**: scorri i server in ordine, mantenendo la posizione e inserendo l'oggetto nel primo che ha spazio sufficiente.
- **First Fit**: uguale a RR ma per ogni oggetto si riparte dal primo server.
- **First Fit Decreasing**: ordina gli oggetti dal più grande al più piccolo e poi applica First Fit. Collocare prima gli oggetti grandi pemette di evitare la frammentazione dello spazio in tanti piccoli residui (che può comportare nei casi peggiori di non riuscire a collocare tutti gli oggetti, anche se una soluzione esiste), lo svantaggio è che ordinare costa.
- **Best Fit**: per ogni oggetto, scegli il server che lascerebbe meno spazio residuo (ma sufficiente, ) dopo l'inserimento.
- **Worst Fit**: per ogni oggetto, scegli il server che lascerebbe più spazio residuo dopo l'inserimento.

### Execute 

Consiste solo nell'attuare effettivamente le decisioni prese dal planner. Se la componente è già in esecuzione, allora il piano può richiedere una *(re)migrazione*.

## Pattern MAPE

Vediamo ora come progettare un sistema di gestione MAPE.
- *MAPE centralizzato:* Tutti i componenti MAPE si trovano in un unico nodo. Rappresenta un architettura semplice ma quel nodo può diventare un collo di bottiglia.
- *MAPE decentralizzato:* le componenti sono organizzate su più nodi. Esistono vari pattern per quanto riguarda l'organizzazione delle componenti:
	- *Organizzazione gerarchica - Master/Slave:* Le componeti sono organizzate in gerarchie, quelle più in alto controllano quelle più in basso.
	- *Organizzazione flat - Coordinated Control:* I controllori cooperano tra loro come peer.

![[MAPE.png]]

### Hierarchical MAPE

#### Master Slave

In questo pattern la distribuzione delle responsabilità è:
- Il master ha come responsabilità quella di Analyze e Plan.
- I vari slave hanno come responsabilità quella di Monitor ed Execute.

I vari *worker* (che possono essere dislocati in aree geografiche diverse) raccolgono e possono pre-elaborare i dati locali, inviando al *singolo* master le informazioni già aggregate. Allora il master analizza tali informazioni e definisce un planning e invia ai worker "execute" le eventuali azioni da compiere.

Il vantaggio principale è che il Master possiede una visione globale del sistema e può prendere decisioni di adattamento orientate al raggiungimento di obiettivi globali.
Tra i svantaggi si ha: *communication overhead, performance bottleneck e Single Point of Failure*.

#### Control Pattern

A differenza del Master-Worker, ogni livello può implementare un ciclo MAPE completo. I diversi cicli MAPE vengono organizzati gerarchicamente e possono operare su scale temporali differenti, occupandosi di aspetti diversi del sistema.

### Flat MAPE

#### Coordinated Control Pattern

È un'architettura decentralizzata in cui più cicli MAPE operano come nodi paritari. Il vantaggio è *maggiore potenziale scalabilità* in quanto non c'è più il singolo nodo Master che può diventare un collo di bottiglia. Il limite è che *coordinare le decisioni tra tanti controllori allo stesso livello è complesso e ha un costo significativo*.
#### Information Sharing Pattern

Rappresenta un caso particolare di Coordinated Control, in cui *solo le componenti di Monitor interagiscono tra loro*. Ha senso in quanto sono i Monitor che raccolgono i dati grezzi ed eventualmente li pre-elaborano. Il vantaggio è *minori interazioni* rispetto a un coordinamento esteso a tutte le fasi, il limite è che i planner possono prender decisioni sub-ottimali o in conflitto.

La scelta dell'architettura MAPE rappresenta un compromesso tra scalabilità, tolleranza ai guasti, semplicità di coordinamento e capacità di raggiungere obiettivi globali.

## Caso di Studio: Self Adaptive 

Vediamo ora in pratica come i concetti di *self-adaptation* vengono applicati concretamente alla gestione automatica delle risorse nei sistemi distribuiti.

### 1. AWS EC2 Auto Scaling

È un servizio di AWS che permette di aggiungere o rimuovere automaticamente istanze EC2 in funzione delle condizioni operative e dello stato di salute di istanze. L'obiettivo è adattare dinamicamente la capacità computazionale dispobile al carico di lavoro, evitando sia la carenza sia lo spreco di risorse.

![[awsautoscaling.png]]

Le istanze vengono organizzate in Auto Scaling Group, caratterizato da tre parametri:
- *Minimum size:* numero minimo di istanze che devono essere mantenute.
- *Desired capacity:* numero di istanze che il gruppo cerca di mantenere.
- *Maximum size:* numero massimo di istanze consentito.

La fase di Monitor del ciclo MAPE viene realizzata attraverso Amazon CloudWatch, che raccoglie metriche relative alle risorse e al carico di lavoro.

Nella fase di Plan, AWS Auto Scaling mette a disposizione diverse politiche:
#### Threshold-based Policy

È una politica euristica reattiva basata su soglie predefinite. Il principio consiste nel monitorare una o più metriche e confrontarle con due valori:
- *Upper threshold:* il superamento provoca uno scale-out.
- *Lower threshold:* al di sotto della quale viene eseguito uno scale-in.

```Python
if metric > upper_threshold:
    scale_out()
elif metric < lower_threshold:
    scale_in()
```

Si hanno due politiche di scaling:
- *Simple Scaling:* quando viene generato un allarme, il sistema applica una variazione fissa della capacità, ad esempio aggiungendo o rimuovendo una singola istanza.
- *Step Scaling:* La variazione della capacità dipende da quanto la metrica supera la soglia configurata.

Il principale vantaggio è la *semplicità di configurazione e compresione*. Mentre i limiti sono:
- La scelta delle metriche richiede conoscenza dell'applicazione.
- Le metriche infrastrutturali non rappresentano necessariamente la qualità percepita dall'utente.
- Le politiche potrebbero non essere robuste in presenza di carichi altamente dinamici.
#### Target-based Policy

È una politica euristica reattiva basata su un valore obiettivo. A differenza delle politiche threshold-based, non è necessario configurare esplicitamente una soglia superiore o inferiore.
Si definisce invece un valore desiderato per una metrica e il sistema modifica automaticametne la capacità per mantenerla il più possibile vicina al target. Ad esempio, possiamo richiedere di mantenere l'utilizzo della CPU al 50%.

Il numero desiderato di repliche viene calcolato secondo la relazione:
$$
\text{desiredReplicas} = \left\lceil \text{currentReplicas} \cdot \frac{\text{currentMetricValue}} {\text{desiredMetricValue}} \right\rceil
$$
Il principale vantaggio è la maggiore semplicità di configurazione, poiché è sufficiente specificare un valore obiettivo anziché definire più soglie.

#### Predictive-based Policy

È una politica di adattamento proattiva basata su tecniche di ML. A differenza delle politiche precedenti, non aspetta che il carico aumenti per intervenire, ma cerca di *prevedere le variazioni future del workload* e pianificare in anticipo l'allocazione delle risorse.

Il sistema utilizza un modello di ML addestrato su dati storici per prevedere il carico futuro. In particolare cerca di identificare pattern riccorenti, come variazioni giornaliere e settimanali.

Le metriche utilizzabili sono:
 - Numero di richieste ricevuto dal LB;
 - Utilizzo delle risorse;

**Vantaggi:**
- Consente di aumentare la capacità prima che il carico provochi un degrado delle prestazioni.
- Può sfruttare pattern ricorrenti per anticipare variazioni prevedibili del workload.

**Limitazioni:**
- La qualità delle previsioni dipende dai dati storici disponibili e dal loro contenuto informativo.
- L'efficacia dipende dalla metrica scelta per prevedere il carico.
- La politica predittiva descritta nelle slide supporta soltanto decisioni di scale-out: per lo scale-in è necessaria una politica separata.

### 2. Self-adaptive Service Selection

Questo caso di studio riguarda l'adattamento dinamico di applicazioni basate su SOA. 
In una SOA, un'applicazione viene costruita attraverso la composizione di diversi servizi, ciascuno dei quali fornisce una determinata funzionalità.

I servizi che costituiscono una SOA possono essere:
- *Astratti:* definisce una funzionalità richiesta dall'applicazione, indipendentemente da come venga implementata.
- *Concreti:* rappresenta una specifica implementazione del servizio astratto, caratterizzata da determinaate proprietà non funzionali.

L'obiettivo consiste nel selezionare le implementazioni concrete in modo da rispettare gli *Service Level Agreements* dell'applicazione.

### 3. Auto-scaling gerarchico nei microservizi

Questo caso di studio riguarda l'autscaling di applicazioni basate su microservizi attraveso un'architettura MAPE gerarchica.

Consideriamo un'applicazione composta da diversi microservizi, ciascuno dei quali può essere replicato per gestire il carico. L'obiettivo è mantenere il tempo di risposta dell'applicazione a una soglia massima $$R_{\text{app}} < R_{\text{max}}$$
Il pattern *Hierarchical Control* consiste in due livelli principali:
- *Microservice Manager:* gestisce l'adattamento di un singolo microservizio; Rapprenseta un controllo locale ed è responsabile dell'andamento di un determinato microservizio. Per decidere se effettuare scale-out o scale-in, utilizza una politica basata sulla *teoria delle code e previsioni del carico di lavoro*.
- *Application Manager:* coordina le decisioni dei Microservice Manager per soddisfare gli obiettivi globali dell'applicazione. Rappresenta un controllo globale dell'applicazione. Il suo compito consiste nel coordinare le operazioni di scaling.