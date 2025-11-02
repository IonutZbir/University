/*
    In Prolog, i predicati assert/1, retract/1 e predicati simili sono utilizzati per manipolare dinamicamente il database
    di fatti e regole durante l'esecuzione del programma. Questi predicati permettono di aggiungere, rimuovere e modificare 
    fatti o regole nel database di Prolog, consentendo una gestione dinamica delle conoscenze.
*/

/*
 * assert() -> Il predicato assert/1 è utilizzato per aggiungere un nuovo fatto o una nuova regola al database.
                Quando un fatto o una regola viene "asserito" (inserito) nel database, esso diventa parte della 
                conoscenza del sistema e può essere usato per rispondere a query successive.
 * retract() -> Il predicato retract/1 è utilizzato per rimuovere un fatto o una regola dal database. 
 *              Se nel database esiste un fatto o una regola che corrisponde a quella specificata in retract/1, esso viene rimosso.
 * retractAll() -> Il predicato retractall/1 è una variante di retract/1, che rimuove tutti i fatti o regole che 
 *                      corrispondono al predicato specificato. Questo è utile se ci sono più istanze di un fatto o regola e 
 *                      vuoi rimuoverle tutte.
 * assertz() -> Aggiunge il nuovo fatto o regola alla fine del database (è equivalente a assert/1).
 * asserta() -> Aggiunge il nuovo fatto o regola all'inizio del database.
 * consult() -> legge una riga e fa assert
*/

:- dynamic cat/1.

assert(cat(tom)). 
assert(cat(michi)).
retract(cat(tom)).
retractAll(cat(_)).

/*
    In Prolog, il termine dynamic è utilizzato per dichiarare che un predicato può essere modificato durante
    l'esecuzione del programma. Questo significa che i fatti e le regole associati a quel predicato possono essere aggiunti 
    o rimossi dal database di Prolog usando predicati come assert/1, retract/1, e simili. 

    :- dynamic predicato/n. 
        - predicato è il nome del predicato.
        - n è il numero di argomenti che prende.
*/

/*
 * =.. (univ) -> lun(0, 1) =.. [lun, 0, 1]
 * A =.. [lun, 0, 1] possiamo generaere predicati e unificarli ad una variabile
*/

/* Funtore = nome di A*/
/* funtore(lun([], 0), X)*/

funtore(A, Funtore) :-
    A =.. [Funtore|_].


