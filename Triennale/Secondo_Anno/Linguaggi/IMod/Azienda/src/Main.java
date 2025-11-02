import java.time.LocalDate;
import java.util.ArrayList;

import models.Dipendente;
import models.Mansione;
import models.Dipendente.Dipartimento;
import services.GestioneDipendente;

public class Main {
    public static void main(String[] args) {
        GestioneDipendente gs = new GestioneDipendente();

        gs.insertDipendente("Ionut", "Zbirciog", LocalDate.of(2002, 11, 9), Dipartimento.MARKETING);
        gs.insertDipendente("Adriano", "Porzia", LocalDate.of(2002, 10, 4), Dipartimento.RISORSE_UMANE);
        gs.insertDipendente("Giacomo", "Pace", LocalDate.of(2002, 9, 9), Dipartimento.MARKETING);

        Dipendente adriano = gs.getDipendente("Adriano", "Porzia");
        Dipendente ionut = gs.getDipendente("Ionut", "Zbirciog");
        Dipendente giacomo = gs.getDipendente("Giacomo", "Pace");

        gs.updateDipendente(Mansione.HR_SPECIALIST, 8, null, adriano);
        gs.updateDipendente(Mansione.MARKETING_SPECIALIST, 7, adriano, ionut);
        gs.updateDipendente(Mansione.MARKETING_SPECIALIST, 7, adriano, giacomo);

        gs.showDipendenti();
        ArrayList<Dipendente> chain = gs.getChainOfCommand(giacomo);

        System.out.println("Chain of command\n\n\n");
        System.out.println(chain);

        System.out.println("\n\n\n");

        ArrayList<Dipendente> hire = gs.sameYearOfHire();
        System.out.println("Same year of hire\n\n\n");
        System.out.println(hire);

    }
}
