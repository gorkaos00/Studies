

import dissimlab.broker.INotificationEvent;
import dissimlab.broker.IPublisher;
import dissimlab.monitors.MonitoredVar;
import dissimlab.random.RNGenerator;
import dissimlab.simcore.BasicSimObj;

import java.util.ArrayList;

public class Kasa extends BasicSimObj {
    private RNGenerator rng;
    private double mi;
    private ArrayList<Klient> kolejka;
    private final ArrayList<Okienko> okienka;
    private boolean okienkoZajete;
    private MonitoredVar czasPrzebywania;
    private MonitoredVar dlugoscKolejki;
    private MonitoredVar zajetosc;
    private int M;
    private int L;
    private int liczbaStrat = 0;
    private double p;
    private double ro;
    private double alfa;
    private double beta;
    private double czasZdatnosci;
    private double czasNaprawy;
    private int maxKlientow;
    private int licznikKlientow; // liczba wygenerowanych
    private int liczbaKlientow; // liczba aktualnie przebywajacych

    public Kasa(RNGenerator rng, double mi, double ro, int M, int L, double p, double alfa, double beta, int max)
    {
        this.rng = rng;
        this.mi = mi;
        this.ro = ro;
        this.kolejka = new ArrayList<>();
        this.okienkoZajete = false;
        this.czasPrzebywania = new MonitoredVar();
        this.dlugoscKolejki = new MonitoredVar();
        this.zajetosc = new MonitoredVar();
        this.okienka = new ArrayList<>();
        this.M = M;
        this.L = L;
        for (int i = 0; i<M; i++)
        {
            Okienko o = new Okienko(i+1);
            okienka.add(o);
        }
        this.p = p;
        this.alfa = alfa;
        this.beta = beta;
        this.czasZdatnosci = rng.exponential(this.alfa);
        this.czasNaprawy = rng.exponential(this.beta);
        this.licznikKlientow = 0;
        this.maxKlientow = max;
        this.liczbaKlientow = 0;
    }

    public boolean isOkienkoZajete() {
        return okienkoZajete;
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
        return zajetosc;
    }

    public ArrayList<Klient> getKolejka()
    {
        return this.kolejka;
    }

    public RNGenerator getRng() {
        return rng;
    }

    public ArrayList<Okienko> getOkienka() {return this.okienka;}
    public int getIleZajetychOkienek()
    {
        int ile = 0;
        for (Okienko okienko : okienka) {
            if (okienko.isZajete()) {
                ile++;
            }
        }
        return ile;
    }
    public int getL()
    {
        return L;
    }
    public void incrementLiczbaStrat()
    {
        liczbaStrat++;
    }
    public void incrementLicznikInteresantow()
    {
        licznikKlientow++;
    }
    public void incrementLiczbaInteresantow() {
        liczbaKlientow++;}
    public void decrementLiczbaInteresantow() {
        liczbaKlientow--;}
    public int getLiczbaStrat()
    {
        return liczbaStrat;
    }
    public double getP()
    {
        return p;
    }
    public double getRo() { return ro;}
    public double getAlfa() {return alfa;}
    public double getCzasNaprawy() {return this.czasNaprawy;}
    public double getCzasZdatnosci() {return this.czasZdatnosci;}

    public void setCzasNaprawy(double czasNaprawy) {
        this.czasNaprawy = czasNaprawy;
    }

    public void setCzasZdatnosci(double czasZdatnosci) {
        this.czasZdatnosci = czasZdatnosci;
    }
    public int getMaxKlientow()
    {
        return this.maxKlientow;
    }
    public int getLicznikKlientow()
    {
        return this.licznikKlientow;
    }
    public int getLiczbaKlientow() {return this.liczbaKlientow;}


    @Override
    public void reflect(IPublisher iPublisher, INotificationEvent iNotificationEvent) {

    }

    @Override
    public boolean filter(IPublisher iPublisher, INotificationEvent iNotificationEvent) {
        return false;
    }
}
