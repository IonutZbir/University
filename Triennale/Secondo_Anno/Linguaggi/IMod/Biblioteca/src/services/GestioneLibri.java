package services;

import java.util.ArrayList;

import models.Libro;
import utils.DatabaseFile;

import java.util.Scanner;

public class GestioneLibri {

    private String messaggio = """
            Inserire le seguenti infomazioni:
            1. Titolo
            2. Autore
            3. iSBN
            4. Numero di copie
            """;

    private DatabaseFile df = new DatabaseFile();

    public void createLibro() {

        String titolo;
        String autore;
        String iSBN;
        int copie;

        Scanner input = new Scanner(System.in);

        System.out.println(messaggio);

        titolo = input.nextLine();
        autore = input.nextLine();
        iSBN = input.nextLine();
        copie = Integer.parseInt(input.nextLine());

        input.close();
        df.insertOne(new Libro(titolo, autore, iSBN, copie));
    }

    public void createLibri() {
        String titolo;
        String autore;
        String iSBN;
        int copie;

        ArrayList<Libro> libri = new ArrayList<>();

        Scanner input = new Scanner(System.in);

        boolean flag = true;

        while (flag) {
            System.out.println(messaggio);

            titolo = input.nextLine();
            autore = input.nextLine();
            iSBN = input.nextLine();
            copie = Integer.parseInt(input.nextLine());

            libri.add(new Libro(titolo, autore, iSBN, copie));

            System.out.println("Hai ancora libri da inserire? SI/NO\n");
            if (input.nextLine().equals("NO")) {
                flag = false;
            }
        }

        input.close();
        df.insertMany(libri);
    }

    public void showLibri() {
        ArrayList<Libro> libri = df.getAll();
        if (libri.size() != 0) {
            for (Libro libro : libri) {
                System.out.println(libro.toString());
            }
        } else {
            System.out.println("Non ci sono libri nella biblioteca!");
        }
    }

    public void search(String autore, String titolo) {
        ArrayList<Libro> libri = df.getAll();
        boolean trovato = false;

        if (libri.size() != 0) {
            for (Libro libro : libri) {
                String a = libro.getAutore();
                String t = libro.getTitolo();

                if (a.equalsIgnoreCase(autore) || t.equalsIgnoreCase(titolo)) {
                    System.out.println(libro.toString());
                    trovato = true; // libro trovato, imposta la flag a true
                }
            }

            if (!trovato) {
                System.out.println("Il libro non è presente nella biblioteca!");
            }
        } else {
            System.out.println("Non ci sono libri nella biblioteca!");
        }
    }

}
