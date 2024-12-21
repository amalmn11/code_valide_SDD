#ifndef PILE_POINTEUR_H // Cette directive évite les inclusions multiples
#define PILE_POINTEUR_H


#include<stdio.h>
#include<stdlib.h>


/*Definition d'une structure de liste */
typedef struct pl
{

    int Entier;/* l'élement de la liste */
    struct pl *svt; /* poiteur sur l'élement au suivant */
 	
}PtPile;/* le nom de la structure */



PtPile *Creer_Cellule(int val)
{
	
    PtPile *NE;
    /* Allouer la mémoire pour NE */
    NE=(PtPile*) malloc(sizeof(PtPile));
    /*L'allocation est mal passé */
    if(!NE)
    {
   		/* Afficher un message d'errreur */
 		printf("\nErreur d allocation du memoire.");
 		/*Sortir du programme */
    	exit(-1);
    }
 	/* Ajouter l'élément */
 	NE->Entier=val;
 	/* Indiquer que le noueud crée n'a pas de séccessur */
 	NE->svt=NULL;
 	return ((PtPile*)NE);/* Recupérere le noeud cré */
 	
}

//cette fonction permet de vérifier si une pile est vide 
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
 		// Stockage du pointeur vers le nœud actuel dans tmp
 		tmp = Mapile; 
 		//Mise à jour du pointeur Liste pour passer au nœud suivant
 		Mapile = Mapile->svt; 
 		// Libération de la mémoire occupée par le nœud actuel
 		free(tmp); 
 	}
 	// À la fin, Liste est NULL, indiquant que la liste est vidée
 	printf("la pile est vide\n");
 	return ((PtPile*)Mapile);
}



#endif  // PILE_POINTEUR_H

