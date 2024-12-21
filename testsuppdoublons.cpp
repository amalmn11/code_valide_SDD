#include <stdio.h>
#include <stdlib.h>

typedef struct lst {
    int Entier;
    struct lst* svt;
} Cellule;

Cellule* Creer_cellule(int entier) {
    Cellule* NE = (Cellule*)malloc(sizeof(Cellule));
    if (!NE) {
        printf("Problème d'allocation");
        exit(EXIT_FAILURE);
    }
    NE->Entier = entier;
    NE->svt = NULL;
    return NE;
}

Cellule* insererDebut(Cellule* liste, Cellule* NE) {
    NE->svt = liste;
    return NE;
}

int existeDansListe(Cellule* liste, int val) {
    Cellule* tmp = liste;
    while (tmp) {
        if (tmp->Entier == val) {
            return 1;
        }
        tmp = tmp->svt;
    }
    return 0;
}

Cellule* supprimerDoublons(Cellule* liste) {
    Cellule* courant = liste;
    Cellule* prev = NULL;
    Cellule* doublons = NULL;

    while (courant) {
        if (existeDansListe(doublons, courant->Entier)) {
            prev->svt = courant->svt;
            free(courant);
        } else {
            doublons = insererDebut(doublons, Creer_cellule(courant->Entier));
            prev = courant;
        }
        courant = prev->svt;
    }

    return liste;
}

void afficherListe(Cellule* liste) {
    Cellule* tmp = liste;
    while (tmp) {
        printf("| %d | ", tmp->Entier);
        tmp = tmp->svt;
    }
    printf("\n");
}

int main() {
    Cellule* liste = NULL;

    liste = insererDebut(liste, Creer_cellule(1));
    liste = insererDebut(liste, Creer_cellule(2));
    liste = insererDebut(liste, Creer_cellule(3));
    liste = insererDebut(liste, Creer_cellule(2));
    liste = insererDebut(liste, Creer_cellule(11));

    printf("Liste initiale :\n");
    afficherListe(liste);

    liste = supprimerDoublons(liste);

    printf("Liste après suppression des doublons :\n");
    afficherListe(liste);

    return 0;
}

