#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define RC '\n'
#define BL ' '
#define PL '+'
#define MN '-'
#define ML '*'
#define DV '/'


typedef union // Definition d'une union 
{
    float operande;
    char operateur;
}Exp;

typedef struct ND // Definition de la structure d'arbre
{
    Exp info;   // champ d'information de l'arbre
    struct ND *fgc, *fdt; // pointeur de fils gauche et droit
}Noeud;
typedef struct CL // Definition de la structure de pile
{
    Exp info;   // champ d'information de la pile
    struct CL *svt; // pointeur suivant
}Cellule;


/* **********
    Nom         : CreerNoeud;
    Sorties     : Noeud *NE : le noeud cree
    Description : la fonction permet de creer un noeud et de le retourner.
********** */
Noeud *CreerNoeud()
{
    Noeud *NE;
    NE = (Noeud *)malloc(sizeof(Noeud));    // Allocation de la memoire
    if (!NE)
    {   
        printf("\nErreur d'allocation de la memoire!");
        exit(0);
    }
    NE->fgc = NE->fdt = NULL;   // Initialiser les fils au NULL
    return ((Noeud *)NE);
}
/* **********
    Nom         : CreerCellule;
    Sortie      : Cellule *CL : la cellule cree
    Description : La fonction permet de creer une cellule et de la retourner
********** */
Cellule *CreerCellule()
{
    Cellule *NE;
    NE = (Cellule *)malloc(sizeof(Cellule)); // Allocation de la memoire
    if (!NE)
    {   
        printf("\nErreur d'allocation de la memoire!");
        exit(0);
    }
    NE->svt = NULL; // Initialisation de pointeur suivant
    return ((Cellule *)NE);
}

/* **********
    Nom         : Epeurer_Blanc;
    Entrees     : char c : un caractere
    Sorties     : char c : un caractere non blanc
    Description : la fonction permet d'ignorer les blancs jusqu'a trouver un
                caractere non blanc et le retourne.
********** */
char Epeurer_Blanc(char c)
{
    return ((char)(c == BL) ? Epeurer_Blanc(getchar()):c);
}
/* **********
    Nom         : EstNumerique;
    Entrees     : char c : un caractere
    Sorties     : int : entier pour indiquer si le caractere est un chiffre
    Description : la fonction permet d'indiquer si un caractere est un 
                chiffre s'elle retourne un entier entre 0 et 9, un blanc 
                s'elle retourne 11, un point s'elle retourne 12, autre si -1.
********** */
int EstNumerique(char c)
{
    if(('0'<=c) && (c<='9')) return ((int)(c-'0')); // le caractere numerique
    if(c == ' ') return ((int)11); // le caractere est un blanc
    if(c == '.') return ((int)12); // le caractere est un point
    return ((int)(-1));
}
/* **********
    Nom         : EstOperateur;
    Entrees     : char c : un caractere
    Sorties     : int : entier pour indiquer si le caractere est un operateur
    Description : la fonction permet d'indiquer si un caractere est un 
                operateur arithmetique, elle retourne 1 si '+', 2 si '-', 3 
                si '*', 4 si '/', 0 si un retour chariot et -1 si autre.
********** */
int EstOperateur(char c)
{   
    switch (c)
    {   case RC : return ((int)0);
        case PL : return ((int)1); 
        case MN : return ((int)2); 
        case ML : return ((int)3); 
        case DV : return ((int)4); 
        default : return ((int)-1);
    }
}
/* **********
    Nom         : Transforme;
    Entrees     : float *operande : pour stoker la valeur de nombre extrait
    Sorties     : char c : le caractere non blanc apres le nombre extrait
    Description : la fonction permet d'extrait un nombre reel dans une chaine
                de caracteres saisie et retourne le caractere non blanc apres
                le nombre extrait. 
********** */
char Transforme(float *operande)
{
    int control; // pour stocker la valeur retournee par "EstNumerique(char)"
    int firstPass = 1; // pour tester la premiere lecture 
    int f = 0; // pour distinguer la partie entiere et la partie reel
    int signe = 1; // pour stocker le signe du nombre
    float result = 0; // pour stocker le nombre extrait
    char c = getchar();
    c = Epeurer_Blanc(c); // Epeurer blanc
    do
    {
        if(firstPass == 1) // Lors de la lecture du premier caractere
        { 
            firstPass = 0; // pour indiquer qu'on a lu le premier caractere
            if ((c == '-') || (c == '+'))
            {   // recuperer le signe du nombre
                if (c == '-') signe = -1; 
                c = getchar();
                continue; // passer a l'iteration suivante
            }        
        }
        control = EstNumerique(c); 
        switch (control)
        {
            case -1:
                printf("\nErreur: caractere non numerique!");
                exit(0);  
            case 11: // un blanc
                c = Epeurer_Blanc(c);
                *operande = (float)(result*signe);
                return ((char)c);  
            

case 12: // un point
                if(f == 0) // on y encore dans la partie entiere
                {
                    f = -1; // passer a la partier reel
                    break;
                }
                printf("\nErreur: un autre point est tape!");
                exit(0);
            default: // caractere numerique
                if (f == 0) result = result*10 + (float)control;
                else result += (float)((float)(control)*pow(10,f--));
        }
        c = getchar();
    } while ((c != PL) && (c != MN) && (c != ML) && (c != DV) && (c != RC));
    *operande = (float)(result*signe);
    return ((char)c);
}

