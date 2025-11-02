package models;

import java.time.LocalDate;
import java.time.Month;
import java.util.HashMap;

public class Sportivo {
    private String nome;
    private String cognome;
    private HashMap<Month, Integer> reti;
    private LocalDate dataAssunzione;
    private TipologiaSportivo tipologia;
    private String nrIscrizione;
    private int livello;
    private static int nrProgressivo = 0;

    public Sportivo(String nome, String cognome, LocalDate dataAssunzione,
            TipologiaSportivo tipologia, int livello) {
        this.nome = nome;
        this.cognome = cognome;
        this.reti = new HashMap<>();
        this.tipologia = tipologia;
        this.nrIscrizione = "TEAM_" + (++nrProgressivo);
        this.setLivello(livello);
        this.setDataAssunzione(dataAssunzione);
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCognome() {
        return cognome;
    }

    public void setCognome(String cognome) {
        this.cognome = cognome;
    }

    public HashMap<Month, Integer> getReti() {
        return new HashMap<>(reti);
    }

    public void addReti(Month mese, int reti) {
        if (reti < 0) {
            throw new IllegalArgumentException("Il numero di reti non può essere negativo.");
        }

        int currReti = this.reti.getOrDefault(mese, 0); // Get current goals or 0 if not present
        this.reti.put(mese, reti + currReti);  
    }

    public LocalDate getDataAssunzione() {
        return dataAssunzione;
    }

    public void setDataAssunzione(LocalDate dataAssunzione) {
        if (dataAssunzione.getYear() < 2000) {
            throw new IllegalArgumentException("L'anno di assunzione deve essere >= 2000!");
        }
        this.dataAssunzione = dataAssunzione;
    }

    public TipologiaSportivo getTipologia() {
        return tipologia;
    }

    public void setTipologia(TipologiaSportivo tipologia) {
        this.tipologia = tipologia;
    }

    public String getNrIscrizione() {
        return nrIscrizione;
    }

    public void setNrIscrizione(String nrIscrizione) {
        this.nrIscrizione = nrIscrizione;
    }

    public int getLivello() {
        return livello;
    }

    public void setLivello(int livello) {
        if (livello < 1 || livello > 5) {
            throw new IllegalArgumentException("Il livello stipendiale deve essere tra 1 e 5.");
        }
        this.livello = livello;
    }

    @Override
    public String toString() {
        return "Sportivo [nome=" + nome + ", cognome=" + cognome + ", reti=" + reti + ", dataAssunzione="
                + dataAssunzione + ", tipologia=" + tipologia + ", nrIscrizione=" + nrIscrizione + ", livello="
                + livello + "]";
    }    
}
