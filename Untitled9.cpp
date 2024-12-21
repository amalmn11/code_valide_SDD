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

typedef struct ND {
    valeur info;
    struct ND *fgch;
    struct ND *fdrt;
} Noeud;

// Prototypes de fonctions
Noeud *creer_noeud();
char epurer_blanc();
int est_signe(char c);
int est_numerique(char car);
int char_TO_int(char c);
int est_operateur(char car);
double lire_reel(char *caractere);
Noeud *inserer_Exp_Arb(Noeud *Arb, double val, char car);
double Calculer_Exp(double Op1, char operateur, double Op2);
Noeud *lire_Expression_arith();
double Evaluer_Arbre_Exp(Noeud *Arb);
void liberer_memoire(Noeud *Arb);
void afficher_infixe(Noeud *Arb);

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
    return car == '+' || car == '/' || car == '-' || car == '*';
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
    if (c == RC || est_operateur(c)) {
        *caractere = c;
        return (Ptent + Ptdecim) * signe;
    }

    printf("\nErreur");
    return -1;
}

//// Fonction pour insérer les éléments dans l'arbre
//Noeud *inserer_Exp_Arb(Noeud *Arb, double val, char car) {
//    Noeud *Nop = creer_noeud();
//    Noeud *Nval = creer_noeud();
//    Nop->info.caractere = car;
//    Nval->info.valeur = val;
//
//    if (!Arb) {
//        Nop->fgch = Nval;
//        Arb = Nop;
//        return Arb;
//    }
//
//    if (car == '+' || car == '-') {
//        Nop->fgch = Arb;
//        Arb = Nop;
//        return Arb;
//    }
//
//    if (car == '*' || car == '/') {
//        Noeud *crt = Arb;
//        while (crt->fdrt) {
//            if (crt->info.caractere == '+' || crt->info.caractere == '-' || crt->info.caractere == '*' || crt->info.caractere == '/') {
//                Nop->fgch = crt->fdrt;
//                crt->fdrt = Nop;
//                return Arb;
//            }
//            crt = crt->fgch;
//        }
//        Nop->fgch = crt;
//        crt->fdrt = Nop;
//        return Arb;
//    }
//
//    return Arb;
//}

Noeud *inserer_Exp_Arb(Noeud *Arb, double val, char car)
{
    Noeud *Nop = creer_noeud();
    Noeud *Nval = creer_noeud();
    Nop->info.caractere = car;
    Nval->info.valeur = val;

    if (!Arb)
    {
        Nop->fgch = Nval;
        Arb = Nop;
        return Arb;
    }

    if (car == '+' || car == '-')
    {
        Nop->fgch = Arb;
        Arb = Nop;
        return Arb;
    }

    if (car == '*' || car == '/')
    {
        Noeud *crt = Arb;
        while (crt->fdrt && (crt->info.caractere == '+' || crt->info.caractere == '-' || crt->info.caractere == '*' || crt->info.caractere == '/'))
        {
            Nop->fgch = crt->fdrt;
            crt->fdrt = Nop;
            return Arb;
        }
        Nop->fgch = crt->fgch;
        crt->fgch = Nop;
        return Arb;
    }

    return Arb;
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
    char car;
    double val;
    do {
        val = lire_reel(&car);
        if (est_operateur(car)) {
            Arb = inserer_Exp_Arb(Arb, val, car);
        } else break;
    } while (car != RC);

    if (car != RC) {
        printf("\nVous n'avez pas saisi l'expression correctement !");
    } else {
        printf("\nBravo ! Vous avez saisi l'expression correctement");
    }

    return Arb;
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
//void afficher_infixe(Noeud *Arb) {
//    if (Arb) {
//        if (Arb->fgch || Arb->fdrt) {
//            printf("(");
//            afficher_infixe(Arb->fgch);
//            printf(" %c ", Arb->info.caractere);
//            afficher_infixe(Arb->fdrt);
//            printf(")");
//        } else {
//            printf("%.3f", Arb->info.valeur);
//        }
//    }
//}

void affichage_infixe(Noeud *Arb)
{
    if (Arb)
    {
        affichage_infixe(Arb->fgch);
        if (Arb->info.caractere != 0)
        {
            printf("%c ", Arb->info.caractere);
        }
        else
        {
            printf("%.3f ", Arb->info.valeur);
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
    Noeud *Arb = NULL;
    double result;

    printf("Entrer une expression arithmétique : ");
    Arb = lire_Expression_arith();

    printf("\nExpression infixée : ");
    afficher_infixe(Arb);

    result = Evaluer_Arbre_Exp(Arb);
    printf("\nLe résultat de l'expression arithmétique est : %.3f\n", result);

    liberer_memoire(Arb); // Libérer la mémoire

    return 0;
}

