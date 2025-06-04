"use strict";

const express = require("express");
const path = require("path");
const cors = require("cors");
const app = express();

app.use(express.json());

app.use(cors());

// Serve static files from the "public" directory
app.use(express.static(path.join(__dirname, "../public")));

// read data from the json file

// routes

/* 
- app.get(route, handler)
- app.post(route, handler)
...
*/

let counter = { counter: 0 };

let colors = { background: "#882200", text: "#44DDAA" };

console.log(counter, colors);

app.get("/counter", (req, res) => {
	res.status(200).json(counter);
});

app.get("/colors", (req, res) => {
	res.status(200).json(colors);
});

app.post("/increase", (req, res) => {
	counter.counter++;
	console.log(counter);
	res.status(200).json({ message: "increased successfully" });
});

app.post("/decrease", (req, res) => {
	counter.counter--;
	console.log(counter);
	res.status(200).json({ message: "decreased successfully" });
});

app.listen(3000, () => {
	console.log("Server running on http://localhost:3000");
});
