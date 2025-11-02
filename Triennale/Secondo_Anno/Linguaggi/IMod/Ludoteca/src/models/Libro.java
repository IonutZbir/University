package models;

import java.time.LocalDate;

public class Libro extends Prodotto {
    private int pagine;

    public Libro(String autore, String titolo, String casaEditrice, LocalDate annoPubblicazione, int pagine,
            int quantita) {
        super(autore, titolo, casaEditrice, annoPubblicazione, quantita);
        this.pagine = pagine;
    }

    public int getPagine() {
        return pagine;
    }

    public void setPagine(int pagine) {
        this.pagine = pagine;
    }

}
