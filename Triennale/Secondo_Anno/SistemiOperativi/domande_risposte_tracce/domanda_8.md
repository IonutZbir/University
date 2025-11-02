## Quesito

Il candidato discuta l'importanza dello scheduling nei sistemi interattivi, con particolare attenzione ai parametri che si cercano di ottimizzare in questi sistemi.
Si chiede di presentare e descrivere almeno tre metodi di scheduling differenti applicati nei sistemi interattivi, specificando 
    - quali aspetti di performance ciascuno di essi mira a migliorare
    - gli eventuali limiti

## Risposta

Nei sistemi interattivi, l'utente si aspetta che il sistema dia risposte immediate alle sue richieste, perciò è molto 
importante lo scheduling, poiche bisogna sempre andare a gestire interrupt, e multipli processi eseguiti in parallelo.

Quindi in questi sistemi, ciò che si cerca maggiormente di ottimizare sono i tempi di risposta alle richieste degli utenti

Alcuni algoritmi di scheduling nei sistemi interattivi sono:

1. Round Robin Scheduling

E' il più vecchio algoritmo di scheduling, è molto semplice ed anche molto usato. E' un algoritmo con prelazione, poichè 
ad ogni processo viene assegnato un quanto di tempo. Ciascun processo viene eseguito per il suo quanto di tempo, se 
supera il quanto, viene bloccato e messo in fondo alla lista. E' molto semplice da implementare in quanto c'è bisogno 
di una sola lista di processi pronti. E' un algoritmo equo in quanto ad ogni processo viene assegnato lo stesso quanto.
Un problema sta nel trovare il giusto quanto di tempo, per bilanciare l'overhead tra il cambio di contesto e la durata 
effettiva dell'esecuzione.

2. Scheduling a priorità

Ad ogni processo viene assegnata una priorità, e di conseguenza lo scheduler andrà a scegliere sempre i processi con 
priorità più grande. Ad ogni interrupt la priorità viene decrementata e quando il la priorità del processo in esecuzione
scade sotto una certa soglia, viene bloccato e viene eseguito il processo successivo con priorià maggiore. Inoltre è 
anche possibile assegnare un quanto di tempo a ciscun processo oltre che la priorità. Un evoluzione di questo algoritmo
è di dividere i processi in classi di priorità, andando a usare questo lo scheduling a priorità tra le classi, e nelle 
classi usare un algoritmo tipo Round Robin.
E' un algoritmo equo in quanto processi più importanti avranno priorità maggiori e processi meno importanti avranno 
priorità più basse.

3. Scheduling a lotteria

Si è pensato di assegnare le risorse del sistema con uno schema a lotteria, ovvero a ciascun processo vengono assegnati
dei "biglietti della lotteria", per esempio per l'utilizzo della CPU. Lo scheduler, semplicemente dovra estrarre i 
biglietti per decidere quale processo eseguire. A processi più importanti possono essere assegnati biglietti extra, per
avere maggiore possibilità di vincita. Permette inoltre ai processi di cooperare, ovvero di scambiarsi biglietti, 
inoltre è ottimo quando arrivano processi nuovi, in quanto bisogna semplicemente assegnare a loro i biglietti.

