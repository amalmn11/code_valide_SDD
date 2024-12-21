#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RC '\n'
#define BL ' '
#define MaxElm 90


char Epurerblanc()
{
	char car;
	while((car=getchar())==BL);
	return ((char)car);
}

//fonction qui permet  de trouver un mot à l'interienr d'une phrase
void trouver_mot()
{
	char Lemot[MaxElm];
	char motlu[MaxElm];
	char car;
	int ind,freq=1;
	/*lecture du mot a rechrcher*/
	printf("Entrer le mot a rechrecher :");
	scanf("%s",Lemot); getchar();
	printf("Entrer la phrase a traiter:");
	/*Rechercher le mot dans la phrase*/
	do
	{
		ind=0;
		car=Epurerblanc();
		if(car==RC) break; //s'il y a un RC avant la phrase 
		motlu[ind]=car;
		//cette boucle recupere un seul mot
		while(((car=getchar())!=BL) && (car!=RC))
		{
			motlu[++ind]=car;
		}
		motlu[++ind]='\0';
		/*on a maintenant un seul mot on peut le comparer 
		avec le mot chercher */
		if(!strcmp(Lemot,motlu))	printf("\n le mot apprait dans la phrase %d fois",freq++);		
	}while(car!=RC);
	if(freq==1) printf("\n le mot n'existe pas ");
}

int main()
{
	trouver_mot();	
}
