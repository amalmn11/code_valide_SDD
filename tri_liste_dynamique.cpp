#include<stdio.h>
#include<stdlib.h>
#include <time.h>


///*Definition d'une structure de liste dynamique*/
//typedef struct lst
//{
// int Entier;/* l'élement de la liste */
// struct lst *svt; /* poiteur sur l'élement au suivant */
//}Dliste;//Cellule


typedef struct element
{
 int val;//l'information de la Dliste.
 struct element *suiv;//le suiv de la Dliste.
}Dliste;


/// Fonction du temps d'execution
void temps(clock_t begin ,clock_t end)
   {
    unsigned long tmp;
    tmp = (end -  begin) * 1000 / CLOCKS_PER_SEC; /// temps en ms
    printf("\n le programme a pris comme temps d'execution : %ld ms \n ",tmp);
   }


//fonction qui permet de creer la liste "Cellule"
Dliste *Creer_Cellule(int val)
{
    Dliste *NE;
    /* Allouer la mémoire pour NE */
    NE = (Dliste *)malloc(sizeof(Dliste));
    if (!NE) /* L'allocation est mal passée */
    {
        /* Afficher un message d'erreur */
        printf("\nErreur d allocation du memoire.");
        /* Sortir du programme */
        exit(-1);
    }
    
    /* Indiquer que le nœud créé n'a pas de successeur */
    NE->suiv = NULL;
    /* Ajouter l'élément */
    NE->val = val;
    
    return ((Dliste *)NE); /* Recupérer le nœud créé */
}




//fonction qui permet de tester si la liste est vide on non
int Est_Vide_Dliste(Dliste *Liste)
{
    return ((int)(Liste == NULL));
}




//fonction qui permet d'afficher la liste
void afficher_Dliste(Dliste *Liste)
{
    Dliste *pcrt;
    printf("\n");
    if (Est_Vide_Dliste(Liste))
        printf("\nLa liste est vide");
    pcrt = Liste;
    while (pcrt)
    {
        /* Afficher élément par élément de la liste */
        printf("| %d |\t", pcrt->val);
        /* Passer à l'élément au suivant */
        pcrt = pcrt->suiv;
    }
    printf("\n");
}


 
//fonction qui permet d'inserer un element a la fin de la liste 
Dliste *InsererFin(Dliste *maliste, Dliste *macel)
{
    Dliste *pcrt;
    /* Vérification que la liste est vide */
    if (Est_Vide_Dliste(maliste))
        return ((Dliste *)macel);
    pcrt = maliste;          /* Initialisation de pcrt pour parcourir la liste */
    /* Parcours de la liste jusqu'au dernier nœud */
    while (pcrt->suiv)
        pcrt = pcrt->suiv;
    pcrt->suiv = macel;        /* Mise à jour du dernier nœud pour pointer vers macel */
    return ((Dliste *)maliste); /* Renvoi de la liste mise à jour */
}


//fonction qui permet de calcule la taille d la liste 
int taille_liste(Dliste *maliste)
{
	Dliste *tmp;
	tmp=maliste;
	int taille=0;
	while(tmp)
	{
		taille++;
		tmp=tmp->suiv;
	}
	return ((int)taille);
}

//fonction qui permet de faire la permutatione entre 2 vals
void Echange_P(int *L1, int *L2)
{
 	int echange;
  	echange = *L1;
  	*L1 = *L2;
  	*L2 = echange;
}

//fonction qui permet de trier la liste par insertion
Dliste *trie_par_insertion(Dliste *L)
{
    int k=0;
    clock_t begin = clock();
	Dliste *Ptr1;//pointeur sur les elements triee
	Dliste *Ptr2;//pointeur sur l'element e inserer dans la partie gauche.
	Dliste *courant;//pointeur pour parcourir la laiste
	courant = L->suiv;

	while(courant)
	{
		Ptr1=L;
		/*Tant queon nea pas parcouru toute la partie gauche*/
		while(Ptr1!= courant)
		{
			Ptr2=courant;
    		/*insertion de l'element pointe par Ptr2 e la
    		bonne position*/
     		if(Ptr1->val > Ptr2->val)
    		{
            	k++;
       			Echange_P(&Ptr1->val,&Ptr2->val);
       			afficher_Dliste(L);
        	}
    		Ptr1=Ptr1->suiv;
    	}
  		courant = courant->suiv;
	} /// fin while(courant)
	clock_t end = clock();
	temps(begin,end);
	printf("  \n le nombre d'iterations  : %d ",k);
	return((Dliste*)L);
}

//fonction qui permet d'inserer un element a la fin de la liste 
Dliste *trier_liste_bulle(Dliste *maliste)
{
   Dliste *tmp,*crt;
   int k=0;
   clock_t begin = clock();
   int taille=taille_liste(maliste);
   while(taille>0)
   {
   		crt=maliste;
   		tmp=crt->suiv;
   		while(crt->suiv)
   		{
   			if(tmp->val<crt->val)
			{
				//permutation
				k++;
				tmp->val=tmp->val+crt->val;
				crt->val=tmp->val-crt->val;
				tmp->val=tmp->val-crt->val;
				afficher_Dliste(maliste);
			}
			crt=crt->suiv;
			tmp=tmp->suiv;
		}
		taille--;
   }
   	clock_t end = clock();
	temps(begin,end);
	printf("  \n le nombre d'iterations  : %d ",k);
   return((Dliste*)maliste);
}


//
//int main()
//{
//	Dliste *liste = NULL; // Initialisation de la liste
//          
//    // Insertion d'éléments à la fin de la liste
//    Dliste *element1 = Creer_Cellule(7);
//    Dliste *element2 = Creer_Cellule(2);
//    Dliste *element3 = Creer_Cellule(5);
//    Dliste *element4 = Creer_Cellule(1);
//     Dliste *element5 = Creer_Cellule(9);
//    Dliste *element6 = Creer_Cellule(-5);
//    Dliste *element7 = Creer_Cellule(11);
//    Dliste *element8 = Creer_Cellule(90);
//    Dliste *element9 = Creer_Cellule(100);
//    Dliste *element10 = Creer_Cellule(0);
//
//    liste = InsererFin(liste, element1);
//    liste = InsererFin(liste, element2);
//    liste = InsererFin(liste, element3);
//    liste = InsererFin(liste, element4);
//    liste = InsererFin(liste, element5);
//    liste = InsererFin(liste, element6);
//    liste = InsererFin(liste, element7);
//    liste = InsererFin(liste, element8);
//    liste = InsererFin(liste, element9);
//    liste = InsererFin(liste, element10);
//    
//    // Affichage de la liste
//    printf("Liste initiale : ");
//    afficher_Dliste(liste);
//    
//    
//    printf("\nla taile de la Liste est : %d ",taille_liste(liste));
//    
//    
//    printf("\n\nla Liste avant le trie : ");
//    afficher_Dliste(liste);
//   
//   
//   	printf("\n\nla Liste apres le trie : ");
//    liste=trier_liste_bulle(liste);
////    afficher_Dliste(liste);
//   
////    printf("\n\nla Liste apres le trie : ");
////    liste=trie_par_insertion(liste);
////    afficher_Dliste(liste); 
//    
//    
//	return ((int)0);
//}




