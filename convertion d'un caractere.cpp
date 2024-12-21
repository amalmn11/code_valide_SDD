#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BL ' '
#define RC '\n'

char Epurer_blanc()
{
	char carac;
//	c=getchar();
//	while(c==BL) c=getchar();
//	return ((char)c);
	while((carac=getchar())==BL);
	return ((char)carac);
}

int EstNumerique(char carac)
{
	return ((int)(carac>='0' && carac<='9'));
}

int convertir(char carac)
{
//	int entier;
//	entier=carac-'0';
//	return((int)entier);
	return((int)carac-'0');
}

int signe(char carac)
{
	return((int)(carac=='+' || carac=='-'));
}

double lire_Entier()
{
	char carac,sign;
	double val=0.0,val1=0.0,virgule=0.0;//entier;
	carac=Epurer_blanc();
	if(carac==RC) printf("\nvous avez entrer RC comme 1ere caracter different de BL ==> fin de programme \n");
	if(signe(carac))
	{
		sign=carac;
		carac=Epurer_blanc();
	}
	do
	{	
		if(EstNumerique(carac))
		{
			//entier=convertir(carac);
			val=val*10+convertir(carac);
		}
		else break;	
		//car=getchar(); et utiliser dans while(car!=RC)
		
	}while((carac=getchar())!=RC);
	if(carac=='.')
	{
		carac=Epurer_blanc();
		do
		{	
			
			if(EstNumerique(carac))
			{
				virgule++;
				val1=val1+convertir(carac)*pow(10,-virgule);
			}	
			else break;
			
		}while((carac=getchar())!=RC);
	}
	if(carac==BL)  carac=Epurer_blanc();
	if(carac==RC)
	{
	//val+=val1;

		if(sign=='-')
		{
			val=val+val1;
			val*=-1;
			return((int)val-val1);
		} 
			return((int)val+val1);

	}  
	printf("erreur");
	return((int)-1);
////	
//////	ça c'est dans le cas ou on a 123 4 et veux afficher 1234
//////	if(carac==BL)  carac=Epurer_blanc();
//////	
//////	if(EstNumerique(carac))
//////	{
//////		val=val*10+convertir(carac);
//////		return((int)val);
//////	}
//////	if(carac=RC)   return((int)val);
	
	
}


int main()
{
	printf("L'entier est : %+8Lf",lire_Entier());
	return (int)0;
}











































//Convertir un caractère numérique en un entier
//int main()
//{
//	char caractere = '1' ;
//	int entier = (int(caractere));
//	printf("%d",entier);
//	return 0;
//}


////utilisation de fonction atoi
//int main() {
//    char caractere = '0';  // Caractère '1'
//    int entier = atoi(&caractere);  // Utilisation de la fonction atoi() pour la conversion
//    printf("%d\n", entier);  // Cela affichera le nombre entier 1
//    return 0;
//}
