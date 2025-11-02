package services;

import java.time.LocalDate;
import java.time.Year;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.NoSuchElementException;

import models.Legge;
import models.TipologiaLegge;

public class GestioneLeggi {
    
    HashMap<String, Legge> archivioLeggi = new HashMap<>();

    public void addLegge(TipologiaLegge tipoLegge, LocalDate dataCreazione, String intestazione, String conclusioni){
        Legge l = new Legge(tipoLegge, dataCreazione, intestazione, conclusioni);
        archivioLeggi.put(l.getId(), l);
    }

    public Legge getLegge(String id){
        Legge l = archivioLeggi.get(id);
        if(l == null){
            throw new NoSuchElementException("La legge non è presente nell'archivio!");
        }
        return l;
    }

    public Legge getLegge(TipologiaLegge tipologiaLegge, LocalDate dataCreazione){
        String id = tipologiaLegge.name() + dataCreazione.toString();
        Legge l = archivioLeggi.get(id);
        if(l == null){
            throw new NoSuchElementException("La legge non è presente nell'archivio!");
        }
        return l;
    }

    public void stessoTipoStessoAnno(TipologiaLegge tipologiaLegge, Year anno){
        ArrayList<Legge> leggi = new ArrayList<>();
        for (Legge l : archivioLeggi.values()) {
            if(l.getDataCreazione().getYear() == anno.getValue() && l.getTipoLegge() == tipologiaLegge){
                leggi.add(l);
            }
        }
        System.out.println(leggi);
    }

    public void get20Articoli(){
        ArrayList<Legge> leggi = new ArrayList<>();
        for (Legge l : archivioLeggi.values()) {
            if(l.getArticoli().size() > 20){
                leggi.add(l);
            }
        }
        System.out.println(leggi);
    }

}
