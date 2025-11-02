package models;

import java.time.LocalDate;
import java.util.ArrayList;

public class Legge {
    private TipologiaLegge tipoLegge;
    private LocalDate dataCreazione;
    private String id;
    private String intestazione;
    private String conclusioni;
    private ArrayList<Articolo> articoli;
    private ArrayList<Object> allegati;

    public Legge(TipologiaLegge tipoLegge, LocalDate dataCreazione, String intestazione, String conclusioni) {
        this.tipoLegge = tipoLegge;
        this.dataCreazione = dataCreazione;
        this.intestazione = intestazione;
        this.conclusioni = conclusioni;
        this.id = setIdentificatore();
        this.allegati = new ArrayList<>();
        this.articoli = new ArrayList<>();
    }

    public String setIdentificatore(){
        String id = this.tipoLegge.name() + this.dataCreazione.toString();
        return id;
    }

    public String getId() {
        return id;
    }

    public void addArticolo(int numeroArticolo, String introduzione, String commi){
        this.articoli.add(new Articolo(numeroArticolo, introduzione, commi));
    }

    public void addArticolo(int numeroArticolo, String introduzione){
        this.articoli.add(new Articolo(numeroArticolo, introduzione));
    }

    public void addAllegato(Object allegato){
        this.allegati.add(allegato);
    }

    public String getIntestazione() {
        return intestazione;
    }

    public String getConclusioni() {
        return conclusioni;
    }

    public TipologiaLegge getTipoLegge() {
        return tipoLegge;
    }

    public LocalDate getDataCreazione() {
        return dataCreazione;
    }

    @Override
    public String toString() {
        return "Legge [tipoLegge=" + tipoLegge + ", dataCreazione=" + dataCreazione + "]\n";
    }

    public ArrayList<Articolo> getArticoli() {
        return new ArrayList<>(articoli);
    }

    public ArrayList<Object> getAllegati() {
        return new ArrayList<>(allegati);
    }
}
