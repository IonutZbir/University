"use strict";

async function fetchCounter() {
	try {
		const res = await fetch("http://localhost:3000/counter");
		const data = await res.json();
		return data;
	} catch (err) {
		console.log("Error fetching data ", err);
		return;
	}
}

async function fetchColors() {
	try {
		const res = await fetch("http://localhost:3000/colors");
		const data = await res.json();
		return data;
	} catch (err) {
		console.log("Error fetching data ", err);
		return;
	}
}

async function updateCounter(type) {
	try {
		let endpoint = "";
		if (type === "add") {
			endpoint = "increase";
		} else if (type === "dec") {
			endpoint = "decrease";
		}

		await fetch(`http://localhost:3000/${endpoint}`, {
			method: "POST",
		});

		await showCounter();
	} catch (error) {
		console.log("Connection error", error);
	}
}

async function changeColors() {
	const colors = await fetchColors();
	const background = colors.background;
	const text = colors.text;

	const header = document.getElementById("header");
	const footer = document.getElementById("footer");
	const menuLinks = document.querySelectorAll("#header nav ul li a");

	menuLinks.forEach(item => {
		item.style.color = text
	})

	header.style.backgroundColor = background
	footer.style.backgroundColor = background

	header.style.color = text
	footer.style.color = text
	
}

async function showCounter() {
	const counter = await fetchCounter();
	const p = document.getElementById("counter");
	p.innerHTML = counter.counter;
}

function menuToggle() {
	document.getElementById("navbar").classList.toggle("active");
}

async function main() {
	await showCounter();
	const add = document.getElementById("add");
	const dec = document.getElementById("dec");
	const toggle = document.getElementById("menuToggle");
	const col = document.getElementById("col");

	add.addEventListener("click", () => updateCounter("add"));
	dec.addEventListener("click", () => updateCounter("dec"));
	col.addEventListener("click", () => changeColors());
	toggle.addEventListener("click", () => menuToggle());

}
main();
