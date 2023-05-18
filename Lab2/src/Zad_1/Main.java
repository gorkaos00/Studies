package Zad_1;

public class Main {

    public static void main(String[] args)
    {
        Funkcja1 f1 = new Funkcja1();
        Calka calka = new Calka();


        System.out.println("------------------------------------------------------------------------------------");
        System.out.println("Funkcja  (3/x):");
        System.out.println("\nLiczba powtorzen: 1000");
        double result = calka.calculate(1, Math.exp(1), f1, 1000);
        double bwzg = Math.abs(result - 3);
        System.out.println("Wynik: "+result);
        System.out.println("Blad bezwzgledny: "+bwzg);

        System.out.println("------------------------------------------------------------------------------------");
        System.out.println("\nLiczba powtorzen: 100000");
        result = calka.calculate(1, Math.exp(1), f1, 100000);
        bwzg = Math.abs(result - 3);
        System.out.println("Wynik: "+result);
        System.out.println("Blad bezwzgledny: "+bwzg);

        System.out.println("------------------------------------------------------------------------------------");
        System.out.println("\nLiczba powtorzen: 10000000");
        result = calka.calculate(1, Math.exp(1), f1, 10000000);
        bwzg = Math.abs(result - 3);
        System.out.println("Wynik: "+result);
        System.out.println("Blad bezwzgledny: "+bwzg);


        Funkcja2 f2 = new Funkcja2();
        System.out.println("------------------------------------------------------------------------------------");
        System.out.println("Funkcja (x^5-x^2+3x+8):");
        System.out.println("\nLiczba powtorzen: 1000");
        result = calka.calculate(0, 5, f2, 1000);
        bwzg = Math.abs(result - 2640);
        System.out.println("Wynik: "+result);
        System.out.println("Blad bezwzgledny: "+bwzg);

        System.out.println("\nLiczba powtorzen: 100000");
        result = calka.calculate(0, 5, f2, 100000);
        bwzg = Math.abs(result - 2640);
        bwzg = bwzg/3;
        System.out.println("Wynik: "+result);
        System.out.println("Blad bezwzgledny: "+bwzg);

        System.out.println("\nLiczba powtorzen: 10000000");
        result = calka.calculate(0, 5, f2, 10000000);
        bwzg = Math.abs(result - 2640);
        System.out.println("Wynik: "+result);
        System.out.println("Blad bezwzgledny: "+bwzg);
    }
}
