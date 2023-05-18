import dissimlab.broker.INotificationEvent;
import dissimlab.broker.IPublisher;
import dissimlab.monitors.MonitoredVar;
import dissimlab.simcore.BasicSimObj;

import java.util.ArrayList;
import java.util.List;

public class Trasa extends BasicSimObj{

    List<Pojazd> listaPojazdow;
    MonitoredVar liczbaPojazdow;
    MonitoredVar czasDrogi;
    double trasa;
    int liczbaOdcinkow;
    public Trasa(double dlugoscTrasy, int odcinki) {
        this.listaPojazdow = new ArrayList<Pojazd>();
        this.liczbaPojazdow = new MonitoredVar();
        this.czasDrogi = new MonitoredVar();
        this.trasa = dlugoscTrasy;
        this.liczbaOdcinkow = odcinki;
    }
    public int ktoryOdcinek(double trasaPojazdu)
    {
        double dlugoscOdcinka = this.trasa/this.liczbaOdcinkow;
        double poczatek = 0;
        double koniec = dlugoscOdcinka;
        for(int i = 0; i<liczbaOdcinkow; i++)
        {
            if(poczatek<trasaPojazdu&&trasaPojazdu<koniec)
                return i+1;
            else if(trasaPojazdu > trasa)
                return liczbaOdcinkow;
            else
            {
                poczatek+=dlugoscOdcinka;
                koniec+=dlugoscOdcinka;
            }
        }
        return 0;
    }


    @Override
    public void reflect(IPublisher iPublisher, INotificationEvent iNotificationEvent)
    {
        ;
    }
    @Override
    public boolean filter(IPublisher iPublisher, INotificationEvent iNotificationEvent)
    {
        return false;
    }

}
