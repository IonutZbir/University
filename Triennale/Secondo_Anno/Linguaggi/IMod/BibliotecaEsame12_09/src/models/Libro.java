package models;

public class Libro extends Prodotto{
    private int nPagine;

    public Libro(String titolo, String entePubblicante, int anno, int nPagine) {
        super(titolo, entePubblicante, anno);
        this.nPagine = nPagine;
    }

    public int getnPagine() {
        return nPagine;
    }

    public void setnPagine(int nPagine) {
        this.nPagine = nPagine;
    }

    @Override
    public String toString() {
        return "Libro [Numero Pagine=" + nPagine + ", Titolo=" + getTitolo() + ", Ente Pubblicante="
                + getEntePubblicante() + ", Anno=" + getAnno() + "]";
    }
}