# LAN

LAN (Local Area Network) è una rete locale di dipositivi, per esempio la rete di casa, della scuola etc.

In base al livello in cui ci troviamo la LAN è vista come:

- A livello di rete la LAN è vista come una **sottorete**.
- A livello di collegamento la LAN è vista come una **rete**.

Le LAN sono sia Ethernet, quindi cablate e anche wireless, si pensi alla rete di casa propria in cui c'è il WI-FI.

A livello di rete abbiamo visto che ogni host possiede un indirizzo IP che sia a 32 o 128 bit.
A livello di collegamento ciascun interfaccia possiede un indirizzo MAC (Medium Access Control), che appunto è associato ad ogni interfaccia, ovvero ad ogni scheda di rete. L'indirizzo MAC è un numero a 48 bit espresso in esadecimale e a differenza dell'indirizzo IP che può cambiare, l'indirizzo MAC accompagna il dispositivo dalla nascita fino alla morte. Quindi è il produttore stesso del dispositivo che si occupa di assegnare l'indirizzo MAC in fase di produzione, indirizzo preso da un blocco assegnato dall' IEEE (l'ente che gestisce gli indirizzi MAC).

Per fare un'analogia con il mondo reale, l'indirizzo IP è come il codice postale mentre l'indirizzo MAC è come il codife fiscale.

Abbiamo visto che al livello di rete, quando si crea il datagramma IP viene aggiunto l'indirizzo IP del mittente e in particolare del destinatario. A livello di collegamento, quando si crea il frame viene aggiunto l'indirizzo MAC del  mittente e del destinatario, in quanto il livello di collegamento si occupa della comunicazione tra nodi adiacenti. Quindi ha bisogno di sapere con esattezza qual'è l'interfaccia fisica a cui deve arrivare il frame.

Dunque, ci viene adesso spontaneo chiederci come si passa di indirizzo IP a indirizzo MAC? La riposta è ARP.

## ARP (Address Resolution Protocol)

ARP è un protocollo a livello di collegamento che ha il compito di tradurre gli indirizzi IP in indirizzi MAC.

Ogni nodo possiede al suo interno una tabella, **ARP Table** in cui ogni record è la mappatura indirizzo IP - MAC address e un campo **TTL (Time To Live)** che rappresenta il tempo per cui vale tale mappatura.

Per popolare questa tabella ci pensa appunto il protocollo ARP. Supponiamo che un nodo A deve scoprire l'indirizzo MAC di un nodo B. A crea un frame contentente il suo indirizzo MAC e IP l' indirizzo IP di B. Come indirizzo MAC inserisce **l'indirizzo di broadcast a livello 2 (FF FF FF FF FF FF)**. Tutti i nodi della rete riceveranno questo frame che lo passeranno al livello di rete, ma solo il vero destinatario, ovvero B risponderà a questo messaggio mandando ad A il proprio MAC address. A questo punto A salva la corrispondeza indirizzo IP - MAC address di B nella propria tabella ARP.  

Il protocollo ARP viene inoltre utilizzato per attacchi alla rete. Parliamo dunque di ARP Spoofing o ARP Poisoning. 
Un attaccante invia in una LAN risposte ARP contraffatte, inducendo l'associazione di un indirizzo IP a un certo MAC address. 
Il protocollo ARP è senza stato, e un nodo aggiorna la propria ARP appena riceve una risposta a precindere chi sia una rispota legale o contraffatta.

È utilizzato in:

- DoS: associare diversi indirizzi IP allo stesso indirizzo MAC per sovraccaricarlo di traffico.
- Man In The Middle: l'attacante associa il proprio indirizzo MAC all'indirizzo IP di un altro nodo, in modo da intercettare (e magari modificare) il traffico destinato a quest'ultimo, per poi re-inoltraglielo.

### Invio di un datagramma a un nodo esterno della rete

<img src="img/ARP.png" width=400>

Anzitutto il nodo A consce soltanto l'indirizzo IP del destinatario, non sa quanti bit stanno nel prefisso direttamente per identificare la sottrete. Tuttuvia A1 sa di appartenere a una sottorete /24, pertanto confronta i 24 bit più significativi del proprio indirizzo con quello dell'indirizzo di B, constatando che sono diversi e quindi capisce che B si trova in una sottorete differente.

