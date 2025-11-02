# ARM

## Introduzione

L'architettura ARM definisce una famiglia di microprocessori RISC (Reduced Istruction Set Computer) a 32 e 64 bit svilippata da ARM (Advanced RISC Machine). Al contrario delle architetture CISC, i processori ARM hanno bisogno di tanti registri per poter massimizzare il throughput di istruzioni avendo a disposizione un set ridotto.

Oltre alle caratteristiche generiche di un architettura RISC, ovvero l'elaborazione dei dati deve avvenire all'interno del processore senza l'intervento della memoria, dunque deve accedere alla memoria solo per operazioni di *load/store*. Le istruzioni devono essere decodificate rapidamente e questo può avvenire solo se hanno un formato regolare e una lunghezza fissata, e inoltre, l'indirizzamento non deve avvenire in troppi passaggi. A queste caratteristiche, l'architettura ARM prevede:

- Un datapath specifico che permette di eseguire inseme le funzioni aritmetico-logiche con quelle di scorrimento su più bit;
- Indirizzamento con autoincremento e autodecremento per ottimizzare i cicli nei programmi;
- Esecuzione di istruzioni di load/store multiple per ottimizzare il throughput dei dati;
- Istruzioni con pre-condizione che vincola l'esecuzione dell'istruzione stessa (*esecuzione condizionale*) che permette al processore ARM di compiere in un unico passaggio quello che per altre CPU richiede l'esecuzione di più istruzioni.

## Il processore ARM

Il processo ARM utilizza un'architettura a 32 bit, dimensione che coincide con quella dei registri, delle istruzioni e dei dati su cui operano tali istruzioni.

Lo spazio di indirizzamento è di 32 bit, e la memoria è indirizzabile al singolo byte, a 16 (halfword) o 32 bit (word).
Il processore ARM può indirizzare fino a $2^{32}$ locazioni di memoria sia nel formato *little-endian (default)* sia *big- endian*. Per abilitare la lettura big-endian, bisogna asserire il pin BIGEND.

Il processore ARM non possiede un istruzione per eseguire la divisione.

## Il modello di programmazione

I processori ARM dispongono di tanti registri per velocizzare le operazioni e il cambio di contesto necessario nella gestione delle eccezioni o nelle operazioni privilegiate.

Le eccezioni sono eventi asincroni che si verificano di fronte a interruzioni hardware attraverso l'asserzione di segnale su un pin del processore, di un interruzione software, di un errore o di un reset.

Quando il processore ARM ha gli interrupt abilitati, è in grado di riconoscere due tipi di interruzioni hardware a diversa priorità:

- $\overline{IRQ}\ (Interrupt\ ReQuest)$ è riconosciuta una interruzione di un dispositivo di bassa priorità;
- $\overline{FIQ}\ (Fast\ Interrupt\ reQuest)$ è riconosciuta una interruzione di un dispositivo di alta priorità;

### Registri

In ARM sono presenti 37 registri a 32 bit, di cui 20 sono duplicati e possono essere utilizzati in sostituzione degli originali quando il processore entra nella modalità privilegiata per rispondere ad una eccezione.

- **16 registri da $R0$ a $R15$**:
    - $R0 - R12$ sono i *General Purpose Register*, utilizzabili dal programmatore
    - $R13$ è lo *Stack Pointer (SP)*
    - $R14$ è il *subroutine Ling Register (LR)*, il registro utilizzato per ripristinare il PC alla istruzione successiva alla chimata ad una subroutine, quando quest'ultima ha terminato l'esecuzione
    - $R15$ è il *Program Counter (PC)*
- **Current Program Status Register (CPSR)**
- **20 registri non accesibili nel modo utente/sistema**:
    - 5 registri da $R8\_FIQ$ a $R12\_FIQ$
    - 10 registri attivi solo nella modalità di risposta ad una eccezione
    - 5 registri attivo uno per volta nella modlità di risposta ad una eccezione che permette di salvare il contenuto del registro di stato corrent CPSR ne registro SPSR.

## CPSR

- *Flag N (Negativo)*: Dipende dall'ultima operazione che ha modificato il registro CPSR. Se il risultato  è minore di 0, $N = 1$, altrimenti $N = 0$.
- *Flag Z (Zero)*: Z = 1 se il risultato dell'ultima operazione che ha impostato il registro di stato è zero. 
- *Flag di riporto o Carry*: C = 1 se durante un'addizione c'é un riporto. C = 0 durante una sottrazione se è richiesta una cifra in prestito.
- *Flag di oVerflow*: V = 1 se l'istruzione che ha impostato il registro di stato ha causato una condizione di overflow.

I più imortanti: (NZCV)

## Logical Shift Left (LSL)

## Logical Shift Right (LSR)

## Arithmetic Shift Right (ASR)

## Rotate Right (ROR)

## Rotate Right con estensione (RRX)

## Rotate Left con estensione (RLX)

## Le modalità di indirizzamento

