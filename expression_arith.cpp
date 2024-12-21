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


typedef struct Nd // Définition de la structure d'arbre
{
Element elem; // champ d'information de l'arbre
struct Nd *fgc, *fdt; // pointeur de fils gauche et droit
}Noeud;

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
Nom : creer_nd
Sorties : Noeud *NE : le noeud créé
Description : la fonction permet de créer un nœud et de le retourner.
************************************************************************** */
Noeud *creer_nd()
{
Noeud *NE;
NE = (Noeud *)malloc(sizeof(Noeud)); // Allocation de la mémoire

if (!NE)
{
printf("\nErreur d'allocation de la mémoire!");
exit(0);
}
NE->fgc = NE->fdt = NULL; // Initialiser les fils au NULL
return ((Noeud *)NE);
} // fin de la fonction creer_nd()



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
}// Fin de la fonction calculer_exp


/* **************************************************************************
Nom : affichage_horiz
Entrée : Un pointeur vers un nœud de l'arbre, Le niveau actuel dans l'arbre
Sortie : elle imprime l'arbre de manière horizontale sur la sortie standard
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
//récursion sur le sous arbre gauche
if (monArb->fgc) affichage_horiz(monArb->fgc, niveau+1 );
}//Fin fonction affichage horizontale



int determiner_cas(char opOLD,char opNV )
{
// on a trois cas à traiter :
//cas 1: si l'opérateur qui vient est un + ou -
if((opNV == PL) || (opNV == MN) ) return ((int) 1);
// cas 2: si l'opérateur / ou * vient après un - ou +
if(((opOLD == PL) || (opOLD == MN)) && ((opNV == ML) || (opNV == DV)))
return ((int) 2);
//cas 3: si l'opérateur / ou * vient après un * ou /

if(((opOLD == ML) || (opOLD == DV)) && ((opNV == ML) || (opNV == DV)))
return ((int) 3);
}//Fin fonction determiner_cas(char opOLD,char opNV )
/* **************************************************************************
Nom : construire_arbre
Entrée : utilise la saisie utilisateur
Sortie : Un pointeur vers la racine de l'arbre d'expression construit.
Description : la fonction prend en entrée une expression arithmétique de l'utilisateur
et construit un arbre d'expression correspondant
************************************************************************** */
Noeud *construire_arbre()
{
//Nop : c’est le Noeud pour stocker l'opérateur
//Nval : c’est le Noeud pour stocker l’opérande
//crt : c’est le Noeud pour stocker le dernier opérateur inséré
Noeud *Arb =NULL,*Nop=NULL,*Nval=NULL,*crt=NULL;
char op; //pour stocker l'opérateur retourner par lire_operande(float *operande)
float val; // pour stocker l'opérande extrait
int garde;// pour stocker la valeur retourner par est_op(char op)
/*pour stocker la valeur retournée par la fonction determiner_cas(char opOLD,char opNV)*/
int cas;
printf("\nEntrer une expression arithmétique : ");
// Boucle de lecture jusqu'à la fin de l'expression
while ((op = lire_operande(&val)) != RC)
{
garde = est_op(op);
// Vérification si l'opérateur est valide
if(garde == -1)
{
printf("\nOperateur invalide!");
exit(0);
}//fin if(garde == -1)
Nval = creer_nd(); // Creer un noeud pour l'operande
Nval->elem.val = val;// affecte la valeur de l'operande
Nop = creer_nd(); // Creer un noeud pour l'opérateur
Nop->elem.op = op;// affecter le l'operateur
if (!Arb) // si Arbre vide
{
Arb = Nop; // l'opérateur devient racine de l'arbre
Arb->fgc = Nval; // l'opérande devient son fils gauche
crt = Arb; // initialiser courant par la racine de l'arbre
}//Fin if (!Arb)
else
{
// Détermination du cas en fonction des opérateurs
cas = determiner_cas(crt->elem.op,Nop->elem.op);
if(cas == 1)// si on est dans le cas 1
{
crt->fdt = Nval;// l'opérande devient fils droit de courant
Nop->fgc = Arb; // le racine devient fils gauche de l'opérateur
Arb = Nop;// l'opérateur devient racine de l'arbre
crt= Arb;// mise à jour de courant à opérateur
}//Fin if(cas == 1)
else if(cas == 2)// si on est dans le cas 2
{
crt->fdt = Nop;// l'opérateur devient fils droit de courant
Nop->fgc = Nval;// l'opérande devient fils gauche de l’opérateur
crt = Nop;// mise à jour de courant à opérateur
}//Fin if(cas == 2)
else // si on est dans le cas 3
{
Nop->fgc = crt;//courant devient fils gauche de l'opérateur
if (Arb == crt) Arb = Nop;// l'opérateur devient la racine
else Arb->fdt = Nop;// l'opérateur devient fils droit de la racine
crt->fdt = Nval;// l'opérande devient fils droit de courant
crt = Nop;// mise à jour de courant à opérateur
}//Fin else de cas 3
}//fin else de if(!Arb)
}//Fin while ((op = lire_operande(&val)) != RC)
//insertion de dernier opérande
Nval = creer_nd(); // Créer un noeud pour l'opérande
Nval->elem.val = val; // affecte la valeur de l'opérande
if (!Arb) return ((Noeud *)Nval); // si l'arbre est vide
if (!crt->fdt) crt->fdt = Nval;
else crt->fgc = Nval;
return ((Noeud *)Arb);
}//Fin fonction construire_arbre()



/* **************************************************************************
Nom : evaluer_exp_arbre
Entrée : la racine d'un arbre d'expression à évaluer
Sortie : le résultat de l'évaluation de l'arbre d'expression (float)
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

    // Construire l'arbre à partir de l'expression arithmétique
    Arbre = construire_arbre();

    // Affichage de l'arbre
    printf("\nAffichage de l'arbre :\n");
    affichage_horiz(Arbre, 0);

    // Évaluation de l'expression arithmétique
    float resultat = evaluer_exp_arbre(Arbre);
    printf("\nLe résultat de l'expression arithmétique est : %.3f\n", resultat);

   

    return 0;
}

