# Teoria

## Design Patterns

I design pattern sono soluzioni generiche, riutilizzabili e collaudate a problemi comuni che si incontrano nello sviluppo del software orientato agli oggetti. Non sono blocchi di codice pronti da incollare, ma piuttosto schemi concettuali, strutture astratte che aiutano a organizzare il codice in modo chiaro, flessibile e manutenibile.

I design pattern sono importanti perchè risolvono problemi che si incontrano spesso nello sviluppo di software. I design pattern offrono standard per risolvere tutte queste problematiche.

Si classificano secondo due criteri, uno riguardo lo scopo (purpose) mentre l'altro riguardo il raggio di azione (scope).

- **Purpose**

    1. **Creazionali**: gestiscono l'istanziazione degli oggetti. Offrono meccanismi per creare oggetti in modo flessibile e indipendente dal contesto concreto.
    2. **Strutturali**: si concentrano sul modo in cui le classi e gli oggetti si compongono.
    3. **Comportamentali**: descrivono come gli oggetti interagiscono e comunicano tra loro, mettendo l'accento sul flusso di controllo e la responsabilità.

- **Scope**

    1. **Classi**: Definiscono le relazioni fra classi e sottoclassi. Le relazioni sono basate sul concetto di ereditarietà e sono quindi statiche (compile time).
    2. **Oggetti**: Definiscono relazioni tra oggetti, che possono cambiare durante l'esecuzione e sono quindi dinamiche.

### 1. Abstract Factory

Fa parte della classe di DP `creazionali` ed ha lo scopo di fornire un'interfaccia per creare famiglie di oggetti correlati o dipendenti senza specificare le loro classi concrete. Si definisce un'interfaccia comune che permette di creare oggetti appartenenti alla stessa famiglia, poi si implementano diverse `fabbriche concrete` per ogni variante.

```Java
interface Button {
    void paint();
}

class WindowsButton implements Button {
    public void paint() {
        System.out.println("Rendering a Windows button");
    }
}

class MacButton implements Button {
    public void paint() {
        System.out.println("Rendering a Mac button");
    }
}

interface GUIFactory {
    Button createButton();
    Checkbox createCheckbox();
}

class WindowsFactory implements GUIFactory {
    public Button createButton() {
        return new WindowsButton();
    }
}

class MacFactory implements GUIFactory {
    public Button createButton() {
        return new MacButton();
    }
}

public class Application {
    private Button button;
    private Checkbox checkbox;

    public Application(GUIFactory factory) {
        button = factory.createButton();
        checkbox = factory.createCheckbox();
    }

    public void render() {
        button.paint();
        checkbox.render();
    }
}
```

In questo modo, il client può creare una GUI per Windows o Mac semplicemente cambiando l’istanza della factory passata al costruttore, senza toccare il resto del codice.

| **Categoria**     | **Contenuto**                                                                                                                                                                                                                                                                                                                        |
|-------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Applicabilità** | - Quando il sistema deve essere **indipendente** dalla modalità di creazione degli oggetti<br>- Quando si devono gestire **famiglie di oggetti correlati** (es. GUI per Windows/Mac)<br>- Quando il **client non deve essere legato** a una classe concreta o famiglia specifica                                                     |
| **Partecipanti**  | - `AbstractFactory`: interfaccia per creare prodotti astratti<br>- `ConcreteFactory`: implementazioni che creano prodotti concreti<br>- `AbstractProduct`: interfaccia dei prodotti da creare<br>- `ConcreteProduct`: implementazioni specifiche dei prodotti<br>- `Client`: utilizza la factory e lavora solo con le interfacce     |
| **Conseguenze**   | - Le **classi concrete sono isolate** e facilmente gestibili<br>- Cambiare famiglia di prodotti è facile: basta sostituire la factory<br>- Aggiungere una nuova **famiglia** richiede nuove classi e **ricompilazione**<br>- Il codice è **più modulare** e flessibile, ma può diventare più complesso se usato in contesti semplici |

### 2. Factory Method

L’idea di fondo è che la creazione di un oggetto non avviene direttamente nel codice, ma viene delegata a un metodo specializzato, chiamato appunto `factory method`. Questo metodo può essere ridefinito dalle sottoclassi per istanziare oggetti specifici. Nel codice orientato agli oggetti, spesso si vuole evitare di usare direttamente `new` per creare un’istanza di una classe concreta, perché così si rende il codice rigido e poco estensibile. Il Factory Method serve proprio a risolvere questo problema: consente alle sottoclassi di decidere quale classe concreta instanziare, mantenendo il codice cliente indipendente.

