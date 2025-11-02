"use strict";

async function fetchEventi() {
    try {
        const res = await fetch("http://localhost:8000/eventi") // GET http://localhost:8000/eventi
        const body = await res.json()
        return body.data
    } catch (error) {
        console.log("Errore durante il fetch degli eventi")
    }
}

async function showEventi() {
    const eventi = await fetchEventi()

    const section_eventi = document.getElementById("eventi")

    eventi.forEach(e => {
        const card = document.createElement("div")
        card.classList.add("card")

        const titolo = document.createElement("p")
        titolo.className = "card-title"
        titolo.innerHTML = e.titolo

        const luogo = document.createElement("p")
        luogo.className = "card-content"
        luogo.innerHTML = e.luogo

        const button = document.createElement("button")
        button.className = "card-button"
        button.innerHTML = "Dettagli"
        button.addEventListener("click", () => showAlertDetails(e.descrizione, e.partecipanti)) // richiamo la funzione di callback usando un'arrow function, per potergli passare dei parametri

        card.appendChild(titolo)
        card.appendChild(luogo)
        card.appendChild(button)

        section_eventi.appendChild(card)

    });   
}

// Funzione per mostrare i dettagli dell'evento
function showAlertDetails(descrizione, partecipanti) {
    //alert(`Descrizione: ${descrizione}\nPartecipanti: ${partecipanti}`); formatted string
    alert("Descrizione: " + descrizione + "\n" + "Partecipanti: " + partecipanti)
}

showEventi()



const toggle = document.getElementById("toggle");
toggle.addEventListener("click", () => {
	document.getElementById("nav").classList.toggle("visible");
});

