
import dissimlab.monitors.Diagram;
import dissimlab.monitors.Statistics;
import dissimlab.random.RNGenerator;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimManager;

import java.awt.*;

public class Main {
    public static void main(String[] args) throws SimControlException{
        SimManager sm = SimManager.getInstance();
        //sm.setEndSimTime(1000);

        RNGenerator rng = new RNGenerator();
        double mi = 0.2;
        double lambda = 0.9;
        double ro = 0.2;
        int maxKlientow = 60;
        double delay = rng.exponential(lambda);
        int M = 3;
        int L = 5;
        double p = 0.4;
        double alfa = 0.05;
        double beta = 0.6;

        Kasa kasa = new Kasa(rng, mi, ro, M, L, p, alfa, beta, maxKlientow);
        Budynek budynek = new Budynek(rng, kasa, lambda, ro, maxKlientow);
        ZdarzenieNowyKlient n = new ZdarzenieNowyKlient(budynek, delay);
        ZdarzenieAwaria a = new ZdarzenieAwaria(kasa, kasa.getCzasZdatnosci());

        sm.startSimulation();
        double pStraty = (double)kasa.getLiczbaStrat()/budynek.getLicznikKlientow();
        System.out.println("------------------------------------------------------");
        System.out.println("Srednia dlugosc kolejki: " + Statistics.arithmeticMean(kasa.getDlugoscKolejki()));
        System.out.println("Sredni czas przebywania klienta: " + Statistics.arithmeticMean(kasa.getCzasPrzebywania()));
        System.out.println("Srednia liczba zajetych okienek: " + Statistics.arithmeticMean(kasa.getZajetosc()));
        System.out.println("Prawdopodobienstwo straty: " + pStraty);
        System.out.println("------------------------------------------------------");

        Diagram d1 = new Diagram(Diagram.DiagramType.TIME, "Zmiana w czasie długości kolejki");
        d1.add(kasa.getDlugoscKolejki(), Color.RED);
        d1.show();

        Diagram d2 = new Diagram(Diagram.DiagramType.DISTRIBUTION, "Dystrybuanta czasu przebywania");
        d2.add(kasa.getCzasPrzebywania(), Color.RED);
        d2.show();

        Diagram d3 = new Diagram(Diagram.DiagramType.TIME, "Zmiana w czasie liczby zajetych okienek");
        d3.add(kasa.getZajetosc(), Color.RED);
        d3.show();

        Diagram d4 = new Diagram(Diagram.DiagramType.DISTRIBUTION, "Dystrybuanta dlugosci kolejki");
        d4.add(kasa.getDlugoscKolejki(), Color.RED);
        d4.show();
    }
}
