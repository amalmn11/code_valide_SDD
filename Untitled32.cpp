#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RC '\n'
#define BL ' '
#define PL '+'
#define MN '-'
#define ML '*'
#define DV '/'

// Structures
typedef union {
    double valeur;
    char caractere;
} valeur;

// Structure arbre
typedef struct ND {
    valeur info;
    struct ND *fgch;
    struct ND *fdrt;
} Noeud;

// Structure générale
typedef struct GN {
    Noeud *Arb;
    Noeud *crt;
} PTarbcrt;

// Prototypes de fonctions
Noeud *creer_noeud();
PTarbcrt *creer_arb_general();
char epurer_blanc();
int est_signe(char c);
int est_numerique(char car);
int char_TO_int(char c);
int est_operateur(char car);
double lire_reel(char *caractere);
void inserer_Exp_Arb(PTarbcrt *ptarbcrt, double val, char car);
double Calculer_Exp(double Op1, char operateur, double Op2);
Noeud *lire_Expression_arith();
double Evaluer_Arbre_Exp(Noeud *Arb);
void liberer_memoire(Noeud *Arb);
void affichage_infixe(Noeud *Arb);

// Création d'un nœud
Noeud *creer_noeud() {
    Noeud *NE = (Noeud *)malloc(sizeof(Noeud));
    if (!NE) {
        printf("Erreur d'allocation !");
        exit(-1);
    }
    NE->fdrt = NE->fgch = NULL;
    return NE;
}

PTarbcrt *creer_arb_general() {
    PTarbcrt *NEarbre;
    NEarbre = (PTarbcrt *)malloc(sizeof(PTarbcrt));
    if (!NEarbre) {
        printf("Erreur d'allocation !");
        exit(-1);
    }
    NEarbre->Arb = NEarbre->crt = NULL;
    return ((PTarbcrt *)NEarbre);
}

// Fonction pour supprimer les espaces blancs
char epurer_blanc() {
    char car;
    while ((car = getchar()) == RC || car == BL);
    return car;
}

// Fonction pour déterminer le signe
int est_signe(char c) {
    switch (c) {
        case '-': return -1;
        case '+': return 1;
        default: return 0;
    }
}

// Fonction pour vérifier si le caractère est numérique
int est_numerique(char car) {
    return '0' <= car && car <= '9';
}

// Conversion de caractère en entier
int char_TO_int(char c) {
    return c - '0';
}

// Fonction pour vérifier si le caractère est un opérateur
int est_operateur(char car) {
    return ((int)(car == '+') || (car == '/') || (car == '-') || (car == '*'));
}

// Fonction pour lire un réel
double lire_reel(char *caractere) {
    char c;
    int i, signe;
    double Ptdecim, Ptent;
    Ptent = 0.0;
    Ptdecim = 0.0;
    c = epurer_blanc();

    if (!(signe = est_signe(c))) {
        if (est_numerique(c))
            Ptent = Ptent * 10.0 + char_TO_int(c);
    }

    while (est_numerique(c = getchar())) {
        Ptent = Ptent * 10.0 + char_TO_int(c);
    }

    if (c == '.') {
        i = -1;
        while (est_numerique(c = getchar())) {
            Ptdecim = Ptdecim + char_TO_int(c) * pow(10, i--);
        }
    }

    if (c == BL) c = epurer_blanc();
    if (!signe) signe = 1;
    *caractere = c;
    return ((double)(Ptent + Ptdecim) * signe);
}

void inserer_Exp_Arb(PTarbcrt *ptarbcrt, double val, char car) {
    Noeud *Nop = creer_noeud();
    Noeud *Nval = creer_noeud();
    Nop->info.caractere = car;
    Nval->info.valeur = val;

    if (!ptarbcrt->Arb) {
        Nop->fgch = Nval;
        ptarbcrt->Arb = Nop;
        ptarbcrt->crt = ptarbcrt->Arb;
    }

    if (car == '+' || car == '-') {
        ptarbcrt->crt->fdrt = Nval;
        Nop->fgch = ptarbcrt->Arb;
        ptarbcrt->Arb = Nop;
        ptarbcrt->crt = ptarbcrt->Arb;
    }
}

// Fonction pour effectuer le calcul
double Calculer_Exp(double Op1, char operateur, double Op2) {
    switch (operateur) {
        case '+': return Op1 + Op2;
        case '-': return Op1 - Op2;
        case '*': return Op1 * Op2;
        case '/':
            if (Op2 != 0) return Op1 / Op2;
            // Cas de division par 0
            printf("\nErreur: Division par 0!!");
            exit(0);
    }
}

// Fonction pour lire l'expression arithmétique
Noeud *lire_Expression_arith() {
    Noeud *Arb = NULL;
    Noeud *crt = NULL;
    PTarbcrt ptarbcrt;
    ptarbcrt = *creer_arb_general();

    char car;
    double val;
    do {
        val = lire_reel(&car);
        if (est_operateur(car)) {
            printf("*");
            inserer_Exp_Arb(&ptarbcrt, val, car);
            Arb = ptarbcrt.Arb;
            crt = ptarbcrt.crt;
        } else if (car == RC) {
            printf("entre dans car==RC\n");
            Noeud *Nval = creer_noeud();
            Nval->info.valeur = val;
            if (ptarbcrt.crt != NULL) {
                printf("*");
                ptarbcrt.crt->fdrt = Nval;
                return ((Noeud *)ptarbcrt.Arb);
            } else
                ptarbcrt.Arb = Nval;
            printf("***");
            return ((Noeud *)ptarbcrt.Arb);
        } else {
            break;
        }
    } while (1);

    // Si nous sortons de la boucle, l'expression n'est pas correcte
    printf("\nVous n'avez pas saisi une expression correcte !\n");
    return NULL;
}

// Fonction pour évaluer l'expression et effectuer le calcul total
double Evaluer_Arbre_Exp(Noeud *Arb) {
    if (Arb) {
        if (!Arb->fgch && !Arb->fdrt) return Arb->info.valeur;
        return Calculer_Exp(Evaluer_Arbre_Exp(Arb->fgch),
                            Arb->info.caractere,
                            Evaluer_Arbre_Exp(Arb->fdrt));
    }
    return 0.0; // Ajout d'une valeur par défaut pour éviter un avertissement
}

// Fonction pour afficher l'expression en notation infixée
void affichage_infixe(Noeud *Arb) {
    if (Arb) {
        affichage_infixe(Arb->fgch);
        if (Arb->info.caractere != 0) {
            printf("%c", Arb->info.caractere);
        } else {
            printf("%.3f", Arb->info.valeur);
        }
        affichage_infixe(Arb->fdrt);
    }
}

// Fonction pour libérer la mémoire allouée à l'arbre
void liberer_memoire(Noeud *Arb) {
    if (Arb) {
        liberer_memoire(Arb->fgch);
        liberer_memoire(Arb->fdrt);
        free(Arb);
    }
}

// Fonction principale
int main() {
    PTarbcrt *Arb = creer_arb_general();
    double result;

    printf("Entrer une expression arithmétique : ");
    Arb->Arb = lire_Expression_arith();

    if (Arb->Arb != NULL) {
        printf("\nExpression infixée : ");
        affichage_infixe(Arb->Arb);

        result = Evaluer_Arbre_Exp(Arb->Arb);
        printf("\nLe résultat de l'expression arithmétique est : %.3f\n", result);

        liberer_memoire(Arb->Arb); // Libérer la mémoire
    }

    free(Arb);

    return 0;
}

