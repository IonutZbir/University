"use strict";

let tasks = [];

async function fetchTasks() {
	try {
		const res = await fetch("http://localhost:3000/tasks");
		const data = await res.json();
		tasks = data.data;
	} catch (error) {
		console.log("Error fetching data, ", error);
		return null;
	}
}

async function showTasks() {
	await fetchTasks();
	const main = document.getElementById("tasks");

	tasks.forEach((element) => {
		const div = document.createElement("div");
		const btn = document.createElement("button");
		const p = document.createElement("p");

		div.className = "card";
		btn.className = "btn";

		btn.id = "btn" + element.id;
		div.id = "card" + element.id;

		btn.innerHTML = "Completa";
		p.innerHTML = element.text;

		if (element.completed) {
			btn.classList.add("btn-disabled");
			btn.disabled = true;
			div.classList.add("card-completed");
		}

		btn.addEventListener("click", () => completeTask(element));

		div.appendChild(p);
		div.appendChild(btn);
		main.appendChild(div);
	});
}

async function completeTask(task) {
	const res = await fetch("http://localhost:3000/tasks/complete/" + task.id, {
		method: "POST",
	});
	const data = await res.json();
	tasks = data.data;

	const btn = document.getElementById("btn" + task.id);
	btn.classList.add("btn-disabled");
	btn.disabled = true;

	const div = document.getElementById("card" + task.id);
	div.classList.add("card-completed");
}

showTasks();
