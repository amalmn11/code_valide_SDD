#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RC '\n'
#define BL ' '
#define PL '+'
#define MN '-'
#define ML '*'
#define DV '/'

typedef union // Définition d'un union
{
float val; // champ de l'opérande
char op; // champ de l'opérateur
}Element;

typedef struct Cel // Définition de la structure de pile
{
	Element elem; // champ d'information de la pile
struct Cel *svt; // pointeur sur la cellule suivante
}Cellule,PTPILE;

/* **************************************************************************
Nom : epurer_blanc
Sortie : Un caractère de type char
Description : Elle renvoie le premier caractère non blanc rencontré après avoir épuré les espaces
************************************************************************** */
char epurer_blanc()
{
char carac;
while( (carac = getchar())==BL );
return ((char)carac);
}//fin fonction epurer_blanc
/* **************************************************************************
Nom : char_TO_int
Entrée : un caractère
Sortie : l'entier équivalent au caractère
Description: fonction qui transforme un caractère en entier
************************************************************************** */
int char_TO_int(char car)
{
return ( (int)( car - '0' ) );
}//fin de la fonction char_TO_int
/* **************************************************************************
Nom : est_signe
13
Entrée : un caractère
Sortie : un entier
Description: Elle renvoie -1 si le caractère est -, 1 s'il est +, et 0 sinon
************************************************************************** */
int est_signe(char car)
{
switch(car)
{
case MN : return( (int) -1 );
case PL : return( (int) 1 );
default : return( (int) 0 );
}
}//fin de la fonction est_signe
/* **************************************************************************
Nom : est_op
Entrée : un caractère de type char
Sortie : Un entier indiquant le type d'opérateur
Description : Les valeurs de retour indiquent le type d'opérateur ou la fin de l'expression
arithmétique.
Si le caractère n'est pas un opérateur valide, la fonction renvoie -1 pour signaler une erreur
************************************************************************** */
int est_op(char car)
{
switch(car)
{
case MN :return((int) 1);
case PL :return((int) 2);
case ML :return((int) 3);
case DV :return((int) 4);
case RC :return((int) 5);
default : return ((int) -1);
}

}//Fin de la fonction est_op(char car)


/* **************************************************************************
Nom : est_numerique
Entrée : Un caractère de type char
Sortie : Un entier (1 ou 0)
Description : Elle renvoie 1 si le caractère est un chiffre numérique (0 à 9) sinon elle renvoie 0
************************************************************************** */
int est_numerique(char car)
{
return ((int)(('0'<=car)&&(car<='9')));

}//Fin de la fonction estNumerique


/* **************************************************************************
Nom : lire_operande
Entrée : float *operande : un pointeur sur le réel qui va être lu
Sortie : un nombre réel de type float (opérande) , type d'opération effectuée (+,-,*,/)
Description : La fonction calcule la valeur finale du nombre réel en combinant la partie entière et la
partie décimale avec le signe approprié, puis récupère le caractère suivant qui représente le type
d'opération à effectuer (+,-,*,/)
************************************************************************** */
char lire_operande(float *operande)
{
char c;// variable stocke le caractère lu au clavier
int i; // i : indice pour calculer la partie décimale de réel
int signe; // variable stocke la valeur de retour de est_signe(char car)
float Ptdecim=0.0;// pour stocker la partie entière de réel
float Ptent=0.0; // pour stocker la partie décimale de réel
c=epurer_blanc(); //lire le premier caractère
if(c == RC)//cas d'erreur , Rc apres un opérateur
{
/*on sort du programme car le dernier élément est un opérateur, tandis qu’il doit être
un opérande!!*/
printf("\nError: tu n'a pas entrer un caractère valide!");
exit(0);
}
//traiter le signe
if(!(signe = est_signe(c)))
{
if(est_numerique(c))
Ptent=Ptent*10.0+char_TO_int(c);
}//fin if (!(signe = est_signe(c)))
//traitement la partie entière
while(est_numerique(c=getchar()))
{
Ptent=Ptent*10.0+char_TO_int(c);

}//Fin while(est_numerique(c=getchar()))
//traitement de la partie decimale
if(c == '.')
{
	i= -1;
	while(est_numerique(c=getchar()))
	{
			Ptdecim=Ptdecim + char_TO_int(c)*pow(10,i--);
	}//Fin while(est_numerique(c=getchar()))
}//Fin if(c == '.')
if(c == BL) c=epurer_blanc();
if(!signe) signe =1;
*operande = (float)((Ptent+Ptdecim)*signe);
return((char) c);
}//Fin de la fonction lire_operande(float *operande)
/* **************************************************************************
Nom : calculer_exp
Entree : premier opérande : réel ,opérateur (+,-,/,*) : caractère, et deuxième opérande:réel
Sortie :Le résultat de l'opération entre les 2 opérandes en fonction de l'opérateur
************************************************************************** */
float calculer_exp(float val1, char op, float val2)
{
switch (op)
{
case PL: return ((float)(val1 + val2));
case MN: return ((float)(val1 - val2));
case ML: return ((float)(val1* val2));
case DV: if (val2 != 0) return ((float)(val1 / val2));
// Cas de division par 0
printf("\nErreur: Division par 0!!");
exit(0);
}

}

