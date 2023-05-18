

public class Klient {
    private int nr;
    private double czasWejscia;
    private double maxCzasOczekiwania;
    private boolean isCierpliwy;
    public Klient(int nr, double czas, double maxCzasOczekiwania)
    {
        this.nr = nr;
        this.czasWejscia = czas;
        this.maxCzasOczekiwania = maxCzasOczekiwania;
        this.isCierpliwy = false;
    }

    public double getCzasWejscia()
    {
        return czasWejscia;
    }

    public double getMaxCzasOczekiwania() { return maxCzasOczekiwania;}

    public void setMaxCzasOczekiwania(double czas)
    {
        this.maxCzasOczekiwania = czas;
    }

    public boolean isCierpliwy() {
        return isCierpliwy;
    }
    public void setCierpliwy(boolean cierpliwy)
    {
        this.isCierpliwy = cierpliwy;
    }

    public int getNr()
    {
        return nr;
    }
}
