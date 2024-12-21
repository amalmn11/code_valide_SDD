#include <stdio.h>
#include <stdlib.h>
#define MaxElm 100


typedef struct Pl
{
	int TabInt[MaxElm];
	int sommet;
}PTPile;

PTPile *creer_TPile()
{
    // Crée et alloue de la mémoire pour une pile vide
    PTPile *P;
    P = (PTPile *)malloc(sizeof(PTPile));
    if (!P)
    {
        printf("Erreur ! Impossible de creer la pile.\n");
        exit(0);
    }
    return (PTPile *)P;
} 

int init_PTPile(PTPile *Mapile)
{
    // Initialise une pile vide
    if (!Mapile) return (int)-1; // La pile n'existe pas
    Mapile->sommet = -1;
    return ((int)1);
}

int est_vide_PTPile(PTPile Mapile)
{
    // Vérifie si la pile est vide
    return ((int)(Mapile.sommet==-1));
}

int est_sature_PTPile(PTPile Mapile)
{
    return ((int)(Mapile.sommet == MaxElm-1));
}

int taille_PTPile(PTPile Mapile)
{
    // Retourne la taille de la pile
    return ((int)(Mapile.sommet+1));
}

int empiler_PTPile(PTPile *Mapile, int n)
{
    // Empile un élément dans la pile
    if (!Mapile)
    {
        printf("Erreur ! La pile n'existe pas.\n");
        exit(0);
    }
    if (est_sature_PTPile(*Mapile))
    {
        printf("La pile est saturee, impossible d'empiler %d.\n", n);
        return (int)0;
    }
    Mapile->TabInt[++(Mapile->sommet)] = n;
    return ((int)1);
}

int sommet_PTPile(PTPile Mapile)
{
    return ((int)Mapile.TabInt[(Mapile.sommet)]);
}

//int sommet_TPile(TPile *P)
//{
//    // Retourne l'élément en haut de la pile sans le dépiler
//    if (!P)
//        return ((int)-1); // La pile n'existe pas
//    if (est_vide_TPile(*P))
//    {
//        printf("La pile est vide, aucun element en haut.\n");
//        return ((int)-1);
//    }
//    return ((int)P->Tab[(P->Sommet)]);
//}




int depiler_PTPile(PTPile *Mapile)
{
    // Dépile un élément de la pile
    if (!Mapile)
        return ((int)0); // La pile n'existe pas
//    if (est_vide_TPile(*Mapile))
//    {
//        printf("La pile est vide, impossible de depiler.\n");
//        return ((int)0);
//    }
//    return ((int)Mapile->Tab[(Mapile->Sommet)--]);
	if (!est_vide_PTPile(*Mapile))
		Mapile->sommet--;
	return ((int)1);
	
}

void afficher_pile(PTPile *MaPile)
{
	int i;
	if (!MaPile)
	{
		printf("\nla pile n'existe pas\n");
		return;
	}
	if(est_vide_PTPile(*MaPile))
	{
		printf("\nla pile est vide\n");
		return;
	}
	for (int i = MaPile->sommet; i >= 0; i--)
    {
        printf("%d\t", MaPile->TabInt[i]);
    }
    printf("\n");
	
}

int main()
{
    PTPile *MaPile = creer_TPile();
    init_PTPile(MaPile);

    // Crée et initialise une pile vide
    printf("Pile cree et initialisee.\n");

    // Ajoute des éléments à la pile
    empiler_PTPile(MaPile, 4);
    empiler_PTPile(MaPile, 5);
    empiler_PTPile(MaPile, 6);

    printf("elements ajoutes a la pile : 4, 5 et 6.\n");

    // Affiche la pile actuelle
    printf("Pile actuelle : \n");
    afficher_pile(MaPile);

    // Affiche la taille de la pile
    printf("La taille de la pile est de %d elements.\n", taille_PTPile(*MaPile));

    // Vérifie si la pile est vide
    printf("La pile est %s.\n", est_vide_PTPile(*MaPile) ? "vide" : "non vide");

    // Vérifie si la pile est saturée
    printf("La pile est %s.\n", est_sature_PTPile(*MaPile) ? "saturee" : "non saturee");

    // Retourne l'élément en haut de la pile sans le dépiler
    printf("Affichage de l'element qui se trouve en haut de la pile : %d\n", sommet_PTPile(*MaPile));
    
    
    afficher_pile(MaPile);

    // Libère la mémoire
    free(MaPile);

    return (int)0;
}

