#ifndef PILE_POINTEUR_H // Cette directive �vite les inclusions multiples
#define PILE_POINTEUR_H


#include<stdio.h>
#include<stdlib.h>


/*Definition d'une structure de liste */
typedef struct pl
{

    int Entier;/* l'�lement de la liste */
    struct pl *svt; /* poiteur sur l'�lement au suivant */
 	
}PtPile;/* le nom de la structure */



PtPile *Creer_Cellule(int val)
{
	
    PtPile *NE;
    /* Allouer la m�moire pour NE */
    NE=(PtPile*) malloc(sizeof(PtPile));
    /*L'allocation est mal pass� */
    if(!NE)
    {
   		/* Afficher un message d'errreur */
 		printf("\nErreur d allocation du memoire.");
 		/*Sortir du programme */
    	exit(-1);
    }
 	/* Ajouter l'�l�ment */
 	NE->Entier=val;
 	/* Indiquer que le noueud cr�e n'a pas de s�ccessur */
 	NE->svt=NULL;
 	return ((PtPile*)NE);/* Recup�rere le noeud cr� */
 	
}

//cette fonction permet de v�rifier si une pile est vide 
int Est_Vide_PtListe(PtPile *Mapile)
{
 	return ((int)(!Mapile));
}


//cette fonction permet de vider une pile 
PtPile *Vider_PtPile(PtPile *Mapile)
{
 	PtPile *tmp;
 	// Utilisation d'une boucle pour parcourir la liste
 	while (Mapile)
 	{
 		// Stockage du pointeur vers le n�ud actuel dans tmp
 		tmp = Mapile; 
 		//Mise � jour du pointeur Liste pour passer au n�ud suivant
 		Mapile = Mapile->svt; 
 		// Lib�ration de la m�moire occup�e par le n�ud actuel
 		free(tmp); 
 	}
 	// � la fin, Liste est NULL, indiquant que la liste est vid�e
 	printf("la pile est vide\n");
 	return ((PtPile*)Mapile);
}



#endif  // PILE_POINTEUR_H

