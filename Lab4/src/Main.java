import dissimlab.monitors.Diagram;
import dissimlab.monitors.Statistics;
import dissimlab.random.RNGenerator;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimManager;

import java.awt.*;

public class Main {
    public static void main(String[] args) throws SimControlException {
        SimManager sm = SimManager.getInstance();


        RNGenerator rng = new RNGenerator();
        double mi = 0.1;
        double lambda = 0.3;
        int maxKlientow = 40;
        double delay = rng.exponential(lambda);

        Kasa kasa = new Kasa(rng,lambda, mi,maxKlientow);
        ZdarzenieNowyKlient n = new ZdarzenieNowyKlient(kasa, delay);

        sm.startSimulation();

        System.out.println("------------------------------------------------------");
        System.out.println("Srednia dlugosc kolejki: " + Statistics.arithmeticMean(kasa.getDlugoscKolejki()));
        System.out.println("Sredni czas przebywania klienta: " + Statistics.arithmeticMean(kasa.getCzasPrzebywania()));
        System.out.println("Srednia zajetosc kasy: " + Statistics.weightedMean(kasa.getZajetosc()));
        System.out.println("------------------------------------------------------");

        Diagram d1 = new Diagram(Diagram.DiagramType.TIME, "Zmiana w czasie długości kolejki");
        d1.add(kasa.getDlugoscKolejki(), Color.RED);
        d1.show();

        Diagram d2 = new Diagram(Diagram.DiagramType.DISTRIBUTION, "Dystrybuanta czasu przebywania");
        d2.add(kasa.getCzasPrzebywania(), Color.RED);
        d2.show();


        Diagram d3 = new Diagram(Diagram.DiagramType.TIME,"Zmiana w czasie zajetosci okeinka");
        d3.add(kasa.getZajetosc(),Color.RED);
        d3.show();
    }

}
