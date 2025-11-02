package models;

import java.time.LocalDate;

public class Prestito {
    private String idPrestito;
    private String idUtente;
    private String isbnLibro;
    private LocalDate dataInizioPrestito;
    private LocalDate dataFinePrestito;

    public Prestito(String idPrestito, String idUtente, String isbnLibro, LocalDate dataInizioPrestito,
            LocalDate dataFinePrestito) {
        this.idPrestito = idPrestito;
        this.idUtente = idUtente;
        this.isbnLibro = isbnLibro;
        this.dataInizioPrestito = dataInizioPrestito;
        this.dataFinePrestito = dataFinePrestito;
    }

    public String getIdPrestito() {
        return idPrestito;
    }

    public void setIdPrestito(String idPrestito) {
        this.idPrestito = idPrestito;
    }

    public String getIdUtente() {
        return idUtente;
    }

    public void setIdUtente(String idUtente) {
        this.idUtente = idUtente;
    }

    public String getIsbnLibro() {
        return isbnLibro;
    }

    public void setIsbnLibro(String isbnLibro) {
        this.isbnLibro = isbnLibro;
    }

    public LocalDate getDataInizioPrestito() {
        return dataInizioPrestito;
    }

    public void setDataInizioPrestito(LocalDate dataInizioPrestito) {
        this.dataInizioPrestito = dataInizioPrestito;
    }

    public LocalDate getDataFinePrestito() {
        return dataFinePrestito;
    }

    public void setDataFinePrestito(LocalDate dataFinePrestito) {
        this.dataFinePrestito = dataFinePrestito;
    }

    @Override
    public String toString() {
        return "Prestito [idPrestito=" + idPrestito + ", idUtente=" + idUtente + ", isbnLibro=" + isbnLibro
                + ", dataInizioPrestito=" + dataInizioPrestito + ", dataFinePrestito=" + dataFinePrestito + "]";
    }
}
