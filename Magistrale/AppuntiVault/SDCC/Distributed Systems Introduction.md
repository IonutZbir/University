L'aumento della potenza dei computer, la capacità di memoria e archiviazione nonché la velocità delle reti hanno reso possibile la creazione di servizi utilizzati da milioni di utenti. Tali servizi devono essere capaci di produrre ed elaborare quantità enormi di dati.

La difficoltà principale è la **scalabilità**: è necessario trovare soluzioni che permettano di fornire servizi a milioni di persone in contemporanea. Poiché una singola macchina ha limiti fisici in termini di CPU, memoria e capacità della rete per ovviare al problema è necessario distribuire e organizzare il carico di lavoro su più macchine.

La **Legge di Metcalfe** afferma che il valore di una rete cresce proporzionalmente al quadrato del numero di utenti connessi. Questo implica che più utenti si connettono a un servizio, più il servizio diventa utile e prezioso.

Il **Gartner hype cycle** afferma che le tecnologie emergenti attraversano diverse fasi: inizialmente c'è un picco di aspettative, seguito da una fase di disillusione, e infine una fase di maturità in cui la tecnologia diventa stabile e ampiamente adottata. Il cloud computing ne rappresenta un esempio evidente.

Distribuire significa dividere qualcosa in più parti assegnandone ognuna ad entità diverse: per questo nel calcolo distribuito si applica spesso il principio di **divide et impera** (un lavoro grande per essere risolto efficaciemente deve essere diviso in più parti che possono essere elaborate in parallelo, per poi riaggregare i risultati).

## Definizione di SD

**DEF (Tanenbaum & van Steen):** un **Sistema Distribuito** è una **collezione di elementi di calcolo autonomi che appare agli utenti come un unico sistema coerente**.

Ironicamente quindi l'utente potrebbe trovarsi a non poter usare il servizio a causa del guasto di una macchina di cui egli non sapeva nemmeno l'esistenza (*Def. di Lamport*). In questo senso si richiama l'attenzione alla **tolleranza ai guasti** che approfondiremo poi.

I prinicipali motivi per cui si costruiscono SD sono:
- Condividere risorse;
- Ridurizione dei costi: utilizzo di più macchine economiche invece di una estremamente costosa;
- Migliorare le prestazioni: una richiesta può essere gestita da un nodo vicino all'utente invece che da un server centrale lontano, oppure il lavoro può essere parallelizzato;
- Migliorare disponibilità e affidabilità: se un nodo si guasta, altri nodi possono continuare a fornire il servizio.
- Risolvere problemi grandi: alcuni problemi richiedono maggiori risorse di quelle disponibili su un'unico nodo, è necessario distribuire il lavoro su più nodi;
- Supportare QoS (Quality of Service) e QoE (Quality of Experience): un sistema distribuito può essere progettato per garantire determinati livelli di prestazioni e affidabilità, migliorando l'esperienza finale dell'utente.

Costruire e verificare un sistema distribuito è più complesso rispetto ad uno centralizzato, in particolare si evidenziano tre caratteristiche:
- *Concorrenza:* più attività avvengono in contemporanea; occore stabilire come coordinare tale attività;
- *Assenza di clock globale:* ogni macchina dispone di un clock interno che non è sincronizzato con quello delle altre macchine; è necessario definire un protocollo che ci permetta di capire qual'è l'ordine corretto degli eventi.
- *Guasti indipendenti e parziali:* un nodo può guastarsi in qualsiasi momento, oppure può interrompersi la comunicazione tra alcuni nodi. Si parla quindi di guasti parziali, mentre i sistemi centralizzati falliscono completamente.

## Challenge

Nella progettazione di un sistema distribuito si incontrano le seguenti challenge:

### 1. Heterogeneity

**Eterogeneità:** significa che i componenti possono essere diversi tra loro: reti, hardware, software, linguaggi di programmazione e implementazioni possono variare.