Dunque A metterà nel campo destinato al MAC address destinatario l'indirizzo MAC della scheda del router, di cui conosce l'indirizzo IP grazie al DHCP. Per risolvere dunque l'indirizzo MAC del router si usa sempre ARP.

A questo punto il router riceve il frame e lo passa al livello di rete che capisce che non è lui il destinatario e procede all'inoltro. Dato che l'altra interfaccia del router è collegata direttamente con la sotterete di B, il router tramite ARP risolve l'indirizzo MAC di B e gli inoltra il frame.

## Ethernet

Ethernet è il protocollo più utilizzato ad oggi all'interno delle LAN. È un protocollo semplice ma che rimane al passo con le velocità di trasmissione richieste. 

Ci sono tre tipologie di rete LAN Ethernet:

1. LAN a BUS: un cavo coassiale che passava per tutte le schede di rete. Se si tagliava un cavo tutta la rete si rompeva.
2. LAN a stella con HUB: Tutti gli host erano collegati mediante hub. L'hub è un dispostivo a livello fisico il quale rigenera il segnale in entrata di un interfaccia e lo inoltra poi a tutte le interfacce tranne a quella da cui è entrato il sengale. (In pratica gli arriva un frame e lo invia in broadcast a tutti). Il problema della topologia a bus e hub è che tutti i nodi non nello stesso dominio di collisione, per cui se due nodi trasmettono in contemporanea, avrò di sicuro collisione. 
3. LAN a stella con SWITCH. I nodi sono collegati ad uno switch, in questo caso lo switch ha il ruolo di gestire il traffico dei pacchetti inoltrandoli ai destinatari. Gli switch sono dispostivi di secondo livello che operano in modalità store and forward (memorizza e inoltra).

> [!NOTE]  
>
> Multiplexing e demultiplexing: Si ha il mux e il demux ad un certo livello quando si vuole seguire più protocolli al livello superiore. 
> A livello di rete si ha il mux/demux poiche si possono seguire piu protocolli di trasporto. UDP o TCP
> A livello di trasporto si ha il mux/demus a maggior ragione, per il numero grande di protocolli a livello di applicazione. HTTP/S, DNS, SSH, SMTP etc...

### Frame Ethernet

<img src="img/ethernet.png" width=400>

- Preambolo: 8 byte totali di cui 7 (10101010) per risvegliare la scheda di rete e sincronizzarla e l ultimo byte (10101011) che serve ad informare il ricevente dell'inizio effettivo del frame.
- Indirizzo sorgente e destinazione. Campi da 6 byte che includono il MAC address della sorgente e della destinazione.
- Tipo: Sono 2 byte dedicati ad indicare un protocollo di livello superiore, pricipalmente IP ma ci sono anche altri. Serve per il demux da parte del ricevente.
- Payload: Contiene il datagramma IP.
- CRC: Controllo a ridondanza ciclica, serve alla NIC di rilevare errori.

### Caratteristiche principali

- È un protocollo **senza connessione**, cioè privo di handshake. Non si crea una connessione tra le due NIC.
- È un protocollo **non affidabile**, le NIC non si scambiano ACK e NAK.
- Utilizza come protocollo MAC il **CSMA/CD con binary backoff**.

> [!NOTE]  
>
> Nel corso degli anni ci sono state e ci sono ancora varie versioni di Ethernet. Ciò che li accomuna sono il protocollo MAC e il formato del frame mentre cio che li differenzia sono le velocità e i mezzi di trasmissione.

## Switch

Lo switch è un **commutatore di pacchetti a livello**. Ha il compito di inoltrare i frame in arrivo al giusto destinatario. Applica un policy di store e forward filtrando i frame Ethernet in base all'indirizzo MAC.

Gli switch sono dei dispositivi trasparenti, ovvero gli host sono inconsapevoli della loro presenza in quanto non possiedono un indirizzo MAC, e anche se lo possedessero, quel indirizzo non verrà mai usato come indirizzo di destinazione. 

Sono dispostivi plug and play basati sull'autoapprendimento, ovvero non è necessario configurarli.

Lo switch elimina le collisioni tra nodi, tranne per le collisioni tra nodo e switch. Dunque nodi diversi possono dialogare senza collisioni dal punto di vista CSMA/CD ma nel caso in cui due nodi voglio comunicare con lo stesso nodo, allora lo switch deve mettere in coda i frame, per non creare collisioni.

<img src="img/switch.png" width=400>

