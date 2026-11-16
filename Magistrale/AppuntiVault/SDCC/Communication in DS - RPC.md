
La comunicazione nei sistemi distribuiti si basa sullo *scambio di messaggi*. Affinché due entità si possano scambiare dei messaggi, esse devono concordare su un protocollo di comunicazione, a partite dal livellio più basso fino al livello di applicazione.

Come già sappiamo, la comunicazione all'interno delle reti è divisa in livelli (pila ISO/OSI o TCP/IP). Per quanto riguarda la comunicazione nei sistemi distribuiti, ci occuperemo della comunicazione a livello *middleware* che offre alle applicazioni distribuiti diverse funzionalità, come:
- Chiamate a procedura remota *RPC*;
- Code di messaggi;
- Comunicazione verso più destinatari.

Oltre ai *middleware di comunicazione*, ne esistono altri come:
- *Naming middleware:* identifica e permette la condivisione di risorse;
- *Security middleware:* permette una comunicazione sicura tra le i vari nodi della rete;
- *Distributed Consensus middleware:* coordina i vari nodi;

## Comunicazione

Possiamo classificare la comunicazione nei sistemi distribuiti in 4 categorie:
#### 1. Persistenza 

Questa categoria riguarda la durata e la memorizzazione del messaggio nel canale o middleware di comunicazione.
- *Comunicazione Persistente:* il middleware conserva il messaggio affinché possa esser consegnato successivamente. In questo caso il destinatario non deve essere necessariamente attivo quando il mittente invia il messaggio.
- *Comunicazione Transiente:* Il messaggio viene mantenuto solo finché mittente e destinatario sono entrambi attivi contemporaneamente. Se la consegna non è possibile al momento, il messaggio viene *scartato*.
#### 2. Sincronizzazione

Questa categoria definisce se il mittente deve bloccarsi in attesa di un evento prima di poter proseguire l'esecuzione.
- *Comunicazione Sincrona:* Un volta inviato il messaggio, il mittente si blocca finché l'operazione non si completa. Sia *invio* che *ricezione* sono operazioni bloccanti. La sincronizzazione (quando il mittente si sblocca) può avvenire in tre momenti diversi: alla sottomissione delle richieste (appena il middleware locale prende in carico il messaggio), alla consegna della richiesta oppure dopo che la richiesta è stata elaborata (RPC).
- *Comunicazione Asincrona*: Una volta inviato il messaggio, il mittente continua la sua esecuzione. Il messaggio viene temporaneamente memorizzato dal middleware in attes di trasmissione. La ricezione può essere bloccante o non bloccante. Se non bloccante, la chiamata ritorna subito, restituendo i dati (se presenti) oppure un indicazione che non c'è nulla da ricevere.

Il vantaggio di asincronia da entrambi i lati è che disaccoppia *(decouples)* mittente e destinatario, permettendo quindi concorrenza e responsiveness maggiori.
#### 3. Dipendenza temporale

Valuta se la corretta comprensione dei dati dipende o meno dal fattore tempo o dall'ordine di arrivo.
- *Comunicazione Discreta:* Ciascun messaggio costituisce un'unità di informazione completa e autonoma (ad esempio una richiesta HTTP).
- *Comunicazione Streaming:* Prevede l'invio continuo di uno o più messaggi legati tra loro da una *relazione temporanea* o ordinati secondo una sequenza di trasmissione. In questo caso l'ordine e il tempo di arrivo sono necessari per la corretta ricostruzione dell'informazione.

### Persistenza e Sincronizzazione

- *Comunicazione Persistente Asincrona:* Il mittente invia il messaggio e continua la sua esecuzione. Il middleware conserva il messaggio in una coda persistente finché il destinatario non è pronto a riceverlo. Il mittente può addirituttra terminare la propria esecuzione prima ancora che il messaggio arrivii al destinatario. Questo tipo di comunicazion permette un disaccoppiamento tra le due entità. Un esempio di comunicazione di questo tipo è l'Email, le chat (WhatsApp, Teams), Message-Oriented Middleware  (Apache Kafka, RabbitMQ).
- *Comunicazione Persistente Sincrona:* Il messaggio viene memorizzato in modo persistente dal middlware, ma il mittente si blocca finché il middleware del ricevente non ha preso in carico il messaggio confermandone la ricezione.

![[persistentsync.png]]

- *Comunicazione Transiente Asincrona:* Il mitttente invia il messaggio e non aspetta, ma il messaggio non viene salvato in nessun storage persistente. Se il destinatario non è online il messaggio va perso definitivamente. Un esempio di comunicazione è UDP.
- *Comunicazione Transiente Sincrona:* Il messaggio non viene memorizzato su disco in modo persistente; se il destinatario è spento, la comunicazione fallisce. Per quanto riguarda la sincronia invece ci sono modalità: *Receipt* (il mittente si blocca non appena ha inviato il messaggio e si sblocca appena il messaggio entra nel buffer di rete del destinatario), *Delivery* (il mittente si blocca non appena ha inviato il messaggio e si sblocca non appena il messaggio viene consegnato al processo destinatario), *Response* (è il modello classico request-reply, il mittente si sblocca non appena riceve la risposta alla sua richiesta).

## Communication Failures

In generale quando un client esegue una chiamata RPC, avviene qunato segue:

![[rpcscheme.png]]

Vedremo che nonostante il middleware nasconda tutti i dettagli implementativi, esso però *non* elimina i problemi dovuti al fatto che ci troviamo in un ambiente distribuito. Esistono quindi diversi fallimenti in terminin di comunicazione:

- *Perdita o ritardo del messaggio:* cade la richiesta o la risposta, oppure la connessione subisce un reset (*pitfall:* assumere che la rete sia sempre affidabile).
- *Crash del server:* Può avvenire prima di eseguire il servizio o dopo aver eseguito il servizio. In entrambi i casi il client non riceve nessuna risposta.
- *Crash del client:* il client muore dopo aver inviato la richiesta.

### Semantiche di fallimento

Le *communication semantics* definiscono le garanzie offerte dal sistema circa l'esecuzione del servizio/consegna del messaggio in presenza di guasti. Più la garanzia è forte maggiore è la complessità implementativa:

Per implementare le varie semantiche si combinano tre primitive fondamentali:
- *RR1 (Request Retry - lato client):* il client riprova a inviare la richiesta alla scandenza di un timeout, fermandosi solo alla ricezione del reply o al raggiungimento di un numero massimo di tentativi;
- *DF (Duplicate Filtering - lato server):* il server riconsce e scarta le richiesta duplicate provenienti dallo stesso client;
- *RR2 (Result Retrasmit - lato server):* il server salva in un cache/log il risulato già calcolato per poterlo ripedire direttamente se riceve un duplicato, senza ricalcolare la funzione.

#### 1. Maybe Semantics
Non rappresenta nessuna garanzia. Il servizio può essere stato eseguito mai o al massimo una volta. Non utilizza quindi nessun meccanismo aggiuntivo. Il client invia la richiesta e va avanti senza ritentare. Se la risposta va persa, il server ha eseguito ma il client non lo saprà mai, se il server va in crash, il servizio non viene eseguto.
Tipico di protocolli come UDP; utile per telemetria, streaming o logging dove la perdita occasionale di campioni è tollerabile rispetto all'overhead.

![[maybe.png]]

#### 2. At-least-once Semantics
Garantisce che il servizio venga eseguito *almeno una volta*. Se la risposta non torna, il client ritrasmette finché non ottiene riscontro;
Per implementarlo, il client usa *RR1* mentre il server non usa nessuna tecnica. Allo scadere di un timeout, il client ritrasmette la richiesta. Se a perdersi era la risposta, il server riceve nuovamente la richiesta ed esegue il calcolo nuovamente.
Questa semantica è sicura solo nel caso di funzioni *idempotenti* ossia operazioni del tipo
$$
f(f(x)) = f(x)
$$
dove eseguire l'operazione più volte con gli stessi parametri non altera lo stato finale rispetto a una sincola operazione. Ad esempio `get(key), put(key, value)`.

#### 3. At-most-once Semantics
Garantisce che il servizio venga eseguito al *massimo una volta*. Se il client riceve la risposta, ha la certezza assoluta che è stato eseguito una sola volta. In caso di fallimento definitivo, potrebbe non essere stato eseguito affatto, ma mai più di una volta.

Per implementarlo, il client utilizza RR1 mentre il server sia DF che RR2. Viene utilizzato in quei sistemi per servizi *non idempotenti*, ad esempi `increment(counter), withdraw(amount)`, dove una doppia esecuzione causerebbe un'inconsistenza di stato.

![[atmostonce.png | 600]]

Il funzionamento è il seguente. Supponiamo che la prima richiesta si perde, a questo punto il client ritrasmette, il server riceve la richieste, la esegue e conserva il risultato. La risposta però si perde quindi il client ritrasmette ancora. Il server riconosce il duplicato e quindi *non riesegue l'operazione* ma restituisce il risultato già calcolato.

Affinché il server riesca ad implementare DF e RR2, deve essere in grado di *saper riconoscere i duplicati e associarle un risultato*. Per fare ciò il client associa a ogni richiesta un identificatore univoco `xid`, mantenendo lo stesso `xid` anche nelle ritrasmissioni successive dopo il timeout. Generalmente, può essere generato come
$$
\texttt{xid = hash(client\_id, nonce)}
$$
A questo punto il server deve solo mantenere una mappa del tipo `xid -> (status, reply)`.
```python
if seen[xid]:
	reply = old[xid]
else:
	reply = handler()
	old[xid] = reply
	seen[xid] = true
```

La cache non può crescere all'infinito: il server elimina le vecchie entry tramite *sliding windows* o associando un tempo massimo di vita (_TTL / maximum lifetime_) alle risposte salvate. Questo schema implementa il design pattern noto come _Idempotent Receiver_.

