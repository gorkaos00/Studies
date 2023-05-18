import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;

public class RuchPojazdow extends BasicSimEvent<Trasa, Object> {
    double dt;
    double czas = simTime();

    public RuchPojazdow(Trasa entity, Object o, double period) throws SimControlException
    {
        super(entity, o, period);
    }
    @Override
    protected void stateChange() throws SimControlException {
        dt = simTime() - czas;
        czas+=dt;
        for(int i = 0; i<super.getSimObj().liczbaPojazdow.getValue(); i++)
        {
            if(super.getSimObj().listaPojazdow.get(i).getCzasPojawienia() != simTime() && super.getSimObj().listaPojazdow.get(i).getStan_pojazdu()==0) {
                int odc = super.getSimObj().ktoryOdcinek(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga());
                super.getSimObj().listaPojazdow.get(i).setPrzebytaDroga(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() + super.getSimObj().listaPojazdow.get(i).getPredkosc() * dt);
                if (super.getSimObj().ktoryOdcinek(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga()) != odc && super.getSimObj().listaPojazdow.get(i).getStan_pojazdu()==0) {
                    System.out.println("[" + simTime() + "]" + ", zmiana stanu symulacji: Pojazd nr " + super.getSimObj().listaPojazdow.get(i).getNr() + ", nr aktualnego odcinka: " + super.getSimObj().ktoryOdcinek(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga()) + ", przebyta droga: " + super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga()+ ", czas drogi: " +( simTime() - super.getSimObj().listaPojazdow.get(i).getCzasPojawienia()));
                }
                if (super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() >= super.getSimObj().trasa && super.getSimObj().listaPojazdow.get(i).getStan_pojazdu()==0) {
                    super.getSimObj().listaPojazdow.get(i).setPrzebytaDroga(super.getSimObj().trasa);
                    double czasDrogi = simTime() - super.getSimObj().listaPojazdow.get(i).getCzasPojawienia();
                    System.out.println("[" + simTime() + "]" + ", Pojazd dotarl na koniec trasy: Pojazd nr " + super.getSimObj().listaPojazdow.get(i).getNr() + ", przebyta droga: " + super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() + ", czas drogi: " + czasDrogi);
                    super.getSimObj().czasDrogi.setValue(czasDrogi);
                    super.getSimObj().listaPojazdow.get(i).setStan_pojazdu(1);
                }
            }
            if(super.getSimObj().listaPojazdow.get(i).getCzasPojawienia() != simTime() && super.getSimObj().listaPojazdow.get(i).getStan_pojazdu()==2) {
                int odc = super.getSimObj().ktoryOdcinek(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga());
                super.getSimObj().listaPojazdow.get(i).setPrzebytaDroga(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() - super.getSimObj().listaPojazdow.get(i).getPredkosc() * dt);
                if (super.getSimObj().ktoryOdcinek(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga()) != odc && super.getSimObj().listaPojazdow.get(i).getStan_pojazdu()==2) {
                    if(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga()<0) {
                        super.getSimObj().listaPojazdow.get(i).setPrzebytaDroga(0);
                    }
                    System.out.println("[" + simTime() + "]" + ", zmiana stanu symulacji: Pojazd nr " + super.getSimObj().listaPojazdow.get(i).getNr() + ", nr aktualnego odcinka: " + super.getSimObj().ktoryOdcinek(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga()) + ", przebyta droga: " + super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga()+ ", czas drogi: " +( simTime() - super.getSimObj().listaPojazdow.get(i).getCzasPojawienia()));
                }
                if (super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() == 0 && super.getSimObj().listaPojazdow.get(i).getStan_pojazdu()==2) {
                    double czasDrogi = simTime() - super.getSimObj().listaPojazdow.get(i).getCzasPojawienia();
                    System.out.println("[" + simTime() + "]" + ", Pojazd dotarl na poczatek trasy: Pojazd nr " + super.getSimObj().listaPojazdow.get(i).getNr() + ", przebyta droga: " + super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() + ", czas drogi: " + czasDrogi);
                    super.getSimObj().czasDrogi.setValue(czasDrogi);
                    super.getSimObj().listaPojazdow.remove(i);
                    super.getSimObj().liczbaPojazdow.setValue(super.getSimObj().liczbaPojazdow.getValue() - 1);

                }




            }
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
