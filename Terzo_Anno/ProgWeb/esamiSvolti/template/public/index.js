"use strict"

// async function fetchProducts() {
//     try {
//         const url = "http://localhost:3000/"
//         const endpoint = "prodotti"
//         const res = await fetch(url + endpoint);
//         const data = await res.json();
//         return data.data;
//     } catch (error) {
//         console.log("Error during fetching data")
//     }
// }

// async function fetchUser(id) {
//     try {
//         const url = "http://localhost:3000/"
//         const endpoint = "utenti/" + id
//         const res = await fetch(url + endpoint);
//         const data = await res.json();
//         if (data.status == "success"){
//             return data.data;
//         }
//         else if(data.status == "fail"){
//             console.log("Error: User undefined")
//             return undefined
//         }
//         else if(data.status == "error"){
//             console.log("Error: Bad Request")
//             return undefined
//         }
//     } catch (error) {
//         console.log("Error during fetching data")
//     }
// }