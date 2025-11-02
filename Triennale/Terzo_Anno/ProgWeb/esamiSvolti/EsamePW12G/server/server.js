"use strict"

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
const data = JSON.parse(fs.readFileSync(__dirname + "/data.json"))

// routes

app.get("/prodotti", (req, res) => {
	res.status(200).json({
		status: "success",
		data: data
	})
})

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