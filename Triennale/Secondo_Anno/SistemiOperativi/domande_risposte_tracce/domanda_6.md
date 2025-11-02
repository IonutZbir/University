## Quesito 

Discutere almeno 3 algoritmi di paginazione, specificando vantaggi e funzionamento.

## Risposta

Quando avviene un page fault, il sistema operativo attraverso algoritmi di sostituzione delle pagine, deve cercare e trovare una pagina da sfrattare per poter fare spazio.

1. Uno dei algoritmi pià facile da implementare è NRU (Not Recently Used). Questo algoritmo tiene traccia delle pagine attraverso i bit R (Riferimento) e M (Modificato)
è le suddivide in 4 classi. Inoltre ad ogni interrupt, il bit R impostato a 0. 

- 00 - R = 0, M = 0 (nessun riferimento, non modificata)
- 01 - R = 0, M = 1 (riferimento, non modificata)
- 10 - R = 1, M = 0 (nessun riferimento, modificata)
- 11 - R = 1, M = 1 (riferimento, modificata)

Al primo sguardo, la classe 1 sembra impossibile, ma si ottiene quando viene impostato a 0 il bit R dopo l'interrupt del clock di una pagina di tipo 3.
L'algoritmo rimuove una pagina a caso dalla classe con numero più basso. E' facile da implementare, semplice, e prestazioni accettabili.

2. Second Chance
E' un evoluzione dell' algoritmo FIFO (First In First Out), di conseguenza abbiamo una linked list delle pagine, quando avviene un page fault, si scorre la lista e si va a guardare
il bit R della pagina, se il bit è 1 allora significa che è stato fatto riferimento alla pagina nell'ultimo clock, quindi viene impostato a 0 e messa in fondo alla lista
e si passa alla prossima. L'algoritmo rimuove (se la pagina è sporca) o riscrive (se pulita) la pagina con bit R = 0. Quando tutte le pagine hanno R = 1, Second Chance diventa FIFO.

3. Clock
E' una lista circolare di frame, con un puntatore simile ad una lancetta, se il bit R è 0 la pagina viene rimossa e ne viene inserita una nuova al suo posto.
Se il bit R è 1, viene azzerrato e la lancetta viene spostata in avanti. E' più efficiente di FIFO è Seconda Chance.

