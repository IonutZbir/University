package models;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.NoSuchElementException;

public class Esame {

    private ArrayList<Studente> studenti = new ArrayList<>();

    private String argJava;
    private String argPrologAndPython;
    private String argOrale;

    private LocalDate dataEsame;


    public Esame(ArrayList<Studente> studenti, String argJava, String argPrologAndPython, String argOrale, LocalDate dataEsame) {
        this.studenti = studenti;
        this.argJava = argJava;
        this.argPrologAndPython = argPrologAndPython;
        this.argOrale = argOrale;
        this.dataEsame = dataEsame;
    }

    

    
    /** 
     * @return LocalDate
     */
    public LocalDate getDataEsame() {
        return dataEsame;
    }

    public void getVotoStudentePerProva(Studente s, TipoProva tp){
        switch (tp) {
            case MOD1:
                System.out.println(argJava);
                System.out.println(s.getVotoMod1(this.dataEsame));
                System.out.println(s);
                break;
            case MOD2:
                System.out.println(argPrologAndPython);
                System.out.println(s.getVotoMod2(this.dataEsame));
                System.out.println(s);
                break;
            case ORALE:
                System.out.println(argOrale);
                System.out.println(s.getVotoOrale(this.dataEsame));
                System.out.println(s);
                break;
            default:
                throw new IllegalArgumentException("Tipologia prova invalida");
        }
    }

    public void getVotoStudentePerEsame(Studente s){
        String valutazione = "";
        int votoFinale = getVotoFinalePerStudente(s);
        if(votoFinale >= 18){
            valutazione = "promosso";
        }
        else{
            valutazione = "bocciato";
        }
        System.out.println("Lo studente " + s + " è stato " + valutazione + " con voto " + votoFinale);
    }

    private int getVotoFinalePerStudente(Studente s){
        return (s.getVotoMod1(dataEsame) + s.getVotoMod2(dataEsame) + s.getVotoOrale(dataEsame)) / 3; 
    }

    private int getNumeroPromossi(){
        int votoFinale;
        int counter = 0;
        for (Studente s : studenti) {
            votoFinale = getVotoFinalePerStudente(s);
            if(votoFinale >= 18)
                counter++;
        }
        return counter;
    }

    private double getPercentualePromossi(){
        return (double) getNumeroPromossi() / studenti.size() * 100;
    }

    public void getInfo(){
        System.out.println("L'esame è stato svolto in data: " + dataEsame);
        System.out.println("All'esame sono partecipati " + studenti.size() + " studenti");
        System.out.println("Sono stati promossi " + getNumeroPromossi() + " studenti");
        System.out.println("La percentuale dei studenti promossi è " + getPercentualePromossi() + "%");
    }


    public void getInfo(String matricola){
        Studente s1  = null;
        for (Studente s : studenti) {
            if (matricola.equals(s.getMatricola())) {
                s1 = s;
                break;
            }
        }
        if(s1 == null){
            throw new NoSuchElementException("Lo studente con matricola " + matricola + "non esiste");
        }

        System.out.println("Data esame: " + dataEsame);
        System.out.println("Voto prova Java: " + s1.getVotoMod1(dataEsame));
        System.out.println("Voto prova Prolog e Python: " + s1.getVotoMod2(dataEsame));
        System.out.println("Voto prova Orale: " + s1.getVotoOrale(dataEsame));
    }
}
