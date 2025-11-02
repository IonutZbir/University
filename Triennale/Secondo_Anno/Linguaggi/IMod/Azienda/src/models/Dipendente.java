package models;

import java.time.LocalDate;

public class Dipendente {

    public enum Dipartimento {
        MARKETING, RISORSE_UMANE, SVILUPPO
    }

    private String nome;
    private String cognome;
    private LocalDate dataDiNascita;
    private LocalDate dataDiAssunzione;

    static private int numeroProgressivo = 0;

    private Mansione mansione;
    private Dipartimento dipartimento;
    private String matricola;
    private int livello;

    private Dipendente capo;

    public Dipendente(String nome, String cognome, LocalDate dataDiNascita, Dipartimento dipartimento) {
        this.nome = nome;
        this.cognome = cognome;
        this.dataDiNascita = dataDiNascita;

        this.dataDiAssunzione = LocalDate.now();
        this.matricola = "CTL_" + String.valueOf(numeroProgressivo + 1);
        this.dipartimento = dipartimento;
        numeroProgressivo++;
    }

    public String getNome() {
        return nome;
    }

    public String getCognome() {
        return cognome;
    }

    public LocalDate getDataDiNascita() {
        return dataDiNascita;
    }

    public LocalDate getDataDiAssunzione() {
        return dataDiAssunzione;
    }

    public Mansione getMansione() {
        return mansione;
    }

    public Dipartimento getDipartimento() {
        return dipartimento;
    }

    public String getMatricola() {
        return matricola;
    }

    public int getLivello() {
        return livello;
    }

    public Dipendente getCapo() {
        return capo;
    }

    public void setMansione(Mansione mansione) {
        this.mansione = mansione;
    }

    public void setDipartimento(Dipartimento dipartimento) {
        this.dipartimento = dipartimento;
    }

    public void setLivello(int livello) {
        this.livello = livello;
    }

    public void setCapo(Dipendente capo) {
        this.capo = capo;
    }

    @Override
    public String toString() {
        return "Dipendente [nome=" + nome + ", cognome=" + cognome + ", dataDiNascita=" + dataDiNascita
                + ", dataDiAssunzione=" + dataDiAssunzione + ", mansione=" + mansione + ", dipartimento=" + dipartimento
                + ", matricola=" + matricola + ", livello=" + livello + ", capo=" + capo + "]";
    }

}
