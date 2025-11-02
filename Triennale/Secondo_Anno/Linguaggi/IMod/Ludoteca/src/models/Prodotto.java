package models;

import java.time.LocalDate;

public class Prodotto {
    private String autore;
    private String titolo;
    private String casaEditrice;
    private LocalDate annoPubblicazione;
    private int quantita;

    public Prodotto(String autore, String titolo, String casaEditrice, LocalDate annoPubblicazione, int quantita) {
        this.autore = autore;
        this.titolo = titolo;
        this.casaEditrice = casaEditrice;
        this.annoPubblicazione = annoPubblicazione;
        this.quantita = quantita;
    }

    public String getAutore() {
        return autore;
    }

    public void setAutore(String autore) {
        this.autore = autore;
    }

    public String getTitolo() {
        return titolo;
    }

    public void setTitolo(String titolo) {
        this.titolo = titolo;
    }

    public String getCasaEditrice() {
        return casaEditrice;
    }

    public void setCasaEditrice(String casaEditrice) {
        this.casaEditrice = casaEditrice;
    }

    public LocalDate getAnnoPubblicazione() {
        return annoPubblicazione;
    }

    public void setAnnoPubblicazione(LocalDate annoPubblicazione) {
        this.annoPubblicazione = annoPubblicazione;
    }

    public int getQuantita() {
        return quantita;
    }

    public void setQuantita(int quantita) {
        this.quantita = quantita;
    }

}
