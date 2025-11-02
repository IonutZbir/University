"use strict"

async function fetchProducts() {
    try {
        const url = "http://localhost:3000/"
        const endpoint = "prodotti"
        const res = await fetch(url + endpoint);
        const data = await res.json();
        return data.data;
    } catch (error) {
        console.log("Error during fetching data")
    }
}

async function showProducts() {
    const products = await fetchProducts()

    const main = document.getElementById("content")

    products.forEach(prod => {
        const div_prods = document.createElement("div")
        const nome = document.createElement("p")
        const price = document.createElement("p")

        div_prods.className = "product"

        nome.innerHTML = prod.nome
        price.innerHTML = prod.prezzo + " &euro;"
        
        div_prods.appendChild(nome)
        div_prods.appendChild(price)

        main.appendChild(div_prods)
    });
}

showProducts()