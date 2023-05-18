#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct Parzyse{
	int x;
	struct parzyste *nast;
	struct parzyste *poprz;
	struct parzyste *most;
}parzyste;

typedef struct N_Parzyste{
	int x;
	struct n_parzyste *nast;
	struct n_parzyste *poprz;
	struct n_parzyste *most;
}n_parzyste;

void liczba_parzysta(parzyste **first1,n_parzyste **first2,int x,int d,int c){
	int i;
	parzyste *nowy;
	nowy=malloc(sizeof(parzyste));
	nowy->x=x;
	nowy->most=NULL;
	if(d==0){
		*first1 = nowy;
		nowy->poprz=*first1;
		nowy->nast=*first1;
		
	}
	
	else if(d==1){
		parzyste *i;
		i=*first1;
		i->nast=nowy;
		nowy->nast=*first1;
		nowy->poprz=*first1;
	}
	
	else{
		
		parzyste *i,*k;
		i=*first1;
		k=i;
		i=i->nast;
		
		while(i->nast!=*first1){
			i=i->nast;
		}
		
		i->nast=nowy;
		nowy->nast=*first1;
		nowy->poprz=i;
		k->poprz=nowy;
	}
	
} 







void liczba_n_parzysta(parzyste **first1,n_parzyste **first2,int x,int c,int d){
	int i;
	n_parzyste *nowy;
	nowy=malloc(sizeof(n_parzyste));
	nowy->x=x;
	nowy->most=NULL;
	if(c==0){
		*first2 = nowy;
		nowy->nast=*first2;
		nowy->poprz=*first2;
	}
	
	else if(c==1){
		n_parzyste *i;
		i=*first2;
		i->nast=nowy;
		nowy->nast=*first2;
		nowy->poprz=*first2;
	}
	
	else{
		n_parzyste *i,*k;
		i=*first2;
		k=i;
		i=i->nast;
		
		
		while(i->nast!=*first2){
			i=i->nast;
		}
		
		i->nast=nowy;
		nowy->nast=*first2;
		nowy->poprz=i;
		k->poprz=nowy;
	}
	
}

void mostowanie(parzyste **first1,n_parzyste **first2){
	parzyste *i;
	n_parzyste *k;
		i=*first1;
		k=*first2;
		i->most=*first2;
		k->most=*first1;
		
	}


void wyswietl(parzyste *first1){
	printf("\n");
	parzyste *i,*j;
	n_parzyste *k,*m,*l;
	
	int b;
	i=first1;
	printf("    Poprzednik \t     Aktualny \t    Nastepnik \t\tMost\n");
	
	do{
		j=i->poprz;
		printf("\t%d\t",j->x);
		if(i->most==NULL){
			b=0;
		}
		else{
			k=i->most;
			b=k->x;
		}
		printf("\t%d\t",i->x);
		i=i->nast;
		printf("\t%d\t",i->x);
		printf("\t%d",b);
		printf("\n");
	}
	while(i!=first1);
	
	k=i->most;
	m=k;
	
	
	printf("\n");
	do{
		l=k->poprz;
		printf("\t%d\t",l->x);
		if(k->most==NULL){
			b=0;
		}
		else{
			i=k->most;
			b=i->x;
		}
		printf("\t%d\t",k->x);
		k=k->nast;
		printf("\t%d\t",k->x);
		
		printf("\t%d",b);
		printf("\n");
		
	}
	while(k!=m);
}

void wyswietl_zap(n_parzyste *first2){
	
	printf("\n");
	n_parzyste *i,*k;
	int poprz,nast,b,a;
	i=first2;
	printf("    Poprzednik \t     Aktualny \t    Nastepnik \t\tMost\n");
	do{
		k=i->poprz;
		printf("\t%d\t",k->x);
		printf("\t%d\t",i->x);
		i=i->nast;
		printf("\t%d\t",i->x);
		printf("\t0");
		printf("\n");

	}
	while(i!=first2);
}

void sortowanie_p(parzyste **first1){
	parzyste *i, *k;
	n_parzyste *l, *m, *n;
	i=*first1;
	k=i;
	int a;
	i=i->nast;
	l=k->most;
	m=l;
	n=l;
	l=l->nast;

	while(i!=*first1){
		if( (i->x) < (k->x) ){
			a=i->x;
			i->x=k->x;
			k->x=a;
			k=*first1;
			i=k->nast;
		}
		else{
			i=i->nast;
			k=k->nast;
		}
	}

	while(l!=n){
		if( (l->x) < (m->x) ){
			a=l->x;
			l->x=m->x;
			m->x=a;
			m=n;
			l=m->nast;
		}
		else{
			l=l->nast;
			m=m->nast;
		}
	}

}

