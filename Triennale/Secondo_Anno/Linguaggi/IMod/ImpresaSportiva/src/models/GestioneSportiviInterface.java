package models;

import java.time.LocalDate;
import java.util.HashMap;

public interface GestioneSportiviInterface {

    void addSportivo(String nome, String cognome, LocalDate dataAssunzione,
            TipologiaSportivo tipologia, int livello);

    Sportivo getSportivo(String nrIscrizione);

    HashMap<Sportivo, Integer> spotiviPremiati();

    void setNumeroRetiPreviste(int numeroRetiPreviste);

    int getNumeroRetiPreviste();

}