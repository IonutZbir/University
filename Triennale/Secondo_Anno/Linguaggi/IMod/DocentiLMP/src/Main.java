import java.time.LocalDate;
import java.util.ArrayList;

import models.Esame;
import models.Studente;

public class Main {
    
    /** 
     * @param args
     */
    public static void main(String[] args) {
        Studente s1 = new Studente("Ionut", "Zbirciog", "21214141");
        Studente s2 = new Studente("Franchino", "ErCriminogeno", "1232151");
        Studente s3 = new Studente("Christian", "ErLibanese", "654222");

        ArrayList<Studente> studs = new ArrayList<>();

        studs.add(s1);
        studs.add(s2);
        studs.add(s3);

        Esame e = new Esame(studs, "OOP", "Predicati e Funzioni", "Bocchini", LocalDate.of(2024, 7, 12));

        s1.setVotoMod1(25, e);
        s1.setVotoMod2(19, e);
        s1.setVotoOrale(17, e);

        s2.setVotoMod1(30, e);
        s2.setVotoMod2(17, e);
        s2.setVotoOrale(19, e);

        s3.setVotoMod1(10, e);
        s3.setVotoMod2(23, e);
        s3.setVotoOrale(20, e);

        e.getVotoStudentePerEsame(s1);
        e.getVotoStudentePerEsame(s2);
        e.getVotoStudentePerEsame(s3);

        e.getInfo();

        e.getInfo(s1.getMatricola());

    }
}
