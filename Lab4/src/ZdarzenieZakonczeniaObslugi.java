import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;




public class ZdarzenieZakonczeniaObslugi extends BasicSimEvent<Kasa, Object> {
    public ZdarzenieZakonczeniaObslugi(Kasa kasa, double delay, Klient klient) throws SimControlException
    {
        super(kasa, delay, klient);
    }
    @Override
    protected void stateChange() throws SimControlException {
        getSimObj().setobslugiwany(null);
        getSimObj().getZajetosc().setValue(0);
        getSimObj().getCzasPrzebywania().setValue(simTime()-getEventParams().getCzasWejscia());
        ZdarzeniRozpoczecieObslugi r = new ZdarzeniRozpoczecieObslugi(getSimObj());

    }

    @Override
    protected void onTermination() throws SimControlException {
        ;
    }

    @Override
    public Klient getEventParams() {
        return (Klient) eventParams;
    }
}