**Middleware:** è uno strato software che offre funzionalità comuni ai componenti distribuiti. Sta al di sopra dei sistemi operativi e fornisce ai sviluppatori un modo uniforme di programmare e comunicare. Ovviamente il middleware non elimina fisicamente le differenze tra le macchine, ma offre astrazioni a livello software che permettono alle macchine di gestire queste differenze.

- *RPC (Remote Procedure Call):* un programma che permette di effettuare chiamate da remoto ad un nodo invocando le sue API.
- *MOM (Message Oriented Middleware):* le componenti comunicano tramite messaggi, che possono essere ricevuti e inviati in modo asincrono.

### 2. Trasparency

La **trasparenza** è la proprietà per cui la presenza di più nodi e la collocazione delle risorse avvengono, per quanto possibile, nascoste ad utenti e applicazioni. Si vuole far percepire il sistema come insieme coerente.

Si distinguono vari tipi di trasparenza:

- **Access transparency**: nasconde le differenze tra risorse locali e remote, permettendo di accedere a entrambe nello stesso modo;
- **Location transparency**: nasconde la posizione fisica delle risorse;
- **Migration transparency**: nasconde che una risorsa può spostarsi da un nodo all'altro;
- **Relocation transparency**: nasconde lo spostamento di una risorsa **mentre la si sta usando**;
- **Replication transparency**: nasconde il fatto che esistano più copie della stessa risorsa;
- **Concurrency transparency**: permette a più utenti di accedere contemporaneamente a una risorsa senza interferenze;
- **Failure transparency**: cercare di nascondere il guasto e ripristino di una componente;

### 3. Openness

Un sistema distribuito *aperto* offre componenti che altri utenti possono utilizzare e riesce ad integrare componenti sviluppate altrove. Per farlo, le componenti devono esporre *interfacce ben definite*: bisogna sapere quali operazioni si possono chiamare e come sono rappresentati i dati scambiati.

Si introducono in questo senso le **IDL (Interface Definition Language)**, descrizioni di strutture dati e interfacce indipendenti, per quanto possibile, da uno specifico linguaggio di programmazione.

I benefici cercati sono **Interoperabilità** (sistemi diversi possono comunicare), **Portabilità** (un componente può essere eseguito su piattaforme diverse) e **Estensibilità** (si possono aggiungere o sostituire componenti).

