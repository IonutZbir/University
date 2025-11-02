import java.time.LocalDate;

import models.Libro;
import services.Biblioteca;

public class Main {
    public static void main(String[] args) {
        Biblioteca b = new Biblioteca();

        b.addProdotto("Il Signore Degli Anelli", "Mondadori", 2000, null, 400);

        Libro p1 = (Libro) b.getProdotto("Il Signore Degli Anelli");
        p1.addPrestito(LocalDate.now(), LocalDate.of(2024, 11, 22), "Ionut", "Zbirciog", 21);

        p1.addPrestito(LocalDate.of(2024, 12, 9), LocalDate.of(2025, 1, 27), "Mario", "Rossi", 21);
        
        p1.addPrestito(LocalDate.of(2025, 5, 21), LocalDate.of(2025, 6, 12), "Ionut", "Zbirciog", 21);

        b.trovaInconsistenze(p1);

        p1.addPrestito(LocalDate.now(), LocalDate.of(2024, 9, 11), "Giovanni", "Verdi", 21);
        System.out.println("Prima di aggiungere:");
        System.out.println(p1.getSeqPrestiti());
        System.out.println("Dopo l'aggiunta: ");
        b.setGiorniRicosengna(p1, 10);
        System.out.println(p1.getSeqPrestiti());
        System.out.println();

        int n = b.maxGiorniPrestiti(p1);
        System.out.println(n);

        Libro p2 = (Libro) b.getProdotto("The Witcher");
    }
}