#### 3. Exactly-once Semantics

Garantisce che il servizio viene eseguite *esattamente* una sola volta, a prescindere da crash o ritrasmissioni. È la più costosa da realizzare, infatti non bastano i 3 meccanismi visti finora, ma ne servono altri.

Exactly-once segue una logica *all-or-nothing*, o l'operazione viene completata una sola volta oppure non deve produrre alcun effetto parziale.

Affinché questa semantica si possa implementare, c'è la necessità di ulteriori meccanismi:
- *Replicazione del Server:* più server mantengono copie del servizio e del suo stato. Un guasto può essere gestito facendo proseguire un'altra replica (es. leader-follower, primary-backup). La difficoltà sta nel fatto di trovarci in un sistema distribuito: *ad ogni operazione tutti i server devono aggiornare il loro stato in modo coerente*.
- *Meccanismi di Recovery:* se avviene un crash, il server deve essere in grado di recuperare lo stato coretto del servizio. Tra questi meccanismi: *checkpoint dello stato*, si salva in una memoria *persistente* lo stato del server ogni $t$ tempo, *checkpoint con snapshot*, non si salva lo stato di un solo server, ma una visione globale anche dei replicati, *wirte-ahead-logging*, prima di eseguire un'operazione, il server salva la richiesta in un log persistente.

**Write-ahead-logging**

Il Write-Ahead Log (WAL), o Commit Log, è *un registro persistente delle operazioni necessarie a ricostruire lo stato del servizio*.

![[writeahead.png]]

Prima di applicare una modifica allo stato in memoria (es. aggiornare una tabella hash o un database key-value), l'operazione viene serializzata e appesa sequenzialmente (_append-only_) su un file di log su disco persistente (SSD/HDD). Poiché è una scrittura sequenziale in coda, è un'operazione rapida e a basso overhead rispetto a scritture casuali su disco. Solo dopo che la scrittura sul log è stata completata (_flushed to disk_), il server aggiorna la propria struttura dati in-memory (`kv.put(key, value)`) e risponde al client.

WAL e Checkpoint differiscono in quanto _checkpoint conserva l'intero stato del sistema in un dato istante_, mentre _WAL è la specifica sequenza delle modifiche_.

Per recuperare da un crash quindi prima il server carica un checkpoint valido, per poi riprodurre le entry successive allo stato presenti nel WAL. In tal caso nessuno stato è perso, _a patto che il log sia stato scritto in memoria persistente prima del crash_.

Scrivere direttamente su storage persistente è molto costoso, un'alternativa migliore è accumulare entry in un buffer e scriverle in gruppi. Se però il server crasha prima che il buffer sia scritto su storage persistente, queste modifiche si perdono.

Per concludere, tra le quattro semantiche, *at-least-once e at-most-once sono le più diffuse*. At-least-once può essere preferita per la semplicità e scalabilità, specie se il servizio è _idempotente_ e se l'applicazione tollera duplicati.

# Programmazione di Applicazioni Distribuitte

La programmazione delle applicazioni distribuite può avvenire in diversi metodi. La *programmazione esplicita* rappresenta l'approccio tradizionale e di basso livello. Si basa interamente sulle *Socker API* (`socket(), bind(), connect(), send(), recv()`) e sulla gestione esplicita dello scambio di messaggi. Rappresenta la base su cui sono costruite le applicazioni di rete native (web server, browser, etc...)

Per superare la complessità delle socket e aumentare il livello di astrazione si fa utilizzo delle *middleware di comunicazione* posiziontate tra OS e applicazione utente.
- *API di alto livello:* espone interfacce applicative pulite invece di descrittori grezzi di socket;
- *Nasconte l'eterogeneità:* maschera la complessità hardware, architetturali e del sistema operativo sottostante.
- Automatizza compiti ripetitivi;
- *Migliore qualità software:* offre soluzioni riusabili, testate e corrette alle problematiche dei sistemi distribuiti.

La *programmazione implicita* invece è un paradigma che concretizza l'astrazione fornita dal middleware nascondendo la complessità sottostante. Lo sviluppo adesso si basa interamente su chiamate a procedure remote *RPC (oppure RMI nella OOP)* che permettodono di invocare funzioni o metodi di oggetti remoti come se fossero normali funzioni: `result = service.calculate(x, y)`.

## RPC

**DEF:** RPC sta per *Remote Procedure Call* e permette di estendere il paradigma convenzionale di invocazione procedurale all'ambiente client-server. Un processo su una macchina $A$ chiama una procedura eseguita su una macchina $B$; durante l'attesa del risultato, il processo chiamante su $A$ viene sospeso. I parametri di input e valori di ritorno viaggiano sulla rete sotto forma di messaggi, ma lo scambio di messaggi sottostante rimane invisibile al sviluppatore.

È standard de facto nei sistemi distribuiti, nel cloud computing e nelle architetture a microservizi. Tra le implementazioni storiche e moderne spiccano Sun RPC, Java RMI, RPyC per Python, il supporto nativo in Go (`net/rpc`), e framework performanti come gRPC e JSON-RPC.

#### Remote vs Local Call

- *Chiamata Locale:* il chiamante esegue il push dei parametri e dell'indirizzo di return sullo stack della memoria locale; il controllo passa alla funzione chiamata, che al termine dell'esecuzione posiziona il valore di ritorno e ripristina il program counter del chiamante nello stesso spazio di indirizzamente.
- *Chiamata Remota:* Per simulare una chiamata locale senza condividere lo stack di memoria, si impiegano i *client stub* e *server stub*; Il client stub espone al client l'interfaccia della procedura remota, intercetta la chiamata locale e nasconde tutti i dettagli di rete. Il server stub riceve i byte dalla rete e si occupa di invocare localmente la procedura reale del server, ritornando poi i risultati al middleware.

![[localremote.png]]

l ciclo completo di una chiamata RPC sincrona segue dieci passaggi sequenziali tra spazio utente, kernel e rete:

**CLIENT:**
L'applicazione client chiama la funzione sul *client stub* come se fosse una funzione locale. Il client stub impacchetta i parametri in una rappresentazione serializzata uniforme (*marshaling*) e prepara il messaggio di richiesta invocando la system call del sistema operativo locale. A questo punto l'OS del client trasmette il pacchetto attraverso la rete verso l'OS del server. L'OS del server riceve i pacchetti e li inoltra al server stub. Il server stub esegue l'*unmarshaling* (estrae e deserializza) dei parametri del messaggio, invoca la procedura locale effettiva passando i parametri estratti. Quando la procedura termina, restituisce la risposta al server stub il quale esegue il marshaling della risposta in un messaggio di reply. L'OS del server invia poi il pacchetto all'OS del client il quale inoltra a sua volta il pacchetto al client che deserializza il valore di ritorno e sblocca l'applicazione client, restituendole il risultato finale.

Per rendere la chiamata remota trasparente, il middleware deve affrontare quattro sfide strutturali.
- *scambio messaggi e protocolli di trasporto:* gestire identificatori di chiamata/risposta e scegliere il layer di trasporto adeguato (TCP per affidabilità o UDP per basse latenze con gestione applicativa dei retry).
- *Passaggio di parametri per riferimento:* rappresenta uno dei vincoli fisici più critici: puntatori di memoria e riferimenti non hanno senso su macchine distinte con spazi di indirizzamento separati. La soluzione tipica consiste nel simulare il passaggio per copia-ripristino (_copy-in / copy-out_) o ricorrere a proxy remoti dedicati.
- *Semantiche di fallimento:* a differenza della chiamata locale (che garantisce intrinsecamente un'esecuzione _exactly-once_), la RPC è soggetta ai guasti di rete e nodi visti prima, dovendo adottare semantiche come **at-least-once** o **at-most-once**.
- *Binding client-server:* il client deve scoprire l'endpoint (IP, porta, versione dell'interfaccia) del server prima di poter chiamare la funzione, tipicamente via name service, registry o discovery service.

Client e server possono eseguire su architetture hardware o sistemi operativi differenti, introducendo discrepanze su:
- *Byte ordering:* ordinamento Little-Endian vs Big-Endian.
- *Dimensione dei tipi nativi:* es. interi a 32 vs 64 bit.
- *Codifica caratteri:* es. ASCII vs UTF-8.
- *Layout di memoria:* padding e allineamento dei campi nelle strutture dati (struct).

Copiare direttamente la memoria grezza (_raw memory dump_) sul socket di rete corromperebbe i dati. Per convertire i dati esistono diverse strategie teoriche:
1. *Encoding specificato nel messaggio:* il mittente invia i dati nel suo formato nativo specificando quale usa, e il ricevente si occupa della conversione.
2. *Il mittente converte nel formato del destinatario:* richiede che il mittente conosca a priori l'architettura di ogni ricevitore; scala malissimo poiché richiede $O(N^2)$ convertitori per $N$ tipologie di architetture distinte.
3. *Codifica comune concordata:* approccio standard adottato dalla quasi totalità dei sistemi RPC. Il mittente converte dal proprio formato locale a quello standard, e il destinatario converte dal formato standard a quello locale, riducendo la complessità a $O(N)$ convertitori.
4. *Broker:* una componente specifica fa da intermediario e si occupa delle conversioni.

Queste quattro soluzioni si ricollegano direttamente a due pattern:

- **Proxy**: se localmente abbiamo client/server stub, allora la conversione verso il formato adatto avviene grazie a questi intermediari. Ricordiamo che questi proxy nascondono quindi i dettagli di comunicazione fornendo un'interfaccia all'utente simile a quella di una chiamata locale. (*Pattern adottato da RPC*)
- **Broker**: direttamente collegato alla soluzione 4, in questo caso l'intermediario è un componente separato ai client e server. Il broker può occuparsi anche di instradamento, individuare i servizi etc... .

#### Passaggio di Parametri

