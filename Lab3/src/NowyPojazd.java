import dissimlab.random.RNGenerator;
import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimManager;

public class NowyPojazd extends BasicSimEvent<Trasa, Object> {

    public NowyPojazd(Trasa trasa, Object o, double period) throws SimControlException
    {
        super(trasa, o, period);
    }
    SimManager sm = SimManager.getInstance();
    RNGenerator r = new RNGenerator();
    double lambda=0.1;
    double c = 10;
    double d = 40;
    double e = 10;
    double f = 40;
    double t = r.exponential(lambda);
    double czasPojawienia = simTime() + t;
    int nr = 1;

    @Override
    protected void stateChange() throws SimControlException
    {
        if(simTime() >= czasPojawienia)
        {
            double v1 = r.uniform(c, d);
            double v2 = r.uniform(c, d);
            double parkowanie =r.uniform(e,f);
            Pojazd p = new Pojazd(nr++, v1,v2,parkowanie, simTime());
            super.getSimObj().listaPojazdow.add(p);
            super.getSimObj().liczbaPojazdow.setValue(super.getSimObj().liczbaPojazdow.getValue()+1);
            System.out.println("["+simTime()+"]"+", nowy Pojazd na trasie: Pojazd nr "+ p.getNr());
            t = r.exponential(lambda);
            czasPojawienia = simTime() + t;
        }
    }
    @Override
    protected void onTermination() throws SimControlException
    {

    }
    @Override
    public Pojazd getEventParams()
    {
        return null;
    }
}
