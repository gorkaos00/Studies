import dissimlab.broker.INotificationEvent;
import dissimlab.broker.IPublisher;
import dissimlab.monitors.MonitoredVar;
import dissimlab.random.RNGenerator;
import dissimlab.simcore.BasicSimObj;

import java.util.ArrayList;

public class Kasa extends BasicSimObj {
    private RNGenerator rng;
    private double lambda;
    private double mi;
    private Klient obslugiwany;
    private ArrayList<Klient> kolejka;
    private MonitoredVar czasPrzebywania;
    private MonitoredVar dlugoscKolejki;
    private MonitoredVar zajetoscKasy;
    private int licznikKlientow;
    private int maxKlientow;

    public int id_klienta = 1;

    public Kasa(RNGenerator rng,double lambda, double mi, int maxKlientow)
    {
        this.rng = rng;
        this.mi = mi;
        this.kolejka = new ArrayList<>();
        this.czasPrzebywania = new MonitoredVar();
        this.dlugoscKolejki = new MonitoredVar();
        this.zajetoscKasy = new MonitoredVar();
        this.maxKlientow=maxKlientow;
        this.lambda=lambda;

    }


    public double getMi() {
        return mi;
    }

    public MonitoredVar getCzasPrzebywania() {
        return czasPrzebywania;
    }

    public MonitoredVar getDlugoscKolejki() {
        return dlugoscKolejki;
    }

    public MonitoredVar getZajetosc() {
        return zajetoscKasy;
    }

    public ArrayList<Klient> getKolejka()
    {
        return this.kolejka;
    }

    public RNGenerator getRng() {
        return rng;
    }


    public void setobslugiwany(Klient klient){ this.obslugiwany=klient;
    }

    public Klient getobslugiwany(){ return obslugiwany;}



    public int getLicznikInteresantow() {
        return licznikKlientow;
    }

    public int getMaxInteresantow() {
        return maxKlientow;
    }

    public void incrementLicznikInteresantow()
    {
        licznikKlientow++;
    }

    public double getLambda()
    {
        return this.lambda;
    }


    @Override
    public void reflect(IPublisher iPublisher, INotificationEvent iNotificationEvent) {

    }

    @Override
    public boolean filter(IPublisher iPublisher, INotificationEvent iNotificationEvent) {
        return false;
    }

}
