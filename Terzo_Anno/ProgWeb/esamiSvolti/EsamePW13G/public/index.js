"use strict"

async function fetchUsers() {
    try {
        const url = "http://localhost:3000/"
        const endpoint = "utenti"
        const res = await fetch(url + endpoint);
        const data = await res.json();
        return data.data;
    } catch (error) {
        console.log("Error during fetching data")
    }
}

async function fetchUser(id) {
    try {
        const url = "http://localhost:3000/"
        const endpoint = "utenti/" + id
        const res = await fetch(url + endpoint);
        const data = await res.json();
        if (data.status == "success"){
            return data.data;
        }
        else if(data.status == "fail"){
            console.log("Error: User undefined")
            return undefined
        }
        else if(data.status == "error"){
            console.log("Error: Bad Request")
            return undefined
        }
    } catch (error) {
        console.log("Error during fetching data")
    }
}

async function showUsers() {
    const users = await fetchUsers()
    
    const main = document.getElementById("content")

    users.forEach(user => {
        const card = document.createElement("div")
        card.className = "card"
        
        const nome = document.createElement("p")
        const cognome = document.createElement("p")
        const email = document.createElement("p")

        nome.innerHTML = user.nome
        cognome.innerHTML = user.cognome
        email.innerHTML = user.email

        card.addEventListener("click", () => getDetails(user.id))

        card.appendChild(nome)
        card.appendChild(cognome)
        card.appendChild(email)

        main.appendChild(card)
    });
}

async function getDetails(id) {
    const user = await fetchUser(id)
    if(user)
    {
        alert("Email: " + user.email)
    }
}

showUsers()