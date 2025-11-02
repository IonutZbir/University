package models;

public enum TipologiaTratte {
    NAZIONALE_BLU(0.15),
    NAZIONALE_GRIGIO(0.1),
    REGIONALE_BLU(0.1),
    REGIONALE_GRIGIO(0.08);

    private double prezzo;

    private TipologiaTratte(double prezzo) {
        this.prezzo = prezzo;
    }

    public double getPrezzo() {
        return prezzo;
    }

}
