#include <stdio.h>
#include <stdlib.h>

// Définition de l'énumération pour les types de nœuds (opérateur ou opérande)
typedef enum {
    OPERANDE,
    OPERATEUR
} TypeNoeud;

// Définition de la structure d'un nœud dans l'arbre
typedef struct Noeud {
    TypeNoeud type;
    char operateur; // Pour stocker l'opérateur
    int operande;   // Pour stocker l'opérande
    struct Noeud *fgc; // Pointeur sur le fils gauche
    struct Noeud *fdt; // Pointeur sur le fils droit
} Noeud;

// Fonction pour créer un nouveau nœud
Noeud* CreerNoeud(TypeNoeud type, char operateur, int operande) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (nouveauNoeud != NULL) {
        nouveauNoeud->type = type;
        nouveauNoeud->operateur = operateur;
        nouveauNoeud->operande = operande;
        nouveauNoeud->fgc = NULL;
        nouveauNoeud->fdt = NULL;
    }
    return nouveauNoeud;
}

// Fonction pour insérer un opérande ou un opérateur dans l'arbre
Noeud* InsererNoeud(Noeud* racine, char operateur, int operande) {
    if (racine == NULL) {
        // Si l'arbre est vide, créer un nouveau nœud avec les données fournies
        return CreerNoeud(OPERANDE, operateur, operande);
    } else if (racine->type == OPERANDE) {
        // Si le nœud actuel est un opérande, insérer l'opérateur comme son fils gauche
        racine->fgc = InsererNoeud(racine->fgc, operateur, operande);
    } else if (racine->type == OPERATEUR) {
        // Si le nœud actuel est un opérateur, comparer les priorités
        if ((operateur == '+' || operateur == '-') && (racine->operateur == '*' || racine->operateur == '/')) {
            // Si l'opérateur à insérer a une priorité inférieure, insérer comme fils gauche du nœud actuel
            racine->fgc = InsererNoeud(racine->fgc, operateur, operande);
        } else {
            // Sinon, insérer comme fils droit du nœud actuel
            racine->fdt = InsererNoeud(racine->fdt, operateur, operande);
        }
    }
    return racine;
}

// Fonction pour afficher l'arbre (parcours infixé)
void AfficherArbre(Noeud* racine) {
    if (racine != NULL) {
        AfficherArbre(racine->fgc);
        if (racine->type == OPERANDE) {
            printf("%d ", racine->operande);
        } else if (racine->type == OPERATEUR) {
            printf("%c ", racine->operateur);
        }
        AfficherArbre(racine->fdt);
    }
}

// Fonction pour libérer la mémoire de l'arbre
void LibererArbre(Noeud* racine) {
    if (racine != NULL) {
        LibererArbre(racine->fgc);
        LibererArbre(racine->fdt);
        free(racine);
    }
}

int main() {
    Noeud* arbre = NULL;

    // Exemple d'utilisation : insertion des opérandes et des opérateurs
    arbre = InsererNoeud(arbre, '+', 5);
    arbre = InsererNoeud(arbre, '*', 3);
    arbre = InsererNoeud(arbre, '2', 0);
    arbre = InsererNoeud(arbre, '-', 4);

    // Affichage de l'arbre
    AfficherArbre(arbre);

    // Libération de la mémoire de l'arbre
    LibererArbre(arbre);

    return 0;
}