/* **************************************************************************
Nom : creer_cel_val
Entrée : une valeur réelle stocker dans la cellule
Sortie : Un pointeur vers la nouvelle cellule de pile créée
Description : La fonction alloue dynamiquement de la mémoire pour une nouvelle cellule de pile,
initialise le champ elem.val avec la valeur fournie, et retourne un pointeur vers cette nouvelle cellule
************************************************************************** */
PTPILE* creer_cel_val(float val)
{
PTPILE *ne;
ne = ( PTPILE *)malloc(sizeof( PTPILE ));
if(!ne) return (( PTPILE *) NULL);
ne->svt=NULL;
ne->elem.val= val;
return (( PTPILE *) ne);
}// Fin de la fonction creer_cel_val
/* **************************************************************************
Nom : creer_cel_op
Entrée : Le caractère représentant un opérateur
Sortie : Un pointeur vers la nouvelle cellule de pile créée
Description :La fonction alloue dynamiquement de la mémoire pour une nouvelle
cellule de pile, initialise le champ elem.op avec le caractère d'opérateur fourni,
et retourne un pointeur vers cette nouvelle cellule
************************************************************************** */
PTPILE* creer_cel_op(char op)
{
PTPILE *ne;
ne = (PTPILE*)malloc(sizeof(PTPILE));
if(!ne) return ((PTPILE*) NULL);
ne->svt=NULL;
ne->elem.op= op;

return ((PTPILE*) ne);
}//Fin de la fonction creer_cel_op
/* **************************************************************************
Nom : empiler
Entrée : Un pointeur vers la pile existante , et Un vers la nouvelle cellule de pile à empiler
Sortie : Un pointeur vers la pile mise à jour après l'empilement
************************************************************************** */
PTPILE* empiler(PTPILE* pile,PTPILE* NE)
{
NE->svt = pile;
pile = NE;
return ((PTPILE *)pile);
} //Fin fonction empiler
/* **************************************************************************
Nom : depiler
Entrée : Un pointeur vers la pile existante
Sortie : Un pointeur vers la pile mise à jour après le dépilement
************************************************************************** */
PTPILE *depiler(PTPILE*pile)
{
if (!pile) return ((PTPILE *)NULL);
pile = pile->svt;
return ((PTPILE *)pile);
} //Fin de la fonction depiler
/* **************************************************************************
Nom : Depiler
Entrée : Pointeur vers la pile
Sortie :Nouveau pointeur vers le sommet de la pile après dépilement
Description :La fonction Depiler permet de retirer le sommet de la pile et le récupérer
************************************************************************** */

