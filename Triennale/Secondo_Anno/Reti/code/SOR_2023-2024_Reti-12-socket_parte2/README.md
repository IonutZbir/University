**Premesse**:
  - l'API C che stiamo usando per la programmazione delle socket è parte della specifica POSIX
  - questa API viene anche detta Berkeley sockets o BSD sockets come riconoscimento della prima
    implementazione in Berkeley Software Distribution (BSD) -- un sistema operativo, ora non piu'
    sviluppato, basato su Research UNIX (attualmente, il termine viene usato spesso per far
    riferimento ai discendenti open source)
  - nei programmi di questa lezione, sto usando la convenzione comune in molti programmi C di
    dichiarare le variabili locali all'inizio di una funzione. Inoltre, per le costanti sto
    usando il preprocessore
  - stiamo vedendo le API operanti in modalita' bloccante. Esse possono operare anche in modalita'
    non bloccante.

Ulteriori riferimenti (in aggiunta a quelli menzionati nella lezione precedente)
  - https://en.wikipedia.org/wiki/Berkeley_sockets
  - `man procfs` per informazioni sul procfs, uno pseudo-filesystem che fornisce una interfaccia
    per le strutture dati del kernel (https://manpages.ubuntu.com/manpages/jammy/man5/proc.5.html)

**Programmi**:
  - `iter_tcpserver` (TCP server iterativo)
    Potete interrogarlo con:

    `nc -N localhost 5000`

    l'opzione -N fa in modo che il quando incontrato EOF (che si puo' generare con CTRL+D), il client chiuda
    la propria parte della connessione (tramite uno shutdown), rimanendo in attesa che il server completi di
    scrivere dati e chiuda la propria parte della connessione.

    Ho notato che nc chiude effettivamente la connessione se CTRL+D viene premuto all'inizio del prompt
    (cioe' all'avvio o dopo un a capo). Altrimenti, invia i dati ma occorre premere una seconda volta CTLR+D

    Il nome "server iterativo" e' legato al fatto che il server itera sulle connessioni in attesa,
    accettandola una alla volta. Provate a connettervi due volte contemporaneamente!

  - approcci alternativi al server:
      - fork o thread per ciascun client: rischio di attacco DoS se non viene posto limite, overhead, specie nel caso dei processi
      - pool di thread o di processi creati in anticipo

**Osservazioni**:
  - se dimenticate htons quando settate il numero di porta, vedrete che il server andra' in
    ascolto su una porta diversa
  - se provate a togliere qualche cast, potete vedere il tipo di warning/errori segnalati da gcc


**Comandi**:
  - Esempi addizionali con ss (https://man7.org/linux/man-pages/man8/ss.8.html#USAGE_EXAMPLES), stati e espressioni