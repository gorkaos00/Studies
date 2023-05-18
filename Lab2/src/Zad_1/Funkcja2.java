package Zad_1;

public class Funkcja2 implements IFunc {
    //miejsce zerowe pochodnej
    public double func(double x)
    {
        return Math.pow(x, 5) - Math.pow(x, 2)+3*x + 8;
    }
    public double max(double a, double b)
    {
        if (b<=a)
        {
            IllegalArgumentException e = new IllegalArgumentException();
            throw e;
        }
        else
        {
            if (func(a) >= func(b)) {
                return func(a);
            } else {
                return func(b);
            }
        }
    }
}