/* **********
    Nom         : Construire_Arbre_Exp;
    Sorties     : Noeud *Arb : un arbre d'une expression arithmetique
    Description : la fonction permet de lire une expression arithmetique et 
                de la representee sous forme d'un arbre binaire.
********** */
Noeud *Construire_Arbre_Exp()
{
    Noeud *Arb = NULL, *NOperateur, *NOperande, *courant;
    char operateur; // pour stocker l'operateur lue
    float operande; // pour stocker l'operande extrait
    int control; // pour stocker la valeur retournee par "EstOperateur(char)" 
    int dir = 1; // pour indiquer la direction d'insertion d'un sous arbre
    printf("\nEntrer une expression arithmetique : "); 
    while ((operateur = Transforme(&operande)) != RC)
    {   
        control = EstOperateur(operateur);
        if (control == -1)
        {
            printf("\nOperateur non defini!");
            exit(0);
        }
        NOperande = CreerNoeud(); // Creer un noeud pour l'operande
        NOperande->info.operande = operande; // affecte la valeur de l'operande
        NOperateur = CreerNoeud(); // Creer un noeud pour l'operateur
        NOperateur->info.operateur = operateur; // affecter le l'operateur
        if (!Arb) // Arbre vide 
        {
            Arb = NOperateur; // l'operateur devient racine de l'arbre
            Arb->fgc = NOperande; // l'operande devient son fils gauche
            courant = Arb; // initialiser courant par la racine de l'arbre
        }
        else 
        {   // l'operande devient le fils libre de dernier operateur inserer
            if (!courant->fdt) courant->fdt = NOperande;
            else courant->fgc = NOperande;
            // si l'operateur est un '+' ou '-'
            if ((control == 1) || (control == 2))
            {   
                if (control == 1) // le cas d'un '+'
                {   
                    if (dir == 0) NOperateur->fgc = Arb;
                    else NOperateur->fdt = Arb;
                    dir = 1-dir; // changer dir pour la prochaine insertion
                }
                // cas d'un '-' l'arbre devient sous arbre gauche de l'operateur
                else NOperateur->fgc = Arb;
                Arb = NOperateur; // l'operateur devient la racine de l'arbre
            }
            else // l'operateur est '*' ou '/'
            {   // le dernier operateur inserer est '+'
                if (courant->info.operateur == PL)
                {   
                    if (dir == 0) 
                    {
                        NOperateur->fgc = Arb->fgc;
                        Arb->fgc = NOperateur;
                    }
                    else 
                    {
                        NOperateur->fgc = Arb->fdt;
                        Arb->fdt = NOperateur;
                    }
                    dir = 1 - dir; // changer dir pour la prochaine insertion
                }
                else
                {   // le dernier operateur inserer est '-'
                    if (courant->info.operateur == MN)
                    {
                        NOperateur->fgc = Arb->fdt;
                        Arb->fdt = NOperateur;
                    }
                    else // le dernier operateur inserer est '*' ou '/'
                    {   // le dernier operateur devient fils gauche
                        NOperateur->fgc = courant; 
                        if (Arb == courant) Arb = NOperateur; 
                        else Arb->fdt = NOperateur;
                    }
                }
            }
            courant = NOperateur;
        }
    }
    NOperande = CreerNoeud(); // Creer un noeud pour l'operande
    NOperande->info.operande = operande; // affecte la valeur de l'operande
    if (!Arb) return ((Noeud *)NOperande); // si l'arbre est vide
    if (!courant->fdt) courant->fdt = NOperande; 
    else courant->fgc = NOperande;
    return ((Noeud *)Arb);
}
/* **********
    Nom         : Calculer_Exp;
    Entrees     : float op1      : le premier operande 
                  char operateur : un operateur 
                  float op2      : le deuxieme operande 
    Sorties     : float result   : le resultat de l'operation 
    Description : la fonction permet d'effectuer une operation arithmetique
                de deux operandes et de retourner le resultat.
********** */
float Calculer_Exp(float Op1, char operateur, float Op2)
{
    switch (operateur)
    {
        case '+': return ((float)Op1 + Op2);
        case '-': return ((float)Op1 - Op2);
        case '*': return ((float)Op1 * Op2);
        case '/': 
            if (Op2 != 0) return ((float)Op1 / Op2);
            // Cas de division par 0
            printf("\nErreur: Division par 0!!");
            exit(0);
    }
}
/* **********
    Nom         : Evaluer_Arbre_Exp;
    Entrees     : Noeud *Arb : la racine de l'arbre 
    Sorties     : float      : le resultat d'evaluation de l'expression 
                arithmetique 
    Description : la fonction permet d'evaluer l'expression arithmetique qui 
                est represente sous forme d'un arbre binaire en effectuant un
                parcour infixe de l'arbre.
********** */
float Evaluer_Arbre_Exp(Noeud *Arb)
{
    if (Arb)
    {
        if (!Arb->fgc && !Arb->fdt) return ((float)Arb->info.operande);
        return ((float)Calculer_Exp(Evaluer_Arbre_Exp(Arb->fgc),
                                    Arb->info.operateur,
                                    Evaluer_Arbre_Exp(Arb->fdt)));
    }
}

