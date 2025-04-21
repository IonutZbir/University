"use strict";

let products = [
    {
        name: "Prodotto 1", price: 10
    },
    {
        name: "Prodotto 2", price: 20
    },
    {
        name: "Prodotto 3", price: 30
    },    
]

let cart = {
    items: [],
    total: 0,
    addItem (product) {
        this.items.push(product);
        this.total += product.price;
    }
};