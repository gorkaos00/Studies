import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;

public class ZdarzeniRozpoczecieObslugi extends BasicSimEvent<Kasa, Object> {


    public ZdarzeniRozpoczecieObslugi(Kasa kasa) throws SimControlException
    {
        super(kasa);
    }

    @Override
    protected void stateChange() throws SimControlException {
        if(getSimObj().getKolejka().size()!=0) {
            Klient i = getSimObj().getKolejka().remove(0);
            getSimObj().getDlugoscKolejki().setValue(getSimObj().getDlugoscKolejki().getValue() - 1);
            getSimObj().setobslugiwany(i);
            getSimObj().getZajetosc().setValue(1);
            double t = getSimObj().getRng().exponential(getSimObj().getMi());
            ZdarzenieZakonczeniaObslugi z = new ZdarzenieZakonczeniaObslugi(getSimObj(), t, i);
        }
    }

    @Override
    protected void onTermination() throws SimControlException {

    }

    @Override
    public Object getEventParams() {
        return null;
    }
}