Il Factory Method è utile quando un codice deve lavorare con un’interfaccia o una superclasse, ma non deve sapere quale sottoclasse concreta utilizzare. La responsabilità della creazione viene così demandata a chi conosce i dettagli.

| **Vantaggi**                                                                             | **Svantaggi**                                                                                   |
|------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------|
| Il codice è **indipendente dalle classi concrete** dei prodotti da creare                | Aggiunge **complessità strutturale** (serve creare nuove sottoclassi per ogni tipo di prodotto) |
| Favorisce il **polimorfismo** e l’estensibilità del codice                               | Può generare una **gerarchia di classi più ampia** e difficile da gestire                       |
| È **facile aggiungere nuovi tipi di prodotto**: basta una nuova sottoclasse con override | Ogni modifica alla logica di creazione richiede la modifica o l’estensione delle classi         |
| Incapsula la logica di istanziazione e semplifica i test                                 | Può risultare **ridondante** in casi semplici dove basta una `new`                              |

- Il Factory Method crea un solo oggetto per volta e si basa sul override del metodo da parte delle sottoclassi.
- L’Abstract Factory fornisce un’intera famiglia di oggetti e lavora con più prodotti tra loro correlati.

### 3. Adapter

Fa parte dei design pattern strutturali, serve a far collaborare classi con interfacce incompatibili tra loro. È come un "traduttore" che si mette in mezzo tra due componenti per farle comunicare, anche se originariamente non erano pensate per lavorare insieme. È strutturato mediante 3 componenti principali:

- **Target** è l'interfaccia che il codice client si aspetta.
- **Adaptee** è la classe esistente che ha l'interfaccia incompatibile.
- **Adapter** è la classe che implementa l'interfaccia `Target`, ma al suo interno usa un oggetto `Adaptee`, adattando i metodi.

```java
// Interfaccia attesa dal client
interface MediaPlayer {
    void play(String filename);
}

// Classe esistente incompatibile
class AdvancedPlayer {
    void playFile(String filePath) {
        System.out.println("Riproduzione: " + filePath);
    }
}

// Adapter
class MediaAdapter implements MediaPlayer {
    private AdvancedPlayer advancedPlayer;

    public MediaAdapter(AdvancedPlayer player) {
        this.advancedPlayer = player;
    }

    public void play(String filename) {
        // adatta il metodo play al metodo playFile
        advancedPlayer.playFile(filename);
    }
}
```

| **Categoria**     | **Contenuto**                                                                                                                                                                                                                                                                                                           |
|-------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Quando usarlo** | - Quando hai classi esistenti (o librerie esterne) con **interfacce incompatibili** rispetto a quelle del tuo sistema<br>- Quando vuoi **riutilizzare codice legacy** senza modificarlo<br>- Quando il tuo sistema ha un'interfaccia standard e devi **integrare componenti esterni**                                   |
| **Vantaggi**      | - **Riutilizzo del codice esistente** senza modificarlo<br>- Permette l’integrazione con librerie o sistemi legacy<br>- Favorisce la **separazione delle responsabilità**: il codice client rimane pulito<br>- Può essere usato per adattare classi con interfacce complesse o sbilanciate                              |
| **Svantaggi**     | - Aggiunge un **livello di astrazione** in più<br>- Può portare a **una proliferazione di classi adapter**, se ne servono molti<br>- Rischio di **mascherare incompatibilità semantiche** (metodi che sembrano simili ma fanno cose diverse)<br>- Può diventare un punto fragile se il codice da adattare cambia spesso |

### 4. Composite

Il Composite è un design pattern strutturale molto elegante, che permette di rappresentare strutture ad albero, in cui oggetti singoli e gruppi di oggetti possono essere trattati in modo uniforme. È particolarmente utile quando si vuole costruire una gerarchia dove ogni nodo può essere una “foglia” (cioè un oggetto semplice) oppure un “composito” (cioè un contenitore di altri oggetti).

Prendiamo per esempio un file system: ci sono file (elementi semplici) e cartelle (che possono contenere altri file o cartelle). Vogliamo poter dire a un file "dammi la dimensione" e ottenere, per esempio, 100KB. Ma vogliamo poter dire la stessa cosa a una cartella, e ricevere la somma delle dimensioni di tutto ciò che contiene, in maniera trasparente.
Ecco dove entra in gioco il Composite: unifica il trattamento di oggetti singoli e composti.

