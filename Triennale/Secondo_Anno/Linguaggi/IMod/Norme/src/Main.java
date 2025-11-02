import java.time.LocalDate;
import java.time.Year;

import models.Legge;
import models.TipologiaLegge;
import services.GestioneLeggi;

public class Main {
    public static void main(String[] args) {
        GestioneLeggi gs = new GestioneLeggi();
        
        gs.addLegge(TipologiaLegge.CIRCOLARE, LocalDate.now(), "Ciao!", "Arrivederci!");
        gs.addLegge(TipologiaLegge.CIRCOLARE, LocalDate.of(2024, 4, 12), "Ciaooo!", "Arrivederci!");
        gs.addLegge(TipologiaLegge.DECRETO, LocalDate.now(), "Ciao!", "Arrivederci!");

        gs.stessoTipoStessoAnno(TipologiaLegge.CIRCOLARE, Year.of(2024));

        Legge l1 = gs.getLegge(TipologiaLegge.CIRCOLARE, LocalDate.of(2024, 4, 12));
        System.out.println(l1);
    }
}
