import java.time.LocalDate;

import services.PersonArchive;

public class Main {
    public static void main(String[] args) {
        PersonArchive pa = new PersonArchive();

        pa.createPerson("Ionut", "Zbirciog", LocalDate.of(2002, 11, 9), "JABDASVDA", "039123", 10, "Software Developer");

        pa.createPerson("Adriano", "Porzia", LocalDate.of(2003, 11, 20), "ADAAFAF", "Meccanico", "IVA313123123");

        pa.createPerson("Francesco", "Cosciotti", LocalDate.of(2002, 11, 25), "CADARAFA", "ISR3114141");


        System.out.println(pa.getPersona("JABDASVDA"));
        System.out.println(pa.getPersona("ADAAFAF"));
        System.out.println(pa.getPersona("CADARAFA"));

    }
}
