import dissimlab.broker.INotificationEvent;
import dissimlab.broker.IPublisher;
import dissimlab.simcore.BasicSimObj;

public class Klient extends BasicSimObj {
    private int nr;
    private double czasWejscia;
    public Klient(int nr, double czas)
    {
        this.nr = nr;
        this.czasWejscia = czas;
    }

    public double getCzasWejscia()
    {
        return czasWejscia;
    }


    @Override
    public void reflect(IPublisher iPublisher, INotificationEvent iNotificationEvent) {

    }

    @Override
    public boolean filter(IPublisher iPublisher, INotificationEvent iNotificationEvent) {
        return false;
    }

}
