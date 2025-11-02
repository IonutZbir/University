"use strict"

async function fetchColors() {
    try {
		const res = await fetch("http://localhost:3000/colors");

		if (!res.ok) {
			console.error("Errore di rete o dati non trovati:", res.status);
			return null;
		}

		const data = await res.json();
		return data;
	} catch (err) {
		console.error("Errore nella richiesta:", err);
		return null;
	}
}

function createSectionsWithColors(colors) {
	const main = document.getElementById("content");

	// Svuota eventuali contenuti precedenti
	main.innerHTML = "";

	colors.forEach((color) => {
		const section = document.createElement("section");
		const title = document.createElement("p");
		section.className = "color";
		title.className = "colorTitle";

		title.innerHTML = color.titolo;

        section.style.backgroundColor = color.colore;

		section.appendChild(title);
		main.appendChild(section);
	});
}

async function showColors() {
	const colors = await fetchColors();

	if (!colors) {
		console.log("Errore durante il recupero di colori");
		return;
	}

	if (colors.length === 0) {
		console.log("Nessun colore trovato");
		return;
	}

	createSectionsWithColors(colors);
}

async function main(){
    const btn = document.getElementById("btn")
    const overlay = document.getElementById("overlay")
    btn.addEventListener("click", () => {
        overlay.style.display = "none"
    })
    
    showColors()
}

main()