/* **********
    Nom         : Empiler;
    Entrees     : Cellule *pile : une pile
                  Cellule *cell : la cellule a inserer
    Sorties     : Cellule *pile : la pile apres l'insertion de cell 
    Description : la fonction permet d'inserer une cellule au sommet de la pile
********** */
Cellule *Empiler(Cellule *pile, Cellule *cell)
{
    cell->svt = pile;
    pile = cell;
    return ((Cellule *)pile);
}
/* **********
    Nom         : Depiler;
    Entrees     : Cellule *pile : une pile
                  Cellule *cell[1] : pour recuperer le sommet
    Sorties     : Cellule *pile : la pile apres la recuperation du sommet
    Description : la fonction permet de recuperer le sommet de la pile
********** */
Cellule *Depiler(Cellule *pile, Cellule *cell[1])
{
    cell[0] = pile;
    if (!pile) return ((Cellule *)NULL);
    pile = pile->svt;
    return ((Cellule *)pile);
}

/* **********
    Nom         : Evaluer_Operation_Pile;
    Entrees     : Cellule *pile : une pile
    Sorties     : Cellule *pile : la pile apres la recuperation du sommet
    Description : la fonction permet de calculer une operation dans la pile
                en depilant l'operande, l'operateur et le deuxieme operande
                puis enpile le resultat dans la pile.
********** */
Cellule *Evaluer_Operation_Pile(Cellule *pile)
{
    Cellule *cell[1];
    float op1, op2, result;
    char operateur;
    if (!pile) return ((Cellule *)NULL);
    pile = Depiler(pile,cell); // Depiler le premier operande
    op1 = cell[0]->info.operande; // le premier operande
    free(cell[0]); // liberer la memoire
    pile = Depiler(pile,cell); // Depiler l'operateur
    operateur = cell[0]->info.operateur; // l'operateur
    free(cell[0]); // liberer la memoire
    pile = Depiler(pile,cell); // Depiler le deuxieme operande
    op2 = cell[0]->info.operande; // le deuxieme operande
    free(cell[0]); // liberer la memoire
    result = Calculer_Exp(op1,operateur,op2); // Effectuer le calcul
    pile = Empiler(pile,CreerCellule()); // Empiler une cellule dans la pile
    pile->info.operande = result; // Affecter le resultat au sommet de la pile
    return ((Cellule *)pile); 
}
int est_num_Un(Exp elem)
{//si elem est un operateur retourner 0
    if((elem.operateur=='+')||(elem.operateur=='*')||(elem.operateur=='/')||(elem.operateur=='-'))
        return 0;
    return 1;
}//fin

