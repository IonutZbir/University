"use strict";

let products = [
	{
		id: 1,
		name: "Laptop",
		price: 1200,
		category: "Electronics",
		quantity: 5,
		image: "/images/laptop.jpg",
	},
	{
		id: 2,
		name: "Smartphone",
		price: 800,
		category: "Electronics",
		quantity: 6,
		image: "/images/smartphone.jpg",
	},
	{
		id: 3,
		name: "Tablet",
		price: 600,
		category: "Electronics",
		quantity: 4,
		image: "/images/tablet.jpg",
	},
	{
		id: 4,
		name: "Headphones",
		price: 200,
		category: "Accessories",
		quantity: 2,
		image: "/images/headphone.jpg",
	},
	{
		id: 5,
		name: "Smartwatch",
		price: 300,
		category: "Accessories",
		quantity: 2,
		image: "/images/smartwatch.jpg",
	},
	{
		id: 6,
		name: "Camera",
		price: 1500,
		category: "Electronics",
		quantity: 3,
		image: "/images/camera.jpg",
	},
	{
		id: 7,
		name: "Gaming Console",
		price: 500,
		category: "Electronics",
		quantity: 7,
		image: "/images/console.jpg",
	},
	{
		id: 8,
		name: "Keyboard",
		price: 100,
		category: "Accessories",
		quantity: 10,
		image: "/images/keyboard.jpg",
	},
	{
		id: 9,
		name: "Mouse",
		price: 50,
		category: "Accessories",
		quantity: 15,
		image: "/images/mouse.jpg",
	},
	{
		id: 10,
		name: "Monitor",
		price: 300,
		category: "Electronics",
		quantity: 8,
		image: "/images/monitor.jpg",
	},
];

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
	quantity.textContent = "Disponibili: " + product.quantity;

	let cat = document.createElement("p");
	cat.className = "product-category";
	cat.textContent = product.category;

	let btn = document.createElement("button");
	btn.className = "btn-add";
	btn.id = "btn-add-" + product.id;
	btn.textContent = "Add to Cart";

	if (product.quantity <= 0) {
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
	p.textContent = product.price * product.quantity + euro;

	let quantity = document.createElement("p");
	quantity.className = "product-quantity";
	quantity.textContent = product.quantity;

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

	let total = cart.products.reduce((sum, product) => sum + product.quantity, 0);
	counter.textContent = total;
}

function updateCartPrice() {
    let amount = document.getElementById("total-amount");
	if (!amount) return; // Se non esiste l'elemento non fa nulla

	let total = cart.products.reduce((sum, product) => sum + product.price * product.quantity, 0);
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

		if (product.quantity > 0) {
			let existingProduct = this.products.find(
				(p) => p.id === product.id
			);
			if (existingProduct) {
				existingProduct.quantity += 1;
			} else {
				this.products.push({ ...product, quantity: 1 });
			}
			product.quantity -= 1;
		}

		console.log(this.products);
	},

	removeProduct(product) {
		let cartProduct = this.products.find((p) => p.id === product.id);

		if (!cartProduct) return;

		cartProduct.quantity -= 1;

		if (cartProduct.quantity === 0) {
			this.products = this.products.filter((p) => p.id !== product.id);
		}

		let originalProduct = products.find((p) => p.id === product.id);
		if (originalProduct) {
			originalProduct.quantity += 1;
		}
	},
};

function main() {
	viewProductList();

	document.addEventListener("click", (event) => {
		if (event.target && event.target.classList.contains("btn-add")) {
			let productId = parseInt(event.target.id.split("-")[2]);
			let product = products.find((p) => p.id === productId);

			if (product) {
				cart.addProduct(product);
			}
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
