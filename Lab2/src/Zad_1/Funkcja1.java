package Zad_1;

public class Funkcja1 implements IFunc {
    public double func(double x)
    {
        return 3/x;
    }
    public double max(double a, double b)
    {
        if (b<=a)
        {
            IllegalArgumentException e = new IllegalArgumentException();
            throw e;
        }
        if(func(a) >= func(b))
        {
            return func(a);
        }
        else
        {
            return func(b);
        }
    }

}
