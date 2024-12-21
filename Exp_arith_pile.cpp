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

typedef struct CL // Definition de la structure de pile
{
    Exp info;   // champ d'information de la pile
    struct CL *svt; // pointeur suivant
}Cellule;

/* **************************************************************************
    Nom         : CreerCellule;
    Sortie      : Cellule *CL : la cellule cree
    Description : La fonction permet de creer une cellule et de la retourner
************************************************************************** */
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
/* **************************************************************************
    Nom         : Empiler;
    Entrees     : Cellule *pile : une pile
                  Cellule *cell : la cellule a inserer
    Sorties     : Cellule *pile : la pile apres l'insertion de cell 
    Description : la fonction permet d'inserer une cellule au sommet de la pile
************************************************************************** */
Cellule *Empiler(Cellule *pile, Cellule *cell)
{
    cell->svt = pile;
    pile = cell;
    return ((Cellule *)pile);
}

/* **************************************************************************
    Nom         : Depiler;
    Entrees     : Cellule *pile : une pile
                  Cellule *cell[1] : pour recuperer le sommet
    Sorties     : Cellule *pile : la pile apres la recuperation du sommet
    Description : la fonction permet de recuperer le sommet de la pile
************************************************************************** */
Cellule *Depiler(Cellule *pile, Cellule *cell[1])
{
    cell[0] = pile;
    if (!pile) return ((Cellule *)NULL);
    pile = pile->svt;
    return ((Cellule *)pile);
}

/* **************************************************************************
    Nom         : EstOperateur;
    Entrees     : char c : un caractere
    Sorties     : int : entier pour indiquer si le caractere est un operateur
    Description : la fonction permet d'indiquer si un caractere est un 
                operateur arithmetique, elle retourne 1 si '+', 2 si '-', 3 
                si '*', 4 si '/', 0 si un retour chariot et -1 si autre.
************************************************************************** */
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

/* **************************************************************************
    Nom         : Epeurer_Blanc;
    Entrees     : char c : un caractere
    Sorties     : char c : un caractere non blanc
    Description : la fonction permet d'ignorer les blancs jusqu'a trouver un
                caractere non blanc et le retourne.
************************************************************************** */
char Epeurer_Blanc(char c)
{
    return ((char)(c == BL) ? Epeurer_Blanc(getchar()):c);
}

/* **************************************************************************
    Nom         : EstNumerique;
    Entrees     : char c : un caractere
    Sorties     : int : entier pour indiquer si le caractere est un chiffre
    Description : la fonction permet d'indiquer si un caractere est un 
                chiffre s'elle retourne un entier entre 0 et 9, un blanc 
                s'elle retourne 11, un point s'elle retourne 12, autre si -1.
************************************************************************** */
int EstNumerique(char c)
{
    if(('0'<=c) && (c<='9')) return ((int)(c-'0')); // le caractere numerique
    if(c == ' ') return ((int)11); // le caractere est un blanc
    if(c == '.') return ((int)12); // le caractere est un point
    return ((int)(-1));
}


/* **************************************************************************
    Nom         : Transforme;
    Entrees     : float *operande : pour stoker la valeur de nombre extrait
    Sorties     : char c : le caractere non blanc apres le nombre extrait
    Description : la fonction permet d'extrait un nombre reel dans une chaine
                de caracteres saisie et retourne le caractere non blanc apres
                le nombre extrait. 
************************************************************************** */
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

/* **************************************************************************
    Nom         : Calculer_Exp;
    Entrees     : float op1      : le premier operande 
                  char operateur : un operateur 
                  float op2      : le deuxieme operande 
    Sorties     : float result   : le resultat de l'operation 
    Description : la fonction permet d'effectuer une operation arithmetique
                de deux operandes et de retourner le resultat.
************************************************************************** */
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


/* **************************************************************************
    Nom         : Evaluer_Operation_Pile;
    Entrees     : Cellule *pile : une pile
    Sorties     : Cellule *pile : la pile apres la recuperation du sommet
    Description : la fonction permet de calculer une operation dans la pile
                en depilant l'operande, l'operateur et le deuxieme operande
                puis enpile le resultat dans la pile.
************************************************************************** */
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

/* **************************************************************************
    Nom         : Expression_Arithmetique_Pile;
    Sorties     : Cellule *pile : une pile contient une expression arithmetique
    Description : la fonction permet de lire une expression arithmetique et 
                de la representee sous forme d'une pile.
************************************************************************** */
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

/* **************************************************************************
    Nom         : Evaluer_Pile_Exp;
    Entrees     : Cellule *pile : une pile
    Sorties     : le résultat d'évaluation de l'expression arithmetique
    Description : la fonction permet d'evaluer l'expression arithmetique qui 
                est représenté sous forme d'une pile.
************************************************************************** */
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


int main() {
    Cellule *pileExpression;
    float resultatExpression;

    // Appel de la fonction pour construire la pile d'expression
    pileExpression = Expression_Arithmetique_Pile();

    // Appel de la fonction pour évaluer l'expression en utilisant la pile
    resultatExpression = Evaluer_Pile_Exp(pileExpression);

    // Affichage du résultat
    printf("\nLe resultat de l'expression est : %f\n", resultatExpression);

    // Libération de la mémoire allouée pour la pile
    // (à ajouter selon les besoins de votre programme)

    return 0;
}





