

import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;


public class ZdarzenieRozpoczecieObslugi extends BasicSimEvent<Kasa, Okienko> {

    public ZdarzenieRozpoczecieObslugi(Kasa kasa, double delay, Okienko okienko) throws SimControlException
    {
        super(kasa, delay, okienko);
    }
    //SimManager sm = SimManager.getInstance();
    @Override
    protected void stateChange() throws SimControlException {

        if(getSimObj().getKolejka().size()!=0) {
            Klient i = getSimObj().getKolejka().remove(0);
            i.setCierpliwy(true);
            getSimObj().getDlugoscKolejki().setValue(getSimObj().getDlugoscKolejki().getValue() - 1);
            getEventParams().getObsluga().add(i);
            getEventParams().setZajete(true);
            getSimObj().getZajetosc().setValue(getSimObj().getIleZajetychOkienek());
            double t = getSimObj().getRng().exponential(getSimObj().getMi());
            System.out.println("[" + simTime() + "] :: rozpoczecie obslugi, " + "Klient nr " + i.getNr()+", Okienko nr "+getEventParams().getNr()+", stan systemu: Liczba zajetych okienek: "+ getSimObj().getIleZajetychOkienek()+", Liczba klientow przy kasach: "+getSimObj().getLiczbaKlientow()+", Dlugosc kolejki: "+(getSimObj().getKolejka().size()));
            ZdarzenieZakonczenieObslugi z = new ZdarzenieZakonczenieObslugi(getSimObj(), t, getEventParams());
        }
    }

    @Override
    protected void onTermination() throws SimControlException {

    }

    @Override
    public Okienko getEventParams() {
        return eventParams;
    }
}
