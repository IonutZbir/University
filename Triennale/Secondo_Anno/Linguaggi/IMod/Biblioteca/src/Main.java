import services.GestioneLibri;

public class Main {
    public static void main(String[] args) {

        GestioneLibri gl = new GestioneLibri();

        // gl.createLibri();
        // gl.createLibro();
        // gl.showLibri();
        gl.search("J.J.R Tolkien", "Il Signore Degli Anelli");
    }
}
