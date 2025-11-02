package models;

public class Dvd extends Prodotto {
    private double durata;

    public Dvd(String titolo, String entePubblicante, int anno, double durata) {
        super(titolo, entePubblicante, anno);
        this.durata = durata;
    }

    public double getDurata() {
        return durata;
    }

    @Override
    public String toString() {
        return "Dvd [Durata=" + durata + ", Titolo=" + getTitolo() + ", Ente Pubblicante="
                + getEntePubblicante() + ", Anno=" + getAnno() + "]";
    }

    
}
