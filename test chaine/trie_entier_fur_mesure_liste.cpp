#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RC '\n'

#define max 50


typedef struct lst
{
	int tabInt[max];
	int nb;
}liste;

liste *Creer_Liste()
{
    liste *p;
    p = (liste *)malloc(sizeof(liste)); //allocation de l'espace mémoire  
    if (!p) exit(1); // si l'allocation a échoué
    return ((liste *)p); //retourne l'adresse de l'espace mémoire réservé
}

int initialise(liste *L)
{
	if(!L) return((int)0);
	L->nb=0;
	return((int)1);
}

int Est_numerique(char c)
{
	if(c>='0' && c<='9') return ((int)c-'0');
	return((int)-1);	
}

//void lire(liste* L)
//{
//	char car;
//	int val,i=0,j;
//	car=getchar();
//	
//	
//	if((Est_numerique(car))==-1)
//	{
//		printf("vous avez pas saisie une valeur numerique");
//		return;
//	}
//	
//	val=Est_numerique(car);
//	L->tabInt[i]=val;
//	L->nb++;
//	do
//	{
//		car=getchar();
//		if((Est_numerique(car))==-1) break;
//		printf("*");
//		val=Est_numerique(car);
//		while(i<L->nb)
//		{
//			
//			if(val<L->tabInt[i])
//			{
//				printf("*");
//				for(j=L->nb-1;j>=i;j++)	L->tabInt[j+1]=L->tabInt[j];
//				L->tabInt[j]=val;
//				L->nb++;
//			}
//			i++;
//		}
//	}while(car!=RC);
//	//affichage
//	for(i=0;i<L->nb;i++) printf("| %d |",L->tabInt[i]);
//}

int lire(liste* L)
{
	char car;
	int val,i,j;
	
	car=getchar();
	while(car!=RC)
	{
		if((Est_numerique(car))==-1)
		{
			printf("vous avez pas saisie une valeur numerique");
			return ((int)0);
		}
		val=Est_numerique(car);
		i=0;	
		while (i < L->nb && val >= L->tabInt[i])   i++;
        for(j = L->nb-1; j >= i; j--)  L->tabInt[j+1] = L->tabInt[j];
        L->tabInt[i]=val;
        L->nb++;
    	car=getchar();
	}
	return ((int)1);
}
	
	


void afficher(liste *L)
{
	int i;
	//affichage
	for(i=0;i<L->nb;i++) printf("| %d |",L->tabInt[i]);
}





int main()
{
	liste *L=Creer_Liste();
	initialise(L);
	lire(L);
	afficher(L);
	return 0;
}
