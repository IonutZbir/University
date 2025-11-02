package models;

import java.time.LocalDate;
import java.util.ArrayList;

public class Prodotto{
    private String titolo;
    private String entePubblicante;
    private int anno;
    private ArrayList<Prestito> seqPrestiti;

    public Prodotto(String titolo, String entePubblicante, int anno){
        this.titolo = titolo;
        this.entePubblicante = entePubblicante;
        this.anno = anno;
        this.seqPrestiti = new ArrayList<>();
    }

    public void addPrestito(LocalDate dataInizio, LocalDate dataPrevistaConsegna, String nome,
            String cognome, double costoAffitto){
        this.seqPrestiti.add(new Prestito(dataInizio, dataPrevistaConsegna, nome, cognome, costoAffitto));
    }

    public void setTitolo(String titolo) {
        this.titolo = titolo;
    }

    public void setEntePubblicante(String entePubblicante) {
        this.entePubblicante = entePubblicante;
    }

    public void setAnno(int anno) {
        this.anno = anno;
    }

    public void setSeqPrestiti(ArrayList<Prestito> seqPrestiti) {
        this.seqPrestiti = seqPrestiti;
    }

    public String getTitolo() {
        return titolo;
    }


    public String getEntePubblicante() {
        return entePubblicante;
    }


    public int getAnno() {
        return anno;
    }


    public ArrayList<Prestito> getSeqPrestiti() {
        
        return new ArrayList<>(seqPrestiti);
    }
    

}