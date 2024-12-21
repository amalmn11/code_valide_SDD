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


typedef struct Nd // D�finition de la structure d'arbre
{
Element elem; // champ d'information de l'arbre
struct Nd *fgc, *fdt; // pointeur de fils gauche et droit
}Noeud;

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
Nom : creer_nd
Sorties : Noeud *NE : le noeud cr��
Description : la fonction permet de cr�er un n�ud et de le retourner.
************************************************************************** */
Noeud *creer_nd()
{
Noeud *NE;
NE = (Noeud *)malloc(sizeof(Noeud)); // Allocation de la m�moire

if (!NE)
{
printf("\nErreur d'allocation de la m�moire!");
exit(0);
}
NE->fgc = NE->fdt = NULL; // Initialiser les fils au NULL
return ((Noeud *)NE);
} // fin de la fonction creer_nd()



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
}// Fin de la fonction calculer_exp


/* **************************************************************************
Nom : affichage_horiz
Entr�e : Un pointeur vers un n�ud de l'arbre, Le niveau actuel dans l'arbre
Sortie : elle imprime l'arbre de mani�re horizontale sur la sortie standard
************************************************************************** */
void affichage_horiz(Noeud *monArb, int niveau)
{
int i=0;
// affichage de sous arbre droit
if (monArb->fdt) affichage_horiz(monArb->fdt, niveau + 1);
// affichage de la racine
for (i=0; i < niveau; i++)
{
printf(" \t");
}
//si il s'agit d'une valeur float
if(est_op(monArb->elem.op)==-1)
printf("(%.3f)\n", monArb->elem.val);
// sinon si s'agit d'un operateur
else printf("(%c)\n", monArb->elem.op);
//r�cursion sur le sous arbre gauche
if (monArb->fgc) affichage_horiz(monArb->fgc, niveau+1 );
}//Fin fonction affichage horizontale



int determiner_cas(char opOLD,char opNV )
{
// on a trois cas � traiter :
//cas 1: si l'op�rateur qui vient est un + ou -
if((opNV == PL) || (opNV == MN) ) return ((int) 1);
// cas 2: si l'op�rateur / ou * vient apr�s un - ou +
if(((opOLD == PL) || (opOLD == MN)) && ((opNV == ML) || (opNV == DV)))
return ((int) 2);
//cas 3: si l'op�rateur / ou * vient apr�s un * ou /

if(((opOLD == ML) || (opOLD == DV)) && ((opNV == ML) || (opNV == DV)))
return ((int) 3);
}//Fin fonction determiner_cas(char opOLD,char opNV )
/* **************************************************************************
Nom : construire_arbre
Entr�e : utilise la saisie utilisateur
Sortie : Un pointeur vers la racine de l'arbre d'expression construit.
Description : la fonction prend en entr�e une expression arithm�tique de l'utilisateur
et construit un arbre d'expression correspondant
************************************************************************** */
Noeud *construire_arbre()
{
//Nop : c�est le Noeud pour stocker l'op�rateur
//Nval : c�est le Noeud pour stocker l�op�rande
//crt : c�est le Noeud pour stocker le dernier op�rateur ins�r�
Noeud *Arb =NULL,*Nop=NULL,*Nval=NULL,*crt=NULL;
char op; //pour stocker l'op�rateur retourner par lire_operande(float *operande)
float val; // pour stocker l'op�rande extrait
int garde;// pour stocker la valeur retourner par est_op(char op)
/*pour stocker la valeur retourn�e par la fonction determiner_cas(char opOLD,char opNV)*/
int cas;
printf("\nEntrer une expression arithm�tique : ");
// Boucle de lecture jusqu'� la fin de l'expression
while ((op = lire_operande(&val)) != RC)
{
garde = est_op(op);
// V�rification si l'op�rateur est valide
if(garde == -1)
{
printf("\nOperateur invalide!");
exit(0);
}//fin if(garde == -1)
Nval = creer_nd(); // Creer un noeud pour l'operande
Nval->elem.val = val;// affecte la valeur de l'operande
Nop = creer_nd(); // Creer un noeud pour l'op�rateur
Nop->elem.op = op;// affecter le l'operateur
if (!Arb) // si Arbre vide
{
Arb = Nop; // l'op�rateur devient racine de l'arbre
Arb->fgc = Nval; // l'op�rande devient son fils gauche
crt = Arb; // initialiser courant par la racine de l'arbre
}//Fin if (!Arb)
else
{
// D�termination du cas en fonction des op�rateurs
cas = determiner_cas(crt->elem.op,Nop->elem.op);
if(cas == 1)// si on est dans le cas 1
{
crt->fdt = Nval;// l'op�rande devient fils droit de courant
Nop->fgc = Arb; // le racine devient fils gauche de l'op�rateur
Arb = Nop;// l'op�rateur devient racine de l'arbre
crt= Arb;// mise � jour de courant � op�rateur
}//Fin if(cas == 1)
else if(cas == 2)// si on est dans le cas 2
{
crt->fdt = Nop;// l'op�rateur devient fils droit de courant
Nop->fgc = Nval;// l'op�rande devient fils gauche de l�op�rateur
crt = Nop;// mise � jour de courant � op�rateur
}//Fin if(cas == 2)
else // si on est dans le cas 3
{
Nop->fgc = crt;//courant devient fils gauche de l'op�rateur
if (Arb == crt) Arb = Nop;// l'op�rateur devient la racine
else Arb->fdt = Nop;// l'op�rateur devient fils droit de la racine
crt->fdt = Nval;// l'op�rande devient fils droit de courant
crt = Nop;// mise � jour de courant � op�rateur
}//Fin else de cas 3
}//fin else de if(!Arb)
}//Fin while ((op = lire_operande(&val)) != RC)
//insertion de dernier op�rande
Nval = creer_nd(); // Cr�er un noeud pour l'op�rande
Nval->elem.val = val; // affecte la valeur de l'op�rande
if (!Arb) return ((Noeud *)Nval); // si l'arbre est vide
if (!crt->fdt) crt->fdt = Nval;
else crt->fgc = Nval;
return ((Noeud *)Arb);
}//Fin fonction construire_arbre()



/* **************************************************************************
Nom : evaluer_exp_arbre
Entr�e : la racine d'un arbre d'expression � �valuer
Sortie : le r�sultat de l'�valuation de l'arbre d'expression (float)
************************************************************************** */
float evaluer_exp_arbre(Noeud *Arb)
{
if (Arb)
{
//si le noeud est une feuille , on retourne la val
if (!Arb->fgc && !Arb->fdt) return ((float)Arb->elem.val);
return ((float) calculer_exp(
evaluer_exp_arbre(Arb->fgc),
Arb->elem.op,
evaluer_exp_arbre(Arb->fdt)
));
}//Fin if(Arb)
}//Fin fonction evaluer_exp_arbre



int main() {
    Noeud *Arbre = NULL;

    // Construire l'arbre � partir de l'expression arithm�tique
    Arbre = construire_arbre();

    // Affichage de l'arbre
    printf("\nAffichage de l'arbre :\n");
    affichage_horiz(Arbre, 0);

    // �valuation de l'expression arithm�tique
    float resultat = evaluer_exp_arbre(Arbre);
    printf("\nLe r�sultat de l'expression arithm�tique est : %.3f\n", resultat);

   

    return 0;
}

