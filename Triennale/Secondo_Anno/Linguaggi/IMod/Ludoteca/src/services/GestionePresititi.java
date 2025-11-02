package services;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import models.Gioco;
import models.Prestito;
import models.Prodotto;

public class GestionePresititi {
    private ArrayList<Prestito> prestitiAttivi = new ArrayList<>();
    private HashMap<LocalDate, Prestito> archivioPrestiti = new HashMap<>();

    GestioneProdotti gProdotti = new GestioneProdotti();

    public void creaPrestito(Prodotto prodotto, LocalTime inizio, String nome, String cognome) {

        if (gProdotti.getInventarioGiochi().contains(prodotto)) {
            if (prodotto.getQuantita() > 0) {
                System.out.println("Ci sono " + prodotto.getQuantita() + "copie disponibili!");
                prestitiAttivi.add(new Prestito(prodotto, inizio, nome, cognome));
            } else {
                LocalTime stima = LocalTime.of(0, 0, 0);
                for (Gioco g : gProdotti.getInventarioGiochi()) {
                    stima.plusMinutes(g.getDurataMedia().getMinute());
                    System.out.println("Non è disponibile una copia del gioco, tempo stimato: " + stima);
                }
            }
        } else {
            System.out.println("Non ci sono copie disponibili.");
        }
    }

    public void restituisciPrestito(LocalDate dataPrestito, Prodotto prodotto, String nome, String cognome) {
        for (Prestito prestito : prestitiAttivi) {
            if (prestito.getProdotto().equals(prodotto) && prestito.getNome().equals(nome)
                    && prestito.getCognome().equals(cognome)) {
                prestito.setFine(LocalTime.now());
                prestito.getProdotto().setQuantita(prestito.getProdotto().getQuantita() + 1);
                archivioPrestiti.put(dataPrestito, prestito);
            }
        }
    }

    public int maxMinutesUsed(Prodotto prodotto) {
        int max = 0;
        for (Map.Entry<LocalDate, Prestito> entry : archivioPrestiti.entrySet()) {
            Prestito prestito = entry.getValue();
            if (prestito.getProdotto().equals(prodotto)) {
                int delta = prestito.getFine().getMinute() - prestito.getInizio().getMinute();
                if (delta > max) {
                    delta = max;
                }
            }
        }
        return max;
    }
}
