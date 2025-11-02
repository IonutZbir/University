package services;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.ArrayList;

import models.Gioco;
import models.Libro;

public class GestioneProdotti {
    private ArrayList<Gioco> inventarioGiochi = new ArrayList<>();
    private ArrayList<Libro> inventarioLibri = new ArrayList<>();

    public void addLibro(String autore, String titolo, String casaEditrice, LocalDate annoPubblicazione, int pagine,
            int quantita) {
        this.inventarioLibri.add(new Libro(autore, titolo, casaEditrice, annoPubblicazione, pagine, quantita));
    }

    public void addGioco(String autore, String titolo, String casaEditrice, LocalDate annoPubblicazione,
            LocalTime durataMedia, int quantita) {
        this.inventarioGiochi.add(new Gioco(autore, titolo, casaEditrice, annoPubblicazione, durataMedia, quantita));
    }

    public ArrayList<Gioco> getInventarioGiochi() {
        return inventarioGiochi;
    }

    public ArrayList<Libro> getInventarioLibri() {
        return inventarioLibri;
    }

}
