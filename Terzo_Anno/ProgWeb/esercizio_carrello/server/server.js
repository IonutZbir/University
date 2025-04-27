"use strict";

const http = require("http");
const { getAllProducts } = require("./api.js");
const port = 8000;

const server = http.createServer((req, res) =>{
    const reqUrl = new URL(req.url, `http://${req.headers.host}`)
    const pathName = reqUrl.pathname;
    
    if (pathName === "/products") {
        const products = getAllProducts();
        res.statusCode = 200;
        res.setHeader('Content-Type', 'application/json');
        res.setHeader("Access-Control-Allow-Origin", "*");
        res.end(products);
    }else if (pathName === "/addToCart") {

    } else {
        res.statusCode = 404;
        console.error("ERROR: Page not found");
        res.end('404: Pagina non trovata');
    }
});

server.listen(port, "127.0.0.1", () => {
    console.log("Server listening on port " + port);
})