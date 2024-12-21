#include <stdio.h>
#include <stdlib.h>

// D�finition de l'�num�ration pour les types de n�uds (op�rateur ou op�rande)
typedef enum {
    OPERANDE,
    OPERATEUR
} TypeNoeud;

// D�finition de la structure d'un n�ud dans l'arbre
typedef struct Noeud {
    TypeNoeud type;
    char operateur; // Pour stocker l'op�rateur
    int operande;   // Pour stocker l'op�rande
    struct Noeud *fgc; // Pointeur sur le fils gauche
    struct Noeud *fdt; // Pointeur sur le fils droit
} Noeud;

// Fonction pour cr�er un nouveau n�ud
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

// Fonction pour ins�rer un op�rande ou un op�rateur dans l'arbre
Noeud* InsererNoeud(Noeud* racine, char operateur, int operande) {
    if (racine == NULL) {
        // Si l'arbre est vide, cr�er un nouveau n�ud avec les donn�es fournies
        return CreerNoeud(OPERANDE, operateur, operande);
    } else if (racine->type == OPERANDE) {
        // Si le n�ud actuel est un op�rande, ins�rer l'op�rateur comme son fils gauche
        racine->fgc = InsererNoeud(racine->fgc, operateur, operande);
    } else if (racine->type == OPERATEUR) {
        // Si le n�ud actuel est un op�rateur, comparer les priorit�s
        if ((operateur == '+' || operateur == '-') && (racine->operateur == '*' || racine->operateur == '/')) {
            // Si l'op�rateur � ins�rer a une priorit� inf�rieure, ins�rer comme fils gauche du n�ud actuel
            racine->fgc = InsererNoeud(racine->fgc, operateur, operande);
        } else {
            // Sinon, ins�rer comme fils droit du n�ud actuel
            racine->fdt = InsererNoeud(racine->fdt, operateur, operande);
        }
    }
    return racine;
}

// Fonction pour afficher l'arbre (parcours infix�)
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

// Fonction pour lib�rer la m�moire de l'arbre
void LibererArbre(Noeud* racine) {
    if (racine != NULL) {
        LibererArbre(racine->fgc);
        LibererArbre(racine->fdt);
        free(racine);
    }
}

int main() {
    Noeud* arbre = NULL;

    // Exemple d'utilisation : insertion des op�randes et des op�rateurs
    arbre = InsererNoeud(arbre, '+', 5);
    arbre = InsererNoeud(arbre, '*', 3);
    arbre = InsererNoeud(arbre, '2', 0);
    arbre = InsererNoeud(arbre, '-', 4);

    // Affichage de l'arbre
    AfficherArbre(arbre);

    // Lib�ration de la m�moire de l'arbre
    LibererArbre(arbre);

    return 0;
}

