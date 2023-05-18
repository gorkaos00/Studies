import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;

public class Parkowanie extends BasicSimEvent<Trasa, Object> {

    public Parkowanie(Trasa entity, Object o, double period) throws SimControlException
    {
        super(entity, o, period);
    }
    protected void stateChange() throws SimControlException{

        for(int i = 0; i<super.getSimObj().liczbaPojazdow.getValue(); i++)

        {
            if (super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() == super.getSimObj().trasa && super.getSimObj().listaPojazdow.get(i).getStan_pojazdu()==1){
                System.out.println("[" + simTime() + "]" + ", Pojazd parkuje: Pojazd nr " + super.getSimObj().listaPojazdow.get(i).getNr() + ", przebyta droga: " + super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() + ", czas drogi: " + ( simTime() - super.getSimObj().listaPojazdow.get(i).getCzasPojawienia()));
                super.getSimObj().listaPojazdow.get(i).setCzasZaprakowania(simTime()+super.getSimObj().listaPojazdow.get(i).getCzasParkowania());
                super.getSimObj().listaPojazdow.get(i).setPrzebytaDroga(super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga()+1);
            }
            if ( super.getSimObj().listaPojazdow.get(i).getCzasZaparkowania()<= simTime() && super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() > super.getSimObj().trasa && super.getSimObj().listaPojazdow.get(i).getStan_pojazdu()==1){
                System.out.println("[" + simTime() + "]" + ", Pojazd zakonczyl parkowanie Pojazd nr " + super.getSimObj().listaPojazdow.get(i).getNr() + ", przebyta droga: " + super.getSimObj().listaPojazdow.get(i).getPrzebytaDroga() + ", czas drogi: " + ( simTime() - super.getSimObj().listaPojazdow.get(i).getCzasPojawienia()));
                super.getSimObj().listaPojazdow.get(i).setStan_pojazdu(2);

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
