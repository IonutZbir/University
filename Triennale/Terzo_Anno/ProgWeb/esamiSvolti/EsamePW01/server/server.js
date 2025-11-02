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

app.get("/colors", (req, res) => {
  if (!data || data.length <= 0){
    res.status(200).json([])
  }
  res.status(200).json(data)
});

app.listen(3000, () => {
	console.log("Server running on http://localhost:3000");
});
