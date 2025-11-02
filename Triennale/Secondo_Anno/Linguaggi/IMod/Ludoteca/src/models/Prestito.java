package models;

import java.time.LocalTime;

public class Prestito {

    private Prodotto prodotto;
    private LocalTime inizio;
    private String nome;
    private String cognome;
    private LocalTime fine = null;

    public Prestito(Prodotto prodotto, LocalTime inizio, String nome, String cognome) {
        this.prodotto = prodotto;
        this.prodotto.setQuantita(prodotto.getQuantita() - 1);
        this.inizio = inizio;
        this.nome = nome;
        this.cognome = cognome;
    }

    public LocalTime getInizio() {
        return inizio;
    }

    public void setInizio(LocalTime inizio) {
        this.inizio = inizio;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCognome() {
        return cognome;
    }

    public void setCognome(String cognome) {
        this.cognome = cognome;
    }

    public LocalTime getFine() {
        return fine;
    }

    public void setFine(LocalTime fine) {
        this.fine = fine;
    }

    public Prodotto getProdotto() {
        return prodotto;
    }

    public void setProdotto(Prodotto prodotto) {
        this.prodotto = prodotto;
    }

}
