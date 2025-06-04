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

/* 
- app.get(route, handler)
- app.post(route, handler)
...
*/

app.get("/articoli", (req, res) => {
  res.status(200).json(data)
})

app.get("/autori", (req, res) => {
  let autori = []
  data.forEach(element => {
    autori.push(element.autore)
  });
  res.status(200).json(autori)
})


app.listen(3000, () => {
  console.log("Server running on http://localhost:3000");
});