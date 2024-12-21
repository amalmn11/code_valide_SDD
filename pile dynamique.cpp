#include <stdio.h>
#include <stdlib.h>

// D�finition de la structure de la pile
typedef struct pile
{
    int entier;            // le champ de donn�e
    struct pile *suivant; // le pointeur suivant
} PTPile;

// Fonction pour cr�er et initialiser la pile
PTPile *creer_PTPile()
{
    PTPile *NE;
    NE = (PTPile *)malloc(sizeof(PTPile));
    if (!NE) // Erreur d'allocation de m�moire
    {
    	return ((PTPile *)NULL);
    	
        //printf("\nErreur d'allocation");
        //exit(-1); // Sortir du programme
    }
    NE->suivant = NULL;
    return ((PTPile *)NE);
}

// Fonction pour empiler un �l�ment
PTPile *empiler_PTPile(PTPile *MaPile, int elem)
{
    PTPile *NE=creer_PTPile();
    NE->entier=elem;
    NE->suivant = MaPile;
    return ((PTPile *)NE);
}

// Fonction pour d�piler un �l�ment
PTPile *depiler_PTPile(PTPile *MaPile)
{
   PTPile *tmp;
   if(!MaPile) return ((PTPile*) NULL);
   tmp=MaPile;
   MaPile=MaPile->suivant;
   free(tmp);
   return((PTPile*)MaPile);
}


// Fonction pour v�rifier si la pile est vide
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

// Fonction pour afficher les �l�ments de la pile
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
    PTPile *MaPile=NULL; // Cr�ation de la pile

    // Empiler des �l�ments
    MaPile = empiler_PTPile(MaPile, 10);
    printf("empiler la valeur 10");
    MaPile = empiler_PTPile(MaPile, 20);
    printf("\nempiler la valeur 20");
    MaPile = empiler_PTPile(MaPile, 30);
    printf("\nempiler la valeur 30\n");

    // Afficher les �l�ments de la pile
    afficher_PTPile(MaPile);

    // Obtenir la taille de la pile
    int taille = taille_PTPile(MaPile);
    printf("Taille de la pile : %d\n", taille);
    // D�piler un �l�ment
    MaPile = depiler_PTPile(MaPile);
    printf("depiler la valeur 30\n");

    // Afficher les �l�ments de la pile apr�s d�pilement
    afficher_PTPile(MaPile);

    // Vider la pile
    printf("Vider la pile.\n");
    MaPile = razer_PTPile(MaPile);
	
    // Afficher les �l�ments de la pile apr�s vidage
    afficher_PTPile(MaPile);

    return 0;
}

