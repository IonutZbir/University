"use strict";

const fs = require("fs")

const data = JSON.parse(fs.readFileSync("data.json", "utf-8"));

const getAll = function(){
    return JSON.stringify(data);
}

const getItem = function(index){
    let item = data.find((el) => el.id === Number(index));
    return JSON.stringify(item);
}

module.exports = {getAll, getItem};