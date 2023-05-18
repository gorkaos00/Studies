
import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;

public class ZdarzenieNaprawa extends BasicSimEvent<Kasa, Object> {
    public ZdarzenieNaprawa(Kasa kasa, double delay) throws SimControlException
    {
        super(kasa, delay);
    }
    @Override
    protected void stateChange() throws SimControlException {

        for(int i = 0; i<getSimObj().getOkienka().size(); i++)
        {
            getSimObj().getOkienka().get(i).setWorking(true);
        }
        System.out.println("["+simTime()+"] :: naprawa systemu, stan systemu: Liczba zajetych okienek: "+getSimObj().getIleZajetychOkienek()+", Liczba klientow przy kasach: " + getSimObj().getLiczbaKlientow()+", Dlugosc kolejki: "+(getSimObj().getKolejka().size()));
        if (getSimObj().getKolejka().size()> 0) {
            ZdarzenieRozpoczecieObslugi z = new ZdarzenieRozpoczecieObslugi(getSimObj(), 0, getSimObj().getOkienka().get(0));
        }
        ZdarzenieAwaria a = new ZdarzenieAwaria(getSimObj(), getSimObj().getRng().exponential(getSimObj().getAlfa()));

    }

    @Override
    protected void onTermination() throws SimControlException {
        ;
    }

    @Override
    public Object getEventParams() {
        return null;
    }
}
