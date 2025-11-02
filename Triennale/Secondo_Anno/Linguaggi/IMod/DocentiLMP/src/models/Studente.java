package models;

import java.time.LocalDate;
import java.util.HashMap;

public class Studente {
    private String nome;
    private String cognome;
    private String matricola;
    
    private HashMap<LocalDate, Integer> votoMod1 = new HashMap<>();
    private HashMap<LocalDate, Integer> votoMod2 = new HashMap<>();
    private HashMap<LocalDate, Integer> votoOrale = new HashMap<>();


    public Studente(String nome, String cognome, String matricola) {
        this.nome = nome;
        this.cognome = cognome;
        this.matricola = matricola;
    }
    public String getNome() {
        return nome;
    }
    public String getCognome() {
        return cognome;
    }
    public String getMatricola() {
        return matricola;
    }
    
    @Override
    public String toString() {
        return "Studente [nome=" + nome + ", cognome=" + cognome + ", matricola=" + matricola + "]";
    }

    public void setVotoMod1(int voto, Esame e) {
        if(voto < 0 || voto > 31){
            throw new IllegalArgumentException("Il voto deve essere compre tra 0 e 31(30L)");
        }

        this.votoMod1.put(e.getDataEsame(), voto);
    }
   
    public void setVotoMod2(int voto, Esame e) {
        if(voto < 0 || voto > 31){
            throw new IllegalArgumentException("Il voto deve essere compre tra 0 e 31(30L)");
        }

        this.votoMod2.put(e.getDataEsame(), voto);
    }
    public void setVotoOrale(int voto, Esame e) {
        if(voto < 0 || voto > 31){
            throw new IllegalArgumentException("Il voto deve essere compre tra 0 e 31(30L)");
        }

        this.votoOrale.put(e.getDataEsame(), voto);
    }

    public int getVotoMod1(LocalDate dataEsame) {
        return votoMod1.get(dataEsame);
    }
    public int getVotoMod2(LocalDate dataEsame) {
        return votoMod2.get(dataEsame);    
    }
    public int getVotoOrale(LocalDate dataEsame) {
        return votoOrale.get(dataEsame);
    }
}
