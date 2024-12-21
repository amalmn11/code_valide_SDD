#include <stdio.h>
#include <stdlib.h>
#include "pile_pointeur.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main()
{
	PtPile *mapile=NULL;
	mapile=Creer_Cellule(3);
	
	if(Est_Vide_PtPile(mapile))  printf("\nla pile est vide");	
	else  printf("\nla pile n'est pas vide");
	
	printf("\nle sommet de la pile est :%d\n",Sommet_PPile(*mapile));
	
	PtPile *cel1=Creer_Cellule(36);
	PtPile *cel2=Creer_Cellule(10);
	PtPile *cel3=Creer_Cellule(3);
	PtPile *cel4=Creer_Cellule(2);
	
	
	PtPile *cel5=Creer_Cellule(11);

	printf("\nl'affichage de la pile : ");
	Afficher_Ppile(mapile);
	
	printf("\n");
	
	Inserer_BonPlace_PPile(mapile,cel1);
	Inserer_BonPlace_PPile(mapile,cel2);
	Inserer_BonPlace_PPile(mapile,cel3);
	Inserer_BonPlace_PPile(mapile,cel4);
	Inserer_BonPlace_PPile(mapile,cel5);
	
	printf("\nl'affichage de la pile : ");
	Afficher_Ppile(mapile);
	
	
	
	

	
	//Vider_PtPile(pile);
	
	return 0;
	
}



