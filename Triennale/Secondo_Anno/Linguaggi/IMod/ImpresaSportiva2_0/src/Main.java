import java.time.LocalDate;
import java.time.Month;
import java.util.ArrayList;
import java.util.HashMap;

import models.Sportivo;
import models.TipologiaSportivo;
import services.GestioneSportivo;

public class Main {

    public static void main(String[] args) {
        GestioneSportivo gs = new GestioneSportivo(10);

        Sportivo ionut = new Sportivo("Ionut", "Zbirciog", LocalDate.now(), 3, TipologiaSportivo.GIOCATORE);
        ionut.setRetiPerMese(Month.AUGUST, 12);

        gs.addSportivo(ionut);
        gs.addSportivo("Adriano", "Porzia", LocalDate.of(2024, 7, 12), 3, TipologiaSportivo.GIOCATORE);

        Sportivo adriano = gs.getSportivo("Adriano", "Porzia");

        adriano.setRetiPerMese(Month.FEBRUARY, 15);
        adriano.setRetiPerMese(Month.MARCH, 23);

        gs.addSportivo("Giacomo", "Pace", LocalDate.now(), 5, TipologiaSportivo.GIOCATORE);

        Sportivo giacomo = gs.getSportivo("TEAM_3");
        
        giacomo.setRetiPerMese(Month.SEPTEMBER, 16);
        giacomo.setRetiPerMese(Month.OCTOBER, 1);
        giacomo.setRetiPerMese(Month.OCTOBER, 5);

        HashMap<Integer, ArrayList<Sportivo>> premiati = gs.getSportiviPremiati();

        System.out.println(premiati);
    }
}
