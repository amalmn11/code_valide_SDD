#ifndef PILE_POINTEUR_H // Cette directive ?vite les inclusions multiples
#define PILE_POINTEUR_H


#include<stdio.h>
#include<stdlib.h>


/*Definition d'une structure de liste */
typedef struct pl
{

    int Entier;/* l'?lement de la liste */
    struct pl *svt; /* poiteur sur l'?lement au suivant */
 	
}PtPile;/* le nom de la structure */



PtPile *Creer_Cellule(int val)
{
	
    PtPile *NE;
    /* Allouer la m?moire pour NE */
    NE=(PtPile*) malloc(sizeof(PtPile));
    /*L'allocation est mal pass? */
    if(!NE)
    {
   		/* Afficher un message d'errreur */
 		printf("\nErreur d allocation du memoire.");
 		/*Sortir du programme */
    	exit(-1);
    }
 	/* Ajouter l'?l?ment */
 	NE->Entier=val;
 	/* Indiquer que le noueud cr?e n'a pas de s?ccessur */
 	NE->svt=NULL;
 	return ((PtPile*)NE);/* Recup?rere le noeud cr? */
 	
}

//cette fonction permet de v?rifier si une pile est vide 
int Est_Vide_PtPile(PtPile *Mapile)
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
 		// Stockage du pointeur vers le n?ud actuel dans tmp
 		tmp = Mapile; 
 		//Mise ? jour du pointeur Liste pour passer au n?ud suivant
 		Mapile = Mapile->svt; 
 		// Lib?ration de la m?moire occup?e par le n?ud actuel
 		free(tmp); 
 	}
 	// ? la fin, Liste est NULL, indiquant que la liste est vid?e
 	printf("la pile est vide");
 	return ((PtPile*)Mapile);
}

//fonction permet d'emplier une cellule
PtPile *Empiler(PtPile *Mapile, PtPile *NE)
{
 // V?rification que macel n'est pas vide (pile non vide)
 	if(!NE)  return((PtPile*)Mapile);
 	if(Est_Vide_PtPile(Mapile))  return((PtPile*)NE);
 	
    // Mise ? jour du pointeur svt de NE pour pointer vers l'ancienne sommet de pile
    NE->svt = Mapile; 
    //Mise ? jour de Mapile pour pointer vers NE
    Mapile = NE; 	
 	//Renvoi e sommet de la pile
 	return ((PtPile*)Mapile);

}

//fonction permet depiler une cellule
PtPile *depiler(PtPile *Mapile)
{
	PtPile *tmp;
	// si la pile est vide 
	if(!Mapile) return ((PtPile *)NULL);
	
	// Stockage du premier n?ud dans tmp
	tmp = Mapile; 
	//Mise ? jour de Mapile pour pointer
	Mapile = Mapile->svt; 
	// Lib?ration de l'espace m?moire pointe par tmp
	free(tmp); 
	// Renvoi du pointeur mis ? jour vers la pile
	return ((PtPile *)Mapile);
}

//fonctio qui calcule la taille d'une pile
int Taille_Ppile(PtPile *mapile)
{	
	int taille = 0; // Initialisation de la taille ? 0
	PtPile *tmp, *pcrt;
    // Si la pile est vide, la taille est 0
	if(!mapile) return ((int)0);
	tmp = NULL;
	// D?placement des cellules pour compter la taille
	while(mapile)
	{
		taille++;//Incr?menter la taille ? chaque d?placement de cellule
		pcrt = mapile;
		mapile = mapile->svt;
		pcrt->svt = tmp;
		tmp = pcrt; // tmp conserve la cellule pour replacer plus tard
	}
	// Replacer les cellules dans l'ordre initial de la pile
	while (tmp)
	{
		pcrt = tmp;
		tmp = tmp->svt;
		pcrt->svt = mapile;
		mapile = pcrt;
	}
	return ((int)taille); // Retour de la taille de la pile
}


//fonction qui permet d'afficher la pile 
void Afficher_Ppile(PtPile *mapile)
{
	PtPile *tmp, *pcrt;
 // Si la pile est vide, affichage d'un message appropri? et retour
	if (Est_Vide_PtPile(mapile))
	{
		printf("\nLa pile est vide");
		return;
	}
	
	tmp = NULL;
	// Affichage des ?l?ments de la pile
	while (!Est_Vide_PtPile(mapile))
	{
		printf("| %d |", mapile->Entier);//Afficher la valeur de l'?l?ment
		pcrt = mapile;
		mapile = mapile->svt;
		pcrt->svt = tmp;
		tmp = pcrt; // tmp conserve la cellule pour replacer plus tard
	}
	// Replacer les cellules dans l'ordre initial de la pile
	while (!Est_Vide_PtPile(tmp))
	{
		pcrt = tmp;
		tmp = tmp->svt;
		pcrt->svt = mapile;
		mapile = pcrt;
	}
}


//fonction qui retourne le sommet de la pile
int Sommet_PPile(PtPile mapile)
{
	return ((int)mapile.Entier);
}


//fonction qui permet d'inserer un element a la bonne place 
PtPile* Inserer_BonPlace_PPile(PtPile *mapile, PtPile *NE)
{
	int rest;
	PtPile *tmp, *pcrt;
	if(Est_Vide_PtPile(mapile)) return((PtPile*)NE);
	tmp = NULL;
	if(NE->Entier < Sommet_PPile(*mapile))
	{
		mapile=	Empiler(mapile,NE);
		return ((PtPile*)mapile);
	}
	//met le sommet de la pile dans la pile temporaire
	tmp=mapile;
	mapile=mapile->svt;
	tmp->svt=NULL;
	//parcurir la pile jusqua ce qu'on trouve un element superieur ou ?gal l'element saisie
	while ((mapile) && ((mapile->Entier<NE->Entier)))
	{
		//met l'element NE dans tmp
		pcrt = mapile;
		mapile = mapile->svt;
		pcrt->svt = tmp;
		tmp = pcrt;
	}
 	//Ins?rer le nouveau element dans mapile
	NE->svt = mapile;
	mapile = NE;
	
	while (tmp)
	{
		//Remetre les element de la pile tmp dans mapile
		pcrt = tmp;
		tmp = tmp->svt;
		pcrt->svt = mapile;
		mapile = pcrt;
	}
	return ((PtPile*)mapile);//Retourner 1 pour indiquer une insertion r?ussie
}





#endif  // PILE_POINTEUR_H





