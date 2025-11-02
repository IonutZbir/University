package models;

import java.time.LocalDate;

public class Impiegato extends Person {
    private String matricola;
    private int livello;
    private String mansione;

    public Impiegato(String nome, String cognome, LocalDate dataDiNascita, String codiceFiscale, String matricola,
            int livello, String mansione) {
        super(nome, cognome, dataDiNascita, codiceFiscale);
        this.matricola = matricola;
        this.livello = livello;
        this.mansione = mansione;
    }

    public String getMatricola() {
        return matricola;
    }

    public void setMatricola(String matricola) {
        this.matricola = matricola;
    }

    public int getLivello() {
        return livello;
    }

    public void setLivello(int livello) {
        this.livello = livello;
    }

    public String getMansione() {
        return mansione;
    }

    public void setMansione(String mansione) {
        this.mansione = mansione;
    }

    @Override
    public String toString() {
        return "Impiegato [matricola=" + matricola + ", livello=" + livello + ", mansione=" + mansione + ", nome="
                + getNome() + ", cognome=" + getCognome() + ", data di nascita=" + getDataDiNascita()
                + ", codice fiscale=" + getCodiceFiscale() + "]\n";
    }

    

}
