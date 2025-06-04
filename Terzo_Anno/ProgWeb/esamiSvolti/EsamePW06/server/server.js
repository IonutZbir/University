"use strict";

const express = require("express");
const fs = require("fs");
const path = require("path");
const cors = require("cors");
const app = express();

app.use(express.json());

app.use(cors());

// Serve static files from the "public" directory
app.use(express.static(path.join(__dirname, "../public")));

// read data from the json file
const data = JSON.parse(fs.readFileSync(__dirname + "/data.json"));

// routes

/* 
- app.get(route, handler)
- app.post(route, handler)
...
*/

app.get("/list", (req, res) => {
	let ids = [];

	data.forEach((element) => {
		ids.push(element.id);
	});

	res.status(200).json({
		status: "success",
		data: ids,
	});
});

app.get("/pics/:id", (req, res) => {
	const id = parseInt(req.params.id);
	const pic = data.find((item) => item.id == id);

	if (isNaN(id)) {
		res.status(400).json({
			status: "error",
			message: "Id Invalido",
			code: 404,
		});
	}else if (pic === undefined) {
		res.status(404).json({
			status: "fail",
			data: {
				id: "id non trovato",
			},
		});
	} else {
		res.status(200).json({
			status: "success",
			data: pic,
		});
	}
});

app.use((req, res, next) => {
	res.status(404).json({
		status: "error",
		message: "URL non trovata",
		code: 404,
	});
});

app.listen(3000, () => {
	console.log("Server running on http://localhost:3000");
});