- A - A' e B - B' possono comunicare in contemporanea.
- A - A' e C - A' non possono comunicare in contemporanea.

Questo avviene solo quando il canale di trasmissione è half-duplex, dunque c'è bisogno del protocollo CSMA/CD.
Quando il canale di trasmissione è full-duplex non avvengono mai collisioni e dunque il protocollo CSMA/CD non serve. 

Le operazioni di filtraggio e inoltro di uno switch sono eseguite mediante una tabella di commutazione
(switch table). Tale tabella di commutazione è composta da voci (entries) per alcuni o per tutti i dipositivi della LAN, e ogni voce è composta da:

1. L'indirizzo MAC del nodo;
2. L’interfaccia dello switch che conduce al nodo;
3. Il momento in cui la voce per quel nodo è stata inserita nella tabella.

Come fa lo switch a conoscere su quale interfaccia inviare il frame se non presente nella tabella? Come funziona l'autoapprendimento dello switch?

Se lo switch non ha la corrispondeza MAC - interfaccia, applica il **flood**, cioè inoltra su tutte le interfacce eccetto quelle che già conosce, in pratica si tratta di un messaggio in broadcast.
Se lo switch ha la corrispondeza MAC - interfaccia, allora invia il frame su quel collegamento **selettivamente**, ovvelo lo manda su quel collegamento soltanto se mittente e destinatario non coincidono. Se coincidono bisogna aggiornare la tabbella e si scarta il frame.

**Funzionamento Switch**

```
1. Registra il collegamento in ingresso e l'indirizzo MAC dell'host mittente
2. Indicizzi la tabella degli switch utilizzando l'indirizzo MAC di destinazione
3. IF viene trovata una voce per la destinazione {
    IF la destinazione è sul segmento dal quale è arrivato il frame{
        scarta il frame
    }ELSE{
        inoltra il frame sull'interfaccia indicata nella voce
    }
} ELSE{
    flood
}
```

### Differenze tra router e switch

- Router: dispositivo a livello di rete. Calcola le tabelle di routing mediante algoritmi di instradamento e gli indirizzi IP. Gli algoritmi di instradamento possono trovare percorsi ottimali (senza cicli) nonostranze cicli nella topologia della rete.
- Switch: dispositivi a livello di collegamento. Calola le tabello di inoltro mediante l'autoapprendimento usando il flooding e gli indirizzi MAC. Gli switch devono essere collegati ad albero (Spanning Tree Protocol), per evitare che il traffico broadcast resti in circolazione per sempre.

## VLAN

VLAN (Virtual Area Network) è costituita da uno o più switch che supporti questa tecnologia. Vediamo ora a cosa sono utilizzate queste VLAN.

Una LAN normale sulla carta può funzionare ma in realtà presenta vari inconvenienti, per esempio:

- **Mancanza di isolamento del traffico**: In una LAN il traffico broadcast deve attraversare tutta la rete, anche quando magari non c'è bisogno, rendendo la rete LAN poco efficiente. Le prestazioni della LAN aumenterebbero se si potesse limitare il campo di tale traffico broadcast.
- **Uso inefficiente degli switch**: Invece di utilizzare tanti switch per ogni sottorete, si potrebbe utilizzare un unico switch con un maggiore numero di porte e configurare il switch in modo opportuno.
- **Gestione degli utenti**: Immaginiamo che un utente di CS si sposti nell'ufficio EE (connesso fisicamente allo switch EE) ma voglia rimanere connesso logicamente allo switch CS. L'unico modo è di usare un filo più grande. 

<img src="img/VLAN.png" width=300>

Tutte queste problematiche si possono risolvere con l'utilizzo di una o più VLAN, usando l'infrastruttura della LAN già presente.

- **Port Based VLAN**: Assegno le porte di uno switch in modo dinamico alle VLAN. È come avere più switch. Per far comunicare le VLAN tra di loro faccio affidamento al **routing**, ovvero i produttori di switch che permettono le VLAN implementano un router nello switch, quindi cominano switch e router. Se le VLAN sono implementate su più switch, per poter far comunicare le VLAN serve collegare gli switch tramite una porta di **trunk**. Dunque su ogni switch viene scelta una porta che viene abilitata come porta di trunk che crea un collegamento tra gli switch.

Ogni VLAN è identificata da un VLAN ID, usato per identificare le porte degli switch assegnate alle varie VLAN. 



