package models;

public class Articolo {
    private int numeroArticolo;
    private String introduzione;
    private String commi = "";
    
    public Articolo(int numeroArticolo, String introduzione, String commi) {
        this.numeroArticolo = numeroArticolo;
        this.introduzione = introduzione;
        this.commi = commi;
    }

    public Articolo(int numeroArticolo, String introduzione) {
        this.numeroArticolo = numeroArticolo;
        this.introduzione = introduzione;
    }

    public int getNumeroArticolo() {
        return numeroArticolo;
    }

    public String getIntroduzione() {
        return introduzione;
    }

    public String getCommi() {
        return commi;
    }
}
