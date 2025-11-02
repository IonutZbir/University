package models;

import java.util.ArrayList;

public class Tratta {
    private double lunghezza;
    private ArrayList<TipologiaTratte> tipTratta;
    private ArrayList<TipologiaTreni> tipTreno;
    private String partenza;
    private String destinazione;

    public Tratta(double lunghezza, ArrayList<TipologiaTratte> tipTratta, ArrayList<TipologiaTreni> tipTreno,
            String partenza,
            String destinazione) {
        this.lunghezza = lunghezza;
        this.tipTratta = tipTratta;
        this.tipTreno = tipTreno;
        this.partenza = partenza;
        this.destinazione = destinazione;
    }

    public double getLunghezza() {
        return lunghezza;
    }

    public ArrayList<TipologiaTratte> getTipTratta() {
        return tipTratta;
    }

    public ArrayList<TipologiaTreni> getTipTreno() {
        return tipTreno;
    }

    public String getPartenza() {
        return partenza;
    }

    public String getDestinazione() {
        return destinazione;
    }

    @Override
    public String toString() {
        return "Tratta [lunghezza=" + lunghezza + ", tipTratta=" + tipTratta + ", tipTreno=" + tipTreno + ", partenza="
                + partenza + ", destinazione=" + destinazione + "]";
    }

}
