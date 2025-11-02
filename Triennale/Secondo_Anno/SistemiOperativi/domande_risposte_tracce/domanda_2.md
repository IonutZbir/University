## Quesito

Il candidato spieghi il concetto di memoria virtuale e il suo ruolo nella gestione della memoria RAM da parte
di un sistema operativo moderno.
Si discuta come la memoria virtuale permetta di gestire programmi che superano la capacità della memoria fisica 
disponibile.
Si descrivano inoltre le tecniche di paging e segmentazione, evidenziando come queste tecniche abbiano migliorato
l'efficienza e la gestione della memoria nei computer.

## Risposta

La memoria virtuale è una tecnica utilizzata nei sistemi moderni per astrarre la memoria principale. Permette di assegnare
più memoria ad un processo di quanta c'è ne a disposizione nella macchina, dando l'impressione a ciascun processo di avere
uno spazio degli indirizzi privato e contiguo. La memoria virtuale utilizza la paginazione, ovvero la memoria viene divisa
in pagine di dimesione fisse, di solito 4 KB che vengono mappate nella memoria fisica in frame di stesse dimesioni. Alcuni
sistemi permettono di avere pagine di dimesioni diverse, per esempio al kernel può essere assegnata una pagina di 1 GB.
Quando un processo fa riferimento ad un indirizzo virtuale, esso viene prima convertito dalla MMU in indirizzo fisico per 
poi essere posto sul bus. La MMU è un cirtuito all'interno della CPU che si occupa di convertire indirizzi virtuali in 
indirizzi fisici. Per esempio con indirizzi da 16 bit, si possono mappare 16 pagine da 4 KB, ovvero 64 KB di memoria 
virtuale, in 8 frame da 4 KB, ovvero una RAM da 32 KB. I primi 3 bit su 16, sono utilizzati come indice all'interno della
tabella delle pagine (ciascun processo dispone di una propria tabella delle pagine, nella quale si trovano le pagine 
usate e non dal processo), in questa tabella si trova il numero del frame fisico sul quale è presente la pagina in memoria. I restanti 12 bit sono i bit di offset, ovvero i bit utilizzati per spostarsi all'interno della pagina o del frame.
Quando viene fatto un riferimento ad una pagina che non si trova all'interno della tabella delle pagine, avviene un Page 
Fault. In questo caso il sistema operativo, attraverso algoritmi di sostituizione delle pagine sceglie una pagina da 
sfrattare per fare spazio. Per velocizzare il meccaniscmo di conversione di un indirizzo virtuale in indirizzo fisico, è 
stato introdotta il TLB, un cirtuito all'interno della MMU che contiene una mini tabella delle pagini, contenente le 
pagine più utilizzate di un processo. Quando avviene un riferimento in memoria, l'MMU prima di cercare all'interno della
tabella delle pagine, cerca la pagina all'interno del TLB.
Un altra tecnica oltre alla paginazione è la segmentazione, usata fino a qualche decennio fa. Nella segmentazione la 
memoria viene divisa in segmenti di dimensioni diverse, offrendo maggiore flessibilità, semplifica il linking, poichè ogni
processo occupa un unico segmento, semplificando il linking, e offre la possibilità di applicare vari livelli di 
protezione. Un grande svantaggio della segmentazione è la frammentazione esterna, che può essere risolto tramite la 
compattazione, ma è un operazione molto costosa. Rispetto alla segmentazione, la paginazione ha solamente frammentazione
interna, poichè l'ultima pagina è sempre vuota circa per metà.

