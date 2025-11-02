"use strict";

async function fetchTasks() {
	try {
		const url = "http://localhost:3000/";
		const endpoint = "tasks";
		const res = await fetch(url + endpoint);
		const data = await res.json();
		return data.data;
	} catch (error) {
		console.log("Error during fetching data");
	}
}

async function showTasks() {
	const tasks = await fetchTasks();

	let ul = document.getElementById("tasks");
    ul.innerHTML = ""

	tasks.forEach((task) => {
		const li = document.createElement("li");
		const btn = document.createElement("button");
		const text = document.createElement("p");

        li.className = "li-task"

        if(task.completed){
            li.style.backgroundColor = "green"
        }else{
            li.style.backgroundColor = "red"
        }

		btn.innerHTML = "Cambia Stato";
		btn.addEventListener("click", () => changeState(task.id));

		text.innerHTML = task.text;

		li.appendChild(text);
		li.appendChild(btn);

		ul.appendChild(li);
	});
}

async function changeState(id) {
	try {
		const url = "http://localhost:3000/";
		const endpoint = "tasks/toggle/" + id;
		const res = await fetch(url + endpoint, {"method": "POST"});
		const data = await res.json();
		if (data.status == "success") {
			showTasks()
            return
		} else if (data.status == "fail") {
			console.log("Error: User undefined");
			return undefined;
		} else if (data.status == "error") {
			console.log("Error: Bad Request");
			return undefined;
		}
	} catch (error) {
		console.log("Error during fetching data");
	}
}

showTasks()

