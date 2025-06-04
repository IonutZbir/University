"use strict"

async function fetchPeople() {
    try {
        const res = await fetch("http://localhost:3000/persone")
        const data = await res.json()
        return data.data
    } catch (error) {
        console.log("Error fetching data, ", error)
        return null
    }
}

function showAlert(person) {
    const text = "Nome: " + person.nome + " " + person.cognome + " Età: " + person.età
    alert(text)
}

async function showPeople() {
    const people = await fetchPeople()

    const ul = document.getElementById("people")
    people.forEach(el => {
        const li = document.createElement("li")
        li.addEventListener("click", () => showAlert(el))
        li.innerHTML = el.nome + " " + el.cognome
        ul.appendChild(li)
    });
}

showPeople()

const toggle = document.getElementById("toggle")
toggle.addEventListener("click", () => {
    const nav = document.getElementById("navbar")
    nav.classList.toggle("active")
})

const updateColors = document.getElementById("colors")
updateColors.addEventListener("click", () => {
    const a = document.querySelectorAll("a")

    a.forEach((item) => item.style.color = "#313131")

    const body = document.querySelector("body")
    body.style.backgroundColor = "#00796b"

})