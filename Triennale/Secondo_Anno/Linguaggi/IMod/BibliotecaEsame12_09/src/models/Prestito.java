package models;

import java.time.LocalDate;

public class Prestito {
    private LocalDate dataInizio;
    private LocalDate dataPrevistaConsegna;
    private LocalDate dataConsegna;
    String nome;
    String cognome;
    private double costoAffitto;
    private static final double PENA = 10; 
    public Prestito(LocalDate dataInizio, LocalDate dataPrevistaConsegna, String nome,
            String cognome, double costoAffitto) {
        setDate(dataInizio, dataPrevistaConsegna, dataConsegna);
        this.costoAffitto = costoAffitto;
        this.nome = nome;
        this.cognome = cognome;
    }

    public void setDataConsegna(LocalDate dataConsenga){
        this.dataConsegna = dataConsenga;
        if(checkConsegna()){
            this.costoAffitto += PENA;
            System.out.println("Hai consegnato in ritardo, nuovo costo " + this.costoAffitto);
        } 
    }

    private boolean checkConsegna(){
        return this.dataConsegna.isAfter(this.dataPrevistaConsegna);
    }

    public void setDate(LocalDate dataInizio, LocalDate dataPrevistaConsegna, LocalDate dataConsegna) {
        if(dataInizio.isAfter(dataConsegna) || dataInizio.isAfter(dataPrevistaConsegna)){
            throw new IllegalArgumentException("La data di inizio non può essere dopo la data di consegna o consegna prevista!");
        }
        this.dataInizio = dataInizio;
        this.dataPrevistaConsegna = dataPrevistaConsegna;
        this.dataConsegna = dataConsegna;
    }

    public void setDataPrevistaConsegna(int giorni) {
        this.dataPrevistaConsegna = this.dataPrevistaConsegna.plusDays(giorni);
    }
    
    public void setNome(String nome) {
        this.nome = nome;
    }
    public void setCognome(String cognome) {
        this.cognome = cognome;
    }
    public void setCostoAffitto(double costoAffitto) {
        this.costoAffitto = costoAffitto;
    }
    public LocalDate getDataInizio() {
        return dataInizio;
    }
    public LocalDate getDataPrevistaConsegna() {
        return dataPrevistaConsegna;
    }
    public LocalDate getDataConsegna() {
        return dataConsegna;
    }
    public String getNome() {
        return nome;
    }
    public String getCognome() {
        return cognome;
    }
    public double getCostoAffitto() {
        return costoAffitto;
    }
    @Override
    public String toString() {
        return "Prestito [dataInizio=" + dataInizio + ", dataPrevistaConsegna=" + dataPrevistaConsegna
                + ", dataConsegna=" + dataConsegna + ", nome=" + nome + ", cognome=" + cognome + ", costoAffitto="
                + costoAffitto + "]";
    }
}