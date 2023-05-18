package Zad_1;
import dissimlab.random.RNGenerator;

public class Calka {
    public double calculate(double a, double b, IFunc f, int rep)
    {
        double result;
        int k = 0;
        double xi, yi, funcValue;
        RNGenerator r = new RNGenerator();
        for(int i=0; i<rep; i++)
        {
            xi = r.uniform(a, b);
            yi = r.uniform(0, f.max(a, b));
            funcValue = f.func(xi);
            if(yi<= funcValue)
            {
                k++;
            }
        }
        result = ((double)k/rep) * (b-a) * f.max(a, b);
        return result;
    }
}
