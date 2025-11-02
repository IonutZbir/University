package models;

public class Libro {
    private String titolo;
    private String autore;
    private String iSBN;
    private int numeroCopieDisponibili;

    public Libro(String titolo, String autore, String iSBN, int numeroCopieDisponibili) {
        this.titolo = titolo;
        this.autore = autore;
        this.iSBN = iSBN;
        this.numeroCopieDisponibili = numeroCopieDisponibili;
    }

    public String getTitolo() {
        return titolo;
    }

    public void setTitolo(String titolo) {
        this.titolo = titolo;
    }

    public String getAutore() {
        return autore;
    }

    public void setAutore(String autore) {
        this.autore = autore;
    }

    public String getiSBN() {
        return iSBN;
    }

    public void setiSBN(String iSBN) {
        this.iSBN = iSBN;
    }

    public int getNumeroCopieDisponibili() {
        return numeroCopieDisponibili;
    }

    public void setNumeroCopieDisponibili(int numeroCopieDisponibili) {
        this.numeroCopieDisponibili = numeroCopieDisponibili;
    }

    @Override
    public String toString() {
        return "Libro [titolo=" + this.titolo + ", autore=" + this.autore + ", iSBN=" + this.iSBN
                + ", numeroCopieDisponibili="
                + this.numeroCopieDisponibili + "]";
    }

    public String toStringCsv() {
        return this.titolo + "," + this.autore + "," + this.iSBN + "," + this.numeroCopieDisponibili;
    }

}
