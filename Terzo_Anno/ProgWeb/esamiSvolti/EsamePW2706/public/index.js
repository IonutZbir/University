"use strict"

async function fetchItems(completed=false) {
    let url = "http://localhost:3000/"
    let endpoint = "items"
    if (completed){
        endpoint = "items-complete"
    }
        
    try {
        const res = await fetch(url + endpoint);
        const data = await res.json();
        return data.data;
    } catch (error) {
        console.log("Error during fetching data")
    }
}

async function showItems(completed=false) {
	const items = await fetchItems(completed);

	let main = document.getElementById("content");
    main.innerHTML = ""

	items.forEach((item) => {

        const box = document.createElement("div")
        box.className = "box"
        const p = document.createElement("p")
        p.innerHTML = item.testo

        const btn = document.createElement("button")
        btn.innerHTML = "Completa"

        if(item.completato){
            p.style.textDecoration = "line-through";
            btn.disabled = true;
            btn.classList.add("disabled");
        }

        box.appendChild(p)
        box.appendChild(btn)

        main.appendChild(box)

	});
}

showItems()

const btnComplete = document.getElementById("completed")
btnComplete.addEventListener("click", () => showItems(true))

const btnAll = document.getElementById("all")
btnAll.addEventListener("click", () => showItems())

const btnChiaro = document.getElementById("chiaro")
btnChiaro.addEventListener("click", () => {
    const body = document.querySelector("body")
    body.classList.remove("dark-theme")

    const boxes = document.querySelectorAll(".box")
    
    boxes.forEach(box => {
        box.classList.remove("dark-theme-box")
    });

    const h = document.querySelector("header")
    const f = document.querySelector("footer")
    h.classList.remove("dark-theme-hf")
    f.classList.remove("dark-theme-hf")

})

const btnScuro = document.getElementById("scuro")
btnScuro.addEventListener("click", () => {
    const body = document.querySelector("body")
    body.classList.add("dark-theme")

    const boxes = document.querySelectorAll(".box")
    
    boxes.forEach(box => {
        box.classList.add("dark-theme-box")
    });
    
    const h = document.querySelector("header")
    const f = document.querySelector("footer")
    h.classList.add("dark-theme-hf")
    f.classList.add("dark-theme-hf")
})