void sortowanie_n(n_parzyste **first2){
	n_parzyste *i, *k;
	i=*first2;
	k=i;
	int a;
	i=i->nast;

	while(i!=*first2){
		if( (i->x) < (k->x) ){
			a=i->x;
			i->x=k->x;
			k->x=a;
			k=*first2;
			i=k->nast;
		}
		else{
			i=i->nast;
			k=k->nast;
		}
	}	
}

int usuwanie_n(n_parzyste **first2, int x){
	n_parzyste *i;
	i=*first2;
	if(i->nast==i){
		parzyste *k;
		k=i->most;
		k->most=NULL;
		free(i);
		free(*first2);
		*first2=NULL;
				
	}
	do{
		if(i->x==x){
			n_parzyste *k,*n;
			k=i->poprz;
			n=i->nast;
			k->nast=n;
			n->poprz=k;
			if(i->most!=NULL){
				n->most=i->most;
				parzyste *l;
				l=n->most;
				l->most=n;
			}
			free(i);
			printf("Usuwanie przebieglo pomyslnie\n");
			return 0;
		}
		else{
			i=i->nast;
		}
	}while(i!=first2);
	printf("Blad usuwania nie ma takiej liczby na liscie");
	return 0;
}

int usuwanie_p(parzyste **first1, int x){
	parzyste *i;
	i=*first1;
	if(i->nast==i){
		n_parzyste *k;
		k=i->most;
		k->most=NULL;
		free(i);
		free(*first1);
		*first1=NULL;		
	}
	do{
		if(i->x==x){
			parzyste *k,*n;
			k=i->poprz;
			n=i->nast;
			k->nast=n;
			n->poprz=k;
			if(i->most!=NULL){
				n->most=i->most;
				n_parzyste *l;
				l=n->most;
				l->most=n;
			}
			free(i);
			printf("Usuwanie przebieglo pomyslnie\n");
			return 0;
		}
		else{
			i=i->nast;
		}
	}while(i!=*first1);
	printf("Blad usuwania nie ma takiej liczby na liscie");
	return 0;
}

int l_p(parzyste *first1,int x,int a,int d){
	parzyste *i;
	if(d==0){
		printf("Lista jest pusta, brak elementow");
	}
	if(d==1){
		i=first1;
		if(i->x==a){
			parzyste *nowy;
			nowy=malloc(sizeof(parzyste));
			i->nast=nowy;
			i->poprz=nowy;
			nowy->nast=i;
			nowy->poprz=i;
			nowy->x=x;
			return 1;
		}
		else
		printf("Brak podanej liczby");
	}
	else{
		i=first1;
		do{
			if(i->x==a){
				parzyste *nowy,*k;
				nowy=malloc(sizeof(parzyste));
				k=i->nast;
				i->nast=nowy;
				nowy->nast=k;
				nowy->x=x;
				nowy->poprz=i;
				k->poprz=nowy;
				return 1;
			}
			i=i->nast;
		
		}while(i->nast!=first1);
		printf("Brak podanej liczby");
		
	}
	return 0;
}
	
	int l_n(n_parzyste *first2,int x,int a,int d){
	n_parzyste *i;
	if(d==0){
		printf("Lista jest pusta, brak elementow");
	}
	if(d==1){
		i=first2;
		if(i->x==a){
			n_parzyste *nowy;
			nowy=malloc(sizeof(n_parzyste));
			i->nast=nowy;
			i->poprz=nowy;
			nowy->nast=i;
			nowy->poprz=i;
			nowy->x=x;
			return 1;
		}
		else
		printf("Brak podanej liczby");
	}
	else{
		i=first2;
		do{
			if(i->x==a){
				n_parzyste *nowy,*k;
				nowy=malloc(sizeof(n_parzyste));
				k=i->nast;
				i->nast=nowy;
				nowy->nast=k;
				nowy->x=x;
				nowy->poprz=i;
				k->poprz=nowy;
				return 1;
			}
			i=i->nast;
		
		}while(i->nast!=first2);
		printf("Brak podanej liczby");
		
	}
	return 0;
}
	