PTPILE *Depiler(PTPILE *pile,PTPILE *sommet_rec[1])
{
sommet_rec[0] = pile;
if (!pile) return ((PTPILE *)NULL);
pile = pile->svt;
return ((PTPILE *)pile);
}//Fin fonction Depiler
/* **************************************************************************
Nom : construire_pile
Entrée : aucune
Sortie : Un pointeur vers la pile qui contient les opérandes et opérateurs de l'expression
arithmétique.
Description : permet à l'utilisateur de saisir une expression arithmétique tout en stockant les
opérandes et opérateurs dans une pile.
************************************************************************** */
PTPILE *construire_pile()
{
PTPILE *pile = NULL, *ne;
char operateur; //représente l'opérateur lu
float operande; //représente l'opérande lu
int garde; //pour vérifier si un opérateur est valide
printf("\nEntrer une expression arithmétique : ");
do
{
// Lecture de l'opérande et de l'opérateur
operateur = lire_operande(&operande);
garde = est_op(operateur);
if (garde == -1)
{
printf("\nErreur: Operateur non valide!");
exit(0);
}//Fin if if (garde == -1)
//creer cellule pour opérande

ne = creer_cel_val(operande);
pile = empiler(pile,ne);
if (operateur!=RC)
{ //c'est pas la fin d'expression arithmétique
//créer cellule pour opérateur
ne = creer_cel_op(operateur);
pile = empiler(pile,ne);
}//Fin if (operateur!=RC)
} while (operateur != RC);
return ((PTPILE *)pile);
}//Fin fonction saisit_stockage_expression
/* **************************************************************************
Nom : evaluer_une_operation
Entrée : une pile initiale
Sortie : une pile résultante
Description : effectue l'évaluation d'une opération arithmétique sur les deux opérandes
au sommet de la pile et l'opérateur correspondant, puis empile le résultat de cette évaluation
************************************************************************** */
PTPILE *evaluer_une_operation(PTPILE *pile)
{
//Déclaration d'une variable pour stocker la cellule dépilée
PTPILE *est_recuperee;
//Déclaration des variables pour les opérandes, l'opérateur et le résultat de l'évaluation
float oper1,oper2,evaluation;
char operateur;
//Vérification si la pile est nulle
if (!pile) return ((PTPILE *)NULL);
//Dépiler la pile pour récupérer le premier opérande
pile = Depiler(pile, &est_recuperee);
oper1 = est_recuperee->elem.val;
//Dépiler la pile pour récupérer l'opérateur
pile = Depiler(pile, &est_recuperee);
operateur = est_recuperee->elem.op;

//Dépiler la pile pour récupérer le deuxième opérande
pile = Depiler(pile, &est_recuperee);
oper2 = est_recuperee->elem.val;
//Calculer le résultat de l'opération
evaluation = calculer_exp(oper1, operateur, oper2);
// Empiler le résultat de l'évaluation
pile = empiler(pile, creer_cel_val(evaluation));
return ((PTPILE *)pile);
} //Fin fonction evaluer_une_operation
/* **************************************************************************
Nom : Evaluer_Exp_Pile
Entrée : Pile dont on a chargée l'expression arithmétique
Sortie : résultat d'évaluation de l'expression arithmétique
Description : la fonction dépile les opérandes et les opérateurs, les empile dans une pile
temporaire, et effectue les calculs en respectant la priorité des opérations. Le résultat
final est retourné en tant que nombre à virgule flottante
************************************************************************** */
float Evaluer_Exp_Pile(PTPILE *pile)
{
PTPILE *pile_temporaire = NULL, *est_recuperee;
char operateur;
// Vérifier si la pile est vide
if (!pile)
{
printf("\nPile vide!!");
return 0.0;
}//Fin if(!pile)
// Dépiler le premier opérande dans la pile et l'empile dans la pile temporaire
pile = Depiler(pile, &est_recuperee);
pile_temporaire = empiler(pile_temporaire, est_recuperee);
while (pile) // Tant que la pile n'est pas vide
{

// Dépiler l'opérateur de la pile et l'empile dans la pile temporaire
pile = Depiler(pile, &est_recuperee);
pile_temporaire = empiler(pile_temporaire, est_recuperee);
operateur = est_recuperee->elem.op; // Garder l'opérateur
// Dépiler le deuxième opérande de la pile et l'empile dans la pile temporaire
pile = Depiler(pile, &est_recuperee);
pile_temporaire = empiler(pile_temporaire, est_recuperee);
if (pile)
{
// Traiter les opérations selon la priorité des opérateurs
if (pile->elem.op == '+')
{
// Évaluer toutes les opérations dans la pile temporaire
while (pile_temporaire->svt)
pile_temporaire = evaluer_une_operation(pile_temporaire);
}//Fin if (pile->elem.op == '+')
else if (pile->elem.op != '/')
{
// Évaluer les opérations jusqu'à l'opérateur '+' ou '-'
while (pile_temporaire->svt)
{
if ((pile_temporaire->svt->elem.op == '+') ||
(pile_temporaire->svt->elem.op == '-'))
break;
pile_temporaire = evaluer_une_operation(pile_temporaire);
}//Fin while (pile_temporaire->svt)
}//Fin else if (pile->elem.op != '/')
}//Fin if (pile)
}//Fin while (pile)
// Évaluer toutes les opérations restantes dans la pile temporaire
while (pile_temporaire->svt)
pile_temporaire = evaluer_une_operation(pile_temporaire);

// Retourner le résultat final
return (float)pile_temporaire->elem.val;
}//Fin fonction Evaluer_Exp_Pile
/* **************************************************************************
Nom : afficher_pile
Entree : Pointeur vers la pile à afficher
Sortie : Affichage de la pile
Description: la fonction est utilisée pour visualiser les éléments d'une pile,
tels que des valeurs en virgule flottante et des opérateurs.
************************************************************************** */
void afficher_pile(PTPILE *pile)
{
PTPILE *tmp = pile;
while (tmp != NULL)
{
// Affichage de la valeur float
if (est_op(tmp->elem.op) == -1)
printf("|%3.2f|\n", tmp->elem.val);
// Affichage de l'opérateur
else
printf("|%5c|\n", tmp->elem.op);
tmp = tmp->svt;
}//Fin while (tmp != NULL)
}//Fin fonction afficher_pile



int main()
{

    // Construire la pile d'expression
    PTPILE *pile = construire_pile();

    // Afficher la pile d'expression
    printf("\nPile d'expression :\n");
    afficher_pile(pile);

    // Évaluer l'expression à l'aide de la pile
    float resultat = Evaluer_Exp_Pile(pile);
    printf("\nResultat de l'expression avec la pile : %.2f\n", resultat);

    return 0;
}

