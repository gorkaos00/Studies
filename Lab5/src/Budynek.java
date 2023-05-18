

import dissimlab.broker.INotificationEvent;
import dissimlab.broker.IPublisher;
import dissimlab.random.RNGenerator;
import dissimlab.simcore.BasicSimObj;

public class Budynek extends BasicSimObj {
    private RNGenerator rng;
    private Kasa kasa;
    private double lambda;
    private int licznikKlientow;
    private int maxKlientow;
    private double ro;

    public int id_klienta = 1;
    public Budynek(RNGenerator rng, Kasa kasa, double lambda, double ro, int maxKlientow)
    {
        this.rng = rng;
        this.kasa = kasa;
        this.lambda = lambda;
        this.ro = ro;
        this.maxKlientow = maxKlientow;
        this.licznikKlientow = 0;
    }
    @Override
    public void reflect(IPublisher iPublisher, INotificationEvent iNotificationEvent) {

    }

    @Override
    public boolean filter(IPublisher iPublisher, INotificationEvent iNotificationEvent) {
        return false;
    }

    public Kasa getKasa() {
        return kasa;
    }

    public int getLicznikKlientow() {
        return licznikKlientow;
    }

    public int getMaxKlientow() {
        return maxKlientow;
    }

    public void incrementLicznikKlientow()
    {
        licznikKlientow++;
    }

    public RNGenerator getRng() {
        return rng;
    }

    public double getLambda()
    {
        return this.lambda;
    }
    public double getRo() {return ro;}

}

