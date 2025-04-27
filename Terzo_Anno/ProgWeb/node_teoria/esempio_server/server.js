"use strict";

const {getAll, getItem} = require("./api.js")

const http = require("http")

const {log, error, warning, info} = require("../../logger/logger.js")

const server = http.createServer((req, res) => {
    const reqUrl = new URL(req.url, `http://${req.headers.host}`)
    const pathName = reqUrl.pathname;
    const id = reqUrl.searchParams.get("id");
    log(pathName + " " + id);
    if (pathName === "/") {
        log(`Host: ${req.headers.host}`);
        if (id) {
            log(`ID richiesto: ${id}`);
            
            res.end(getItem(id));
        } else {
            res.end(getAll());
        }
    } else {
        res.statusCode = 404;
        log('Pagina non trovata', error);
        res.end('Pagina non trovata');
    }
})


const port = 8000;

server.listen(port, "127.0.0.1", () => {
    log("Server listening on port " + port);
})