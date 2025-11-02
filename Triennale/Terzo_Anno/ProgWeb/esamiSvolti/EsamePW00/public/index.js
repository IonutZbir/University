"use strict";

async function fetchArticles() {
	try {
		const res = await fetch("http://localhost:3000/articles");

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

function createSectionsWithArticles(articles) {
	const articlesDiv = document.getElementById("articles");

	// Svuota eventuali contenuti precedenti
	articlesDiv.innerHTML = "";

	articles.forEach((article) => {
		const section = document.createElement("section");
		const title = document.createElement("p");
		const content = document.createElement("p");
		section.className = "article";
		title.className = "articleTitle";

		title.innerHTML = article.titolo;
		content.innerHTML = article.contenuto;

		section.appendChild(title);
		section.appendChild(content);
		articlesDiv.appendChild(section);
	});
}

async function showArticles() {
	const articles = await fetchArticles();

	if (!articles) {
		console.log("Errore durante il recupero articoli");
		return;
	}

	if (articles.length === 0) {
		console.log("Nessun articolo trovato");
		return;
	}

	createSectionsWithArticles(articles);
}

function menu() {
	const toggleBtn = document.getElementById("menuToggle");
	const menu = document.getElementById("mobileMenu");

	toggleBtn.addEventListener("click", () => {
		if (window.innerWidth < 1000) {
			menu.classList.toggle("active");

			// Cambia colore della scritta MENU
			if (toggleBtn.style.color === "black") {
				toggleBtn.style.color = "red";
			} else {
				toggleBtn.style.color = "black";
			}
		}
	});
}

async function main() {
	await showArticles();
    menu()
}

main();
