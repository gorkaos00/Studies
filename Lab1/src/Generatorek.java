
import static java.lang.Math.log;

public class Generatorek {
    int a;
    int b;
    int M;
    int x0;
    int xn;
    public Generatorek(int a, int b, int M, int x0,int xn) {
        this.a = a;
        this.b = b;
        this.M = M;
        this.x0 = x0;
        this.xn = xn;
    }

    public int NextInt() {
        xn = (a * xn + b) % M;
        return xn;
    }

    public double NextDouble() {
        double temp = NextInt();
        double zakres_double = M;
        return temp / zakres_double;
    }

    public double NextDouble(double low, double high) {
        double un = NextDouble();
        return low + (high - low) * un;
    }

    public double exponential(double lambda) {
        double temp = -(log(1 - NextDouble()) / lambda);
        return temp;
    }

    public double dyskret(double[] xx, double[] p) {
        double u = NextDouble();
        double sum = 0;
        int licznik = 0;
        while (sum <= u) {
            sum += p[licznik];
            licznik++;
        }
        return xx[licznik - 1];
    }

    public void dyskretAnalyze() {
        System.out.println("Analiza metody dyskret:");
        System.out.println("Wypis wartosci dla n = 1000:");
        double avg = 0;
        double[] xx = {-2, -1, 0, 1, 2, 3, 4};
        double[] p = {0.05, 0.1, 0.3, 0.02, 0.18, 0.15, 0.2};
        double suma_p = 0;
        int warunek=0;
        for (int i = 0; i < p.length; i++) {
            suma_p += p[i];
            if(p[i]<0){
                warunek=1;
            }
        }
        if (suma_p == 1.0 && p.length==xx.length && warunek==0) {
            for (int i = 0; i < 1000; i++) {
                avg += dyskret(xx, p);
            }
            avg /= 1000;
            System.out.println("Wartosc srednia: " + avg);
            double avg_teoretic = 0;
            for (int i = 0; i < p.length; i++) {
                avg_teoretic += p[i] * xx[i];
            }
            System.out.println("Wartosc srednia teoretyczna: " + avg_teoretic);
        } else {
            System.out.println("Blad zsumowane prawdopodobienstwo nie jest rowne 1 lub podano rozne ilosci parametrow");
        }
    }

}
