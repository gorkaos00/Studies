import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;

public class KlientNiecierpliwy extends BasicSimEvent<Budynek,Object> {
    int nr;

    public KlientNiecierpliwy(Budynek budynek, double delay , int nr) throws SimControlException{
        super(budynek, delay);
        this.nr=nr;
    }





    @Override
    protected void stateChange() throws SimControlException {

            getSimObj().getKasa().decrementLiczbaInteresantow();
            System.out.println("[" + simTime() + "] :: koniec cierpliwosci klienta - strata, Klient nr " + getSimObj().getKasa().getKolejka().get(nr).getNr() + ", stan systemu: Liczba zajetych okienek: " + getSimObj().getKasa().getIleZajetychOkienek() + ", Liczba klientow przy kasach: " + getSimObj().getKasa().getLiczbaKlientow() + ", Dlugosc kolejki: " + (getSimObj().getKasa().getKolejka().size() - 1));
            getSimObj().getKasa().getCzasPrzebywania().setValue(simTime() - getSimObj().getKasa().getKolejka().get(nr).getCzasWejscia());
            getSimObj().getKasa().getKolejka().remove(nr);
            getSimObj().getKasa().getDlugoscKolejki().setValue(getSimObj().getKasa().getDlugoscKolejki().getValue() - 1);
            getSimObj().getKasa().incrementLiczbaStrat();

        }


    @Override
    protected void onTermination() throws SimControlException {

    }


    @Override
    public Object getEventParams() {
        return null;
    }
}
