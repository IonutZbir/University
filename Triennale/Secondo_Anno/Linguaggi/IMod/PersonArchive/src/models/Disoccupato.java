package models;

import java.time.LocalDate;

public class Disoccupato extends Person {
    private String iscrizioneRegistroDisoccupazione;

    public Disoccupato(String nome, String cognome, LocalDate dataDiNascita, String codiceFiscale,
            String iscrizioneRegistroDisoccupazione) {
        super(nome, cognome, dataDiNascita, codiceFiscale);
        this.iscrizioneRegistroDisoccupazione = iscrizioneRegistroDisoccupazione;
    }

    public String getIscrizioneRegistroDisoccupazione() {
        return iscrizioneRegistroDisoccupazione;
    }

    public void setIscrizioneRegistroDisoccupazione(String iscrizioneRegistroDisoccupazione) {
        this.iscrizioneRegistroDisoccupazione = iscrizioneRegistroDisoccupazione;
    }

    @Override
    public String toString() {
        return "Disoccupato [iscrizioneRegistroDisoccupazione=" + iscrizioneRegistroDisoccupazione + ", nome="
                + getNome() + ", cognome=" + getCognome() + ", data di nascita=" + getDataDiNascita()
                + ", codice fiscale=" + getCodiceFiscale() + "]\n";
    }

    

}
