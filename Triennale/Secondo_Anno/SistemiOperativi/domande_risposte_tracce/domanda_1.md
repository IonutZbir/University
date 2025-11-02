## Quesito

Il candidato discuta l'importanza dello scheduling nei sistemi batch, con particolare attenzione ai parametri che si cercano di ottimizzare in questi sistemi.
    Si chiede di presentare e descrivere almeno tre metodi di scheduling differenti applicati nei sistemi batch,
    specificando. 
    - quali aspetti di performance ciascuno di essi mira a migliorare
    - gli eventuali limiti

## Risposta

All'interno dei sistemi batch, i programmi detti anche job vengono eseguiti in modo sequenziale, e nella maggior parte 
dei casi, non è importante avere una risposa immediata. In questi sistemi, gli obiettivi sono di massimizzare il 
throuput, ovvero il numero di job eseguiti per ora, minimizzare il tempo di turnaround, ovvero il tempo di esecuzione
di ciascun job e di mantenere la CPU sempre occupata. Ci sono 3 algoritmi di scheduling per sistemi batch:
    - First Come, First Served. E' un algoritmo senza prelazione, infatti lo scheduler esegue il primo processo che arriva      per un tempo indeterminato, poi esegue gli altri processi in ordine di arrivo. E' un algoritmo semplice da 
      implementare, infatti lo scheduler ha bisogno di tenere una linked list, e ogni volta che arriva un nuovo processo 
      o viene bloccato il processo in esecuzione, viene messo in fondo alla lista. L'unico svantaggio e che puo portare
      a lunghi tempi di attesa per processi I/O bound in presenza di processi CPU bound.
    - Shortest Job First. E' un algoritmo senza prelazione, in cui c'è bisogno di sapere in anticipo il tempo di 
      esecuzione di ciascun processo. Lo scheduler sceglie di eseguire il processo con il minor tempo di esecuzione,
      andando a minimizzare il termpo di turnaround medio. Per esempio se ci sono 4 processi A (8 min), B (4 min),
      C (4 min), D (4 min), un ordine di esecuzione senza SJF sarebbe ABCD con tempo medio di 14 min e con SJF BCDA,
      con tempo medio di 11 min. L'algoritmo è ottimo quando i processi arrivano tutti allo stesso istante, mentre diventa
      inefficiente quando i processi arrivano in istanti diversi.
    - Shortest Remaining Time Next. E' una versione di SJF con prelazione, va a migliorare lo svantaggio di SJF, poichè
      quando arriva un nuovo processo, viene comparato il tempo di esecuzione del processo in esecuzione con il tempo
      di esecuzione del nuovo processo. Se il nuovo processo ci mette di meno, viene sceglto per l'esecuzione.
