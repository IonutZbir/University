package services;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.NoSuchElementException;

import models.Disoccupato;
import models.Impiegato;
import models.LiberoProfessionista;
import models.Person;

public class PersonArchive {
    private static final int ANNO_MINIMO = 1900; 

    static private HashMap<String, Person> archivioPersone = new HashMap<>();

    public void createPerson(String nome, String cognome, LocalDate dataDiNascita, String codiceFiscale, String matricola, int livello, String mansione){
        if(dataDiNascita.getYear() < ANNO_MINIMO){
           throw new IllegalArgumentException("Anno Invalido: l'anno di nascita è inferiore a " + ANNO_MINIMO); 
        }

        archivioPersone.put(codiceFiscale, new Impiegato(nome, cognome, dataDiNascita, codiceFiscale, matricola, livello, mansione));
    }

    public void createPerson(String nome, String cognome, LocalDate dataDiNascita, String codiceFiscale, String professione, String partitaIVA){
        if(dataDiNascita.getYear() < ANNO_MINIMO){
           throw new IllegalArgumentException("Anno Invalido: l'anno di nascita è inferiore a " + ANNO_MINIMO); 
        }

        archivioPersone.put(codiceFiscale, new LiberoProfessionista(nome, cognome, dataDiNascita, codiceFiscale, professione, partitaIVA));
    }

    public void createPerson(String nome, String cognome, LocalDate dataDiNascita, String codiceFiscale, String iscrizioneRegistroDisoccupazione){
        if(dataDiNascita.getYear() < ANNO_MINIMO){
           throw new IllegalArgumentException("Anno Invalido: l'anno di nascita è inferiore a " + ANNO_MINIMO); 
        }

        archivioPersone.put(codiceFiscale, new Disoccupato(nome, cognome, dataDiNascita, codiceFiscale, iscrizioneRegistroDisoccupazione));
    }

    public String getPersona(String codiceFiscale){

        Person p = archivioPersone.get(codiceFiscale);
        if(p == null){
            throw new NoSuchElementException("La persona con codice fiscale: {" + codiceFiscale + "} non esiste!");
        }
        return p.toString();
    }
}
