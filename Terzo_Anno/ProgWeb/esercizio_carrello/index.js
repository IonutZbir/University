"use strict";

let products = [];

const server_url = "http://127.0.0.1:8000/products";
const request = new XMLHttpRequest();
request.open("GET", server_url, true);

request.onload = function() {
    if (request.status === 200) {
        products = JSON.parse(request.responseText);
        console.log(products);
		viewProductList();
    } else {
        console.error("Error fetching products: " + request.statusText);
    }
};

request.onerror = function() {
    console.error("Network error.");
};

request.send(null);


let euro = "\u20AC";

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

function viewProductList() {
	let container = document.getElementById("container-products");

	products.forEach((product) => {
		container.appendChild(createProductCard(product));
	});
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

function updateProductsView() {
	let container = document.getElementById("container-products");
	container.innerHTML = ""; // Cancello il contenuto renderizzato della lista dei prodotti precedente
	viewProductList(); // renderizzo il nuovo contenuto della lista
}

let cart = {
	products: [],
	addProduct(product) {
		// avendo usato una arrow function, esse non hanno la proprietà "this", quindi uso una dichiarazione normale
		if (product.stock > 0) {

			let existingProduct = this.products.find(
				(p) => p.id === product.id
			);
			if (existingProduct) {
				existingProduct.cartQuantity += 1;
			} else {
				this.products.push({ ...product, cartQuantity: 1 });
			}
			product.stock -= 1;
			console.log("Add Product:" + this.products);
		}

	},

	removeProduct(product) {
		let cartProduct = this.products.find((p) => p.id === product.id);

		if (!cartProduct) return;

		cartProduct.cartQuantity -= 1;

		if (cartProduct.cartQuantity === 0) {
			this.products = this.products.filter((p) => p.id !== product.id);
		}

		let originalProduct = products.find((p) => p.id === product.id);
		if (originalProduct) {
			originalProduct.stock += 1;
		}
	},
};

function main() {
	

	document.addEventListener("click", (event) => {
		if (event.target && event.target.classList.contains("btn-add")) {
			let productId = parseInt(event.target.id.split("-")[2]);
			let product = products.find((p) => p.id === productId);

			if (product) {
				cart.addProduct(product);
			}
			console.log(product)
			updateCartView();
			updateProductsView();
		}

		if (event.target && event.target.classList.contains("btn-rem")) {
			let productId = parseInt(event.target.id.split("-")[2]);
			let product = products.find((p) => p.id === productId);

			if (product) {
				cart.removeProduct(product);
			}
			updateCartView();
			updateProductsView();
		}
	});
}

main();
