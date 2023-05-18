package Zad_2;

public class Okienko {
    private int nr;
    private double to;
    private double zajeta;
    public Okienko(int nr, double to)
    {
        this.zajeta = 0;
        this.nr = nr;
        this.to = to;
    }
    public int getNumber()
    {
        return this.nr;
    }
    public double getTime()
    {
        return this.to;
    }

    public void setZajete(double time)
    {
        this.zajeta = time;
    }

    public double getZajete()
    {
        return this.zajeta;
    }

}
