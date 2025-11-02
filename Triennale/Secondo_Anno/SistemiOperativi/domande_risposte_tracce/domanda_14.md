## Quesito

Cosa è un processo? Quali sono i stati di un processo?

## Risposta

Un processo è un programma in esecuzione. Tutto il software eseguibile sul computer, incluso il sistema operativo è organizzato a processi. La parte del sistema operativo che si 
occupa di decidere quale processo assegnare alla CPU per l'esecuzione è detto scheduler e il meccanisco è detto algoritmo di scheduling. In sistemi monoprocessore, i processi sono 
eseguiti sequenzialmente, ma in modo molto rapido, dando comunque l'illusione all'utente di parallelismo. Mentre si parla di vero parallelismo in sistemi multiprocessore, dove 
ciascuna CPU esegue un processo. All'avvio del sistema viene eseguite il primo processo, detto init che ha PID 1, il PID è il identificatore univoco di ciascun processo all'interno
del sistema operativo. In alcuni sistemi, il PID 2 è il processo kthread, ovvero il processo che si occupa della gesiote dei thread a livello kernel.

In UNIX i processi sono organizzati in modo gerarchico, secondo la gerarchie Parent - Child. In questo modo, c'è meno rischi di avere processi zombie, ovvero processi che sono inattivi
e che non possono essere eseguiti, perché quando il processo padre termina la sua eseguzione, il sistema operativo termina l'esecuzione di tutti i suoi processi figli.
Quando un processo crea un processo figlio, il filgio è un clone del padre, ha il proprio spazio degli indirizzi, i prori registri, come Program Counter o PSW, e viene eseguite in 
parallelo, indipendentemente dal padre. 

Ci sono 4 casi in cui avviene la creazione di un processo. All'avvio del sistema, vengono eseguiti decine o centinaia di processi, un processo viene create da un a altro processo, 
usando per esempio la chiamata di sistema fork(), può essere creato a richiesta di un utente oppure mediante lavori batch. La terminazione di un processo, invece può essere volontaria
per esempio il processo termina semplicemente la sua esecuzione dopo aver svolto il suo compito oppure involontario, per esempio terminazione causata da un errore fatale,
come segmentation fault.

Il processo, durante il suo ciclo di vita si può trovare in 3 diversi stati. Ready (il processo è in uno stato di attesa, ma è pronto per essere eseguito), 
Blocked (il processo è in uno stato di attesa, ma non è pronto per l'esecuzione, poichè in attesa di qualche risorsa), Running (il processo è in esecuzione).

Tra questi 3 stati ci sono 4 configurazioni.

- Running - Blocked: Avviene quando il processo blocca la sua esecuzione perchè in attesa di qualche risorsa (I/O). 
- Running - Ready: Avviene quando lo scheduler decide di eseguire un altro processo, magari con priorità maggiore, e il processo attuale è ancora pronto per l'esecuzione, e viene 
semplicemente messo in lista di attesa.
- Ready - Running: Il processo viene scelto dallo scheduler per l'esecuzione.
- Blocked - Ready: Il processo ha ottenuto la risorsa ed è pronto per essere eseguito. Viene posto nella lista dei processi pronti per l'esecuzione.