È strutturato mediante 3 principali componenti:

1. **Component**: Un'interfaccia o classe astratta che definisce le operazioni comuni.
2. **Leaf**: Una classe concreta che rappresenta un oggetto "atomico" e implementa direttamente le operazioni.
3. **Composite**: Una classe che rappresenta un contenitore, che contiene una lista di altri `Component` (fligli o composite). Implementa le operazioni in modo ricorsivo.

```java
interface Graphic {
    void draw();
}

// Foglia
class Circle implements Graphic {
    public void draw() {
        System.out.println("Disegno un cerchio");
    }
}

// Composito
class CompositeGraphic implements Graphic {
    private List<Graphic> children = new ArrayList<>();

    public void add(Graphic g) {
        children.add(g);
    }

    public void draw() {
        for (Graphic g : children) {
            g.draw(); // chiamata ricorsiva
        }
    }
}
```

| **Categoria**     | **Contenuto**                                                                                                                                                                                                                                                                                                                                                                                      |
|-------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Quando usarlo** | - Quando vuoi rappresentare **strutture gerarchiche ad albero** (es. file system, menu, componenti grafici)<br>- Quando hai bisogno di **trattare allo stesso modo oggetti singoli e contenitori**<br>- Quando le operazioni devono essere **applicate ricorsivamente** a una struttura composta                                                                                                   |
| **Vantaggi**      | - Permette un **trattamento uniforme** di oggetti e composizioni<br>- Facilita l’uso della **ricorsione** su strutture complesse<br>- Il codice client è **semplificato**: lavora sempre con l’interfaccia `Component`<br>- Migliora la **flessibilità** e la **componibilità** degli oggetti                                                                                                      |
| **Svantaggi**     | - Può essere difficile **limitare le operazioni solo a certi tipi** (es. operazioni che hanno senso solo per i Leaf)<br>- Rischio di **compromettere la trasparenza**: il client potrebbe dover distinguere fra Leaf e Composite<br>- Aggiunge **complessità inutile** se usato in strutture semplici<br>- La **gestione dei figli** (aggiunta, rimozione) può creare ambiguità se lasciata libera |

### 5. Decorator

È uno dei più raffinati tra i design pattern strutturali. Il suo scopo è aggiungere dinamicamente nuovi comportamenti a un oggetto, senza dover modificare il codice della classe originale, e senza creare sottoclassi multiple per ogni possibile combinazione di funzionalità.

Supponiamo di avere un oggetto di tipo `TextView` che mostra del testo. A volte vuoi che il testo abbia il bordo, altre volte scrollabile, altre ancora colorato. Si potrebbe pensare di creare tante sottoclassi (es. BordedTextView, ScrollTextView, ScrollAndBordedTextView...) ma diventa presto ingestibile.

Con il Decorator, invece, possiamo comporre dinamicamente questi comportamenti, creando oggetti che avvolgono altri oggetti, aggiungendo logica prima o dopo la chiamata originale.

Il decorator si struttura con 4 componenti:

1. **Component**: Un interfaccia comune che definisce l'operazione base.
2. **ConcreteComponent**: La classe reale che implementa `Component`, quella da decorare.
3. **Decorator**: Una classe astratta che implementa `Component` e contiene un riferimento a un altro component (quello da decorare).
4. **ConcreteDecorator**: Estende `Decorator`, aggiungendo comportamenti prima o dopo aver delegato la chiamata all'oggetto decorato.

```java
interface VisualComponent {
    void draw();
}

// Componente base
class TextView implements VisualComponent {
    public void draw() {
        System.out.println("Disegno del testo");
    }
}

// Decorator astratto
abstract class ComponentDecorator implements VisualComponent {
    protected VisualComponent component;

    public ComponentDecorator(VisualComponent component) {
        this.component = component;
    }

    public void draw() {
        component.draw();  // delega al componente decorato
    }
}

// Concrete Decorator
class BorderDecorator extends ComponentDecorator {
    public BorderDecorator(VisualComponent component) {
        super(component);
    }

    public void draw() {
        super.draw();
        System.out.println("...e disegno un bordo");
    }
}

class ScrollDecorator extends ComponentDecorator {
    public ScrollDecorator(VisualComponent component) {
        super(component);
    }

    public void draw() {
        super.draw();
        System.out.println("...e aggiungo lo scrolling");
    }
}

VisualComponent text = new TextView();
VisualComponent decorated = new BorderDecorator(new ScrollDecorator(text));
decorated.draw();
```

