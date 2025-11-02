import java.util.ArrayList;
import java.util.Arrays;

import models.Biglietto;
import models.TipologiaTratte;
import models.TipologiaTreni;
import services.GestioneBiglietto;

public class Main {
        public static void main(String[] args) {
                GestioneBiglietto gb = new GestioneBiglietto();

                gb.addTratta(
                                200,
                                new ArrayList<TipologiaTratte>(
                                                Arrays.asList(TipologiaTratte.NAZIONALE_BLU,
                                                                TipologiaTratte.NAZIONALE_GRIGIO)),
                                new ArrayList<TipologiaTreni>(
                                                Arrays.asList(TipologiaTreni.ALTA_V, TipologiaTreni.NORMALE)),
                                "Roma",
                                "Firenze");

                gb.addTratta(
                                220,
                                new ArrayList<>(Arrays.asList(TipologiaTratte.NAZIONALE_BLU)),
                                new ArrayList<>(Arrays.asList(TipologiaTreni.NORMALE)),
                                "Roma",
                                "Pisa");

                gb.addTratta(
                                50,
                                new ArrayList<>(Arrays.asList(TipologiaTratte.REGIONALE_BLU)),
                                new ArrayList<TipologiaTreni>(
                                                Arrays.asList(TipologiaTreni.ALTA_V, TipologiaTreni.NORMALE)),
                                "Firenze",
                                "Pisa");

                gb.addTratta(
                                170,
                                new ArrayList<>(Arrays.asList(TipologiaTratte.NAZIONALE_BLU)),
                                new ArrayList<TipologiaTreni>(
                                                Arrays.asList(TipologiaTreni.ALTA_V, TipologiaTreni.NORMALE)),
                                "Roma",
                                "Napoli");

                gb.addTratta(
                                80,
                                new ArrayList<>(Arrays.asList(TipologiaTratte.REGIONALE_BLU,
                                                TipologiaTratte.NAZIONALE_GRIGIO)),
                                new ArrayList<TipologiaTreni>(
                                                Arrays.asList(TipologiaTreni.ALTA_V, TipologiaTreni.NORMALE)),
                                "Napoli",
                                "Foggia");

                ArrayList<Biglietto> biglietti = gb.generaBiglietti("Roma", "Firenze");

                System.out.println(biglietti);

        }

}
