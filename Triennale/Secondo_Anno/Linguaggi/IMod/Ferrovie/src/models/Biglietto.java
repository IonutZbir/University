package models;

import java.util.ArrayList;

public class Biglietto {
    private String partenza;
    private String destinazione;
    private ArrayList<Tratta> percorso;
    private double prezzo;
    private TipologiaTreni tipTreno;

    public Biglietto(String partenza, String destinazione, ArrayList<Tratta> percorso, double prezzo,
            TipologiaTreni tipTreno) {
        this.partenza = partenza;
        this.destinazione = destinazione;
        this.percorso = percorso;
        this.prezzo = prezzo;
        this.tipTreno = tipTreno;
    }

    public String getPartenza() {
        return partenza;
    }

    public void setPartenza(String partenza) {
        this.partenza = partenza;
    }

    public String getDestinazione() {
        return destinazione;
    }

    public void setDestinazione(String destinazione) {
        this.destinazione = destinazione;
    }

    public ArrayList<Tratta> getPercorso() {
        return percorso;
    }

    public void setPercorso(ArrayList<Tratta> percorso) {
        this.percorso = percorso;
    }

    public double getPrezzo() {
        return prezzo;
    }

    public void setPrezzo(double prezzo) {
        this.prezzo = prezzo;
    }

    public TipologiaTreni getTipTreno() {
        return tipTreno;
    }

    public void setTipTreno(TipologiaTreni tipTreno) {
        this.tipTreno = tipTreno;
    }

    @Override
    public String toString() {
        return "Biglietto [partenza=" + partenza + ", destinazione=" + destinazione + ", percorso=" + percorso
                + ", prezzo=" + prezzo + ", tipTreno=" + tipTreno + "]\n\n";
    }

}