Ricordiamo i metodi classi di passaggio di parametri:
- *Passaggio per valore:* il valore viene copiato nello stack locale; le modifiche della funzione chiamante non toccano i dati del chiamante.
- *Passaggio per riferimento:* la procedura riceve un riferimento al dato originale, quindi modificandolo si modifica anche il dato del chiamante.
- *Passaggio copy-restore:* la procedura riceve una copia del dato, ma al termine della chiamata il valore modificato viene copiato sul dato originale del chiamante.

L'RPC simula il passaggio per riferimento adottando il *call by copy-restore*: il _client stub_ impacchetta l'intero blocco di dati referenziato nel messaggio di richiesta, il _server stub_ lo ricrea nel proprio heap/stack e, se il server lo modifica, il valore aggiornato viene re-inviato con il reply per sovrascrivere la variabile originale sul client.
Richiede che la dimensione dei dati sia nota a priori e fallisce in presenza di puntatori annidati complessi (es. grafi o liste concatenate con puntatori grezzi), a meno di non serializzare ricorsivamente l'intera struttura.

#### Semantiche di Fallimento

Ricordiamo le semantiche di fallimento:
- *Exactly-once:* la procedura viene eseguita esattamente una volta; è la garanzia ideale ma complessa e onerosa da implementare nei sistemi distribuiti.
- *At-least-once:* la chiamata viene eseguita una o più volte; si applica solo a operazioni *idempotenti*, poiché le ritrasmissioni dovute a timeout possono causare esecuzioni duplicate sul server.
- *At-most-once:* la chiamata viene eseguita al massimo una volta (oppure nessuna, in caso di crash permanente); richiede lato server il tracciamento dello stato e il filtraggio dei duplicati tramite `xid` e memorizzazione della risposta.

Implementare semantiche *Exaclty-once* è molto complesso, ci concentreremo su RPC che implementano *At-least-once* e *At-most-once*.

#### Server Binding

Il _binding_ è il meccanismo con cui il client individua l'endpoint del server (indirizzo IP e porta del processo specifico):
- **Static Binding vs. Dynamic Binding:**
    - **Statico:** l'endpoint è hardcoded nel codice o noto a design time. È semplice e privo di overhead a runtime, ma privo di flessibilità.
    - **Dinamico:** l'endpoint viene risolto a runtime, abilitando ridirezioni automatiche, bilanciamento del carico e tolleranza ai guasti in caso di server replicati. Introduce però un costo aggiuntivo di risoluzione.
