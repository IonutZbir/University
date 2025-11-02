package models;

import java.util.ArrayList;

public class Prodotto {
    private String identificativo;
    private String etichetta;
    ArrayList<Componente> componenti;
    private double costoGiornaliero;
    private int tempoRealizzazione;
    private double fattoreGuadagno;

    public Prodotto(String identificativo, String etichetta,
            ArrayList<Componente> componenti, double costoGiornaliero, int tempoRealizzazione, double fattoreGuadagno) {
        this.identificativo = identificativo;
        this.etichetta = etichetta;
        this.componenti = componenti;
        this.costoGiornaliero = costoGiornaliero;
        this.tempoRealizzazione = tempoRealizzazione;
        this.fattoreGuadagno = fattoreGuadagno;
    }

    public String getIdentificativo() {
        return identificativo;
    }

    public String getEtichetta() {
        return etichetta;
    }

    public void setCostoGiornaliero(double costoGiornaliero) {
        this.costoGiornaliero = costoGiornaliero;
    }

    public void setFattoreGuadagno(double fattoreGuadagno) {
        this.fattoreGuadagno = fattoreGuadagno;
    }

    public int getTempoTotaleStimatoOrdineComponenti(){
        int max = 0;
        for (Componente comp : this.componenti) {
            max = Math.max(max, comp.getTempoDiOrdinazione());
        }
        return max;
    }

    public int getNumeroDiComponenti(){
        return this.componenti.size();
    }

    public double getCostoDiRealizzazione(){
        return (double)this.tempoRealizzazione * this.costoGiornaliero;
    }

    private double getCostoComplessivoComponenti(){
        double costo = 0;
        for (Componente comp : this.componenti) {
            costo += comp.getCosto();
        }
        return costo;
    }

    private double getCostoComplessivoProduzione(){
        return this.getCostoComplessivoComponenti() + this.getCostoDiRealizzazione();
    }

    public double getPrezziAcquirenti(){
        return this.getCostoComplessivoProduzione() + this.fattoreGuadagno;
    }

    @Override
    public String toString() {
        return "Prodotto [identificativo=" + identificativo + ", etichetta=" + etichetta + ", componenti=" + componenti
                + ", getPrezziAcquirenti()=" + getPrezziAcquirenti() + "]";
    }

    
}
