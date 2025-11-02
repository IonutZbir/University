package models;

public class Utente {
    private String nome;
    private String cognome;
    private String idUtente;
    private int numeroLibriInPrestito;

    public Utente(String nome, String cognome, String idUtente, int numeroLibriInPrestito) {
        this.nome = nome;
        this.cognome = cognome;
        this.idUtente = idUtente;
        this.numeroLibriInPrestito = numeroLibriInPrestito;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCognome() {
        return cognome;
    }

    public void setCognome(String cognome) {
        this.cognome = cognome;
    }

    public String getIdUtente() {
        return idUtente;
    }

    public void setIdUtente(String idUtente) {
        this.idUtente = idUtente;
    }

    public int getNumeroLibriInPrestito() {
        return numeroLibriInPrestito;
    }

    public void setNumeroLibriInPrestito(int numeroLibriInPrestito) {
        this.numeroLibriInPrestito = numeroLibriInPrestito;
    }

    @Override
    public String toString() {
        return "Utente [nome=" + nome + ", cognome=" + cognome + ", idUtente=" + idUtente + ", numeroLibriInPrestito="
                + numeroLibriInPrestito + "]";
    }

}
