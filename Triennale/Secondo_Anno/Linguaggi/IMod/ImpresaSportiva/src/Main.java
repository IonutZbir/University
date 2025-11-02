import java.time.LocalDate;
import java.time.Month;
import java.util.HashMap;
import java.util.Map;

import models.GestioneSportiviInterface;
import models.Sportivo;
import models.TipologiaSportivo;
import services.GestioneSportivi;

public class Main {
    public static void main(String[] args) {
        GestioneSportiviInterface gs = new GestioneSportivi();

        gs.addSportivo("Ionut","Zbirciog", LocalDate.of(2023, 6, 24), TipologiaSportivo.GIOCATORE, 4);
        
        gs.addSportivo("Adriano","Porzia", LocalDate.of(2022, 7, 14), TipologiaSportivo.GIOCATORE, 4);
        
        gs.addSportivo("Giacomo","Pace", LocalDate.of(2024, 9, 12), TipologiaSportivo.PREPARATORE_ATTLETICO, 3);
        
        gs.getSportivo("TEAM_1").addReti(Month.APRIL, 12);
        gs.getSportivo("TEAM_1").addReti(Month.MARCH, 9);
        gs.getSportivo("TEAM_1").addReti(Month.JULY, 14);
        gs.getSportivo("TEAM_2").addReti(Month.SEPTEMBER, 10);
        gs.getSportivo("TEAM_3").addReti(Month.OCTOBER, 20);

        gs.setNumeroRetiPreviste(10);

        HashMap<Sportivo, Integer> premiati = gs.spotiviPremiati();

        System.out.println("Numero reti previste minimo: " + gs.getNumeroRetiPreviste() + "\n");
        for (Map.Entry<Sportivo, Integer> entry : premiati.entrySet()) {
            int nMesi = entry.getValue();
            Sportivo s = entry.getKey();

            System.out.println(s.getNome() + " " + s.getCognome() + " ha segnato almeno " + gs.getNumeroRetiPreviste() + " in " + nMesi + " mesi");

        }

    }
}
