package services;

import java.util.HashMap;
import models.Associazione;
import models.Categoria;
import models.Negozio;
import models.Ristorante;
import models.Scopo;
import utils.Deserializer;

public class FactoryImpl implements Factory {
    @Override
    public <T> T create(String path){
        Deserializer s = new Deserializer(path);
        String fileName = s.getFileName();
        HashMap<String, String> data = s.getData();
        switch (fileName) {
            case "negozio":
                return (T) creaNegozio(data);
            case "ristorante":
                return (T) creaRistorante(data);
            case "associazione":
                return (T) creaAssociazione(data);
            default:
                throw new IllegalArgumentException("Nome del file non supportato: " + fileName);
        }
    }

    private Negozio creaNegozio(HashMap<String, String> data){
        String partitaIVA = data.get("partita_IVA");
        String sede = data.get("sede");
        String merceVenduta = data.get("merce_venduta");
        int inAttivitaDal = Integer.parseInt(data.get("in_attività_dal"));

        return new Negozio(partitaIVA, sede, merceVenduta, inAttivitaDal);
    }

    private Ristorante creaRistorante(HashMap<String, String> data){
        String partitaIVA = data.get("partita_IVA");
        String sede = data.get("sede");
        String categoriaString = data.get("categoria");
        int inAttivitaDal = Integer.parseInt(data.get("in_attività_dal"));
        Categoria categoria;

        switch (categoriaString) {
            case "pizzeria":
                categoria = Categoria.PIZZERIA;
                break;
            case "italiano":
                categoria = Categoria.ITALIANO;
                break;
            case "etnico":
                categoria = Categoria.ETNICO;
                break;
            default:
                throw new IllegalArgumentException("Categoria inesistente" + categoriaString);
        }
        return new Ristorante(partitaIVA, sede, categoria, inAttivitaDal);
    }

    private Associazione creaAssociazione(HashMap<String, String> data){
        String sede = data.get("sede");
        int inAttivitaDal = Integer.parseInt(data.get("in_attività_dal"));
        String scopoString = data.get("scopo");
        Scopo scopo;
        switch (scopoString) {
            case "ricreativo":
                scopo = Scopo.RICREATIVO;
                break;
            case "culturale":
                scopo = Scopo.CULTURALE;
                break;
            case "volontario":
                scopo = Scopo.VOLONTARIATO;
            default:
                throw new IllegalArgumentException("Scopo inesistente " + scopoString);
        }
        return new Associazione(sede, scopo, inAttivitaDal);
    }
}
