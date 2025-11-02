package models;

import java.time.LocalDate;

public class LiberoProfessionista extends Person {
    private String professione;
    private String partitaIVA;

    public LiberoProfessionista(String nome, String cognome, LocalDate dataDiNascita, String codiceFiscale,
            String professione, String partitaIVA) {
        super(nome, cognome, dataDiNascita, codiceFiscale);
        this.professione = professione;
        this.partitaIVA = partitaIVA;
    }

    public String getProfessione() {
        return professione;
    }

    public void setProfessione(String professione) {
        this.professione = professione;
    }

    public String getPartitaIVA() {
        return partitaIVA;
    }

    public void setPartitaIVA(String partitaIVA) {
        this.partitaIVA = partitaIVA;
    }

    @Override
    public String toString() {
        return "LiberoProfessionista [professione=" + professione + ", partitaIVA=" + partitaIVA + ", nome="
                + getNome() + ", cognome=" + getCognome() + ", data di nascita=" + getDataDiNascita()
                + ", codice fiscale=" + getCodiceFiscale() + "]\n";
    }

    
}
