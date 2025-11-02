import models.Associazione;
import models.Negozio;
import models.Ristorante;
import services.Factory;
import services.FactoryImpl;

public class Main {
    public static void main(String[] args) {
        Factory f = new FactoryImpl();
        Negozio n = f.create("Negozio.txt");
        System.out.println(n);
        Ristorante r = f.create("Ristorante.txt");
        System.out.println(r);
        Associazione a = f.create("Associazione.txt");
        System.out.println(a);
    }
}
