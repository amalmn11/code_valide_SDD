#include <stdio.h>
#include <stdlib.h>

// Définition de la structure de la pile
typedef struct pile
{
    int entier;            // le champ de donnée
    struct pile *suivant; // le pointeur suivant
} PTPile;

// Fonction pour créer et initialiser la pile
PTPile *creer_PTPile()
{
    PTPile *NE;
    NE = (PTPile *)malloc(sizeof(PTPile));
    if (!NE) // Erreur d'allocation de mémoire
    {
    	return ((PTPile *)NULL);
    	
        //printf("\nErreur d'allocation");
        //exit(-1); // Sortir du programme
    }
    NE->suivant = NULL;
    return ((PTPile *)NE);
}

// Fonction pour empiler un élément
PTPile *empiler_PTPile(PTPile *MaPile, int elem)
{
    PTPile *NE=creer_PTPile();
    NE->entier=elem;
    NE->suivant = MaPile;
    return ((PTPile *)NE);
}

// Fonction pour dépiler un élément
PTPile *depiler_PTPile(PTPile *MaPile)
{
   PTPile *tmp;
   if(!MaPile) return ((PTPile*) NULL);
   tmp=MaPile;
   MaPile=MaPile->suivant;
   free(tmp);
   return((PTPile*)MaPile);
}


// Fonction pour vérifier si la pile est vide
int est_vide_PTPile(PTPile *MaPile)
{
    return ((int)(!MaPile));
}

// Fonction pour vider la pile    
PTPile *razer_PTPile(PTPile *MaPile)
{
	PTPile *tmp;
	while(MaPile)
	{
		tmp=MaPile;
		MaPile=MaPile->suivant;
		free(tmp);
	}
	return ((PTPile *)NULL);
}

// Fonction pour afficher les éléments de la pile
void afficher_PTPile(PTPile *MaPile)
{
	//si la pile est vide
    if(est_vide_PTPile(MaPile)) 
    {
    	printf("la pile est vide\n");
    	return;
	}
    //si la pile existe
    PTPile *tmp = MaPile;
    printf("Affichage des elements de la pile:\n");
    //tant que tmp!=NULL
    while (tmp)
    {
    		//afficher la valeur 
            printf("%d\t", tmp->entier);
            //tmp pointe sur la cellule suivante
            tmp = tmp->suivant;
    }
    printf("\n");

}


// Fonction pour obtenir la taille de la pile
int taille_PTPile(PTPile *MaPile)
{
    int taille = 0;
    PTPile *ptcrt, *tmp;
    tmp=NULL;
    //tant que MaPile n'est pas NULL
    while (MaPile)
    {
        
        ptcrt=MaPile;//ptcrt pointe sur le sommet
        //MaPile pointe sur la cellule suivante
        MaPile=MaPile->suivant;
        ptcrt->suivant=tmp;
        tmp=ptcrt;
        taille++;//incrementer la taile
    }
    //fin de while maintenant Mapile==NULL
    while(tmp)
    {
    	ptcrt=tmp;
    	tmp=tmp->suivant;
    	ptcrt->	suivant=MaPile;
    	MaPile=ptcrt;
	}
	return ((int)taille);
    
}


int main()
{
    PTPile *MaPile=NULL; // Création de la pile

    // Empiler des éléments
    MaPile = empiler_PTPile(MaPile, 10);
    printf("empiler la valeur 10");
    MaPile = empiler_PTPile(MaPile, 20);
    printf("\nempiler la valeur 20");
    MaPile = empiler_PTPile(MaPile, 30);
    printf("\nempiler la valeur 30\n");

    // Afficher les éléments de la pile
    afficher_PTPile(MaPile);

    // Obtenir la taille de la pile
    int taille = taille_PTPile(MaPile);
    printf("Taille de la pile : %d\n", taille);
    // Dépiler un élément
    MaPile = depiler_PTPile(MaPile);
    printf("depiler la valeur 30\n");

    // Afficher les éléments de la pile après dépilement
    afficher_PTPile(MaPile);

    // Vider la pile
    printf("Vider la pile.\n");
    MaPile = razer_PTPile(MaPile);
	
    // Afficher les éléments de la pile après vidage
    afficher_PTPile(MaPile);

    return 0;
}

