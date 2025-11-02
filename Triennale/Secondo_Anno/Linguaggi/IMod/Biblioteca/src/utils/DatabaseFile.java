package utils;

import java.io.File;
import java.util.ArrayList;

import models.Libro;
import models.Utente;
import models.Prestito;

public class DatabaseFile {

    private String fileLibri = "src/database/Libri.csv";
    private String fileUtenti = "src/database/Utenti.csv";
    private String filePrestiti = "src/database/Prestiti.csv";

    public void insertOne(Libro libro) {
        WriteToFile wtf = new WriteToFile(this.fileLibri);
        wtf.write(libro.toStringCsv() + "\n");
    }

    public void insertMany(ArrayList<Libro> libri) {
        WriteToFile wtf = new WriteToFile(this.fileLibri);
        for (Libro libro : libri) {
            wtf.write(libro.toStringCsv() + "\n");
        }
    }

    public ArrayList<Libro> getAll() {
        ReadFromFile rff = new ReadFromFile(this.fileLibri);
        ArrayList<String> data = new ArrayList<>();
        ArrayList<Libro> libri = new ArrayList<>();
        String autore, titolo, iSBN;
        int copie;
        data = rff.read();

        for (String d : data) {
            String splitted[] = d.split(",");

            titolo = splitted[0];
            autore = splitted[1];
            iSBN = splitted[2];
            copie = Integer.parseInt(splitted[3]);

            libri.add(new Libro(titolo, autore, iSBN, copie));
        }

        return libri;
    }
}
