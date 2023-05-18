import dissimlab.monitors.Diagram;
import dissimlab.monitors.Statistics;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimManager;

import java.awt.*;

public class Main {
    public static void main(String[] args) throws SimControlException {
        SimManager sm = SimManager.getInstance();
        sm.setEndSimTime(1000);
        Trasa trasa = new Trasa(400.0, 4);
        NowyPojazd nowyPojazd = new NowyPojazd(trasa, null, 1);
        RuchPojazdow ruchPojazdow = new RuchPojazdow(trasa, null, 1);
        Parkowanie parkowanie =new Parkowanie(trasa,null,1);
        sm.startSimulation();
        System.out.println("Srednia liczba pojazdow na trasie: "+ Statistics.weightedMean(trasa.liczbaPojazdow));
        System.out.println("Sredni czas drogi: "+ Statistics.arithmeticMean(trasa.czasDrogi)+"\n");

        Diagram liczbaPieszych = new Diagram(Diagram.DiagramType.TIME, "Przebieg zmian liczby pojazdow na trasie w czasie");
        liczbaPieszych.add(trasa.liczbaPojazdow, Color.RED);
        liczbaPieszych.show();

        Diagram czasPrzemarszu = new Diagram(Diagram.DiagramType.DISTRIBUTION, "Dystrybuanta czasu przejazdy");
        czasPrzemarszu.add(trasa.czasDrogi, Color.RED);
        czasPrzemarszu.show();



    }
}
