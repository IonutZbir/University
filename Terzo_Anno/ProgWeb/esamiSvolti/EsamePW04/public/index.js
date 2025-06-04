"use strict";

let data;

async function fetchData() {
	try {
		const res = await fetch("http://localhost:3000/data");
		data = await res.json();
		data.forEach((element) => {
			console.log(element);
		});
	} catch (error) {
		console.log("Error fetching data");
	}
}

async function showData() {
	const main = document.getElementById("content");
    main.innerHTML = ""
	data.forEach((element) => {
        const div = document.createElement("div")
        div.style.height = "10%"
        div.style.width = "10%"
        div.style.backgroundColor = element.colore
        div.style.position = "absolute"
        div.style.top = element.pos_vert + "%"
        div.style.left = element.pos_orizz + "%"
        div.addEventListener("click", () => {
            div.remove()
        })
        main.appendChild(div)
    });
}

const title = document.getElementById("title");
title.addEventListener("click", showData);

fetchData();
