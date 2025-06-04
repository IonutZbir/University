"use strict";

async function fetchArticles() {
	try {
		const res = await fetch("http://localhost:3000/articoli");
		return await res.json();
	} catch (error) {
		console.log("Error fetching data");
		return null;
	}
}

async function fetchAuthors() {
	try {
		const res = await fetch("http://localhost:3000/autori");
		return await res.json();
	} catch (error) {
		console.log("Error fetching data");
		return null;
	}
}

function showDetails(titolo, autore) {
	const text =
		"Titolo: " +
		titolo +
		"\nAutore: " +
		autore +
		"\nContenuto: It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English.";
	window.alert(text);
}

async function showArticles() {
	const articles = await fetchArticles();
	const container = document.getElementById("content");

	articles.forEach((element) => {
		const box = document.createElement("div");
		box.className = "box";
		const title = document.createElement("h4");
		title.innerHTML = element.titolo;

		const autore = document.createElement("p");
		autore.innerHTML = "Autore: " + element.autore;

		const desc = document.createElement("p");
		desc.innerHTML = element.contenuto;

		const btn = document.createElement("button");
		btn.textContent = "Mostra dettagli";
		btn.addEventListener("click", () =>
			showDetails(element.titolo, element.autore)
		);

		box.appendChild(title);
		box.appendChild(autore);
		box.appendChild(desc);
		box.appendChild(btn);

		container.appendChild(box);
	});
}

async function showModal() {
	const authors = await fetchAuthors();

	const ul = document.getElementById("elenco");
	ul.innerHTML = "";
	authors.forEach((element) => {
		const li = document.createElement("li");
		li.innerHTML = element;
		ul.appendChild(li);
	});

	document.getElementById("overlay").classList.add("visible");
}

showArticles();

const menuToggle = document.getElementById("toggle");
menuToggle.addEventListener("click", () => {
	document.getElementById("navbar").classList.toggle("active");
});

const modal = document.getElementById("showAuthors");
modal.addEventListener("click", showModal);

const modalToggle = document.getElementById("modalToggle");
modalToggle.addEventListener("click", () => {
	document.getElementById("overlay").classList.remove("visible");
	document.getElementById("modal").classList.remove("visible");
});
