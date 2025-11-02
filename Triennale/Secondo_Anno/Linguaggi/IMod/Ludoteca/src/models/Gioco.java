package models;

import java.time.LocalDate;
import java.time.LocalTime;

public class Gioco extends Prodotto {
    private LocalTime durataMedia;

    public Gioco(String autore, String titolo, String casaEditrice, LocalDate annoPubblicazione,
            LocalTime durataMedia, int quantita) {
        super(autore, titolo, casaEditrice, annoPubblicazione, quantita);
        this.durataMedia = durataMedia;
    }

    public LocalTime getDurataMedia() {
        return durataMedia;
    }

    public void setDurataMedia(LocalTime durataMedia) {
        this.durataMedia = durataMedia;
    }

}
