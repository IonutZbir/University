package services;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.NoSuchElementException;

import models.Sportivo;
import models.TipologiaSportivo;

public class GestioneSportivo {
    
    private int minReti;
    private ArrayList<Sportivo> archivioSportivi;

    public GestioneSportivo(int minReti) {
        this.minReti = minReti;
        this.archivioSportivi = new ArrayList<>();
    }

    public void addSportivo(Sportivo sp){
        archivioSportivi.add(sp);
    }

    public void addSportivo(String nome, String cognome, LocalDate dataAssunzione, int livelloStipendiale, TipologiaSportivo tipoSportivo){
        archivioSportivi.add(new Sportivo(nome, cognome, dataAssunzione, livelloStipendiale, tipoSportivo));
    }

    // public void addSportivo(){
    //     Scanner input = new Scanner(System.in);
    //     System.out.println("Inserisci il nome dello sportivo");  
    // }

    // for i
    public Sportivo getSportivo(String nome, String cognome){
        for (int i = 0; i < archivioSportivi.size(); i++) {
            Sportivo s = archivioSportivi.get(i);
            if(s.getNome().equals(nome) && s.getCognome().equals(cognome)){
                return s;    
            }
        }
        // Lo sportivo non esiste
        throw new NoSuchElementException("Lo sportivo non esiste!");
    }

    // for each
    public Sportivo getSportivo(String nrIscrizione){
        for (Sportivo sportivo : archivioSportivi) {
            if(sportivo.getNrIscrizione().equals(nrIscrizione)){
                return sportivo;
            }
        }
        // Lo sportivo non esiste
        throw new NoSuchElementException("Lo sportivo non esiste!");
    }

    public HashMap<Integer, ArrayList<Sportivo>> getSportiviPremiati(){
        HashMap<Integer, ArrayList<Sportivo>> premiati = new HashMap<>();
        int counter;
        for (Sportivo sportivo : archivioSportivi) {
            if(sportivo.getLivelloStipendiale() >= 3 && sportivo.getTipoSportivo() == TipologiaSportivo.GIOCATORE){
                counter = 0;
                for (int reti : sportivo.getRetiPerMese().values()) {
                    if(reti >= minReti){
                        counter++;
                    }
                }
                if(counter > 0){ // almeno un mese in cui ha segnato minReti
                    ArrayList<Sportivo> p = premiati.getOrDefault(counter, new ArrayList<>());
                    p.add(sportivo);
                    premiati.put(counter, p);
                }
            }
        }
        return premiati;
    }
}