Un sistema è più facile da estendee se è composto da parti relativamente piccole, che si possono adattare o sostituire. Per progettarlo è utile distinguere tra **Meccanismo** (come il sistema rende possibile un'operazione) e **Politica** (quale scelta compie usando quel meccanismo).

### 4. Scalability

Un sistema è **scalabile** se riesce a mantenere le prestazioni adeguate anche quando il carico cresce significativamente. Si distinguono tre tipi di scalabilità:

- *Size Scalability* se il numero di utenti o risorse cresce;
- *Geographical Scalability* se aumenta la distanza tra i nodi;
- *Administrative Scalability* se aumenta il numero di amministratori o gestori del sistema.
La scalabilità è una delle caratteristiche *core* dei sistemi distribuiti.

Siano
- $S = \text{ tempo di servizio}$;
- $U = \text{ tempo di utilizzo}$;
- $R = \text{ tempo di risposta}$;
Allora per un semplice modello di coda si ha
$$
\frac{R}{S} = \frac{1}{1-U}
$$
In questo modo, se $U$ è basso, allora $R$ è vicino a $S$ e dunque la richiesta aspetta poco. 
Quando invece $U$ si avvicina a 1, la coda e il tempo di risposta crescono rapidamente.

Ci sono due tipologie di scaling:
- *Vertical Scaling:* si rende più potente un singolo nodo, ad esempio aggiundo più RAM;
- *Horizontal Scaling:* si aggiungono più nodi al sistema, distribuendo il carico di lavoro tra essi.

Le varie tecniche di scaling sono:

1. **Nascondere la latenza**: con la comunicazione asincrona, un programma invia una richiesta e può continuare altro lavoro mentre aspetta la risposta. Tuttavia non tutti i modelli sono adatti a questo approccio, ad esempio se un programma deve fare una richiesta e poi immediatamente usare il risultato per continuare l'elaborazione.
2. **Spostare il calcolo**: una parte del lavoro può essere svolta dal client o da altri nodi, ad es. una decisione può essere presa vicino ai dispositivi che producono i dati oppure affidata a risorse cloud in base alle esigenze
3. **Distribuire dati e calcolo**: Si partizionano dati o compiti; di nuovo principio divide et impera.
4. **Replicare risorse e dati**: si creano più copie; una replica vicina può ridurre il tempo di accesso ed inoltre se un nodo si guasta, altre copie possono continuare a fornire il servizio

Tuttavia la replicazione introduce il problema per cui se una copia viene modificata, le altre copie devono essere aggiornate. Questo richiede un protocollo di **consenso** tra le repliche per garantire che tutte abbiano lo stesso stato. Inoltre dipende in base al dominio applicativo: es. per sistemi di controllo di traffico aereo si hanno requisiti molto severi.

### 5. Dependability

Indica quanto possiamo fare affidamento sul fatto che un sistema si comporti come previsto. Nel caso dei sistemi distribuiti è una questione delicata visto che i guasti possono essere parziali e indipendenti. Si distinguono quattro proprietà:

1. **Availability**: posso usare il servizio **adesso**? Si può interpretare come la probabiltià che il sistema sia operativo in un dato momento: $$A = \frac{\text{MTTF}}{\text{MTTF + MTTR}}$$dove MTTF (Mean Time To Failure) è il tempo medio tra guasti e MTTR (Mean Time To Repair) è il tempo medio per riparare un guasto. (99% di disponibilità risulta in 3.65 giorni di inattività, 99.99% risulta in 52 min.)
2. **Reliability**: continuerà a funzionare **senza interruzioni** per il tempo che mi serve? La **Reliability** riguarda invece la probabilità che la componente, funzionante all'inizio, continui a funzionare senza guasti per tutto l'intervallo considerato.
3. **Safety**: quanto è improbabile che un guasto produca conseguenze catastrofiche?
4. **Maintainability**: quanto è facile ripristinare il servizio dopo un guasto?

*NOTA:* Disponibilità e Affidabilità non coincidono quando il sistema può essere riparato. In particolare:

- un sistema che si interrompe per un ms ogni ora è disponibile per quasi tutto il tempo, ma ha guasti molto frequenti quindi è poco affidabile
- al contrario un sistema che funziona senza guasti per tutto l'anno eccetto due settimane in cui è spento ha poca disponibilità ma è molto affidabile.

Tre termini fondamentali in Dependability sono parte di una possibile catena:  
**Fault** (causa) $\to$ **Error** (stato interno errato) $\to$ **Failure** (servizio non conforme).  
Ad esempio una memoria danneggiata (fault) può produrre un valore sbagliato al suo interno (error) per cui il programma restituirà un risultato errato all'utente finale (failure). Un errore interno può causare una failure, ma non è detto che accada se viene rilevato e risolto prima che il servizio venga compromesso.

I fault possono essere transitori, intermittenti o permanenti, e possono causare guasti a cascata tra componenti.

Per affrontare i guasti ci sono varie tecniche:
- fault prevention
- fault tolerance (progettare il sistema affinché continui a funzionare anche in presenza di guasti)
- fault removal
- fault forecasting (prevedere guasti futuri e pianificare la manutenzione).

### 6. Security

Un sistema distribuito deve proteggere dati e operazioni scambiati tra componenti.

- **Confidentiality**: le informazioni sono accessibili soltanto a soggetti autorizzati
- **Integrity**: dati e risorse possono essere modificati soltanto in modo autorizzato

Si distinguono inoltre Autenticazione, Autorizzazione (verificare quali operazioni quell'identità può compiere) e Trust (avere garanzia che un'entità si comporterà come previsto). Un utente ad es. può essere autenticato correttamente ma non autorizzato a leggere un certo file.

Alcuni strumenti crittografici per la sicurezza sono crittografia simmetrica (una chiave per cifrare e decifrare), crittografia asimmetrica (una chiave pubblica per cifrare e una privata per decifrare). Si utilizzano in questo senso prevalentemente funzioni hash crittografiche.





