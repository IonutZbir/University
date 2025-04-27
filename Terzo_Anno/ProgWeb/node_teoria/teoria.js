"use strict";

// Proviamo a leggere dei dati json da file

const fs = require("fs")

/*  
    Legge il contenuto del file in modo non bloccante,
    ovvero mentre aspetta di leggere il file il programma continua con la sua esecuzione
*/
fs.readFile("data.json", "utf-8", (err, data) => {
    if (err) throw err;
    console.log("ASYNC")
    console.log(data)
})

/*
    Legge il file in modo bloccante, ovvero sincrona, il programma si ferma finchè la lettura non è completata
*/
// JSON.parse converte stringa in JSON
// JSON.strigify converte JSON in stringa

const data = JSON.parse(fs.readFileSync("data.json", "utf-8"))
console.log(data)


