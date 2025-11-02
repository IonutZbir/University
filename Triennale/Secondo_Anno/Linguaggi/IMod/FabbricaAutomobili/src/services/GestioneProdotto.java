package services;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.NoSuchElementException;

import models.Componente;
import models.Prodotto;

public class GestioneProdotto {
    private HashMap<String, Prodotto> archivioProdotti = new HashMap<>();

    public void addProdotto(String indentificativo, String etichetta, ArrayList<Componente> componenti, double costoGiornaliero, int tempoRealizzazione, double fattoreGuadagno){
        archivioProdotti.put(indentificativo, new Prodotto(indentificativo, etichetta, componenti, costoGiornaliero, tempoRealizzazione, fattoreGuadagno));
    }

    public Prodotto getProdotto(String identificativo){
        Prodotto p = this.archivioProdotti.get(identificativo);
        if (p == null) {
            throw new NoSuchElementException("Il prodotto " + identificativo + " non è stato trovato");
        }
        return p;
    }

    public void setFattoreGuadagno(double fattoreGuadagno){
        for (Prodotto p : archivioProdotti.values()) {
            p.setFattoreGuadagno(fattoreGuadagno);
        }
    }

    public void setCostoGiornaliero(double costoGiornaliero){
        for (Prodotto p : archivioProdotti.values()) {
            p.setCostoGiornaliero(costoGiornaliero);
        }
    }

    @Override
    public String toString() {
        return "Catalogo Prodotti:\n " + this.archivioProdotti;
    }

    
}