| **Categoria**     | **Contenuto**                                                                                                                                                                                                                                                                                                                                             |
|-------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Quando usarlo** | - Quando vuoi **aggiungere funzionalità a oggetti esistenti** senza modificare il loro codice<br>- Quando non vuoi o non puoi usare l’**ereditarietà** per estendere il comportamento<br>- Quando hai bisogno di **combinare dinamicamente** diversi comportamenti opzionali<br>- Quando il sistema deve essere **estendibile e configurabile a runtime** |
| **Vantaggi**      | - Permette l’**aggiunta flessibile e modulare** di responsabilità<br>- **Evita la proliferazione di sottoclassi** per ogni combinazione possibile<br>- Favorisce la **composizione** invece dell’ereditarietà<br>- Funziona anche con **classi già esistenti o chiuse alla modifica**                                                                     |
| **Svantaggi**     | - L’**annidamento di più decoratori** può rendere il codice difficile da seguire<br>- La **complessità aumenta** con troppi livelli di decorazione<br>- È importante **gestire con attenzione l’ordine** con cui i decoratori vengono applicati<br>- Difficile da debuggare: ogni comportamento può essere "nascosto" in un decoratore diverso            |

### 6. Observer

L’Observer serve per creare una relazione uno-a-molti tra oggetti: quando un oggetto cambia stato, tutti gli oggetti che lo osservano vengono automaticamente notificati e aggiornati.

È strutturato mediante 4 principali componenti:

1. **Subject (Observable)**: Espone metodi per aggiungere/rimuovere osservatori e per notificare gli aggiornamenti.
2. **ConcreteSubject**: Implementa il `Subject` e contiene lo stato da osservare. Quando cambia, notific tutti gli observer.
3. **Observer**:  Interfaccia che dichiara il metodo `update()`.
4. **ConcreteObserver**: Implementa `Observer` e reagisce agli aggiornamenti del soggetto.

```java
// Observer
interface Observer {
    void update(String news);
}

// Subject
interface NewsAgency {
    void registerObserver(Observer o);
    void removeObserver(Observer o);
    void notifyObservers(String news);
}

// ConcreteSubject
class RealNewsAgency implements NewsAgency {
    private List<Observer> observers = new ArrayList<>();

    public void registerObserver(Observer o) {
        observers.add(o);
    }

    public void removeObserver(Observer o) {
        observers.remove(o);
    }

    public void notifyObservers(String news) {
        for (Observer o : observers) {
            o.update(news);
        }
    }
}

// ConcreteObserver
class EmailSubscriber implements Observer {
    public void update(String news) {
        System.out.println("Email ricevuta: " + news);
    }
}

RealNewsAgency agency = new RealNewsAgency();
Observer user1 = new EmailSubscriber();

agency.registerObserver(user1);
agency.notifyObservers("È uscito un nuovo articolo!");
```

| **Categoria**     | **Contenuto**                                                                                                                                                                                                                                                                                                                                                       |
|-------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Quando usarlo** | - Quando un cambiamento in un oggetto richiede **l’aggiornamento automatico di altri oggetti**<br>- Quando vuoi mantenere una **dipendenza loosely coupled** tra soggetto e osservatori<br>- Quando vuoi implementare **sistemi di notifica, eventi, broadcast**                                                                                                    |
| **Vantaggi**      | - Favorisce il **disaccoppiamento** tra soggetto e osservatori<br>- Gli oggetti possono **reagire ai cambiamenti senza conoscere in dettaglio la logica del soggetto**<br>- Estendibile: puoi aggiungere o rimuovere osservatori **dinamicamente**<br>- È alla base dei sistemi **event-driven**                                                                    |
| **Svantaggi**     | - In sistemi grandi, può diventare difficile **tracciare l’ordine e le conseguenze delle notifiche**<br>- Se non gestito bene, può portare a **problemi di performance** (troppe notifiche)<br>- Rischio di **dipendenze nascoste** e comportamenti imprevisti<br>- Il soggetto notifica tutti gli osservatori **senza sapere se sono ancora interessati o validi** |

### 7. Template Method

