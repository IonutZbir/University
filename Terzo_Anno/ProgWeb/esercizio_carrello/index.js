"use strict";

const server_url = "http://127.0.0.1:8000/";
const euro = "\u20AC";

let products = [];

function fetchProducts() {
	let url = server_url + "products";
	const request = new XMLHttpRequest();
	request.open("GET", url, true);

	request.onload = function () {
		if (request.status === 200) {
			products = JSON.parse(request.responseText);
			console.log(products);
			viewProductList();
		} else {
			console.error("Error fetching products: " + request.statusText);
		}
	};

	request.onerror = function () {
		console.error("Network error.");
	};

	request.send(null);
}

function createProductCard(product) {
	if (!product || typeof product !== "object") {
		throw new Error("Invalid product object");
	}

	let div = document.createElement("div");
	div.className = "product";
	div.id = "product-" + product.id;

	let img = document.createElement("img");
	img.src = product.image;
	img.alt = product.name;

	let n = document.createElement("p");
	n.className = "product-name";
	n.textContent = product.name;

	let p = document.createElement("p");
	p.className = "product-price";
	p.textContent = product.price + euro;

	let quantity = document.createElement("p");
	quantity.className = "product-quantity";
	quantity.textContent = "Disponibili: " + product.stock;

	let cat = document.createElement("p");
	cat.className = "product-category";
	cat.textContent = product.category;

	let btn = document.createElement("button");
	btn.className = "btn-add";
	btn.id = "btn-add-" + product.id;
	btn.textContent = "Add to Cart";

	if (product.stock <= 0) {
		quantity.className = "error-quantity-product";
		quantity.textContent = "Stock Esaurito";
		btn.disabled = true;
		btn.classList.add("disabled");
	}

	div.appendChild(img);
	div.appendChild(n);
	div.appendChild(p);
	div.appendChild(quantity);
	div.appendChild(cat);
	div.appendChild(btn);

	return div;
}

function viewProductList() {
	let container = document.getElementById("container-products");

	products.forEach((product) => {
		container.appendChild(createProductCard(product));
	});
}

function updateProductsView() {
	let container = document.getElementById("container-products");
	container.innerHTML = ""; // Cancello il contenuto renderizzato della lista dei prodotti precedente
	viewProductList(); // renderizzo il nuovo contenuto della lista
}

function addProductToCart(product) {
	if (!product || typeof product !== "object") {
		throw new Error("Invalid product object");
	}
	let url = server_url + "addToCart?id=" + product.id;
	console.log(url);
	const request = new XMLHttpRequest();
	request.open("POST", url, true);
	request.setRequestHeader("Content-Type", "application/json");
	request.send(JSON.stringify(product));

	request.onload = function () {
		if (request.status === 200) {
			let res = JSON.parse(request.responseText);
			console.log(res);
		} else {
			console.error("Error Adding Product: " + request.statusText);
		}
	};

	request.onerror = function () {
		console.error("Network error.");
	};
}

function main() {
	fetchProducts();

	document.addEventListener("click", (event) => {
		if (event.target && event.target.classList.contains("btn-add")) {
			let productId = parseInt(event.target.id.split("-")[2]);
			let product = products.find((p) => p.id === productId);

			if (product) {
				addProductToCart(product);
			}
		}
	});
}

main();
