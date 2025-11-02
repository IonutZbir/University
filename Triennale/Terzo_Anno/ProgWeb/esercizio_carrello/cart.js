"use strict";

function createProductCart(product) {
	if (!product || typeof product !== "object") {
		throw new Error("Invalid product object");
	}

	let div = document.createElement("div");
	div.className = "product";
	div.id = "product-cart-" + product.id;

	let img = document.createElement("img");
	img.src = product.image;
	img.alt = product.name;

	let n = document.createElement("p");
	n.className = "product-name";
	n.textContent = product.name;

	let p = document.createElement("p");
	p.className = "product-price";
	p.textContent = product.price * product.cartQuantity + euro;

	let quantity = document.createElement("p");
	quantity.className = "product-quantity";
	quantity.textContent = product.cartQuantity;

	let cat = document.createElement("p");
	cat.className = "product-category";
	cat.textContent = product.category;

	let btn = document.createElement("button");
	btn.className = "btn-rem";
	btn.id = "btn-rem-" + product.id;
	btn.textContent = "Remove";

	div.appendChild(img);
	div.appendChild(n);
	div.appendChild(p);
	div.appendChild(quantity);
	div.appendChild(cat);
	div.appendChild(btn);

	return div;
}

function viewProductListCart() {
	let container = document.getElementById("container-cart");

	cart.products.forEach((product) => {
		container.appendChild(createProductCart(product));
	});
}

function updateCartCounter() {
    let counter = document.getElementById("total-products");
	if (!counter) return; // Se non esiste l'elemento non fa nulla

	let total = cart.products.reduce((sum, product) => sum + product.cartQuantity, 0);
	counter.textContent = total;
}

function updateCartPrice() {
    let amount = document.getElementById("total-amount");
	if (!amount) return; // Se non esiste l'elemento non fa nulla

	let total = cart.products.reduce((sum, product) => sum + product.price * product.cartQuantity, 0);
	amount.textContent = total + euro;
}

function updateCartView() {
	let container = document.getElementById("container-cart");
	container.innerHTML = ""; // Cancello il contenuto renderizzato del carrello precedente
	viewProductListCart(); // renderizzo il nuovo contenuto del carrello
    updateCartCounter();
    updateCartPrice();
}