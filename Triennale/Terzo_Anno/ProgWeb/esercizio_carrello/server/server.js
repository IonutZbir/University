"use strict";

const http = require("http");
const { getAllProducts } = require("./api.js");
const port = 8000;

const server = http.createServer((req, res) => {
	const reqUrl = new URL(req.url, `http://${req.headers.host}`);
	const pathName = reqUrl.pathname;
	const id = reqUrl.searchParams.get("id");

	// Header CORS per tutte le rotte
	res.setHeader("Access-Control-Allow-Origin", "*");
	res.setHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
	res.setHeader("Access-Control-Allow-Headers", "Content-Type");

	// Gestione preflight (richieste OPTIONS)
	if (req.method === "OPTIONS") {
		res.writeHead(204);
		res.end();
		return;
	}

	if (pathName === "/products") {
		const products = getAllProducts();
		res.statusCode = 200;
		res.setHeader("Content-Type", "application/json");
		res.end(products);
	} else if (pathName === "/addToCart" && id && req.method === "POST") {
		let body = "";
		req.on("data", (chunk) => {
			body += chunk.toString();
		});
		req.on("end", () => {
			try {
				const product = JSON.parse(body);
				console.log("Prodotto ricevuto dal client:", product);
				// Salvataggio simulato del prodotto
				res.statusCode = 200;
				res.setHeader("Content-Type", "application/json");
				res.end(
					JSON.stringify({
						message: "Prodotto aggiunto con successo",
						prodotto: product,
					})
				);
			} catch (err) {
				res.statusCode = 400;
				res.end("Errore nel parsing del corpo della richiesta");
			}
		});
	} else {
		res.statusCode = 404;
		res.end("404: Pagina non trovata");
	}
});

server.listen(port, "127.0.0.1", () => {
	console.log("Server listening on port " + port);
});
