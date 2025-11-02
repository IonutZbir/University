"use strict"

const toggle = document.getElementById("toggle")
toggle.addEventListener("click", () =>{
    document.getElementById("nav").classList.toggle("responsive")
})