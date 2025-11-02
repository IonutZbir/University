"use strict";

async function fetchData() {
	try {
		const res = await fetch("http://localhost:3000/data");
		const data = await res.json();
		if (!data.status) {
			return data;
		}
		return null;
	} catch (error) {
		console.log("Error fetching data", error);
		return null;
	}
}

async function showData(mode) {
	const data = await fetchData();
	if (data == null) {
		console.log("No data provided");
		return;
	}
	const content = document.getElementById("content");
    content.innerHTML = ""; // Clear previous content
	if (mode) {
		const pre = document.createElement("pre");

		let text = "";

		text = JSON.stringify(data, null, 4);

		pre.textContent = text;
		content.appendChild(pre);
	}else{
        const ul = document.createElement("ul");
        data.forEach(element => {
            const li = document.createElement("li");
            li.style.fontWeight = "bold"
            li.innerHTML = element.prodotto + " " + element.desc
            ul.appendChild(li)
        });
		
		content.appendChild(ul);
        const btn = document.getElementById("convert");
        btn.remove()
    }
}

window.addEventListener("load", () => showData(1));
const btn = document.getElementById("convert");
btn.addEventListener("click", () => showData(0));

