#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RC '\n'
#define BL ' '
#define PL '+'
#define MN '-'
#define ML '*'
#define DV '/'

typedef union // D�finition d'un union
{
float val; // champ de l'op�rande
char op; // champ de l'op�rateur
}Element;

typedef struct Cel // D�finition de la structure de pile
{
	Element elem; // champ d'information de la pile
struct Cel *svt; // pointeur sur la cellule suivante
}Cellule,PTPILE;

/* **************************************************************************
Nom : epurer_blanc
Sortie : Un caract�re de type char
Description : Elle renvoie le premier caract�re non blanc rencontr� apr�s avoir �pur� les espaces
************************************************************************** */
char epurer_blanc()
{
char carac;
while( (carac = getchar())==BL );
return ((char)carac);
}//fin fonction epurer_blanc
/* **************************************************************************
Nom : char_TO_int
Entr�e : un caract�re
Sortie : l'entier �quivalent au caract�re
Description: fonction qui transforme un caract�re en entier
************************************************************************** */
int char_TO_int(char car)
{
return ( (int)( car - '0' ) );
}//fin de la fonction char_TO_int
/* **************************************************************************
Nom : est_signe
13
Entr�e : un caract�re
Sortie : un entier
Description: Elle renvoie -1 si le caract�re est -, 1 s'il est +, et 0 sinon
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
Entr�e : un caract�re de type char
Sortie : Un entier indiquant le type d'op�rateur
Description : Les valeurs de retour indiquent le type d'op�rateur ou la fin de l'expression
arithm�tique.
Si le caract�re n'est pas un op�rateur valide, la fonction renvoie -1 pour signaler une erreur
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
Entr�e : Un caract�re de type char
Sortie : Un entier (1 ou 0)
Description : Elle renvoie 1 si le caract�re est un chiffre num�rique (0 � 9) sinon elle renvoie 0
************************************************************************** */
int est_numerique(char car)
{
return ((int)(('0'<=car)&&(car<='9')));

}//Fin de la fonction estNumerique


