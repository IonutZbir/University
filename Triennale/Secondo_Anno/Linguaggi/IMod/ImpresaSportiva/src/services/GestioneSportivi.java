package services;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.NoSuchElementException;

import models.GestioneSportiviInterface;
import models.Sportivo;
import models.TipologiaSportivo;

public class GestioneSportivi implements GestioneSportiviInterface {
    private static HashMap<String, Sportivo> archivioSportivi = new HashMap<>();
    private int numeroRetiPreviste;

    @Override
    public void addSportivo(String nome, String cognome, LocalDate dataAssunzione,
            TipologiaSportivo tipologia, int livello){
        
        Sportivo s = new Sportivo(nome, cognome, dataAssunzione, tipologia, livello);
        archivioSportivi.put(s.getNrIscrizione(), s);
    }

    // TODO Menu

    @Override
    public Sportivo getSportivo(String nrIscrizione) {
        Sportivo s = archivioSportivi.getOrDefault(nrIscrizione, null);
        if (s == null) {
            throw new NoSuchElementException("Lo sportivo non esiste");
        }
        return s;
    }

    @Override
    public HashMap<Sportivo, Integer> spotiviPremiati() {
        HashMap<Sportivo, Integer> premiati = new HashMap<>();
        int counter;
        for (Sportivo sp : archivioSportivi.values()) {
            if (sp.getLivello() >= 3) {
                counter = 0;
                for (int value : sp.getReti().values()) {
                    if (value >= numeroRetiPreviste) {
                        counter++;
                    }
                }
                if (counter > 0) {
                    premiati.put(sp, counter);
                }
            }
        }
        return premiati;
    }

    @Override
    public void setNumeroRetiPreviste(int numeroRetiPreviste) {
        if (numeroRetiPreviste < 0) {
            throw new IllegalArgumentException("Il numero di reti non può essere negativo");
        }
        this.numeroRetiPreviste = numeroRetiPreviste;
    }

    @Override
    public int getNumeroRetiPreviste() {
        return numeroRetiPreviste;
    }

}
