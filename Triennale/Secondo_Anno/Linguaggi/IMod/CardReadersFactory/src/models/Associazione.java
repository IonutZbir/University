package models;

public class Associazione {
    private String sede;
    private Scopo scopo;
    private int inAttivitaDal;

    public Associazione(String sede, Scopo scopo, int inAttivitaDal) {
        this.sede = sede;
        this.scopo = scopo;
        setInAttivitaDal(inAttivitaDal);;
    }

    public void setInAttivitaDal(int inAttivitaDal){
        if(inAttivitaDal < 1800 || inAttivitaDal > 2024){
            throw new IllegalArgumentException("L'anno di attività deve esssere compreso tra 1800 e 2024");
        }
        this.inAttivitaDal = inAttivitaDal;
    }

    @Override
    public String toString() {
        return "Associazione [sede=" + sede + ", scopo=" + scopo + ", inAttivitaDal=" + inAttivitaDal + "]";
    }

}