/* **********
    Nom         : Expression_Arithmetique_Pile;
    Sorties     : Cellule *pile : une pile contient une expression arithmetique
    Description : la fonction permet de lire une expression arithmetique et 
                de la representee sous forme d'une pile.
********** */
Cellule *Expression_Arithmetique_Pile()
{
    Cellule *pile = NULL, *NE;
    char operateur;
    float operande;
    int control;
    printf("\nEntrer une expression arithmetique : "); 
    do
    {
        operateur = Transforme(&operande);
        control = EstOperateur(operateur);
        if (control == -1) 
        {
            printf("\nErreur: Operateur non valide!");
            exit(0);
        }
        NE = CreerCellule(); // Creer une cellule pour l'operande
        NE->info.operande = operande; // affecter l'operande
        pile = Empiler(pile,NE); 
        if (control != 0)
        {   // Si on n'a pas encore arriver a la fin de l'expression
            NE = CreerCellule(); // Creer une cellule pour l'operateur
            NE->info.operateur = operateur; // Affecter l'operateur
            pile = Empiler(pile,NE);
        }
    } while (operateur != RC);
    return ((Cellule *)pile);
}

/* **********
    Nom         : Evaluer_Pile_Exp;
    Entrees     : Cellule *pile : une pile
    Sorties     : le resultat d'evaluation de l'expression arithmetique
    Description : la fonction permet d'evaluer l'expression arithmetique qui 
                est represente sous forme d'une pile.
********** */
float Evaluer_Pile_Exp(Cellule *pile)
{
    Cellule *tmp = NULL, *cell[1];
    char operateur;
    if (!pile)  // pile vide
    {
        printf("\nPile vide!!");
        return ((float)0);
    }
    // Depiler le premier operande dans la pile et l'empiler dans tmp
    pile = Depiler(pile,cell);
    tmp = Empiler(tmp,cell[0]);
    while (pile) // Tant que la pile n'est pas vide
    {
        // Depiler l'operateur de la pile et l'empiler dans la pile tmp
        pile = Depiler(pile,cell);
        tmp = Empiler(tmp,cell[0]);
        operateur = cell[0]->info.operateur; // Garder l'operateur
        // Depiler le deuxieme operande de la pile et l'empiler dans tmp
        pile = Depiler(pile,cell);
        tmp = Empiler(tmp,cell[0]);
        if (pile)
        {
            if (pile->info.operateur == PL)
            {   // Effectuer le calcule de toutes les operations dans la pile tmp
                while (tmp->svt) tmp = Evaluer_Operation_Pile(tmp);
            }
            else if (pile->info.operateur != DV)
            {
                while (tmp->svt)
                {   // Effectuer le calcule jusqu'a l'operateur '+' ou '-' 
                    if ((tmp->svt->info.operateur == PL) || 
                        (tmp->svt->info.operateur == MN)) break;
                    tmp = Evaluer_Operation_Pile(tmp);
                }
            }
        }
    }
    // Effectuer toutes les operations restantes dans la pile tmp
    while (tmp->svt) tmp = Evaluer_Operation_Pile(tmp);
    return ((float)tmp->info.operande);
}



//void AffichageHorizental(Noeud *Arb,int n) {
//    if (Arb) {
//        AffichageHorizental(Arb->fgc,n+1);
//        printf("\n");
//        for(int i=0;i<n;i++)  printf("\t");
//        if (!Arb->fgc && !Arb->fdt) printf("%.2f ", Arb->info.operande);
//    else printf("%c ", Arb->info.operateur);
//		AffichageHorizental(Arb->fdt,n+1);
//    }
//}

void AffichageHorizental(Noeud *monArb, int niveau)

{
int i=0;
// afficher le sous arbre droit
if (monArb->fdt) AffichageHorizental(monArb->fdt, niveau + 1);
// afficher la racine
for (i=0; i < niveau; i++)
{
printf("\t\t");
}
// c'est c'est un flottant
if(est_num_Un(monArb->info))
printf("%.3f\n", monArb->info.operande);
// sinon
else printf("%c\n", monArb->info.operateur);
// afficher le sous arbre gauche de la meme maniere
if (monArb->fgc) AffichageHorizental(monArb->fgc, niveau+1 );
}


int main() {
    // Construire l'arbre à partir de l'expression arithmétique
    Noeud *Arbre = Construire_Arbre_Exp();

    // Affichage de l'arbre
    printf("\nAffichage de l'arbre : \n");
    AffichageHorizental(Arbre,0);
    printf("\n");

    // Évaluation de l'expression à l'aide de l'arbre
    float resultat_arbre = Evaluer_Arbre_Exp(Arbre);
    printf("Le résultat de l'expression avec l'arbre est : %.2f\n", resultat_arbre);

    // L'évaluation de l'expression à l'aide de la pile
    Cellule *pile_expression = Expression_Arithmetique_Pile();
    float resultat_pile = Evaluer_Pile_Exp(pile_expression);
    printf("Le résultat de l'expression avec la pile est : %.2f\n", resultat_pile);

    return 0;
}
