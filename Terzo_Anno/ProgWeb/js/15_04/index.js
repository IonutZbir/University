"use strict";

function somma(a, b) {
    return a + b;
}

function calc() {

    let n1, n2, ret;
    
    // prompt ritorna una stringa, o eseguo il cast a int con `parseInt() o uso Number()`
    
    n1 = Number(prompt("Inserisci il primo numero: "));
    n2 = Number(prompt("Inserisci il secondo numero: "));
    
    ret = somma(n1, n2);
    
    alert("La somma è: " + ret);
}

calc();