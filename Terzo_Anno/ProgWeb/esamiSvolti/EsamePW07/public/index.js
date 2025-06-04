"use strict";

async function fetchData() {
	try {
		const res = await fetch("http://localhost:3000/citations");
		const data = await res.json();
		return data.data;
	} catch (error) {
		console.log("Error fetching data", error);
		return null;
	}
}

async function showFrase(valore, frase) {
	const div = document.getElementById("frase");
    div.style.display = "block"
    div.innerHTML = ""
	const text = document.createElement("p");
	const val = document.createElement("p");
    text.innerHTML = frase
    val.innerHTML = valore
    div.appendChild(text)
    div.appendChild(val)
}

async function showCitations() {
	const citations = await fetchData();
	const ul = document.getElementById("list");
	citations.forEach((el) => {
		const li = document.createElement("li");
		const a = document.createElement("a");

		li.appendChild(a);
		a.innerHTML = el.ID;
		a.addEventListener("click", () => showFrase(el.valore, el.frase));

		ul.appendChild(li);
	});
}

showCitations();
