#include<stdio.h>
#include<stdlib.h>

/*Definition d'une structure de liste dynamique*/
typedef struct lst
{
 int Entier;/* l'�lement de la liste */
 struct lst *svt; /* poiteur sur l'�lement au suivant */
}PtListe;//Cellule


//fonction qui permet de creer la liste "Cellule"
PtListe *Creer_Cellule(int val)
{
    PtListe *NE;
    /* Allouer la m�moire pour NE */
    NE = (PtListe *)malloc(sizeof(PtListe));
    if (!NE) /* L'allocation est mal pass�e */
    {
        /* Afficher un message d'erreur */
        printf("\nErreur d allocation du memoire.");
        /* Sortir du programme */
        exit(-1);
    }
    
    /* Indiquer que le n�ud cr�� n'a pas de successeur */
    NE->svt = NULL;
    /* Ajouter l'�l�ment */
    NE->Entier = val;
    
    return ((PtListe *)NE); /* Recup�rer le n�ud cr�� */
}




//fonction qui permet de tester si la liste est vide on non
int Est_Vide_PtListe(PtListe *Liste)
{
    return ((int)(Liste == NULL));
}




//fonction qui permet d'afficher la liste
void afficher_PtListe(PtListe *Liste)
{
    PtListe *pcrt;
    printf("\n");
    if (Est_Vide_PtListe(Liste))
        printf("\nLa liste est vide");
    pcrt = Liste;
    while (pcrt)
    {
        /* Afficher �l�ment par �l�ment de la liste */
        printf("| %d |", pcrt->Entier);
        /* Passer � l'�l�ment au suivant */
        pcrt = pcrt->svt;
    }
}


 
//fonction qui permet d'inserer un element a la fin de la liste 
PtListe *InsererFin(PtListe *maliste, PtListe *macel)
{
    PtListe *pcrt;
    /* V�rification que la liste est vide */
    if (Est_Vide_PtListe(maliste))
        return ((PtListe *)macel);
    pcrt = maliste;          /* Initialisation de pcrt pour parcourir la liste */
    /* Parcours de la liste jusqu'au dernier n�ud */
    while (pcrt->svt)
        pcrt = pcrt->svt;
    pcrt->svt = macel;        /* Mise � jour du dernier n�ud pour pointer vers macel */
    return ((PtListe *)maliste); /* Renvoi de la liste mise � jour */
}



int taille_liste(PtListe *maliste)
{
	PtListe *tmp;
	tmp=maliste;
	int taille=0;
	while(tmp)
	{
		taille++;
		tmp=tmp->svt;
	}
	return ((int)taille);
}


//fonction qui permet d'inserer un element a la fin de la liste 
PtListe *trier_liste_bulle(PtListe *maliste)
{
   PtListe *tmp,*crt;
   int taille=taille_liste(maliste);
   while(taille>0)
   {
   		crt=maliste;
   		tmp=crt->svt;
   		while(crt->svt)
   		{
   			if(tmp->Entier<crt->Entier)
			{
				//permutation
				tmp->Entier=tmp->Entier+crt->Entier;
				crt->Entier=tmp->Entier-crt->Entier;
				tmp->Entier=tmp->Entier-crt->Entier;
			}
			crt=crt->svt;
			tmp=tmp->svt;
		}
		taille--;
   }
   return((PtListe*)maliste);
}



int main()
{
	PtListe *liste = NULL; // Initialisation de la liste

    // Insertion d'�l�ments � la fin de la liste
    PtListe *element1 = Creer_Cellule(17);
    PtListe *element2 = Creer_Cellule(8);
    PtListe *element3 = Creer_Cellule(0);
    PtListe *element4 = Creer_Cellule(3);

    liste = InsererFin(liste, element1);
    liste = InsererFin(liste, element2);
    liste = InsererFin(liste, element3);
    liste = InsererFin(liste, element4);
    
    // Affichage de la liste
    printf("Liste initiale : ");
    afficher_PtListe(liste);
    
    
    printf("\nla taile de la Liste est : %d ",taille_liste(liste));
    
    
    printf("\n\nla Liste avant le trie : ");
    afficher_PtListe(liste);
   
   
    printf("\n\nla Liste apres le trie : ");
    liste=trier_liste_bulle(liste);
    afficher_PtListe(liste); 
    
    
	return ((int)0);
}


