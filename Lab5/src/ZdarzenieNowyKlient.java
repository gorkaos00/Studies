


import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimManager;


public class ZdarzenieNowyKlient extends BasicSimEvent<Budynek, Object> {

    public ZdarzenieNowyKlient(Budynek budynek, double delay) throws SimControlException
    {
        super(budynek, delay);
    }
    SimManager sm = SimManager.getInstance();
    double czasPojawienia = simTime() + getSimObj().getRng().exponential(getSimObj().getLambda());
    @Override
    protected void stateChange() throws SimControlException {
        if (getSimObj().getLicznikKlientow() < getSimObj().getMaxKlientow()) {
            getSimObj().incrementLicznikKlientow();
            getSimObj().getKasa().incrementLicznikInteresantow();
            Klient klient = new Klient(getSimObj().id_klienta++, simTime(), simTime()+getSimObj().getRng().exponential(getSimObj().getRo()));
            KlientNiecierpliwy cierp = new KlientNiecierpliwy(getSimObj(),simTime()+getSimObj().getRng().exponential(getSimObj().getRo()),getSimObj().id_klienta);
            if (getSimObj().getKasa().getLiczbaKlientow() < getSimObj().getKasa().getL()) {

                getSimObj().getKasa().incrementLiczbaInteresantow();
                getSimObj().getKasa().getKolejka().add(klient);
                getSimObj().getKasa().getDlugoscKolejki().setValue(getSimObj().getKasa().getDlugoscKolejki().getValue() + 1);
                System.out.println("[" + simTime() + "] :: nowy Klient, " + "Klient nr " + klient.getNr() + ", stan systemu: Liczba zajetych okienek: " + getSimObj().getKasa().getIleZajetychOkienek() + ", Liczba klientow przy kasach: " + getSimObj().getKasa().getLiczbaKlientow()+", Dlugosc kolejki: "+(getSimObj().getKasa().getKolejka().size()));
                for (int i = 0; i < getSimObj().getKasa().getOkienka().size(); i++) {
                    if (!getSimObj().getKasa().getOkienka().get(i).isZajete() && getSimObj().getKasa().getOkienka().get(i).isWorking()) {
                        ZdarzenieRozpoczecieObslugi r = new ZdarzenieRozpoczecieObslugi(getSimObj().getKasa(), 0, getSimObj().getKasa().getOkienka().get(i));
                    }
                }
            } else {
                System.out.println("[" + simTime() + "] :: nowy Klient, " + "Klient nr " + klient.getNr() + ", stan systemu: osiagnieto maksymalna pojemnosc kas: " + getSimObj().getKasa().getLiczbaKlientow() + ", strata klienta");
                getSimObj().getKasa().incrementLiczbaStrat();
            }
            czasPojawienia = getSimObj().getRng().exponential(getSimObj().getLambda());
            ZdarzenieNowyKlient n = new ZdarzenieNowyKlient(getSimObj(), czasPojawienia);
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
