package models;

public class Ristorante {
    private String partitaIva;
    private String sede;
    private Categoria categoria;
    private int inAttivitaDal;

    public Ristorante(String partitaIva, String sede, Categoria categoria, int inAttivitaDal) {
        this.partitaIva = partitaIva;
        this.sede = sede;
        this.categoria = categoria;
        setInAttivitaDal(inAttivitaDal);
    }

    public void setInAttivitaDal(int inAttivitaDal){
        if(inAttivitaDal < 1800 || inAttivitaDal > 2024){
            throw new IllegalArgumentException("L'anno di attività deve esssere compreso tra 1800 e 2024");
        }
        this.inAttivitaDal = inAttivitaDal;
    }

    @Override
    public String toString() {
        return "Ristorante [partitaIva=" + partitaIva + ", sede=" + sede + ", categoria=" + categoria
                + ", inAttivitaDal=" + inAttivitaDal + "]";
    }

}
