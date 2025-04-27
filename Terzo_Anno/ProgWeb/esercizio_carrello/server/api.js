"use strict";

const fs = require("fs");
const { join } = require("path");

const filePath = join(__dirname, "products.json");
console.log(filePath)

const data = JSON.parse(fs.readFileSync(filePath, "utf-8"))

function getAllProducts() {
    return JSON.stringify(data);
}

function getProductById(id){
    return JSON.stringify(data.find((el) => el.id === Number(id)));
}

function addProductToCart(product){
    const productExists = data.some((el) => el.id === product.id);
    if (productExists) {
        productExists.stock -= 1;
        productExists.cartQuantity += 1;
    }else{
    }

    data.push(product);
    fs.writeFileSync(filePathCart, JSON.stringify(data, null, 2), "utf-8");
}

module.exports = {getAllProducts, getProductById}

