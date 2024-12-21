#include <stdio.h>
#include <stdlib.h>
#include "pile_pointeur.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main()
{
	PtPile *pile=NULL;
	pile=Creer_Cellule(3);
	
	
	PtPile *cel1=Creer_Cellule(36);
	PtPile *cel2=Creer_Cellule(10);
	PtPile *cel3=Creer_Cellule(3);
	PtPile *cel4=Creer_Cellule(2);
	
	Vider_PtPile(pile);
	
	return 0;
	
}
