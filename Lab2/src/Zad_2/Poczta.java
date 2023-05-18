package Zad_2;

import dissimlab.random.RNGenerator;

public class Poczta {
    private RNGenerator r;
    private int N;
    private Okienko[] okienka;
    private double simTime;

    public Poczta(int N) {
        this.simTime = 0;
        this.r = new RNGenerator();
        this.N = N;
        this.okienka = new Okienko[N];
        for(int i = 0; i<N; i++)
        {
            okienka[i] = new Okienko(i+1, r.exponential(1));
            System.out.println("Okienko nr "+okienka[i].getNumber()+" o czasie obslugi: "+okienka[i].getTime()+" utworzone");
        }
    }

    public void checkwindows(double simTime)
    {
        for(int i=0; i<N; i++)
        {
            if(simTime>=okienka[i].getZajete())
            {
                okienka[i].setZajete(0);
                System.out.println("Okienka nr "+okienka[i].getNumber()+" wolne");
            }
            else
            {
                System.out.println("Okienka nr "+okienka[i].getNumber()+" zajete");
            }
        }
    }

    public void Symuluj(double czasZakon, int liczZglosz)
    {

        System.out.println("Czas trwania symulacji: "+czasZakon);
        System.out.println("Maksymalna liczba interesantow: "+liczZglosz);
        int licz_zgl = 0;
        int licz_n_zgl=0;
        double apptime;
        while(licz_zgl+licz_n_zgl<liczZglosz&&simTime<=czasZakon)
        {
            System.out.println("---------------------------------------------------------------------------");
            apptime = r.exponential(1);
            simTime+=apptime;
            checkwindows(simTime);
            System.out.println("Nowy interesant, czas zgloszenia: "+simTime);

            boolean przyjeto = false;
            for(int i=0; i<N; i++)
            {
                if(okienka[i].getZajete()==0)
                {
                    przyjeto = true;
                    okienka[i].setZajete(simTime+okienka[i].getTime());
                    System.out.println("Okienko nr "+okienka[i].getNumber()+" przyjelo interesanta i bedzie zajete do chwili: "+okienka[i].getZajete());
                    licz_zgl++;
                    break;
                }
            }
            if(!przyjeto)
            {
                System.out.println("Wszystkie okienka sa zajete. Interesant nieobsluzony");
                licz_n_zgl++;
            }
            System.out.println("---------------------------------------------------------------------------");
        }
        double p_obslugi=(double)licz_zgl/(licz_zgl+licz_n_zgl);
        System.out.println("Koniec trwania symulacji, liczba obsluzonych interesantow: "+licz_zgl+" liczba nie obsluzonych interesantow:"+licz_n_zgl+" Na maksymalnie: "+liczZglosz +" w czasie trwania symulacji rownym: "+simTime);
        System.out.println("Prawdopodobienstwo obslugi interesanta wynosi: "+p_obslugi);
        System.out.println("Prawdopodobienstwo nie obsluzenia interesanta wynosi: "+ (1-p_obslugi));
    }

}
