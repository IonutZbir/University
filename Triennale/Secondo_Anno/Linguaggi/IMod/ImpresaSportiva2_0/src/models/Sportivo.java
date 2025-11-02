package models;

import java.time.LocalDate;
import java.time.Month;
import java.util.HashMap;

public class Sportivo {

    private String nome;
    private String cognome;
    private LocalDate dataAssunzione;
    private HashMap<Month, Integer> retiPerMese;
    private String nrIscrizione; // TEAM_2
    private static int counter = 0;
    private int livelloStipendiale;
    private TipologiaSportivo tipoSportivo;

    // primitivi -> int, float, char[], double
    // references -> Integer, Float, Double, String, 
    // class

    public Sportivo(String nome, String cognome, LocalDate dataAssunzione, int livelloStipendiale, TipologiaSportivo tipoSportivo) {
        this.nome = nome;
        this.cognome = cognome;
        this.nrIscrizione = "TEAM_" + (++counter);
        this.retiPerMese = new HashMap<>();
        this.tipoSportivo = tipoSportivo;
        setDataAssunzione(dataAssunzione); // data di assunzione >= 1800
        setLivelloStipendiale(livelloStipendiale);
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setCognome(String cognome) {
        this.cognome = cognome;
    }

    public void setLivelloStipendiale(int livelloStipendiale){
        if(livelloStipendiale < 1 || livelloStipendiale > 5){
            throw new IllegalArgumentException("Il livello stipendiale deve essere compreso tra 1 e 5!");
        }
        this.livelloStipendiale = livelloStipendiale;
    }

    public void setDataAssunzione(LocalDate dataAssunzione) {
        if(dataAssunzione.getYear() < 1800){
            throw new IllegalArgumentException("La data di assunzione deve essere >= 1800!");
        }
        this.dataAssunzione = dataAssunzione;
    }

    public void setRetiPerMese(Month mese, int reti) {
        if(reti <= 0){
            throw new IllegalArgumentException("Le reti devono essere > 0!");
        }
        int retiCurr = retiPerMese.getOrDefault(mese, 0);
        retiPerMese.put(mese, reti + retiCurr);
    }

    public String getNome() {
        return nome;
    }

    public String getCognome() {
        return cognome;
    }

    public LocalDate getDataAssunzione() {
        return dataAssunzione;
    }

    public HashMap<Month, Integer> getRetiPerMese() { // return StrutturaDati
        return new HashMap<>(retiPerMese); // copia
    }

    public String getNrIscrizione() {
        return nrIscrizione;
    }

    public int getLivelloStipendiale() {
        return livelloStipendiale;
    }

    public TipologiaSportivo getTipoSportivo() {
        return tipoSportivo;
    }

    public void setTipoSportivo(TipologiaSportivo tipoSportivo) {
        this.tipoSportivo = tipoSportivo;
    }

    @Override
    public String toString() {
        return "Sportivo [nome=" + nome + ", cognome=" + cognome + ", dataAssunzione=" + dataAssunzione
                + ", livelloStipendiale=" + livelloStipendiale + ", tipoSportivo=" + tipoSportivo + "]\n";
    }

}
