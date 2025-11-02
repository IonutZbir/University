package services;

import java.time.Period;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.NoSuchElementException;

import models.Dvd;
import models.Libro;
import models.Prestito;
import models.Prodotto;

public class Biblioteca {
    private HashMap<String, Prodotto> archivioProdotti = new HashMap<>();

    public void addProdotto(String titolo, String entePubblicante, int anno, ArrayList<Prestito> seqPresititi, int nPagine){
        archivioProdotti.put(titolo ,new Libro(titolo, entePubblicante, anno, nPagine));
    }

    public void addProdotto(String titolo, String entePubblicante, int anno, ArrayList<Prestito> seqPresititi, double durata){
        archivioProdotti.put(titolo, new Dvd(titolo, entePubblicante, anno, durata));
    }

    public Prodotto getProdotto(String titolo){
        Prodotto p = archivioProdotti.get(titolo);
        if(p == null){
            throw new NoSuchElementException("Il prodotto " + titolo + " non è presente!");
        }
        return p;
    }

    public void setGiorniRicosengna(Prodotto p, int giorni){
        for (Prestito pre : p.getSeqPrestiti()) {
            pre.setDataPrevistaConsegna(giorni);
        }
    }

    public int maxGiorniPrestiti(Prodotto p){
        int max = 0;
        for (Prestito pre : p.getSeqPrestiti()) {
                Period periodo = Period.between(pre.getDataInizio(), pre.getDataConsegna());
                int days = periodo.getDays();
                if(days > max){
                    max = days;
                }
        }
        return max;
    }

    public void trovaInconsistenze(Prodotto p){
        ArrayList<Prestito> inconsistenze = new ArrayList<>();
        ArrayList<Prestito> seqPrestiti = p.getSeqPrestiti();

        System.out.println("\nControllo inconsistenze per il prodotto: " + p);

        if (seqPrestiti.size() > 1) {
            for (int i = 0; i < seqPrestiti.size(); i++) {
                Prestito prestito1 = seqPrestiti.get(i);
    
                for (int j = 0; j < seqPrestiti.size(); j++) {
                    Prestito prestito2 = seqPrestiti.get(j);
    
                    if (prestito1.getDataInizio().isBefore(prestito2.getDataConsegna()) &&  !prestito1.equals(prestito2)) {
                        if (!inconsistenze.contains(prestito1)){
                            inconsistenze.add(prestito1);
                        }
                    }
                }
            }
        } else {
            System.err.println("Non ci sono abbastanza prestiti per questo prodotto");
        }

        if(inconsistenze.isEmpty()){
            System.out.println("Non sono state trovate inconsistenze");
        }else{
            System.out.println("Sono state trovate inconsistenze per i seguneti prestiti: ");
            for (Prestito prestito : inconsistenze) {
                System.out.println(prestito);
            }
            System.out.println();
        }

    }

}