- **Le due fasi del binding dinamico:**
    1. **Naming (prima dell'esecuzione):** il client fa riferimento a un nome logico univoco del servizio associato a un'interfaccia astratta (es. `/PaymentService`), senza vincolarsi a un IP fisico.
    2. **Addressing (durante l'esecuzione):** al momento dell'invocazione, il nome logico viene risolto nell'endpoint reale, permettendo al middleware di selezionare una tra le diverse repliche disponibili.
- **Modalità di Addressing:**
    - **Esplicito:** il client trasmette la richiesta in broadcast/multicast sulla rete locale e si aggancia al primo server che risponde.
    - **Implicito:** approccio canonico basato su un registro centrale (es. Portmapper, Consul, ZooKeeper). Il server registra il proprio endpoint all'avvio (passo 1); il client stub interroga il registry tramite lookup (passo 2 e 3); ottenuti IP e porta, il client esegue la vera RPC direttamente verso il server (passo 4). Per evitare overhead a ogni singola chiama.

#### Altre Problematiche

- **RPC Sincrone e Asincrone:** Il primo caso è quello classico e garantito praticamente da tutte le implementazioni di RPC: il chiamante attende il risultato prima di proseguire oltre la chiamata. Il secondo caso è più difficile: il chiamante avvia l'operazione e continua le sue attività. Il risultato è gestito successivamente con gli strumenti previsti dal framework, es. un handler o una conferma della ricezione della richiesta da parte del server. Inoltre ricorda che le RPC che consideriamo usano tutte *comunicazione transiente*, i.e. non forniscono al modello una coda persistente che conserva le richieste aspettando che un destinatario assente torni disponibile.
- **La trasparenza RPC è limitata:** Se è vero che l'interfaccia può assomigliare a una funzione locale, il comportamento non è proprio identico.  Anzitutto in termini di *prestazioni* RPC aggiunge molti costi tra cui codifica/decodifica, copia dei dati, passaggi attraverso SO runtime e soprattutto trasmissione su rete (dei confronti in LAN mostrano valori dell'ordine di 0.1-1ms, contro i ns di una chiamata locale, milioni di volte peggio specie se si va fuori dalla LAN!)
- **Fallimenti:** Il client può non trovare il server, perdere la connessione o non ricevere risposta; e client e server possono fallire indipendentemente.  Anche usare TCP non garantisce che la procedura venga eseguita e che il client ne conosca il risultato, dato che *l'affidabilità del trasporto non risolve da sola i guasti applicativi*.
- **Concorrenza e replicazione:** Non tutti i framework gestiscono automaticamente richieste concorrenti/repliche del server, alcuni server possono elaborare una sola richiesta per volta.
- **Sicurezza:** Il middleware offre protezioni adeguate? Es. Autenticazione (client e server sono chi dicono di essere), Autorizzazione (il client può eseguire la procedura richiesta?), Confidenzialità (un osservatore può leggere i msg?), Integrità (si riescono a rilevare alterazioni dei msg?) e *protezione da replay attacks*
- (un attaccante può intercettare e ritrasmettere un msg valido?)


## IDL

Come facciamo ora a generare *client-server stub?* Ricordiamo che molti linguaggi non offrono supporto nativo per RPC. Una soluzione a questo problema è l'uso delle IDL (Interface Definition Language).

**DEF:** IDL è uno strumento che permette agli sviluppatori di descrivere le signatures delle procedure remote in modo del tutto indipendente dall'architettura hardware e dal linguaggio di programmazione. A partire dal file di specifica, il compilatore crea automaticamente gli stub, i quali incorporano:
- il codice di *marshalling*;
- il codice di *unmarshalling*;
- la logica di *trasporto di rete*;

Le definizioni somigliano a prototipi o interfacce di funzioni `C/Java`:
```Apache Thrift IDL
service KeyValueStore {
    i32 put(1: string key, 2: string value),
    string get(1: string key),
}
```

![[idlcompilechain.png]]

Nel diagramma si può osservare l'intero flusso di compilazione e integrazione.
Il developer scrive *la definizione IDL*, il *codice client che invoca il servizio* e *le funzioni server che realizzano le operazioni*.  
Il compilatore IDL genera il supporto necessario secondo il framework: client e server stub, codice di conversione dei dati e header al supporto di comunicazione.
Il codice applicativo viene compilato assieme al supporto generato e alle librerie necessarie.  

## Sun RPC

**Sun RPC** (noto anche come **ONC RPC** -  _Open Network Computing RPC_) è il sistema RPC storico sviluppato da Sun Microsystems negli anni '80.

Le interfacce dei servizi sono definite tramite **XDR** - *eXternal Data Representation*. 
Utilizza un file di interfaccio `.x` dove vengono definite le interfacce dei servizi. Il compilatore `rpcgen` elabora il file `.x` e genera automaticamente:
- il file header C (`.h`) contentente le firme delle procedure;
- Le funzioni XDR di marshalling e unmarshalling;
- Il client stub `_clnt.c` e il server stub `_svc.c`.

XDR usa in particolare un *formato binario con typing implicito*, per cui vengono trasmessi i valori dei parametri senza indicarne il tipo. Ciò è possibile perché _client e server conoscono già i tipi grazie alla definizione dell'interfaccia IDL_.

#### Come definire una procedura

`square.x`
```C
struct square_in { /* input argument */
	long arg1;
}

struct square_out { /* output argument */
	long res1;
}

program SQUARE_PROG {
	version SQUARE_VERS {
		square_out SQUAREPROC(square_in) = 1; /* proc. nr. 1 */
	} = 1; /* version number */
} = 0x31230000;
```

- Ogni procedura remota accetta un *un solo parametro di input* e restituisce *un solo valore di output*. Se occorre passare più argomenti o ritornare più valori essi vanno incapsulati all'interno di una `struct`.
- Per convenienza, gli identificatori definiti nel file IDL si scrivono in *maiuscolo*.
- A ogni entità viene assegnato un identificatore numerico univoco.

Dopo aver compilato il file `.x` con `rpcgen -C square.x`, lo sviluppatore deve scrivere solo il codice applicativo reale:

- **Lato client (`square_client.c`):** scrive il `main()` per raccogliere l'input utente, localizzare il server, effettuare il binding ed eseguire la chiamata remota.
- **Lato server (`square_server.c`):** implementa solo la funzione di calcolo (`squareproc_1_svc`). **Non c'è un `main()` sul server**, perché il loop di ricezione, il binding sul portmapper e il dispatch delle chiamate vengono generati automaticamente da `rpcgen` all'interno dello skeleton (`square_svc.c`).

`square_server.c`
```C
#include <stdio.h>
#include <rpc/rpc.h>
#include "square.h" /* generated by rpcgen */
square_out *squareproc_1_svc(square_in *inp, struct svc_req *rqstp) {
	static square_out out;
	out.res1 = inp->arg1 * inp->arg1;
	return(&out);
}
```

- Il nome della procedura remota diventa `<nome_procedura_minuscolo>_<versione>_svc`.
- Sia i parametri in ingresso (`square_in *inp`) sia il valore di ritorno (`square_out *`) utilizzano puntatori.
- Il risultato restituito *deve essere dichiarato `static`*. Poiché viene ritornato l'indirizzo di memoria (`&out`), se la variabile fosse allocata localmente sullo stack verrebbe deallocata al termine della funzione, corrompendo la risposta prima che lo stub del server riesca a serializzarla per trasmetterla sulla rete.

`square_client.c`
```C
#include <stdio.h>
#include <rpc/rpc.h>
#include "square.h" /* generated by rpcgen */
// execute: ./square_client <server> <integer>

int main(int argc, char **argv) {
	CLIENT *clnt;
	char *host;
	square_in in;
	square_out *result;
	if (argc != 3) {
		printf("usage: client <hostname> <integer-value>\n");
		exit(1);
	}
	host = argv[1];
	clnt = clnt_create(host, SQUARE_PROG, SQUARE_VERS, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror(host);
		exit(1);
	}
	in.arg1 = atol(argv[2]);
	if ((result = squareproc_1(&in, clnt)) == NULL) {
		printf("%s", clnt_sperror(clnt, argv[1]));
		exit(1);
	}
	printf("result: %ld\n", result->res1);
	exit(0);
}
```
All'interno del client viene qundi creato il handler, che ha come paramentri
```
CLIENT *clnt_create(char *host, unsigned long prog,
					unsigned number vers, char *proto)
```

Crea la struttura `CLIENT` configurata per usare il protocollo di trasporto specificato (`"tcp"` o `"udp"`).
Se fallisce (restituisce `NULL`), l'errore viene stampato con `clnt_pcreateerror(host)`

Invoca poi la procedura la cui firma è generata dal client stub seguendo il pattern `<nome_procedura_minuscolo>_<versione>`.


![[sunrpc.png]]

**Come fa il client a sapere a quale porta connettersi?**
- Il server, avviandosi su una porta casuale o assegnata dal sistema operativo, contatta il proprio `portmapper` locale (sulla porta 111) per registrare la corrispondenza tra `program number`, `version number`, protocollo di trasporto (`tcp`/`udp`) e il rispettivo numero di porta.
- Quando il client invoca `clnt_create()`, il client stub invia una richiesta di interrogazione (_lookup_) al `portmapper` dell'host remoto (sempre sulla porta 111) specificando la tupla `<program, version, protocol>`.
- Il `portmapper` legge la propria tabella interna e invia indietro al client stub *il numero di porta* su cui il server RPC è in ascolto.
- Il *client stub* prende quel numero di porta, crea la connessione/socket diretta verso tale porta ed invia la richiesta RPC effettiva (`squareproc_1`) direttamente al server stub.

![[sunrpcbind.png]]

| **Caratteristica**              | **Dettaglio / Implementazione**                                                                                                                                                                                                                                            |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Procedure Remote**            | • Supporta più procedure nello stesso programma RPC e più versioni dello stesso programma.<br>• Vincolo di un singolo parametro di input e un singolo valore di ritorno (richiede `struct` per più valori).<br>• Passaggio dei parametri gestito tramite **copy-restore**. |
| **Indipendenza dal Trasporto**  | Supporta la selezione di **TCP** o **UDP** a runtime (tramite parametro in `clnt_create`).                                                                                                                                                                                 |
| **Modello di Sincronizzazione** | Chiamate **sincrone e bloccanti** (il client resta sospeso fino all'arrivo del reply).                                                                                                                                                                                     |
| **Concorrenza**                 | **Nessuna concorrenza di default** (il server gestisce le richieste in modo sequenziale/single-threaded).                                                                                                                                                                  |
| **Codice degli Stub**           | Codice sorgente C esplicito e visibile, generato automaticamente dal compilatore **`rpcgen`**.                                                                                                                                                                             |
| **Semantica di Fallimento**     | **At-least-once** basata su ritrasmissione dopo timeout del client, senza deduplicazione lato server.                                                                                                                                                                      |
| **Server Binding**              | Risoluzione dinamica degli endpoint tramite il demone **port mapper** (porta 111).                                                                                                                                                                                         |
| **Sicurezza**                   | Autenticazione non presente nel protocollo base, integrata tramite **Secure RPC** (es. AUTH_DES/AUTH_SYS).                                                                                                                                                                 |

**NOTA:** Client e Server non devono per forza essere scritti in C. Poiché Sun RPC fa uso di IDL per la definizione di interfacce e poichè i dati viaggiano in formato XDR, client e server possono essere scritti in linguaggi diversi, infatti, finché un programma rispetta il formato dei byte XDR e la struttura dei messaggi ONC RPC (Program, Version, Procedure, XID), il server non ha alcun modo di sapere (né gli interessa) in quale linguaggio sia scritto il client, e viceversa.

## Java RMI

Java RMI - **Remote Methos Invocation** si può definire come una RPC di *seconda generazione*, mentre l'RPC classico invoca procedure procedurali/C-like su un host remoto, RMI consente a un oggetto in esecuzione all'interno di una *Java Virtual Machine (JVM)* di invocare metodi su oggetti situati in un'altra JVM (sulla stessa macchina o su host remoti distinti).

Si ha una netta separazione tra interfaccia e implementazione:
- *Remote interface* definisce i prototipi dei metodi invocabili da altre JVM.
- *Remote object* è l'istanza concreta della classe che implementa l'interfaccia remota. Lo stato interno dell'oggetto non è distribuito: risiede interamente nella memoria della JVM del server.

Come in Sun RPC, anche Java RMI sfrutta il proxy patter, infatti
- Lato *client*, un oggetto *stub* (proxy locale) espone l'interfaccia remota e serializza la chiamata.
- Lato *server*, la richiesta viene ricevuta da un dispatcher (lo *skeleton* in JDK 1.1, sostituito nativamente dal runtime RMI e reflection a partire da JDK 1.2) che invoca il metodo sull'oggetto reale.

`EchoInterface.java`
```Java
import java.rmi.Remote; 
import java.rmi.RemoteException; 

public interface EchoInterface extends Remote { 
	String getEcho(String echo) throws RemoteException; 
}
```

Ogni interfaccia deve estendere `java.rmi.Remote`, questo segna alla JVA che i metodi all'interno sono invocabili dall'esterno. Inoltre, ogni metodo ha l'obbligo di lanciare un'eccezione in modo tale che il client che invoca il metodo è forzato a gestire a runtime i possibili errori.

Al contrario di Sun RPC, che usa XDR per il formato dei dati, Java RMI sfrutta nativamente la Java Object Serialization  `writeObject/ReadObject`, che converte lo stato degli oggetti in flussi di byte e viceversa. Non serve quindi nessun IDL separato. Nasconde l'eterogeneità dell'hardware, ma non *quella linguistica*, sia client che server devono essere scritti in Java.

Il passaggio dei paramentri in Java RMI dipende da che tipo di dato viene passato.
- Per i *paramentri primitivi*, quindi `int, char, float...` vengono passati per valore.
- Gli *oggetti ordinari serializzabili* (cioè quelli che implementano `Serializble`) vengono passati anche essi per valore tramite serializzazione.
- Gli *oggetti remoti* vengono invece passati per *riferimento*, si invia solo un riferimento all'oggetto ("fisicamente" rimane sulla JVM originaria) contenente le info necessarie per identificarlo e contattarlo (ip, porta, id dell'oggetto, etc...)

**Esempio:**
`EchoRMIServer.java`
```Java
import java.rmi.RemoteException;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;

public class EchoRMIServer extends UnicastRemoteObject
        implements EchoInterface {
    public EchoRMIServer() throws RemoteException {
        super();
    }
    // Implement remote method
    @Override
    public String getEcho(String s) throws RemoteException {
        return s;
    }

    public static void main(String[] args) {
        try {
            // Create an instance of echo server
            EchoRMIServer serverRMI = new EchoRMIServer();
            // Start RMI registry on port 1099
            Registry reg = LocateRegistry.createRegistry(1099);
            // Register remote object
            reg.bind("EchoService", serverRMI);
            System.out.println("Echo RMI Server ready");
        } catch (Exception e) {
            System.err.println("EchoRMIServer exception:");
            e.printStackTrace();
        }
    }
}
```

**Come funziona**
1. `extends UnicastRemoteObject`: permette di esportare l'oggetto remoto, rendendolo disponibile a ricevere invocazioni RMI.
2. `implements EchoInterface`: obbliga la classe a implementare i metodi definiti nell'interfaccia remota.
3. `super()`: richiama il costruttore di `UnicastRemoteObject`, che esporta automaticamente l'oggetto remoto.
4. `LocateRegistry.createRegistry(1099)`: crea e avvia un registro RMI sulla porta 1099.
5. `reg.bind("EchoService", serverRMI)`: associa il nome `"EchoService"` all'oggetto remoto, permettendo ai client di recuperare uno stub attraverso il registry.

`EchoRMIClient.java`
```Java

import java.rmi.Naming;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EchoRMIClient {
    public static void main(String[] args) {
        try {
            // Connect to remote RMI service
            EchoInterface service = (EchoInterface) 
            Naming.lookup("rmi://localhost:1099/EchoService");
            // Interact with user
            BufferedReader stdIn = new BufferedReader(
                new InputStreamReader(System.in)
            );
            String message, echo;
            System.out.print("Message? ");
            message = stdIn.readLine();
            // Call remote method
            echo = service.getEcho(message);
            System.out.println("Echo: " + echo + "\n");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

**Come Funziona**
Per poter invocare un metodo remoto, il client deve innanzitutto ottenere lo stub dell'oggetto remoto, ovvero un oggetto locale che funge da intermediario tra il client e il server.
Questo avviene attraverso l'istruzione:
```Java
EchoInterface serverRMI = (EchoInterface) Naming.lookup("[EchoService](rmi://localhost:1099/EchoService)");
```

In particolare:
- `Naming.lookup("EchoService")` interroga il registry RMI cercando un oggetto registrato con il nome `EchoService` e restituisce un riferimento remoto, rappresentato localmente da uno stub.
- `(EchoInterface)` effettua un cast del riferimento restituito all'interfaccia remota, permettendo al client di invocare i metodi definiti da quest'ultima.
- `serverRMI` rappresenta quindi lo stub lato client, mentre la variabile con lo stesso nome utilizzata nel server faceva riferimento all'oggetto effettivo che implementava i metodi remoti.

Questo evidenzia un aspetto della trasparenza della distribuzione: una volta ottenuto lo stub, il client può invocare i metodi remoti utilizzando una sintassi analoga a quella delle chiamate locali, senza dover gestire esplicitamente la comunicazione di rete.
Una volta ottenuto lo stub, il client effettua la chiamata al metodo remoto come se fosse una chiamata normale.

È importante sottolineare che la chiamata RMI è *sincrona e bloccante*: il thread del client rimane in attesa fino a quando il server non restituisce il risultato oppure la chiamata termina con un'eccezione.

**Flusso completo di una chiamata RMI**
Il funzionamento complessivo può essere riassunto nei seguenti passaggi:
1. Registrazione dell'oggetto remoto: il server crea ed esporta l'oggetto remoto, registrandolo nel registry RMI attraverso un nome simbolico, nel nostro caso `EchoService`.
2. Ricerca dell'oggetto remoto: il client esegue `Naming.lookup("EchoService")` e ottiene lo stub associato all'oggetto remoto.
3. Invocazione del metodo: il client richiama `getEcho(message)` sullo stub. Quest'ultimo prepara la richiesta, includendo le informazioni necessarie a identificare il metodo e i suoi parametri, serializzando i dati quando necessario e inviando la richiesta al server.
4. Esecuzione sul server: il runtime RMI del server riceve la richiesta, deserializza i parametri e invoca il metodo `getEcho(message)` sull'oggetto remoto effettivo. Nelle versioni meno recenti di Java RMI queste operazioni erano associate a uno skeleton esplicito, mentre nelle implementazioni moderne vengono gestite direttamente dal runtime RMI. Al termine dell'esecuzione, il server prepara una risposta contenente il risultato oppure un'eccezione.
5. Restituzione del risultato: lo stub lato client riceve la risposta, deserializza i dati e restituisce il risultato al programma chiamante oppure propaga l'eccezione ricevuta.

| Caratteristica                       | Descrizione                                                                                                                                                                            |
| ------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Trasparenza di accesso               | Le chiamate remote hanno una sintassi simile a quelle locali, ma i fallimenti di rete rimangono visibili.                                                                              |
| Serializzazione                      | Utilizza la serializzazione Java per trasferire parametri e risultati tra client e server. Gli oggetti passati per valore devono essere serializzabili.                                |
| Generazione degli stub               | Non richiede un compilatore IDL. Gli stub vengono generati dinamicamente dal runtime RMI nelle versioni moderne di Java.                                                               |
| Tipo di chiamata                     | Le invocazioni remote sono sincrone e bloccanti: il client attende il risultato o un'eccezione.                                                                                        |
| Concorrenza                          | Il server può gestire più richieste contemporaneamente. Il codice che accede a risorse condivise deve essere thread-safe, ad esempio usando `synchronized`.                            |
| Semantica dei fallimenti             | At-most-once: una singola invocazione remota non viene eseguita più di una volta dal meccanismo RMI. In caso di errore, il client potrebbe non sapere se il metodo sia stato eseguito. |
| Binding del server                   | Utilizza l'RMI Registry per associare nomi simbolici agli oggetti remoti, consentendo ai client di recuperarne gli stub.                                                               |
| Gestione delle eccezioni             | I metodi remoti devono dichiarare `RemoteException` per gestire possibili errori di comunicazione.                                                                                     |
| Sicurezza                            | Per cifrare e proteggere le comunicazioni è possibile configurare socket factory basate su TLS. La cifratura non è garantita automaticamente dalla configurazione RMI standard.        |
| Distributed Garbage Collection (DGC) | Gestisce il ciclo di vita degli oggetti remoti attraverso riferimenti con scadenza (lease), che vengono periodicamente rinnovati dai client.                                           |

## Python RPyC

In Python ci sono varie implementazioni di RPC. Consideriamo RPyC perché permette di mostrare sia l'invocazione dei metodi remoti sia le chiamate asincrone di *callback*. Come in Java RMI, anche qui client e server devono essere scritti in Python.

Anche qui l'obiettivo è la *trasparenza all'accesso*: unvocare un metodo remoto deve avere una sistassi simile a quella dell'invocazione di un metodo locale. Python facilita questo approccio in quanto:
- Non serve dichiarare i tipi dei parametri e del risultato, la gestione è runtime in quanto *dinamicamente tipicizzato*.
- *Runtime introspection:* tramite il module `inspect` è possibile esaminare oggetti e metodi a runtime.

Vediamo ora nel dettaglio le carratestiche di `RPyC`.
- L'accesso agli oggetti remoti avviene attraverso un *proxy dinamco*, chiamato `netref` che rappresenta un oggetto remoto.
- I proxy sono creati a runtime, quindi non c'è la necessità di IDL per la definizione del servizio.
- *Simmetria nella comunicazione:* rispetto ai modelli tradizionali di RPC, in RPyC, entrambe le parti possono invocare metodi remoti sull'altra. Questo permette di implementare meccanismi di *callback remote*, in cui il server richiama un metodo sul client.
- *Chiamate sincrone e ed asincrone*;
- Per quanto riguarda la *sicurezza*, RPyC prevede meccanismi per controllare l'accesso remoto. Solo i metodi dichiarati come `exposed` potranno essere acceduti, inoltre è possibile stabilire una connessione sicura tramite TLS.

**Server e Client:**

RPyC mette a disposizione diverse implementazioni del server, che si distinguono principalmente per il modello di concorrenza utilizzato per gestire le connessioni e le richieste dei client.

|Implementazione|Descrizione|
|---|---|
|`ThreadedServer`|Crea un thread dedicato per ogni connessione client, permettendo di gestire più connessioni contemporaneamente.|
|`OneShotServer`|Gestisce una singola connessione e termina dopo la sua chiusura.|
|`ThreadPoolServer`|Utilizza un pool di thread per gestire le richieste, limitando il numero di thread impiegati.|
|`ForkingServer`|Crea un processo separato per ogni connessione, isolando l'esecuzione dei diversi client|

Quando viene stabilita la connessione, il client può accedere a `conn.root`, che rappresenta un netref dell'oggetto radice del servizio remoto.

Questo oggetto costituisce il punto di accesso ai metodi e agli attributi esposti dal server.

**Passaggio di parametri**

RPyC utilizza internamente un meccanismo di marshalling (serializzazione) per trasferire dati e riferimenti agli oggetti tra processi remoti.
- Il passaggio per valore viene utilizzato principalmente per i tipi built-in immutabili di Python, come `int`, `float`, `str`, `bool` e alcuni tipi di tuple.
- Il passaggio per riferimento viene utilizzato per gli oggetti che RPyC non trasferisce per valore, tra cui molti oggetti mutabili, come liste, dizionari e file aperti.

**RPyC Service**

In RPyC, ogni connessione permette di accedere a un servizio remoto (Service), che definisce l'insieme delle operazioni e degli oggetti accessibili da un client.

Il servizio stabilisce quindi una politica di esposizione, determinando quali funzionalità possono essere invocate da remoto e quali rimangono interne al server.

Un servizio RPyC viene definito attraverso una classe Python che eredita da `rpyc.Service`.

```Python
import rpyc

class CalculatorService(rpyc.Service):
    def exposed_add(self, a, b):
        return a + b

    def exposed_div(self, a, b):
        return a / b
```

A differenza di Java RMI, non è necessario definire un'interfaccia remota separata: l'interfaccia del servizio è implicita, cioè determinata direttamente dai metodi e dagli oggetti esposti dalla classe.

Il client accede al servizio attraverso `conn.root`, un netref che rappresenta l'istanza del servizio presente sul server.

Per impostazione predefinita, un metodo definito in un servizio può essere reso accessibile da remoto anteponendo il prefisso `exposed_` al suo nome

Il client potrà invocarlo semplicemente attraverso:
```Python
conn.root.add(4, 7)
```
Il prefisso `exposed_` non compare nella chiamata del client, perché RPyC gestisce automaticamente la corrispondenza tra `add` ed `exposed_add`.

**Esempio**

`server.py`
```Python

import rpyc
from rpyc.utils.server import ThreadedServer

class CalculatorService(rpyc.Service):

    def exposed_add(self, a, b):
        return a + b

    def exposed_div(self, a, b):
        return a / b

    def exposed_fib(self, n):
        seq = []
        a, b = 0, 1
        while a < n:
            seq.append(a)
            a, b = b, a + b
        return seq

    def foo(self):
        print("foo")

if __name__ == "__main__":
    t = ThreadedServer(CalculatorService, port=18861)
    print("Service started on port 18861")
    t.start()
```

`client.py`
```Python

import rpyc

conn = rpyc.connect("localhost", 18861)

# RPC for add
x = conn.root.add(4, 7)
assert x == 11
# RPC for div
try:
    result = conn.root.div(4, 2)
    print("Division result:", result)
    conn.root.div(4, 0)
except ZeroDivisionError:
    print("Division by zero error")

# RPC for fib
print(conn.root.fib(1000))
conn.close()
```

**RPyC Asincrono**

RPyC supporta le chiamate remote asincrone, permettendo al client di avviare un'operazione sul server senza dover attendere immediatamente il risultato.

1. *Future Pattern:* il client avvia un'operazione remota e recupera il risultato successivamente.
2. *Callback asincrone:* il client fornisce al server una funzione che quest'ultimo potrà invocare per notificare eventi, come la modifica di un file.

RPyC permette di trasformare un metodo remoto in una versione asincrona utilizzando `rpyc.async_()`. 
`server.py`
```Python
def exposed_slow_add(self, a, b):
    time.sleep(3)
    return a + b
```

`client.py`
```Python
slow_add = rpyc.async_(conn.root.slow_add)

res = slow_add(4, 7)

# Il client può eseguire altre operazioni
print(res.ready)

res.wait()
print(res.value)
```

In questo caso, `slow_add(4, 7)` restituisce rapidamente un oggetto `AsyncResult`, che rappresenta il risultato futuro della chiamata.
Il risultato non è necessariamente già disponibile, ma potrà essere recuperato successivamente.
L'oggetto `AsyncResult` mette a disposizione diverse operazioni:

|Operazione|Significato|
|---|---|
|`res.ready`|Indica se il risultato è disponibile, senza bloccare il chiamante.|
|`res.wait()`|Blocca il chiamante fino al completamento della chiamata.|
|`res.value`|Restituisce il risultato; attende se necessario e propaga eventuali eccezioni.|
|`res.set_expiry(t)`|Imposta un limite temporale per l'attesa del risultato.|
|`res.add_callback(f)`|Registra una funzione da eseguire quando il risultato diventa disponibile.|

**Callback**

Vediamo ora un esempio più complesso di asincronia riguardante monitoraggio delle modifiche di un file tramite *callback* e in particolare con un pattern *observer*.

Il funzionamento generale è il seguente: il client chiede al server di monitorare un file, il server ne controlla periodicamente lo stato e quando rileva una modifica chiama una funzione definita sul client, e il client stampa la notifica.  
La funzione richiamata si chiama *callback*.

In particolare quello che fa il client è passare al server un *riferimento alla propria funzione*, di modo che il server possa invocarla quando necessario.  
Da qui si vede bene la simmetria di RPyC: la comunicazione non si limita in chiamate dal client al server.

A questo si collega il pattern *observer*, dove il client interessato a un evento vuole riceve una notifica quando l'evento si verifica.  
Vediamo ora un esempio dove viene creato un monitor dedicato per ogni richiesta di monitoraggio: non si ha un solo monitor che invia lo stesso evento a tutti i client.

`server.py`
```Python

import rpyc
import os
import time
from threading import Thread
from rpyc.utils.server import ThreadedServer


class FileMonitorService(rpyc.Service):
    class exposed_FileMonitor(object):
        def __init__(self, filename, callback, interval=1):
            self.filename = filename
            self.interval = interval
            self.last_stat = None
            self.callback = rpyc.async_(callback)
            self.active = True
            self.thread = Thread(target=self.work)
            self.thread.start()

        def exposed_stop(self):
            self.active = False
            self.thread.join()

        def work(self):
            while self.active:
                stat = os.stat(self.filename)
                if self.last_stat is not None and 
                self.last_stat != stat:
                    self.callback(self.last_stat, stat)

                self.last_stat = stat
                time.sleep(self.interval)


if __name__ == "__main__":
    # Spawn a thread for each connection
    server = ThreadedServer(
        FileMonitorService,
        port=18871
    )

    server.start()
```

La classe esterna `class FileMonitorService(rpyc.Service)` definisce il servizio, al suo interno si espone la classe `class exposed_FileMonitor(object)` che rappresenta il monitor del file. Esporla serve a far sì che il client possa creare un'istanza di monitor sul server ottentendo solo un `netref` all'oggetto istanziato sul server.

Il costruttore riceve `filename` come percorso del file da monitorare sul server, `callback` riferimento alla funzione client da invocare quando il file cambia, `interval` come tempo di polling tra un controllo e l'altro (default 1 secondo).

Con `self.callback = rpyc.async_(callback)` si prepara la callback asincrona, per cui quando il server la invoca non deve aspettare che la funzione sul client termini prima che possa proseguire.

Il costruttore avvia poi un thread `self.thread = Thread(target=self.work)` e `self.thread.start()` per eseguire il metodo `work()`, che si occupa del monitoraggio.

Il metodo `exposed_stop()` è esposto perché il client deve poter fermare il monitoraggio quando vuole.

`client.py`
```Python
import rpyc
import time
import os

# File to monitor
filename = "/tmp/floop.bloop"

if os.path.exists(filename):
    os.remove(filename)

# Open file to monitor
f = open(filename, "wb", buffering=0)

# Connect to RPyC server that monitors file changes
conn = rpyc.connect("localhost", 18871)

# Start background thread that handles incoming asynchronous events
# from server, without blocking the client
bgsrv = rpyc.BgServingThread(conn)

# Define the callback function on client side
# Called by server whenever the monitored file changes
def on_file_changed(oldstat, newstat):
    print("\nfile changed")
    print(f"    old stat: {oldstat}")
    print(f"    new stat: {newstat}")

# Create the remote file monitor and pass filename and callback
filemon = conn.root.FileMonitor(filename, on_file_changed)

# Wait for file monitor to check the initial file state
time.sleep(2)

# Change file size
print("\n---> Change file")
f.write(b"loop")
time.sleep(2)

# Change file size again
print("\n---> Change file again")
f.write(b"groop")
time.sleep(2)

# Cleanup
f.close()
filemon.stop()
bgsrv.stop()
conn.close()

```

La funzione `on_file_change(oldstat, newstat)` è la callback che il server invoca quando rileva una modifica del file. Il corpo della callback resta sempre sul client!

Con questa riga
`filemon = conn.root.FileMonitor(filename, on_file_change)`
il client richiede la creazione di un oggetto monitor sul server, passandogli il percorso del file e un riferimento alla callback. Restituisce in `filemon` un netref che rappresenta l'oggetto monitor remoto sul server, quindi per ogni client si definisce un monitor dedicato.

|Caratteristica|Descrizione|
|---|---|
|Trasparenza di accesso|Permette di invocare metodi remoti con una sintassi simile a quella locale, attraverso proxy dinamici chiamati netref.|
|IDL e Stub|Non richiede IDL né generazione preventiva degli stub. I netref vengono creati dinamicamente a runtime.|
|Service Registry|Opzionale. Il client può connettersi direttamente al server conoscendone indirizzo IP e porta.|
|Esposizione di metodi e classi|Solo i metodi e le classi esplicitamente esposti sono normalmente accessibili da remoto, secondo la configurazione del servizio.|
|Chiamate sincrone|Il client rimane bloccato fino alla ricezione del risultato o di un'eccezione.|
|Chiamate asincrone|Tramite `rpyc.async_()` è possibile effettuare chiamate non bloccanti, ottenendo un oggetto `AsyncResult` secondo il Future Pattern.|
|Comunicazione simmetrica|Client e server possono invocare reciprocamente metodi remoti, consentendo l'utilizzo di callback remote.|
|Concorrenza|Supporta diversi modelli di concorrenza, come `ThreadedServer` e `ThreadPoolServer`. L'accesso allo stato condiviso richiede sincronizzazione esplicita, ad esempio tramite `Lock`.|
|Semantica dei fallimenti|Best effort: non garantisce automaticamente il completamento delle chiamate remote. Non prevede retry automatici né deduplicazione delle richieste lato server.|
|Gestione degli errori|Le applicazioni devono gestire esplicitamente eccezioni, disconnessioni e possibili esiti incerti delle operazioni remote.|

## Go RPC

In fornisce supporto built-in per RPC. Il pacchetto `net/rpc` fa parte della libreria standand.

Il servizio è implementato sempre secondo il pattern *proxy client-server*.
Il meccanismo è *type-safe* in quanto i metodi esposti devono rispettare un firma precisa e utilizzare tipi compatibili con il sistema di serializzazione.

Come protocolli di trasporto si può scegliere tra TCP e HTTP. Permette inoltre una gestione concorrente delle richieste provenienti da più client. Per quanto riguarda la serializzazione, utilizza di default il formato `gob` di Go per la codifica e decodifica dei dati. Inoltre, non richiede un file IDL per la definizione dell'interfaccia dei servizi.

Per definire un servizio RPC in Go, bisogna definire una *struct* che identifica il servizio esposto, i cui metodi saranno esposti ai clienti. Ciascun metodo deve rispettare la seguente firma:
```Go
func (t* T) Method(args ArgType, reply *ReplyType) error
```
Affiché un metodo (e tipo di dato) sia esposto ai client, la prima lettera del nome deve essere in *maiuscolo*. Ogni metodo deve avere in ingresso 2 parametri:
- `args ArgType` generalmente una struct che racchiude molteplici parametri da inviare al server;
- `reply *ReplyType` è un puntatore, generalmente ad una struct che racchiude i dati di ritorno.
Infine, ogni metodo deve ritornare un errore (o `nil` se non ci sono errori).

`Calculator.go`
```Go
package server

import "errors"

type Args struct {
	A, B int
}

type Quotient struct {
	Quo, Rem int
}

type Arith int

func (t *Arith) Multiply(args *Args, reply *int) error {
	*reply = args.A * args.B
	return nil
}

func (t *Arith) Divide(args *Args, quo *Quotient) error {
	if args.B == 0 {
		return errors.New("divide by zero")
	}
	quo.Quo = args.A / args.B
	quo.Rem = args.A % args.B
	return nil
}
```

Una volta definito un servizio RPC attraverso una `struct` e i relativi metodi esportati, è necessario registrare il servizio e avviare un server in grado di ricevere le richieste remote dei client.

Il package `net/rpc` fornisce le funzionalità necessarie per registrare i servizi, accettare le connessioni e gestire le chiamate RPC

Per rendere accessibili da remoto i metodi di un oggetto, bisogna registrarlo presso il server RPC.
```Go
func (server *Server) Register(rcvr any) error

func (server *Server) RegisterName(name string, rcvr any) error
```

Entrambi ricevono un parametro `rcvr` (receiver), che rappresenta l'oggetto da registrare, generalmente un puntatore a una `struct`.
Il tipo `any` è un alias di `interface{}` e permette di passare un valore di qualsiasi tipo.

- `Register()`: permette di registrare un servizio utilizzando automaticamente il nome del suo tipo concreto.
- `RegisterName()`: Permette di specificare esplicitamente il nome con cui registrare il servizio.
```Go
// server
rpc.Register(Calculator)

rpc.Register("MathService", Calculator)

// client
Calculator.Add
// oppure
MathService.Add
```

Dopo aver registrato il servizio, bisogna creare un listener di rete per ricevere le connessioni dei client.
```Go
func Listen(network, address string) (Listener, error)
```
È importante osservare che `net.Listen()` non accetta direttamente le connessioni e non esegue metodi RPC: prepara solamente il punto di ascolto.

Una volta creato il listener, il server deve iniziare ad accettare le connessioni.
```Go
rpc.Accept(listener)
```
La funzione `rpc.Accept()` utilizza il listener per accettare continuamente nuove connessioni e gestire le richieste RPC.

**Nota:** Il package `net/rpc` supporta la gestione concorrente delle richieste.
In particolare, `Accept()` avvia una goroutine per ogni connessione accettata. All'interno di ciascuna connessione, il runtime RPC può gestire più richieste contemporaneamente.

![[goRPC.svg | 600]]

**Nota:** `rpc.Accept(listener)` è una funzione bloccante: continua ad accettare connessioni e normalmente non restituisce il controllo finché il listener non viene chiuso o si verifica un errore che interrompe il ciclo.

Se il programma principale deve eseguire altre operazioni contemporaneamente, è possibile avviarla in una goroutine:
```Go
go rpc.Accept(listener)

// Il main può continuare a eseguire altre operazioni
```

`server.go`
```Go
// HTTP
arith := new(Arith)
rpc.Register(arith)
rpc.HandleHTTP()
l, err := net.Listen("tcp", ":1234")
if err != nil {
	log.Fatal("listen error:", err)
}
go http.Serve(l, nil)
```

```Go
// TCP
arith := new(Arith)
rpc.Register(arith)
l, err := net.Listen("tcp", ":1234")
if err != nil {
	log.Fatal("listen error:", err)
}
rpc.Accept(listener)
```

Una volta avviato il server RPC, il client deve stabilire una connessione e invocare i metodi remoti precedentemente registrati.

Il package `net/rpc` mette a disposizione tre operazioni principali:
##### 1. `Dial()`: stabilisce una connessione con il server RPC.

```Go
func Dial(network, address string) (*Client, error)
```
La funzione riceve due parametri:

- `network`: protocollo di trasporto utilizzato, ad esempio `"tcp"`.
- `address`: indirizzo e porta del server, ad esempio `"localhost:1234"`.

Restituisce un puntatore a `rpc.Client`, attraverso il quale sarà possibile invocare i metodi remoti, oppure un errore se la connessione non può essere stabilita.

```Go
client, err := rpc.Dial("tcp", "localhost:1234")
if err != nil {
    log.Fatal(err)
}
defer client.Close()
```

**Nota:** Se il server utilizza RPC su HTTP, bisogna invece utilizzare `rpc.DialHTTP()`.

##### 2. `Call()`: esegue una chiamata RPC sincrona e bloccante.

```Go
func (client *Client) Call(
    serviceMethod string,
    args any,
    reply any,
) error
```

A questo punto il client può eseguire una chiamata ad uno dei metodi esposti dal server.
```Go
// chiama sincrona
args := &server.Args{7,8}
var reply int
err = client.Call("Arith.Multiply", args, &reply)
if err != nil {
	log.Fatal("arith error:", err)
}
fmt.Printf("Arith: %d*%d=%d", args.A, args.B, reply)
```


##### 3. `Go()`: esegue una chiamata RPC asincrona, permettendo al client di continuare la propria esecuzione.

Go supporta anche le chiamate RPC asincrone attraverso il metodo `Go()` del package `net/rpc`.
```Go
func (client *Client) Go(
    serviceMethod string,
    args any,
    reply any,
    done chan *Call,
) *Call
```

A differenza di `Call()`, il metodo `Go()` non attende il completamento della chiamata remota, ma restituisce immediatamente un puntatore a una struttura `rpc.Call`
```Go
type Call struct {
    ServiceMethod string
    Args          any
    Reply         any
    Error         error
    Done          chan *Call
}
```

Il campo `Done` è un canale utilizzato per notificare il completamento della chiamata.

```Go
//Chiamata asincrona
quotient := new(Quotient)
divCall := client.Go("Arith.Divide", args, quotient, nil)
replyCall := <-divCall.Done

if replyCall.Error != nil {
    log.Fatal(replyCall.Error)
}

fmt.Println("Result %v:", quotient)
```

l funzionamento è il seguente:
1. Il client invoca `client.Go()`, avviando la richiesta RPC.
2. `Go()` restituisce immediatamente un oggetto `*rpc.Call`, senza attendere la risposta.
3. Il client può continuare a eseguire altre operazioni.
4. Quando il server completa la richiesta, il runtime RPC inserisce la struttura `*Call` nel canale `Done`.
5. Il client recupera la notifica attraverso `<-divCall.Done` e può leggere il risultato.

L'operazione `<-divCall.Done` è bloccante se la chiamata non è ancora terminata.

Se il parametro `done` passato a `Go()` è `nil`, il package crea automaticamente un canale buffered. È anche possibile fornire un proprio canale buffered per gestire le notifiche.

Il package `net/rpc` di Go adotta una semantica di tipo maybe, ovvero non garantisce che una chiamata remota venga effettivamente eseguita in presenza di fallimenti di comunicazione.

In particolare, se una chiamata RPC fallisce, il client potrebbe non essere in grado di determinare se il metodo remoto sia stato eseguito oppure no.

Inoltre, non implementa automaticamente:

- Retry: se una chiamata fallisce, non viene automaticamente ritentata.
- Timeout applicativi per chiamata: `Call()` non prevede un parametro per impostare un tempo massimo di attesa.

Il client può ricevere un errore quando si interrompe la connessione oppure quando il metodo remoto restituisce un valore `error` diverso da `nil`.

È importante distinguere un errore applicativo da un errore di comunicazione: nel primo caso il server ha restituito un errore; nel secondo, il client potrebbe non conoscere l'esito dell'operazione

Il server RPC di Go non implementa un meccanismo automatico di deduplicazione delle richieste.

Ogni richiesta RPC contiene un numero di sequenza `Seq`, che viene utilizzato per associare la risposta alla richiesta corrispondente.

Tuttavia, questo identificatore non viene utilizzato dal server per riconoscere eventuali richieste duplicate.

**Nota:** sta quindi allo sviluppatore implementare dei meccanismi migliori per la gestione dei fallimenti.

#### Sun RPC vs Java RMI, RPyC, Go

| Tipo di trasparenza | Sun RPC                                                                                                                                   | Java RMI                                                                                                                     | RPyC                                                                                                                | Go RPC                                                                                                                               |
| ------------------- | ----------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| 1. Accesso          | Parziale: gli stub generati da `rpcgen` nascondono la comunicazione, ma richiedono convenzioni specifiche (IDL, versioni, nomi generati). | Elevata: invocazione tramite riferimento remoto con sintassi simile a quella locale. Richiede gestione di `RemoteException`. | Elevata: proxy dinamici (netref) permettono di utilizzare la normale sintassi Python, ad esempio `conn.root.add()`. | Parziale: chiamata remota esplicita tramite `client.Call()` o `client.Go()`. I metodi esposti devono rispettare una firma specifica. |
| 2. Locazione        | Parziale: il client conosce l'host e interroga il port mapper per ottenere la porta del servizio.                                         | Parziale: il client contatta l'RMI Registry e ottiene lo stub cercando il servizio per nome.                                 | Limitata: il client deve generalmente conoscere host e porta. Il registry è opzionale.                              | Limitata: il client deve conoscere host e porta. `RegisterName()` assegna un nome al servizio, ma non fornisce discovery di rete.    |
| 3. Concorrenza      | Dipende dall'implementazione del server e dal modello di gestione delle richieste.                                                        | Supporta richieste concorrenti;                                                                                              | Supporta diversi modelli, ad esempio `ThreadedServer`.                                                              | Supporto integrato: goroutine per connessioni e richieste.                                                                           |
| 4. Fallimenti       | At-least-once con ritrasmissioni, tipicamente su UDP;                                                                                     | At-most-once: non riesegue automaticamente una chiamata già eseguita, ma l'esito può rimanere incerto in caso di guasto.     | Best-effort / Maybe: nessun retry automatico o deduplicazione. Gestione dei fallimenti a carico dello sviluppatore. | Maybe: nessun retry automatico, timeout per chiamata o deduplicazione integrata.                                                     |
| 5. Replicazione     | Non supportata automaticamente. Richiede meccanismi esterni.                                                                              | Non supportata automaticamente. Richiede meccanismi esterni.                                                                 | Non supportata automaticamente. Richiede meccanismi esterni.                                                        | Non supportata automaticamente. Richiede meccanismi esterni.                                                                         |


## gRPC

Le applicazioni distribuite moderne sono spesso costruite secondo il pattern a *microservizi*, ossia l'applicazione viene suddivisa in un insieme di serivizi indipendenti che comunicano tra di loro attraverso la rete.

Ogni microservizio è caratterizzato da alcune proprietà:
- *Indipendenza e autonomia:* può essere sviluppato, distribuito e scalato indipendentemente dagli altri.
- *Orientamento alle funzionalità di business:* ogni servizio è responsabile di una specifica funzionalità dell'applicazione.
- *Accoppiamento debole (loose coupling):* i servizi interagiscono attraverso interfacce ben definite, riducendo le dipendenze reciproche.
- *Sviluppo poliglotta:* i microservizi possono essere implementati utilizzando linguaggi di programmazione differenti.


![[microservizirpc.svg | 500]]

I middleware RPC tradizionali, come Sun RPC, Java RMI e Go `net/rpc`, presentano limitazioni nell'interoperabilità tra linguaggi, nella gestione dei fallimenti o nell'integrazione con infrastrutture cloud.

Nasce quindi l'esigenza di un middleware che offra comunicazione efficiente, interoperabilità, scalabilità e strumenti per gestire sistemi distribuiti complessi.

**DEF:** *gRPC* è un framework RPC open-source ad alte prestazioni, sviluppato originariamente da Google. È progettato per funzionare su piattaforme differenti e supporta numerosi linguaggi di programmazione, rendendolo particolarmente adatto alle architetturare a microservizi.

gRPC viene utilizzato in infrastrutture cloud-native come [[https://etcd.io/]], un database `chiave-valore` distribuito, *containerd, Kubernetes*, etc...

### Trasporto e comunicazione - HTTP/2

gRPC utilizza come protocollo di *trasporto* HTTP/2, sfruttando le sue caratteristiche fondamentali, quali:
- *Multiplexing:* Più chiamate RPC possono condividere contemporaneamente una singola connessione TCP, utilizzando stream HTTP/2 diversi.
- *Flow Control:* Regola la quantità di dati trasmessi, evitando di sovraccaricare il ricevente.
- *Bidirectional Streaming:* Client e server possono inviare sequenze di messaggi in entrambe le direzioni.
- *Header Compression:* Compressione degli header tramite HTTP/2.

gRPC quindi supporta 4 modalità di comunicazione tra server e client: *Unary RPC, Server Streaming, Client Streaming, Bidirectional Streaming*.

HTTP/2 mantiene la stessa semantica di HTTP, ma introduce alcuni miglioramenti rispetto a HTTP/1.1:
- *Binary Framing Layer:* un strato che suddivide la comunicazione in unità più piccole, chiamate *frame*, codificare in binario. Quando un client invia una richiesta, HTTP/2 la rappresenta mediante una sequenza di frame, che possono contenere headers o dati. Ogni frame contiene uno `Stream ID`, che permette al destinatario di riconoscere lo stream a cui appartiene. Questo consente di intercalare frame appartenenti a frame diversi sulla stessa connessione TCP.

*Limiti:* Nonostante il multiplexing, HTTP/2 presenta una limitazione data dall'utilizzo di TCP. Poiché TPC garantisce l'ordine dei segmenti, se un segmento viene perso, i dati successivi non possono essere consegnati all'applicazione finché non viene recuperato il segmento mancante. Questo significa che la perdita di un segmento può bloccare temporaneamente tutti gli stream.

Questo problema prende il nome di *TCP-level Head-of-line Blocking*. Questa è una delle motivazioni dello sviluppo di HTTP/3 su QUIC.

![[http2.png]]
### IDL - Protocol Buffers

gRPC utilizza Protocol Buffers (Protobuf), un meccanismo di serializzazione dei dati sviluppato da Google, che svolge due funzioni fondamentali:
1. *IDL:* permette di definire le interfacce dei servizi remoti e i tipi di dati scambiati, indipendentemente dal linguaggio di programmazione.
2. *Serializzazione:* permette di rappresentare i dati in un formato binario compatto ed efficiente, adatto alla trasmissione in rete.

Protocol Buffers permette di rappresentare dati strutturati attraverso dei messaggi. Un messaggio è un insieme di campi, ciascuno caratterizzato da:
- *Tipo:* `string`, `int32`, `bool`.
- *Nome:* identifica il campo nel codice.
- *Numero:* identificatore univoco del campo all'interno del messaggio, utilizzato durante la serializzazione.

```proto3
syntax = "proto3";

message Person {
    string name = 1;
    int32 id = 2;
    string email = 3;
}
```

Quindi, se dobbiamo inviare il seguente messaggio:
```
Person {
    name: "Mario"
    id: 42
    email: "mario@example.com"
}
```

Protocol Buffers non trasmette direttamente questa rappresentazione testuale, ma la converte in una sequenza di byte.
Nel formato binario, i campi vengono identificati principalmente attraverso il loro numero, anziché il nome.
Questo permette di ridurre la dimensione dei messaggi rispetto a formati testuali come JSON.
Inoltre, Protobuf è *strongly typed*, perché i tipi dei campi sono definiti esplicitamente nello schema.
**NOTA:** il formato binario Protobuf non è *self-describing*: i dati serializzati non contengono tutte le informazioni necessarie a ricostruire autonomamente lo schema originale. Per interpretarli correttamente, il destinatario deve conoscere la definizione del messaggio.

Oltre alla serializzazione, gRPC utilizza ProtocoloBuffers anche come IDL.
```Proto3

syntax = "proto3";

package ecommerce;

service ProductInfo {
    rpc addProduct(Product) returns (ProductID);
    rpc getProduct(ProductID) returns (Product);
}

message Product {
    string id = 1;
    string name = 2;
    string description = 3;
}

message ProductID {
    string value = 1;
}
```

Una volta definito il file `.proto`, è possibile utilizzare il compilatore `protoc` insieme ai plugin specifici del linguaggio.

Il compilatore genera:
- Classi o tipi dei messaggi: rappresentano i dati definiti nel file `.proto` e forniscono il supporto alla serializzazione e deserializzazione.
- Client stub: proxy locale che permette al client di invocare i metodi del servizio remoto.
- Interfacce o codice di supporto lato server: consentono di implementare i metodi remoti e gestire le richieste ricevute.

![[grpc.svg | 600]]
l processo di sviluppo può essere suddiviso in tre fasi.

1. *Definizione del contratto:* Si crea un file `.proto` contenente i servizi RPC, i metodi disponibili e i tipi di messaggi scambiati tra client e server.
2. *Compilazione:* Si utilizza `protoc`, insieme ai plugin gRPC, per generare automaticamente i tipi dei messaggi, gli stub client e le interfacce server. Ad esempio, in Go:
```bash
protoc --go_out=. --go-grpc_out=. product.proto
```    
3. *Implementazione:* Lo sviluppatore implementa a logica dei metodi remoti lato server e utilizza lo stub generato per invocarli dal client.

**Esempio:** [[https://github.com/grpc/grpc-go/tree/master/examples/helloworld/ | Hello world with gRPC in Go]].

In gRPC è molto facile modifare un'applicazione aggiungendo un nuovo servizio remoto:
1. Si modifica la definizione dell'interfaccia all'interno del file `.proto`.
2. Si rigenerano client e server stub.
3. Si modifica l'implementazione del servizio lato server.
4. Si aggiorna il client facendo la chiamata al nuovo metodo.

#### Metodi di comunicazione

Come accennato precedentemente, gRPC supporta 4 modalità di comunicazione.
1. *Unary RPC:* il client invia un'unica richiesta al server ed aspetta l'unica risposta dal server. Simula la tipica chiamata a funzione.
 ```
 rpc Method(Input) returns (Output);
 ```
 2. *Server Streaming RPC:* Il client invia un'unica richiesta al server, il quale risponde con uno *stream* di messaggi il cui ordine è garantito dal framework.
```
 rpc Method(Input) returns (stream Output);
```
3. *Client Streaming RPC:* Il client invia uno stream di richieste al server. Il server legge tutti i messaggi e invia un'unica risposta al client.
```
 rpc Method(stream Input) returns (Output);
```
4. *Bidirectional Streaming RPC:* Sia client che server inviano stream di messaggi. Ciascuno di essi può leggere e scrivere in modo indipendente. Il server può aspettare e leggere tutti i messaggi inviati dal client e rispodere una solta volta inviando il stream di rispost oppure rispodere a ciascun mesaggio per volta.
```
 rpc Method(stream Input) returns (stream Output);
```

**Esempio:** [[https://github.com/grpc/grpc-go/tree/master/examples/route_guide | implementazione delle 4 modalità di comunicazione]]

#### Trasparenze di gRPC

- *Accesso:* gRPC offre un elevato livello di trasparenza di accesso attraverso il Proxy Pattern. Il client invoca i metodi sullo stub generato automaticamente a partire dal file `.proto`, senza dover gestire direttamente la serializzazione, l'invio dei messaggi e la ricezione delle risposte. Inoltre, grazie a Protocol Buffers, la comunicazione è indipendente dal linguaggio: ad esempio, un client Java può invocare metodi di un server Go. La trasparenza non è comunque totale: il client deve creare un canale gRPC, utilizzare lo stub e gestire gli eventuali errori remoti.
- *Locazione:* Come meccanismo di default, gRPC fa uso di DNS, non c'è direttamente un meccanismo di service discovery. Esiste comunque la possibilità di integrare resolver personalizzati con sistemi come Consul o Eureka e una service mesh come Istio.
- *Concorrenza:* Il framework permette a più chiamate di essere in corso contemporaneamente. Come al solito però l'accesso concorrente a risorse condivise va gestito dal programmatore.
- *Replicazione:* Si integra tramite *load balancers* che siano client-side o esterni.
- *Fallimento:* gRPC supporta semantica *at-most-once*. Alcuni fallimenti (es. crash del server mid-call) potrebbero risultare in _partial execution_. Non c'è quindi supporto per semantica exactly-once.

Per quanto riguarda la trasparenza di fallimento in particolare due strategie che si possono implementare lato client:

- *Retry con backoff esponenziale:* se un tentativo fallisce allora il client riprova dopo un'attesa che cresce in modo esponenziale.
- *Request hedging:* se un primo tentativo è ancora in corso ma è abbastanza lento da giustificare un secondo tentativo, il client invia una seconda richiesta magari verso un'altra replica. Quando arriva la risposta, il client può cancellare i tentativi ancora in corso.

Altra trasparenza presente in gRPC è quella legata alla *sicurezza*: gRPC supporta *SSL/TLS (anche mTLS)* per cifrare le comunicazioni e autenticare i peer.
