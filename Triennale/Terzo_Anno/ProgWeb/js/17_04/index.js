"use strict"

let calc = {
    n1 : 0,
    n2 : 0,
    insert(p1, p2){
        this.n1 = p1;
        this.n2 = p2;
    },
    add() {
        return this.n1 + this.n2;
    },
    
    sub() {
        return this.n1 - this.n2;
        
    },

    mul() {
        return this.n1 * this.n2;
        
    },

    div() {
        let res = this.n2 != 0 ? this.n1 / this.n2 : "Errore: non si può dividere per 0";
        return res;
    }
}

let giorni = [
    "lunedì",
    "martedì",
    "mercoledì",
    "giovedì",
    "venerdì",
    "sabato",
    "domenica",
]


giorni.unshift(giorni.pop())

giorni.forEach((giorno) => {
    console.log(giorno.toUpperCase())
});

// let a = ["pippo", "pluto"];

// a.map((el) => {
//     el.toUpperCase()
// });

// a.reduce((acc, item) => {
//     console.log(acc)
//     acc + item
// })


