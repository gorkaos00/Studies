
public class Main {


    public static void main(String[] args) {
        Generatorek Generatorek = new Generatorek(97,11,100,0,0);
        System.out.println("Ciag dla NextInt");
        for(int i=0;i<100;i++){
            System.out.println(Generatorek.NextInt());
        }
        System.out.println("\n");
        System.out.println("\n");
        System.out.println("Ciag dla NextDouble");
        for(int i=0;i<100;i++){
            System.out.println(Generatorek.NextDouble());
        }
        System.out.println("\n");
        System.out.println("\n");
        System.out.println("Ciag dla NextInt(high,low)");
        for(int i=0;i<100;i++){
            System.out.println(Generatorek.NextDouble(3,12));
        }
        System.out.println("\n");
        System.out.println("\n");
        System.out.println("Ciag dla exponential");
        for(int i=0;i<100;i++){
            System.out.println(Generatorek.exponential(0.7));
        }
        System.out.println("\n");
        System.out.println("\n");

        Generatorek.dyskretAnalyze();
    }
}