È un pattern comportamentale che si basa su un’idea molto semplice ma estremamente potente: definire lo scheletro di un algoritmo in una classe astratta, lasciando alcuni passi da implementare alle sottoclassi.

La struttura del pattern consiste di:

1. **AbstractClass**: Contiene il template method che definisce i passi dell'algoritmo. Implementa alcuni passi, lasciando altri come metodi astratti o "hook" da sovrascrivre.
2. **ConcreteClass**: Implementa i metodi astratti, completando così il comportamento.

```java
// Classe astratta
abstract class DataProcessor {
    // Template method
    public final void process() {
        readData();
        processData();
        saveData();
    }

    protected abstract void readData();
    protected abstract void processData();

    // Metodo "hook": opzionale da sovrascrivere
    protected void saveData() {
        System.out.println("Salvataggio su file di default");
    }
}

// Classe concreta
class CSVDataProcessor extends DataProcessor {
    protected void readData() {
        System.out.println("Lettura dati da CSV");
    }

    protected void processData() {
        System.out.println("Elaborazione dati CSV");
    }
}

DataProcessor processor = new CSVDataProcessor();
processor.process();  // Esegue lo schema definito dalla superclasse
```

| **Categoria**     | **Contenuto**                                                                                                                                                                                                                                                                                                                                                                |
|-------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Quando usarlo** | - Quando hai un algoritmo con una **struttura fissa ma passi variabili**<br>- Quando vuoi **centralizzare il controllo del flusso** lasciando personalizzazione ai figli<br>- Quando vuoi **evitare la duplicazione del codice comune** in più sottoclassi                                                                                                                   |
| **Vantaggi**      | - Favorisce il **riuso del codice**: la logica comune è definita una sola volta<br>- Permette di **variare solo ciò che serve**, lasciando intatta la struttura<br>- Riduce l’**effetto domino** delle modifiche (le regole base restano concentrate nella superclasse)<br>- Promuove il principio **“Hollywood”**: “Don’t call us, we’ll call you”                          |
| **Svantaggi**     | - Introduce una **forte dipendenza tra superclasse e sottoclassi**<br>- Più difficile da **comprendere e mantenere** se la gerarchia diventa complessa<br>- L’eccessivo uso di metodi astratti può **forzare le sottoclassi** a scrivere codice non sempre necessario<br>- Poco flessibile in confronto alla **composizione** (che può essere preferibile in certi contesti) |

### 8. Strategy

Permette di definire una famiglia di algoritmi (o comportamenti), incapsularli ciascuno in una classe diversa, e renderli intercambiabili. In questo modo, l’oggetto che li usa non ha bisogno di sapere quale strategia specifica sta usando: sa solo che tutte seguono un’interfaccia comune.
È un’alternativa alla programmazione ad `if` annidati o alla logica dispersa: ogni comportamento è separato e testabile da solo.

È strutturato nel seguente modo:

1. **Strategy**: Definisce il metodo comune che tutte le strategie devono implementare.
2. **ConcreteStrategy**: Una o più classi che implementano `Strategy` e forniscono versioni diverse dell'algoritmo.
3. **Context**: Contiene un riferimento a una `Strategy` e la usa per eseguire l'operazione desiderata.

```java
// Strategy
interface PaymentStrategy {
    void pay(double amount);
}

// Concrete Strategies
class CreditCardPayment implements PaymentStrategy {
    public void pay(double amount) {
        System.out.println("Pagato " + amount + " con carta di credito");
    }
}

class PayPalPayment implements PaymentStrategy {
    public void pay(double amount) {
        System.out.println("Pagato " + amount + " con PayPal");
    }
}

// Context
class ShoppingCart {
    private PaymentStrategy strategy;

    public ShoppingCart(PaymentStrategy strategy) {
        this.strategy = strategy;
    }

    public void checkout(double amount) {
        strategy.pay(amount);
    }
}

ShoppingCart cart = new ShoppingCart(new PayPalPayment());
cart.checkout(50.0);

cart = new ShoppingCart(new CreditCardPayment());
cart.checkout(120.0);
```