/* **************************************************************************
Nom : lire_operande
Entr�e : float *operande : un pointeur sur le r�el qui va �tre lu
Sortie : un nombre r�el de type float (op�rande) , type d'op�ration effectu�e (+,-,*,/)
Description : La fonction calcule la valeur finale du nombre r�el en combinant la partie enti�re et la
partie d�cimale avec le signe appropri�, puis r�cup�re le caract�re suivant qui repr�sente le type
d'op�ration � effectuer (+,-,*,/)
************************************************************************** */
char lire_operande(float *operande)
{
char c;// variable stocke le caract�re lu au clavier
int i; // i : indice pour calculer la partie d�cimale de r�el
int signe; // variable stocke la valeur de retour de est_signe(char car)
float Ptdecim=0.0;// pour stocker la partie enti�re de r�el
float Ptent=0.0; // pour stocker la partie d�cimale de r�el
c=epurer_blanc(); //lire le premier caract�re
if(c == RC)//cas d'erreur , Rc apres un op�rateur
{
/*on sort du programme car le dernier �l�ment est un op�rateur, tandis qu�il doit �tre
un op�rande!!*/
printf("\nError: tu n'a pas entrer un caract�re valide!");
exit(0);
}
//traiter le signe
if(!(signe = est_signe(c)))
{
if(est_numerique(c))
Ptent=Ptent*10.0+char_TO_int(c);
}//fin if (!(signe = est_signe(c)))
//traitement la partie enti�re
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
Entree : premier op�rande : r�el ,op�rateur (+,-,/,*) : caract�re, et deuxi�me op�rande:r�el
Sortie :Le r�sultat de l'op�ration entre les 2 op�randes en fonction de l'op�rateur
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
Entr�e : une valeur r�elle stocker dans la cellule
Sortie : Un pointeur vers la nouvelle cellule de pile cr��e
Description : La fonction alloue dynamiquement de la m�moire pour une nouvelle cellule de pile,
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
Entr�e : Le caract�re repr�sentant un op�rateur
Sortie : Un pointeur vers la nouvelle cellule de pile cr��e
Description :La fonction alloue dynamiquement de la m�moire pour une nouvelle
cellule de pile, initialise le champ elem.op avec le caract�re d'op�rateur fourni,
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
Entr�e : Un pointeur vers la pile existante , et Un vers la nouvelle cellule de pile � empiler
Sortie : Un pointeur vers la pile mise � jour apr�s l'empilement
************************************************************************** */
PTPILE* empiler(PTPILE* pile,PTPILE* NE)
{
NE->svt = pile;
pile = NE;
return ((PTPILE *)pile);
} //Fin fonction empiler
/* **************************************************************************
Nom : depiler
Entr�e : Un pointeur vers la pile existante
Sortie : Un pointeur vers la pile mise � jour apr�s le d�pilement
************************************************************************** */
PTPILE *depiler(PTPILE*pile)
{
if (!pile) return ((PTPILE *)NULL);
pile = pile->svt;
return ((PTPILE *)pile);
} //Fin de la fonction depiler
/* **************************************************************************
Nom : Depiler
Entr�e : Pointeur vers la pile
Sortie :Nouveau pointeur vers le sommet de la pile apr�s d�pilement
Description :La fonction Depiler permet de retirer le sommet de la pile et le r�cup�rer
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
Entr�e : aucune
Sortie : Un pointeur vers la pile qui contient les op�randes et op�rateurs de l'expression
arithm�tique.
Description : permet � l'utilisateur de saisir une expression arithm�tique tout en stockant les
op�randes et op�rateurs dans une pile.
************************************************************************** */
PTPILE *construire_pile()
{
PTPILE *pile = NULL, *ne;
char operateur; //repr�sente l'op�rateur lu
float operande; //repr�sente l'op�rande lu
int garde; //pour v�rifier si un op�rateur est valide
printf("\nEntrer une expression arithm�tique : ");
do
{
// Lecture de l'op�rande et de l'op�rateur
operateur = lire_operande(&operande);
garde = est_op(operateur);
if (garde == -1)
{
printf("\nErreur: Operateur non valide!");
exit(0);
}//Fin if if (garde == -1)
//creer cellule pour op�rande

ne = creer_cel_val(operande);
pile = empiler(pile,ne);
if (operateur!=RC)
{ //c'est pas la fin d'expression arithm�tique
//cr�er cellule pour op�rateur
ne = creer_cel_op(operateur);
pile = empiler(pile,ne);
}//Fin if (operateur!=RC)
} while (operateur != RC);
return ((PTPILE *)pile);
}//Fin fonction saisit_stockage_expression
/* **************************************************************************
Nom : evaluer_une_operation
Entr�e : une pile initiale
Sortie : une pile r�sultante
Description : effectue l'�valuation d'une op�ration arithm�tique sur les deux op�randes
au sommet de la pile et l'op�rateur correspondant, puis empile le r�sultat de cette �valuation
************************************************************************** */
PTPILE *evaluer_une_operation(PTPILE *pile)
{
//D�claration d'une variable pour stocker la cellule d�pil�e
PTPILE *est_recuperee;
//D�claration des variables pour les op�randes, l'op�rateur et le r�sultat de l'�valuation
float oper1,oper2,evaluation;
char operateur;
//V�rification si la pile est nulle
if (!pile) return ((PTPILE *)NULL);
//D�piler la pile pour r�cup�rer le premier op�rande
pile = Depiler(pile, &est_recuperee);
oper1 = est_recuperee->elem.val;
//D�piler la pile pour r�cup�rer l'op�rateur
pile = Depiler(pile, &est_recuperee);
operateur = est_recuperee->elem.op;

//D�piler la pile pour r�cup�rer le deuxi�me op�rande
pile = Depiler(pile, &est_recuperee);
oper2 = est_recuperee->elem.val;
//Calculer le r�sultat de l'op�ration
evaluation = calculer_exp(oper1, operateur, oper2);
// Empiler le r�sultat de l'�valuation
pile = empiler(pile, creer_cel_val(evaluation));
return ((PTPILE *)pile);
} //Fin fonction evaluer_une_operation
/* **************************************************************************
Nom : Evaluer_Exp_Pile
Entr�e : Pile dont on a charg�e l'expression arithm�tique
Sortie : r�sultat d'�valuation de l'expression arithm�tique
Description : la fonction d�pile les op�randes et les op�rateurs, les empile dans une pile
temporaire, et effectue les calculs en respectant la priorit� des op�rations. Le r�sultat
final est retourn� en tant que nombre � virgule flottante
************************************************************************** */
float Evaluer_Exp_Pile(PTPILE *pile)
{
PTPILE *pile_temporaire = NULL, *est_recuperee;
char operateur;
// V�rifier si la pile est vide
if (!pile)
{
printf("\nPile vide!!");
return 0.0;
}//Fin if(!pile)
// D�piler le premier op�rande dans la pile et l'empile dans la pile temporaire
pile = Depiler(pile, &est_recuperee);
pile_temporaire = empiler(pile_temporaire, est_recuperee);
while (pile) // Tant que la pile n'est pas vide
{

// D�piler l'op�rateur de la pile et l'empile dans la pile temporaire
pile = Depiler(pile, &est_recuperee);
pile_temporaire = empiler(pile_temporaire, est_recuperee);
operateur = est_recuperee->elem.op; // Garder l'op�rateur
// D�piler le deuxi�me op�rande de la pile et l'empile dans la pile temporaire
pile = Depiler(pile, &est_recuperee);
pile_temporaire = empiler(pile_temporaire, est_recuperee);
if (pile)
{
// Traiter les op�rations selon la priorit� des op�rateurs
if (pile->elem.op == '+')
{
// �valuer toutes les op�rations dans la pile temporaire
while (pile_temporaire->svt)
pile_temporaire = evaluer_une_operation(pile_temporaire);
}//Fin if (pile->elem.op == '+')
else if (pile->elem.op != '/')
{
// �valuer les op�rations jusqu'� l'op�rateur '+' ou '-'
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
// �valuer toutes les op�rations restantes dans la pile temporaire
while (pile_temporaire->svt)
pile_temporaire = evaluer_une_operation(pile_temporaire);

// Retourner le r�sultat final
return (float)pile_temporaire->elem.val;
}//Fin fonction Evaluer_Exp_Pile
/* **************************************************************************
Nom : afficher_pile
Entree : Pointeur vers la pile � afficher
Sortie : Affichage de la pile
Description: la fonction est utilis�e pour visualiser les �l�ments d'une pile,
tels que des valeurs en virgule flottante et des op�rateurs.
************************************************************************** */
void afficher_pile(PTPILE *pile)
{
PTPILE *tmp = pile;
while (tmp != NULL)
{
// Affichage de la valeur float
if (est_op(tmp->elem.op) == -1)
printf("|%3.2f|\n", tmp->elem.val);
// Affichage de l'op�rateur
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

    // �valuer l'expression � l'aide de la pile
    float resultat = Evaluer_Exp_Pile(pile);
    printf("\nResultat de l'expression avec la pile : %.2f\n", resultat);

    return 0;
}

