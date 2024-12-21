#include<stdio.h>
#include<stdlib.h>
#include <time.h>


/*Definition d'une structure de liste dynamique*/
typedef struct lst
{
 int Entier;/* l'élement de la liste */
 struct lst *svt; /* poiteur sur l'élement au suivant */
}PtListe;//Cellule

/// Fonction du temps d'execution
void temps(clock_t begin ,clock_t end)
   {
    unsigned long tmp;
    tmp = (end -  begin) * 1000 / CLOCKS_PER_SEC; /// temps en ms
    printf("\n le programme a pris comme temps d'execution : %ld ms \n ",tmp);
   }


//fonction qui permet de creer la liste "Cellule"
PtListe *Creer_Cellule(int val)
{
    PtListe *NE;
    /* Allouer la mémoire pour NE */
    NE = (PtListe *)malloc(sizeof(PtListe));
    if (!NE) /* L'allocation est mal passée */
    {
        /* Afficher un message d'erreur */
        printf("\nErreur d allocation du memoire.");
        /* Sortir du programme */
        exit(-1);
    }
    
    /* Indiquer que le nœud créé n'a pas de successeur */
    NE->svt = NULL;
    /* Ajouter l'élément */
    NE->Entier = val;
    
    return ((PtListe *)NE); /* Recupérer le nœud créé */
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
        /* Afficher élément par élément de la liste */
        printf("| %d |", pcrt->Entier);
        /* Passer à l'élément au suivant */
        pcrt = pcrt->svt;
    }
}


 
//fonction qui permet d'inserer un element a la fin de la liste 
PtListe *InsererFin(PtListe *maliste, PtListe *macel)
{
    PtListe *pcrt;
    /* Vérification que la liste est vide */
    if (Est_Vide_PtListe(maliste))
        return ((PtListe *)macel);
    pcrt = maliste;          /* Initialisation de pcrt pour parcourir la liste */
    /* Parcours de la liste jusqu'au dernier nœud */
    while (pcrt->svt)
        pcrt = pcrt->svt;
    pcrt->svt = macel;        /* Mise à jour du dernier nœud pour pointer vers macel */
    return ((PtListe *)maliste); /* Renvoi de la liste mise à jour */
}


//fonction qui permet de calcule la taille d la liste 
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

//fonction qui permet de faire la permutatione entre 2 entiers
void Echange_P(int *L1, int *L2)
{
 	int echange;
  	echange = *L1;
  	*L1 = *L2;
  	*L2 = echange;
}

//fonction qui permet de trier la liste par insertion
PtListe *trie_par_insertion(PtListe *L)
{
    int k=0;
    clock_t begin = clock();
	PtListe *Ptr1;//pointeur sur les elements triee
	PtListe *Ptr2;//pointeur sur l'element e inserer dans la partie gauche.
	PtListe *courant;//pointeur pour parcourir la laiste
	courant = L->svt;

	while(courant)
	{
		Ptr1=L;
		/*Tant queon nea pas parcouru toute la partie gauche*/
		while(Ptr1!= courant)
		{
			Ptr2=courant;
    		/*insertion de l'element pointe par Ptr2 e la
    		bonne position*/
     		if(Ptr1->Entier > Ptr2->Entier)
    		{
            	k++;
       			Echange_P(&Ptr1->Entier,&Ptr2->Entier);
       			afficher_PtListe(L);
        	}
    		Ptr1=Ptr1->svt;
    	}
  		courant = courant->svt;
	} /// fin while(courant)
	clock_t end = clock();
	temps(begin,end);
	printf("  \n le nombre d'iterations  : %d ",k);
	return((PtListe*)L);
}

//fonction qui permet d'inserer un element a la fin de la liste 
PtListe *trier_liste_bulle(PtListe *maliste)
{
   PtListe *tmp,*crt;
   int k=0;
   clock_t begin = clock();
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
				k++;
				tmp->Entier=tmp->Entier+crt->Entier;
				crt->Entier=tmp->Entier-crt->Entier;
				tmp->Entier=tmp->Entier-crt->Entier;
			}
			crt=crt->svt;
			tmp=tmp->svt;
		}
		taille--;
   }
   	clock_t end = clock();
	temps(begin,end);
	printf("  \n le nombre d'iterations  : %d ",k);
   return((PtListe*)maliste);
}



int main()
{
	PtListe *liste = NULL; // Initialisation de la liste

    // Insertion d'éléments à la fin de la liste
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
   
//    printf("\n\nla Liste apres le trie : ");
//    liste=trie_par_insertion(liste);
//    afficher_PtListe(liste); 
    
    
	return ((int)0);
}