void usuwanie_calkowite_p(parzyste **first1){
	parzyste *i,*p;
	n_parzyste *k,*j;
	i=*first1;
	p=i->poprz;
	p->nast=NULL;
	p=i;
	k=i->most;
	
	while(i!=NULL){
		if(i->most!=NULL){
			k=i->most;
		}
		i=i->nast;
		free(p);
		p=i;
		p=NULL;
	}
	j=k->poprz;
	j->nast=NULL;
	j=k;
	k=k->nast;
	while(k!=NULL){
		free(j);
		j=NULL;
		j=k;
		k=k->nast;
		
	}
	free(k);
	free(j);
}

void usuwanie_calkowite_n(n_parzyste **first2){
		n_parzyste *i,*p;
		i=*first2;
		p=i;
		while(p!=NULL){
			i=i->nast;
			free(p);
			p=i;
		}
	}



int main(){
	parzyste *first1=NULL;
	n_parzyste *first2=NULL;
	
	srand((unsigned int)time(NULL));
	
	int a,c=0,d=0,b,x,i,y=1,n=2000;
	while(y>0){
		printf("\nCo chcesz zrobic:\n");
		printf("[0]Opuscic program\n[1]Dodac wybrana ilosc pseudolosowych wartosci\n[2]Dodac jedna wybrana przez siebie wartosc\n[3]Wyswietlic wszystkie elementy\n[4]Posortowac elementy\n[5]Usunac wybrana przez siebie liczbe z listy\n[6]Wstawic wybrana liczbe przed inna liczba\n[7]Wyczyscic liste\n");
		printf("Twoj wybor:");
		scanf("%d",&y);
		switch(y){
			case 0 :free(first1);free(first2); return 0; break;
			case 1 : 
				system("cls");
				printf("Ile liczb chcesz wygenerowac:");
				scanf("%d",&x);
				printf("Oto Twoje liczby:\n");
				for(i=0;i<x;i++){
					a=(rand()%n);
					printf("%d\t",a);
					b=a%2;
					if(b==1){
						liczba_n_parzysta(&first1,&first2,a,c,d);
						c++;
					}
					else{
						liczba_parzysta(&first1,&first2,a,d,c);	
						d++;
					}
				}
				if(c>0 && d>0){
					mostowanie(&first1,&first2);
				}
				break;
			
			case 2:
				system("cls");
				printf("Podaj liczbê która chcesz dodac:");
				scanf("%d",&x);
				if(x%2==1){
					liczba_n_parzysta(&first1,&first2,x,c,d);
					c++;
				}
				else{
					liczba_parzysta(&first1,&first2,x,d,c);	
					d++;
				}
			
				if(c>0 && d>0){
					mostowanie(&first1,&first2);
				}
				break;
		
			case 3:
				system("cls");
				if(first2!=NULL && first1==NULL){
					wyswietl_zap(first2);
				}
				else if(first1!=NULL){
					wyswietl(first1);
				}
				else{
					printf("Listy puste");
				}
				break;
			case 4:
				system("cls");
				if(first1==NULL){
					sortowanie_n(&first2);
				}
				else{
					sortowanie_p(&first1);
				}
				break;
			case 5:
				system("cls");
				if(first1==NULL){
					wyswietl_zap(first2);
				}
				else{
					wyswietl(first1);
				}
				printf ("Ktora liczbe z listy chcesz usunac:");
				scanf("%d",&x);
				if(x%2==1){
					usuwanie_n(&first2,x);
				}
				else{
					usuwanie_p(&first1,x);
				}
				break;
			case 6:
				system("cls");
				printf("Podaj liczbe ktora chesz wstawic:");
				scanf("%d",&x);
				printf("Podaj wartosc elementu przed ktory chcesz wstawic podana przez Ciebie liczbe:");
				scanf("%d",&a);
				system("cls");
				if(x%2==0 && a%2==0){
					b=l_p(first1,x,a,d);
					if(b==1){
						d++;
					}
				}
		
				if(x%2==1 && a%2==1){
					b=l_n(first2,x,a,c);
					if(b==1){
						c++;
					}	
				}
				else{
					printf("Listy dziela sie na parzyste i nieparzyste, jesli chcesz dodac liczbe parzysta musisz dodac ja przed liczbe parzysta i odwrotnie\n \n");
				}
				break;	
			case 7:
				if(first1!=NULL){
					usuwanie_calkowite_p(&first1);
				}
				else{
					usuwanie_calkowite_n(&first2);
				}
				first2=NULL;
				first1=NULL;
				d=0;
				c=0;
				printf("Usuwanie przebieglo pomyslnie");
				break;		
		}
	}
	free(first1);
	free(first2);
	return 0;
}
