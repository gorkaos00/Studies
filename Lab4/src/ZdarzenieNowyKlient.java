import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimManager;



public class ZdarzenieNowyKlient extends BasicSimEvent<Kasa, Object> {

    public ZdarzenieNowyKlient(Kasa kasa, double delay) throws SimControlException
    {
        super(kasa, delay);
    }
    SimManager sm = SimManager.getInstance();
    double czasPojawienia = simTime() + getSimObj().getRng().exponential(getSimObj().getLambda());
    Klient i;
    @Override

    protected void stateChange() throws SimControlException {
        if (getSimObj().getLicznikInteresantow() < getSimObj().getMaxInteresantow()) {
            getSimObj().incrementLicznikInteresantow();
            Klient klient = new Klient(getSimObj().id_klienta++, getRunTime());
            i=klient;
            getSimObj().getKolejka().add(klient);
            getSimObj().getDlugoscKolejki().setValue(getSimObj().getDlugoscKolejki().getValue() + 1);
            if(getSimObj().getobslugiwany()==null)
            {
                ZdarzeniRozpoczecieObslugi r = new ZdarzeniRozpoczecieObslugi(getSimObj());
            }
        }
        else if (getSimObj().getLicznikInteresantow() == getSimObj().getMaxInteresantow() && getSimObj().getKolejka().size()==0 && getSimObj().getobslugiwany()==null)
        {
            sm.stopSimulation();
        }
        czasPojawienia = getSimObj().getRng().exponential(getSimObj().getLambda());
        ZdarzenieNowyKlient n = new ZdarzenieNowyKlient(getSimObj(), czasPojawienia);
    }

    @Override
    protected void onTermination() throws SimControlException {

    }

    @Override
    public Object getEventParams() {
        return null;
    }
}
