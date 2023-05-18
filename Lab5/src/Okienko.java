

import java.util.ArrayList;

public class Okienko {
    private boolean isZajete;
    private boolean isWorking;
    private int nr;
    private ArrayList<Klient> obsluga;
    public Okienko(int nr)
    {
        this.isZajete = false;
        this.isWorking = true;
        this.nr = nr;
        this.obsluga = new ArrayList<>();
    }
    public int getNr()
    {
        return this.nr;
    }
    public boolean isZajete()
    {
        return isZajete;
    }
    public void setZajete(boolean zajete)
    {
        this.isZajete = zajete;
    }

    public boolean isWorking() {
        return isWorking;
    }

    public void setWorking(boolean working) {
        this.isWorking = working;
    }

    public ArrayList<Klient> getObsluga() {
        return obsluga;
    }
}
