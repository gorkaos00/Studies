

import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;


public class ZdarzenieZakonczenieObslugi extends BasicSimEvent<Kasa, Okienko> {
    public ZdarzenieZakonczenieObslugi(Kasa kasa, double delay, Okienko okienko) throws SimControlException
    {
        super(kasa, delay, okienko);
    }
    @Override
    protected void stateChange() throws SimControlException {
        if(getEventParams().getObsluga().size()>0) {
            getEventParams().setZajete(false);
            getSimObj().getZajetosc().setValue(getSimObj().getIleZajetychOkienek());
            double p = getSimObj().getRng().uniform(0, 1);
            if (p <= getSimObj().getP()) {
                System.out.println("[" + simTime() + "] :: zakonczenie obslugi - powrot do kolejki, Klient nr " + getEventParams().getObsluga().get(0).getNr() + ", Okienko nr " + getEventParams().getNr() + ", stan systemu: Liczba zajetych okienek: " + getSimObj().getIleZajetychOkienek() + ", Liczba klientow przy kasach: " + getSimObj().getLiczbaKlientow()+", Dlugosc kolejki: "+(getSimObj().getKolejka().size()+1));
                getEventParams().getObsluga().get(0).setCierpliwy(false);
                getEventParams().getObsluga().get(0).setMaxCzasOczekiwania(simTime() + getSimObj().getRng().exponential(getSimObj().getRo()));
                getSimObj().getKolejka().add(getEventParams().getObsluga().get(0));
                getSimObj().getDlugoscKolejki().setValue(getSimObj().getDlugoscKolejki().getValue() + 1);

            }
            else{
                getSimObj().decrementLiczbaInteresantow();
                System.out.println("[" + simTime() + "] :: zakonczenie obslugi - odejscie od kas, Klient nr " + getEventParams().getObsluga().get(0).getNr() + ", Okienko nr " + getEventParams().getNr() + ", stan systemu: Liczba zajetych okienek: " + getSimObj().getIleZajetychOkienek() + ", Liczba klientow przy kasach: " + getSimObj().getLiczbaKlientow()+", Dlugosc kolejki: "+(getSimObj().getKolejka().size()));
                getSimObj().getCzasPrzebywania().setValue(simTime() - getEventParams().getObsluga().get(0).getCzasWejscia());
            }
            getEventParams().getObsluga().remove(0);
            ZdarzenieRozpoczecieObslugi r = new ZdarzenieRozpoczecieObslugi(getSimObj(), 0, getEventParams());
        }

    }

    @Override
    protected void onTermination() throws SimControlException {
        ;
    }

    @Override
    public Okienko getEventParams() {
        return eventParams;
    }
}
