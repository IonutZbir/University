package models;

public class Componente {
    private String nome;
    private String paese;
    private Visibilita visibilita;
    private int tempoDiOrdinazione;
    private double costo;

    public Componente(String nome, String paese, Visibilita visibilita, int tempoDiOrdinazione, double costo) {
        this.nome = nome;
        this.paese = paese;
        this.visibilita = visibilita;
        this.tempoDiOrdinazione = tempoDiOrdinazione;
        this.costo = costo;
    }

    public String getNome() {
        return nome;
    }

    public String getPaese() {
        return paese;
    }

    public Visibilita getVisibilita() {
        return visibilita;
    }

    public int getTempoDiOrdinazione() {
        return tempoDiOrdinazione;
    }

    public double getCosto() {
        return costo;
    }

    @Override
    public String toString() {
        return "Componente [nome=" + nome + ", paese=" + paese + ", visibilita=" + visibilita + ", tempoDiOrdinazione="
                + tempoDiOrdinazione + ", costo=" + costo + "]";
    }
}
