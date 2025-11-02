package services;

import java.util.ArrayList;
import java.util.Set;

import models.Biglietto;
import models.TipologiaTratte;
import models.TipologiaTreni;
import models.Tratta;

public class GestioneBiglietto {

    ArrayList<Tratta> tratteDisponibili = new ArrayList<>();

    public void addTratta(double lunghezza, ArrayList<TipologiaTratte> tipTratta, ArrayList<TipologiaTreni> tipTreno,
            String partenza,
            String destinazione) {
        tratteDisponibili.add(new Tratta(lunghezza, tipTratta, tipTreno, partenza, destinazione));
    }

    public ArrayList<Biglietto> generaBiglietti(String partenza, String destinazione) {
        ArrayList<Biglietto> bigliettiDisponibili = new ArrayList<>();

        for (Tratta tratta : tratteDisponibili) {
            if (tratta.getPartenza().equals(partenza)) {
                ArrayList<Tratta> percorso = new ArrayList<>();
                percorso.add(tratta);

                // Se la destinazione della tratta è quella richiesta, aggiungi il biglietto
                if (tratta.getDestinazione().equals(destinazione)) {
                    aggiungiBiglietti(tratta, partenza, destinazione, percorso, bigliettiDisponibili);
                }
                // Altrimenti, continua la ricerca ricorsivamente per tratte successive
                else {
                    generaBigliettiDaIntermedio(tratta.getDestinazione(), destinazione, percorso, bigliettiDisponibili);
                }
            }
        }

        return bigliettiDisponibili;
    }

    // Metodo per cercare tratte partendo da una città intermedia
    private void generaBigliettiDaIntermedio(String intermedio, String destinazione, ArrayList<Tratta> percorso,
            ArrayList<Biglietto> bigliettiDisponibili) {
        for (Tratta tratta : tratteDisponibili) {
            if (tratta.getPartenza().equals(intermedio)) {
                ArrayList<Tratta> nuovoPercorso = new ArrayList<>(percorso);
                nuovoPercorso.add(tratta);

                // Se la tratta porta alla destinazione finale, aggiungi il biglietto
                if (tratta.getDestinazione().equals(destinazione)) {
                    aggiungiBiglietti(tratta, percorso.get(0).getPartenza(), destinazione, nuovoPercorso,
                            bigliettiDisponibili);
                }
                // Altrimenti, continua la ricerca ricorsiva
                else {
                    generaBigliettiDaIntermedio(tratta.getDestinazione(), destinazione, nuovoPercorso,
                            bigliettiDisponibili);
                }
            }
        }
    }

    // Metodo per aggiungere biglietti disponibili, anche considerando più tipi di
    // tratta e treni
    private void aggiungiBiglietti(Tratta tratta, String partenza, String destinazione, ArrayList<Tratta> percorso,
            ArrayList<Biglietto> bigliettiDisponibili) {

        // Se ci sono 2 tipologie di tratte
        if (tratta.getTipTratta().size() == 2) {
            // Se ci sono 2 tipologie di treni
            if (tratta.getTipTreno().size() == 2) {
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        double prezzo = tratta.getTipTratta().get(i).getPrezzo() * tratta.getLunghezza()
                                * tratta.getTipTreno().get(j).getPrezzo();
                        bigliettiDisponibili.add(
                                new Biglietto(partenza, destinazione, percorso, prezzo, tratta.getTipTreno().get(j)));
                    }
                }
                // Se c'è solo 1 tipologia di treno
            } else if (tratta.getTipTreno().size() == 1) {
                for (int i = 0; i < 2; i++) {
                    double prezzo = tratta.getTipTratta().get(i).getPrezzo() * tratta.getLunghezza()
                            * tratta.getTipTreno().get(0).getPrezzo();
                    bigliettiDisponibili
                            .add(new Biglietto(partenza, destinazione, percorso, prezzo, tratta.getTipTreno().get(0)));

                }
            }
            // Se c'è solo 1 tipologia di tratta
        } else if (tratta.getTipTratta().size() == 1) {
            // Se ci sono 2 tipologie di treno
            if (tratta.getTipTreno().size() == 2) {
                for (int i = 0; i < 2; i++) {
                    double prezzo = tratta.getTipTratta().get(0).getPrezzo() * tratta.getLunghezza()
                            * tratta.getTipTreno().get(i).getPrezzo();
                    bigliettiDisponibili
                            .add(new Biglietto(partenza, destinazione, percorso, prezzo, tratta.getTipTreno().get(i)));
                }
                // Se c'è solo 1 tipologia di treno
            } else if (tratta.getTipTreno().size() == 1) {
                double prezzo = tratta.getTipTratta().get(0).getPrezzo() * tratta.getLunghezza()
                        * tratta.getTipTreno().get(0).getPrezzo();
                bigliettiDisponibili
                        .add(new Biglietto(partenza, destinazione, percorso, prezzo, tratta.getTipTreno().get(0)));
            }
        }
    }
}
