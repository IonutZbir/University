# Bluetooth

La tecnologia Bluetooth è principalmente utilizzata per sostiuire i collegamente cablati sulla scrivania. Quindi inceve di usare periferiche cablate, è molto più comodo usare periferiche Bluetooth.

Bluetooth serve a creare le cosidette **PAN (Personal Area Network)**, ovvero reti personali.

Bluetooth usa la banda ISM, con frequenza 2.4 - 2.5GHz, frenquenza altamente trafficata in quanto vi trasmetteva la vecchia teconologia WiFI, e tuttora molti apparati elettrici emettono radiazionielettromagnetiche su quella frequenza. Dunque Bluetooth è stato pensato con una particolare attenzione alle interferenze.

Bluetooth combina TDM e FDM con slot tipicamente di 625 $\mu s$ in ognuno dei queli vari utenti trasmettono in uno dei diversi 79 canali. In questo modo c'è garanzia che non vi siano collisioni.

Bluetooth fa uso della **tecnica Frequency-Hooping Spread Spectrum (FHSS)** il mittente cambia canale di trasmissione secondo una sequenza pseudo-casuale, in questo modo riduce le interferenze con altre fonti di radiazione elettromagnetica.

Bluetooth, opera in maniera ad hoc, quindi senza infrastruttura. La rete in cui opera Bluetooth è detta WPAN p **piconet**, in quanto è una rete di dimensione ridotta e vi sono pochi dispositivi. Infatti il numero massimo di dispositivi **attivi** è 8, di cui uno è il **Master** che si occupa di regolare la velocitò di trasimissione, il clock, il polling (per polling si intende il permesse di trasmettere dati) dei client, mentre i restanti sono appunto detti **Client**.

Quindi il Master deve dare il permesso a ciasun client di poter trasmettere. Dunque Bluetooth non solo combina TDM e FDM ma anche il **protocollo a rotazione** del polling.

Oltre ai dispositivi attivi, ci possono essere fino a 255 dispositivi **parked**, ovvero dispositivi addormentati che non possono trasmettere dati finché il master non cambia il loro stato da parked ad attivo.

Because Bluetooth ad hoc networks must be self-organizing, it’s worth looking
into how they bootstrap their network structure. When a master node wants to form a
Bluetooth network, it must first determine which other Bluetooth devices are within
range; this is the neighbor discovery problem. The master does this by broadcasting
a series of 32 inquiry messages, each on a different frequency channel, and repeats
the transmission sequence for up to 128 times. A client device listens on its chosen
frequency, hoping to hear one of the master’s inquiry messages on this frequency.
When it hears an inquiry message, it backs off a random amount of time between
0 and 0.3 seconds (to avoid collisions with other responding nodes, reminiscent of
Ethernet’s binary backoff) and then responds to the master with a message contain-
ing its device ID.

Poiché Bluetooth è una rete ad hoc, allora si deve auto-organizzare (bootstrapping), ovvero i nodi si autoassemblano nella piconet.

Quando un nodo master vuole creare una rete Bluetooth, deve prima determinare se ci sono dispositivi Bluetooth nel suo range, questo processo prende il nome di **Neighbor Discovery**. Il master invia ripetutamente messaggi di richiesta in broadcast per vedere i nodi disponibili, i dispositivi disponibili rispondono dopo un ritardo casuale. Una volta che il master ha scoperto i dispositivi, invita tali client ad unirsi alla sua piconet. Questo processo prende il nome di **Paging**. Quando riceve un ACK manda al dispositivo il pattern per il frequency hopping, il clock relativo allo slot FDM e un indirizzo da usare nella comunicazione.

**Beacon**: Dispositivi che inviano frequentemente un messaggio, per esempio con un identificatore.
Per esempio un beacon trasmette appena entro dentro casa e fa accendere le luci a quella sorca di ALEXA.
