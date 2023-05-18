public class Pojazd  {

    private int nr;
    private double predkosc;
    private double predkosc2;
    private double przebytaDroga;
    private double czasPojawienia;
    private double czasParkowania;
    private double czasZaparkowania;
    private double stan_pojazdu=0;
    public Pojazd(int nr, double predkosc,double predkosc2,double czasParkowania,double czas)
    {
        this.nr = nr;
        this.predkosc = predkosc;
        this.predkosc2 = predkosc2;
        this.przebytaDroga = 0;
        this.czasPojawienia = czas;
        this.czasParkowania=czasParkowania;
    }

    public int getNr()
    {
        return this.nr;
    }

    public double getPrzebytaDroga()
    {
        return this.przebytaDroga;
    }

    public double getPredkosc()
    {
        return this.predkosc;
    }

    public double getPredkosc2()
    {
        return this.predkosc2;
    }

    public double getCzasParkowania() {return this.czasParkowania;}

    public double getCzasPojawienia()
    {
        return this.czasPojawienia;
    }
    public void setPrzebytaDroga(double s)
    {
        this.przebytaDroga = s;
    }

    public double getCzasZaparkowania()
    {
        return this.czasZaparkowania;
    }
    public void setCzasZaprakowania(double s)
    {
        this.czasZaparkowania = s;
    }

    public double getStan_pojazdu()
    {
        return this.stan_pojazdu;
    }
    public void setStan_pojazdu(double s)
    {
        this.stan_pojazdu = s;
    }
}
