

import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;

public class ZdarzenieAwaria extends BasicSimEvent<Kasa, Object> {

    public ZdarzenieAwaria(Kasa kasa, double delay) throws SimControlException
    {
        super(kasa, delay);
    }
    @Override
    protected void stateChange() throws SimControlException {

        if(getSimObj().getLicznikKlientow()<getSimObj().getMaxKlientow()) {
            for (int i = 0; i < getSimObj().getOkienka().size(); i++) {
                getSimObj().getOkienka().get(i).setWorking(false);
                getSimObj().getOkienka().get(i).setZajete(false);
                getSimObj().getZajetosc().setValue(getSimObj().getIleZajetychOkienek());
                if (getSimObj().getOkienka().get(i).getObsluga().size() > 0) {
                    System.out.println("[" + simTime() + "] :: awaria systemu, Klient nr " + getSimObj().getOkienka().get(i).getObsluga().get(0).getNr() + ", wraca na poczatek kolejki, stan systemu: Liczba zajetych okienek: " + getSimObj().getIleZajetychOkienek() + ", Liczba klientow przy kasach: " + getSimObj().getLiczbaKlientow()+", Dlugosc kolejki: "+(getSimObj().getKolejka().size()+1));
                    getSimObj().getOkienka().get(i).getObsluga().get(0).setCierpliwy(false);
                    getSimObj().getOkienka().get(i).getObsluga().get(0).setMaxCzasOczekiwania(simTime() + getSimObj().getRng().exponential(getSimObj().getRo()));
                    getSimObj().getKolejka().add(0, getSimObj().getOkienka().get(i).getObsluga().remove(0));
                    getSimObj().getDlugoscKolejki().setValue(getSimObj().getDlugoscKolejki().getValue() + 1);
                } else {
                    System.out.println("[" + simTime() + "] :: awaria systemu, stan systemu: Liczba zajetych okienek: " + getSimObj().getIleZajetychOkienek() + ", Liczba klientow przy kasach: " + getSimObj().getLiczbaKlientow()+", Dlugosc kolejki: "+(getSimObj().getKolejka().size()));
                }
            }
            double t = getSimObj().getCzasNaprawy();
            ZdarzenieNaprawa z = new ZdarzenieNaprawa(getSimObj(), t);
        }
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