| **Categoria**     | **Contenuto**                                                                                                                                                                                                                                                                                                                                  |
|-------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Quando usarlo** | - Quando hai **comportamenti diversi** che possono essere **separati e riutilizzati**<br>- Quando vuoi **evitare logiche condizionali complesse**<br>- Quando hai bisogno di **cambiare algoritmo o logica a runtime**<br>- Quando vuoi **testare o estendere comportamenti** in modo modulare                                                 |
| **Vantaggi**      | - **Aggiunta o modifica facile** delle strategie senza toccare il codice del contesto<br>- Favorisce la **composizione** rispetto all’ereditarietà<br>- Ogni strategia è **incapsulata**, testabile e riutilizzabile<br>- Promuove il **principio aperto/chiuso**: puoi aggiungere nuove strategie senza modificare quelle esistenti           |
| **Svantaggi**     | - Può introdurre **troppe classi** se le strategie sono molte<br>- Il contesto deve **conoscere la strategia esternamente**, o delegare la scelta<br>- Se le strategie condividono troppo codice, può esserci **duplicazione o necessità di un’astrazione intermedia**<br>- Meno intuitivo da usare se i comportamenti sono semplici e statici |

### 9. Singleton

Il Singleton è un pattern che garantisce che una classe abbia una sola istanza e fornisce un punto di accesso globale a quella istanza.

È utile quando è necessario un solo oggetto condiviso da tutto il sistema, ad esempio per:

- la configurazione di un'applicazione
- un logger
- una connessione a un database
- un gestore di risorse

L’idea è semplice:

1. Rendere il costruttore privato, così nessuno può creare istanze dall’esterno.
2. Fornire un metodo statico che restituisce l’unica istanza (creata alla prima chiamata).

```java
public class Logger {
    private static Logger instance;

    // Costruttore privato
    private Logger() {
        // inizializzazione
    }

    public static Logger getInstance() {
        if (instance == null) {
            instance = new Logger();  // lazy initialization
        }
        return instance;
    }

    public void log(String message) {
        System.out.println("LOG: " + message);
    }
}
```

| **Categoria**     | **Contenuto**                                                                                                                                                                                                                                                                                                                                       |
|-------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Quando usarlo** | - Quando serve **una sola istanza condivisa** nel sistema (es. logger, configurazione)<br>- Quando serve **controllare l'accesso globale** a una risorsa o a un componente centrale<br>- Quando vuoi **centralizzare lo stato o il coordinamento** di un sistema                                                                                    |
| **Vantaggi**      | - Garantisce **una sola istanza** (controllo centralizzato)<br>- È facile da implementare e usare<br>- Fornisce un **accesso globale e coerente** a risorse comuni<br>- Può essere migliorato per essere **lazy o thread-safe**                                                                                                                     |
| **Svantaggi**     | - Può violare il **principio di singola responsabilità**: gestisce anche il proprio ciclo di vita<br>- Rende difficile **testare o sostituire** l’oggetto in test unitari<br>- È spesso considerato una forma **"controllata" di global state**<br>- In ambienti multi-thread, può causare **problemi di concorrenza** se non gestito correttamente |

## Use case - Include ed Exclude

Un Use Case rappresenta un’interazione tra un attore (utente o sistema esterno) e il sistema, relativa a una funzionalità specifica. Quando le funzionalità si ripetono o hanno varianti, si usano i meccanismi di inclusione (`include`) e estensione (`extend`) per modularizzare e riutilizzare i comportamenti.

- **Include**: rappresenta una relazione obbligatoria tra due use case: uno include sempre l'altro durante la sua esecuzione. Si usa quando un comportamento è comune a più use case. Quando si vuole evitare duplicazioni. Quando si vuole modularizzare un comportamento ripetuto.
Per esempio gli use case "Registra Utente" e "Recupera Password", entrambi includono "Inviare Email".
Graficamente si rappresenta mediante una linea trateggiata con freccia vero il caso d'uso incluso.
- **Exclude**: rappresenta una relazione opzionale, cioè un caso d'uso può estendere un altro caso solo se una certa condizione è soddisfatta. Si usa quando un comportamento è facoltativo. Quando si vuole aggiungere funzionalità opzionali senza complicare il caso d'uso principale.
Per esempio il caso d'uso generale "Inserire Risultato" -> `extend` "Segnalare Irregolarità", ovvero in alcuni casi particolari, durante l'inserimento del risultato, l'arbitro può decidere di segnalare un'irregolarità.
Graficamente si rappresenta mediante una linea trateggiata con freccia verso il caso d'uso principale.

