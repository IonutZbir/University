"use strict"

let prods = []

async function fetchData() {
    try {
        const res = await fetch("http://localhost:3000/prod")
        const data = await res.json()
        prods = data.data
    } catch (error) {
        console.log("Error fetching data", error)
    }
}

async function decrease(el, idx){
    const n = document.getElementById(idx)
    el.numero--;
    n.innerHTML = "Numero: " + el.numero
}

async function showProds() {
    await fetchData()
    const main = document.getElementById("content")

    prods.forEach((el, idx) => {
        const div = document.createElement("div")
        const name = document.createElement("p")
        const n = document.createElement("p")
        n.id = idx
        div.className = "box"

        div.addEventListener("click", () => decrease(el, idx))
        name.innerHTML = "Prodotto: " + el.prodotto
        n.innerHTML = "Numero: " + el.numero

        div.appendChild(name)
        div.appendChild(n)

        main.appendChild(div)
        console.log(el)
    });
}

setTimeout(showProds, 5000)