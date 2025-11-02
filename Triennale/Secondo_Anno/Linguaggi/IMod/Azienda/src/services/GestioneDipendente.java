package services;

import java.time.LocalDate;
import java.util.ArrayList;

import models.Dipendente;
import models.Mansione;
import models.Dipendente.Dipartimento;

public class GestioneDipendente {
    private ArrayList<Dipendente> dipendenti = new ArrayList<>();

    public void insertDipendente(String nome, String cognome, LocalDate dataDiNascita, Dipartimento dip) {

        dipendenti.add(new Dipendente(nome, cognome, dataDiNascita, dip));

    }

    public void updateDipendente(Mansione mansione, int livello, Dipendente capo, Dipendente curr) {
        curr.setCapo(capo);
        curr.setMansione(mansione);
        if (livello < 1 || livello > 8) {
            throw new IllegalArgumentException("Il livello deve essere compreso tra 1 e 8.");
        }
        curr.setLivello(livello);
    }

    public ArrayList<Dipendente> getChainOfCommand(Dipendente impiegato) {

        ArrayList<Dipendente> chain = new ArrayList<>();

        while (impiegato.getCapo() != null) {
            chain.add(impiegato.getCapo());
            impiegato = impiegato.getCapo();
        }

        return chain;
    }

    public Dipendente nextEmployer(Dipendente currEmployer) {

        for (Dipendente dip : this.dipendenti) {
            if (dip.getCapo().equals(currEmployer.getCapo()) && dip.getMansione().equals(currEmployer.getMansione())) {
                return dip;
            }
        }

        System.out.println("Non è possibile sostituire l'impiegato!!");
        return null;
    }

    public ArrayList<Dipendente> sameYearOfHire() {
        ArrayList<Dipendente> dipSameYearOfHire = new ArrayList<>();

        for (Dipendente d1 : this.dipendenti) {
            for (Dipendente d2 : this.dipendenti) {
                if (!d1.equals(d2)) {
                    if (d1.getDipartimento().equals(d2.getDipartimento()) &&
                            d1.getDataDiAssunzione().getMonth() == d2.getDataDiAssunzione().getMonth() &&
                            d1.getDataDiAssunzione().getYear() == d2.getDataDiAssunzione().getYear()) {
                        dipSameYearOfHire.add(d1);
                    }
                }
            }
        }

        return dipSameYearOfHire;

    }

    public Dipendente getDipendente(String nome, String cognome) {
        for (Dipendente dip : this.dipendenti) {
            if (dip.getNome().equals(nome) && dip.getCognome().equals(cognome)) {
                return dip;
            }
        }

        System.out.println("Non è stato trovato nessun impiegato!");
        return null;
    }

    public Dipendente getDipendente(String matricola) {
        for (Dipendente dip : this.dipendenti) {
            if (dip.getMatricola().equals(matricola)) {
                return dip;
            }
        }

        System.out.println("Non è stato trovato nessun impiegato!");
        return null;
    }

    public void showDipendenti() {
        for (Dipendente dip : dipendenti) {
            System.out.println(dip.toString());
        }
    }

}
