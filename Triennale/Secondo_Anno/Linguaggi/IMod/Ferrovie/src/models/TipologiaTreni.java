package models;

public enum TipologiaTreni {
    NORMALE(1.0),
    ALTA_V(1.5);

    private double prezzo;

    private TipologiaTreni(double prezzo) {
        this.prezzo = prezzo;
    }

    public double getPrezzo() {
        return prezzo;
    }
}