| **Relazione**      | **Include**                                    | **Extend**                         |
|--------------------|------------------------------------------------|------------------------------------|
| **Tipo di legame** | Obbligatorio                                   | Opzionale                          |
| **Direzione**      | Dal caso d’uso principale verso quello incluso | Dal caso esteso verso quello base  |
| **Quando si usa**  | Per **comportamenti comuni** riutilizzabili    | Per **funzionalità opzionali**     |
| **Attivazione**    | Sempre                                         | Solo se si verifica una condizione |
| **Obiettivo**      | **Modularizzare** e riutilizzare               | **Espandere** in modo flessibile   |

## Software Requiments: funzionali, non funzionali e di dominio

I requisiti software sono la descrizione dei servizi che un sistema software deve fornire, insieme ai vincoli da rispettare sia in fase di sviluppo che durante la fase di opertività del software. Esistono due categorie di requisiti SW:

- **Requisiti utente**: Descrizione in liguaggio naturale dei servizi che il sistema deve fornire e dei vincoli operativi.
- **Requisiti di sistema**: Specificati mediante la stesura di un documento strutturato che descrive in modo dettagliato i servizi chhe il sistema SW deve fornire. Ci sono 3 categorie:

### Requisiti Funzionali

I requisiti funzionali descrivono le funzionalità specifiche che il sistema deve offrire. Essi definiscono le azioni che il sistema deve compiere in risposta a determinati input o situazioni.

### Requisiti non Funzionali

I requisiti non funzionali specificano le qualità e le caratteristiche che il sistema deve possedere, senza riferirsi a funzionalità specifiche. Essi influenzano l'esperienza dell'utente e le prestazioni del sistema. Per esempio:

- **Prestazioni**: Tempo di risposta, throuthput, utilizzo delle risorse.
- **Sicurezza**: Protezione dei dati, autenticazione, autorizzazione.
- **Usabilità**: Facilità d'uso, accessibilità, design dell'interfaccia cliente.

### Requisiti di Dominio

Un requisito di dominio descrive un comportamento, un vincolo o una regola che non è universale per tutti i software, ma che vale solo in un certo contesto di applicazione (dominio). Spesso questi requisiti non sono espressi direttamente dall'utente, perché sono dati per scontati da chi opera nel settore, ma sono comunque essenziali affinché il sistema sia accettabile, corretto e conforme alle aspettative.

Ignorare un requisito di dominio può rendere un sistema non conforme alla legge, inutilizzabile, o scartato dagli utenti esperti del settore. Per questo, durante l'analisi dei requisiti, è fondamentale conivolgere esperti del dominio, come avvocati, medici, funzionari pubblici etc... .

| **Tipo di requisito** | **Focus**                                                             |
| --------------------- | --------------------------------------------------------------------- |
| **Funzionali**        | Cosa il sistema fa (comportamento)                                    |
| **Non funzionali**    | Come il sistema si comporta (prestazioni, sicurezza...)               |
| **Di dominio**        | **Requisiti specifici del settore**, spesso imposti da regole esterne |

## Modelli

Il modello del ciclo di vita del software specifica la serie di fasi attraverso cui il prodotto software progredisce e l'ordine con cui vanno eseguite, dalla definizione dei requisiti alla dismissione.

### Modello Build & Fix

Il modello Build & Fix è uno dei modelli di sviluppo software più semplici e primitivi, spesso adottato in contesti non professionali o da sviluppatori alle prime armi. In questo approccio, il software viene costruito senza una vera analisi dei requisiti nè una progettazione preliminare, e viene continuamente corretto e modificato man mano che emergono problemi e richieste.

Consiste in un semplice ciclo:

1. Build: Si scrive il codice in base a una vaga idea di cosa debba fare il programma.
2. Fix: Quando emergono problemi o richieste, si corregge modificando direttamente il codice.
3. Si ripete il ciclo finché il cliente non si dichiara soddisfatto.

### Modello a cascata (Waterfall)

Il modello a cascata è uno dei più classici e storici modelli di sviluppo del software. È stato uno dei primi ad essere formalizzato e si basa su un approccio sequenzale e lineare: ogni fase del progetto deve essere completata prima di passare alla successiva. Dopo ogni fase c'è la verifica, si tratta di controllare che il processo di sviluppo sia stato eseguito correttamente e che gli artefatti prodotti siano conformi alle specifiche. Oltre alla fase di verification c'è la fase di validation nella quale si verifica che il prodotto soddisfi effettivamente i bisogni dell'utente finale.

### Modello a prototipi

### Modello a spirale

### Modello iterativo o incrementale

### Modello Agile
