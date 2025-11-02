# Ritardi

Ritardi e Perdite
Non solo ritardo di trasmissione, vi sono altri fattori da considerare.
Anzitutto quando un pacchetto è pronto per essere trasmesso (è arrivato nella sua interezza secondo la tecnica store-forward) vi è un ritardo di elaborazione da parte del router per eseguire la funzione di inoltro (leggere il pacchetto, accedere alla tabella etc…). Questo ritardo è nell’ordine dei microsecondi.
Si ha poi il ritardo di accodamento che è il ritardo generato dal fatto che un pacchetto che deve essere trasmesso in una certa linea di uscita non può perché ce ne sta già un altro o più ad attendere di essere trasmesso -> il pacchetto va nel buffer. Dipende dal livello di congestione del router (casuale).
Il ritardo di trasmissione è quello che dipende dalla formula L/R.
Il ritardo di propagazione è il corrispettivo del ritardo di propagazione ma in senso puramente fisico, legato alla lunghezza d del collegamento fisico e alla velocità di propagazione del segnale v (tipicamente velocità della luce 2x10^8)
dprop = d/v
Il ritardo end to end rappresenta l’accumulo di ritardi per ogni nodo lungo il percorso sorgente-destinazione per l’invio del pacchetto. Si ha:
dend-to-end = sum-perogni-i (delab-i + dacc-i + dtrasm-i + dprop-i)
Ogni ritardo è misurato in ms. 
Definiamo come intensità di traffico la formula L a / R, dove L lunghezza del pacchetto in bit, R larghezza di banda e a la velocità media di arrivo dei pacchetti.