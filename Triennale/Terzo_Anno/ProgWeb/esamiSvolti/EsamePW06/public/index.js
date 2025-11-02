"use strict";

let nDivs = 0;

async function fetchData() {
	try {
		const res = await fetch("http://localhost:3000/list");
		const data = await res.json();
        return data.data
	} catch (error) {
		console.log("Error fetching data, ", error);
		return null;
	}
}

async function fetchPicById(id) {
	try {
		const res = await fetch("http://localhost:3000/pics/" + id);
		const data = await res.json();
		if(res.ok)
		    return data.data;
	} catch (error) {
		console.log("Error fetching data, ", error);
		return null;
	}
}

async function showModal(id) {
    const pic = await fetchPicById(id)

    const banner = document.createElement("div")
    const body = document.querySelector("body");
    banner.className = "banner"
    banner.innerHTML = pic.desc
    body.appendChild(banner)
}

async function loadFourDivs(n = 0) {
	const data = await fetchData();
	const ul = document.getElementById("content");

	for (let index = n; index < 4 + n; index++) {
		const element = data[index];
		if (element !== undefined) {
			const box = document.createElement("li");
			const a = document.createElement("a");
			box.className = "box";
            a.addEventListener("click", () => showModal(element))
			a.innerHTML = element;
			box.appendChild(a);
			ul.appendChild(box);
			nDivs++;
		}
	}
}

function appendMore() {
	console.log(nDivs);
	loadFourDivs(nDivs);
}

loadFourDivs();

const btn = document.getElementById("append");
btn.addEventListener("click", appendMore);
