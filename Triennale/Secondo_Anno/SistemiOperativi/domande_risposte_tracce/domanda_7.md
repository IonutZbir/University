## Quesito

Discutere l'importanza degli interrupt e di come vengono gestiti dal sistema operativo.

## Risposta

Gli interrupt sono un meccaniscmo di notifica da parte dell'hardware verso la CPU. Sono molto importanti nei sistemi 
interrativi in quanto l'utente si aspetta risposte rapide da parte del sistema. Hanno prioritò maggiore rispetto ai 
processi utente, quindi vengono gestiti subito, appena arrivano. Quando avviene un interrupt da parte dell'hardware, 
viene gestito immediatamente se non c'è ne uno in corso. L'hardware invia alla CPU un numero, per identificare il 
tipo di interrupt, questo numero viene poi usato come indice all'interno del vettore degli interrupt, nel quale si 
in ciascuna posizione si trova l'indirizzo di memoria della ISR (Interrupt Service Routine), routine che gestisce 
l'interrupt. A questo punto il sistema operativo deve: 

- bloccare il processo corrente, salvare lo stato del processo mediante piccole e veloci routine assembly.
- impostare l'MMU e forse la TLB per la routine.
- eseguire la ISR. Una volta eseguita, manda un messaggio di conferma.
- a questo punto, il SO, chiama lo scheduler per decidere quale processo eseguire, il processo bloccato, il processo che
magari era bloccato poiche in attesa di I/O, adesso pronto per l'esecuzione oppure un altro processo a caso. 
- una volta scelto il processo da eseguire bisogna impostare di nuovo l'MMU e la TLB pe il nuovo processo.
