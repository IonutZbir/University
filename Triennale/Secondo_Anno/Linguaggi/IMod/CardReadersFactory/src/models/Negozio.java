package models;

public class Negozio {
    private String partitaIva;
    private String sede;
    private String merceVenduta;
    private int inAttivitaDal;

    public Negozio(String partitaIva, String sede, String merceVenduta, int inAttivitaDal) {
        this.partitaIva = partitaIva;
        this.sede = sede;
        this.merceVenduta = merceVenduta;
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
        return "Negozio [partitaIva=" + partitaIva + ", sede=" + sede + ", merceVenduta=" + merceVenduta
                + ", inAttivitaDal=" + inAttivitaDal + "]";
    }
}
