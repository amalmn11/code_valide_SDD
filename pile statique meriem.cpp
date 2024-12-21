#include <stdio.h>
#include <stdlib.h>

// Déclaration des constantes
#define MaxElem 50 // Nombre maximum d'éléments dans la pile

// Déclaration des types et des structures
typedef struct
{
    int Tab[MaxElem]; // Tableau de la pile
    int Sommet;       // Indique le sommet de la pile
} TPile;


// Définition des fonctions

TPile *creer_TPile()
{
    // Crée et alloue de la mémoire pour une pile vide
    TPile *P;
    P = (TPile *)malloc(sizeof(TPile));
    if (P == NULL)
    {
        printf("Erreur ! Impossible de creer la pile.\n");
        exit(0);
    }
    return (TPile *)P;
}

int initialiser_TPile(TPile *P)
{
    // Initialise une pile vide
    if (!P)
        return (int)-1; // La pile n'existe pas
    P->Sommet = -1;
    return ((int)1);
}

int taille_TPile(TPile P)
{
    // Retourne la taille de la pile
    return ((int)(P.Sommet + 1));
}

int est_vide_TPile(TPile P)
{
    // Vérifie si la pile est vide
    return ((int)(P.Sommet == -1));
}

int est_sature_TPile(TPile P)
{
    // Vérifie si la pile est saturée
//    if (!P)
//        return ((int)-1); // La pile n'existe pas
    return ((int)(P.Sommet == MaxElem - 1));
}

int empiler_TPile(TPile *P, int n)
{
    // Empile un élément dans la pile
    if (!P)
    {
        printf("Erreur ! La pile n'existe pas.\n");
        exit(0);
    }
    if (est_sature_TPile(*P))
    {
        printf("La pile est saturee, impossible d'empiler %d.\n", n);
        return (int)0;
    }
    P->Tab[++(P->Sommet)] = n;
    return ((int)1);
}

int depiler_TPile(TPile *P)
{
    // Dépile un élément de la pile
    if (!P)
        return ((int)-1); // La pile n'existe pas
    if (est_vide_TPile(*P))
    {
        printf("La pile est vide, impossible de depiler.\n");
        return ((int)-1);
    }
    return ((int)P->Tab[(P->Sommet)--]);
}

//fonction qui retourne l'element qui se trouve dans le sommet
int sommet_TPile(TPile *P)
{
    // Retourne l'élément en haut de la pile sans le dépiler
    if (!P)
        return ((int)-1); // La pile n'existe pas
    if (est_vide_TPile(*P))
    {
        printf("La pile est vide, aucun element en haut.\n");
        return ((int)-1);
    }
    return ((int)P->Tab[(P->Sommet)]);
}

//fonction qui permet d'afficher les elements de la pile
void afficher_TPile(TPile *P)
{
    // Affiche les éléments de la pile
    if (est_vide_TPile(*P))
    {
        printf("La pile est vide.\n");
        return;
    }
    printf("Affichage des elements de la pile :\n");
    for (int i = P->Sommet; i >= 0; i--)
    {
        printf("%d\t", P->Tab[i]);
    }
}

// Fonction principale
int main()
{
    TPile *P = creer_TPile();
    initialiser_TPile(P);

    // Crée et initialise une pile vide
    printf("Pile cree et initialisee.\n");

    // Ajoute des éléments à la pile
    empiler_TPile(P, 4);
    empiler_TPile(P, 5);
    empiler_TPile(P, 6);

    printf("elements ajoutes a la pile : 4, 5 et 6.\n");

    // Affiche la pile actuelle
    printf("Pile actuelle : \n");
    afficher_TPile(P);

    // Affiche la taille de la pile
    printf("\nLa taille de la pile est de %d elements.\n", taille_TPile(*P));

    // Vérifie si la pile est vide
    printf("La pile est %s.\n", est_vide_TPile(*P) ? "vide" : "non vide");

    // Vérifie si la pile est saturée
    printf("La pile est %s.\n", est_sature_TPile(*P) ? "saturee" : "non saturee");

    // Dépile un élément de la pile
    depiler_TPile(P);
    printf("element depile.\n");
    
    // Retourne l'élément en haut de la pile aprés le dépilement
    printf("affichage d'element qui se trouve en haut de la pile : %d\n", sommet_TPile(P));

    // Affiche la pile après le défilement
    printf("Pile actuelle : \n");
    afficher_TPile(P);

    // Libère la mémoire
    free(P);

    return (int)0;
}
