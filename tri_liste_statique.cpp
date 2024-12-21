#include<stdio.h>
#include<stdlib.h>
#define NBMAX 100
#include <time.h>


typedef struct
{
 int tab[NBMAX];//Un Tlisteau avec MAX nombre d'elements.
 int nbElem;//Indice du dernier element.
}Tliste;


//typedef struct TB
//{
// int TabInt[MaxElem]; /* Tbleau des données */
// int nbElem; /* Nombre d'élemnts dans le tableau */
//}Tab;

/// Fonction du temps d'execution
void temps(clock_t begin ,clock_t end)
{
    unsigned long tmp;
    tmp = (end -  begin) * 1000 / CLOCKS_PER_SEC; /// temps en ms
    printf("\n le programme a pris comme temps d'execution : %ld ms \n ",tmp);
}


//fonction qui permet de creer la liste 
Tliste *Creer_Tliste()
{
    Tliste *maTliste;
    /**allocation dynamique du pointeur*/
    maTliste = (Tliste*)malloc(sizeof(Tliste));
    /** Echec d'allocation de mémoire */
    if (!maTliste)
    {
        /** afficher un message d'erreur */
        printf("\nErreur d allocation de mémoire!!!");
        exit(-1);
    }
    /** si l'allocation est bien fait on retourne le pointeur */
    return ((Tliste*)maTliste);
}

//fonction qui permet d'nitialiser la liste 
int Init_Tliste(Tliste *maTliste)
{
    /** Vérification de l'existence du Tlisteleau */
    if (!maTliste) /** cas où le Tliste n'existe pas */
    {
        printf("\nErreur d allocation memoire!!!");
        exit(-1);/** quitter le programme */
    }//Fin if
    maTliste->nbElem = 0; /** Initialiser le nombre d'élement à 0 */
    return ((int)1);
}

//fonction qui permet de tester si la liste est saturer on non
int Est_Saturee_Tliste(Tliste maTliste)
{
    return ((int)(maTliste.nbElem == NBMAX));
}

//fonction qui permet de tester si la liste est vide on non
int Est_Vide_Tliste(Tliste maTliste)
{
    return ((int)(maTliste.nbElem == 0));
}



/* Affiche les éléments du Tlisteleau Tliste */
void afficher_Tliste(Tliste maTliste)
{
    int i;
//    printf("\nLes elements actuels du Tlisteleau:");
    if (Est_Vide_Tliste(maTliste))/** si le Tlisteleau est vide */
        printf("\nLa liste est vide.");/** message d'erreur */
    /** boucle pour parcourir le Tlisteleau case par case */
    for (i = 0; i < maTliste.nbElem; i++)
        printf("|  %d  |", maTliste.tab[i]);/** afficher l'element */
}


//fonction qui permet d'inserer un element a la fin de la liste "la fin du Tlisteleau"
int Inserer_Fin_Tliste(Tliste *maTliste, int val)                         
{
    /** vérification de l'existance de Tlisteleau */
    if (!maTliste)/** s'il n'existe pas */
    {
        printf("\nErreur d'allocation!!!");//afficher message d'erreur
        return ((int)-1);
    }
    if (Est_Saturee_Tliste(*maTliste)) /*Si La Tlistele est saturée */
    {
        printf("\nLe Tlisteleau est saturé !!!");//message d'erreur
        return ((int)0);
    }
    /* Insertion réussie (il y a de la place) */
    maTliste->tab[maTliste->nbElem++] = val;
    /* Insertion réussie */
    return 1;
}


void echange(int *a,int *b)
{
	
	*a=*a+*b;
	*b=*a-*b;
	*a=*a-*b;
					
}
void trie_bulle(Tliste *maTliste)
{
	int i;
	int n=maTliste->nbElem;
	int a,k=0;
	clock_t begin = clock();
	while(n>0)
	{
		for(i=0;i<maTliste->nbElem-1;i++)
		{
			afficher_Tliste(*maTliste);
			printf("\n\n");
			if(maTliste->tab[i]>maTliste->tab[i+1]) 
			{
				k++;
				echange(&maTliste->tab[i],&maTliste->tab[i+1]);
			}
		}
		
		n--;
	}
	printf("  \n le nombre d'iterations  : %d ",k);
  	clock_t end = clock();
  	temps(begin,end);	
}


//foction qui permet de trier le Tlisteleau par trie par insertion
int trie_par_insertion(Tliste *maTliste)
{
	int i,j,crt,k=0;
	if (!maTliste)/** s'il n'existe pas */
    {
        printf("\nErreur d'allocation!! la liste n'existe pas !!");//afficher message d'erreur
        return ((int)0);
	}
	clock_t begin = clock();
	for(i=1;i<=maTliste->nbElem;i++)
	{
		crt=maTliste->tab[i];
		afficher_Tliste(*maTliste);
		printf("\n\n");
		for(j=i-1;j>=0 && maTliste->tab[j]>crt;j--)
		{
			maTliste->tab[j+1]=maTliste->tab[j];
			k++;
		}	

		maTliste->tab[j+1]=crt;
	}
	printf("  \n le nombre d'iterations  : %d ",k);
  	clock_t end = clock();
  	temps(begin,end);	
	return ((int)1);
}

/************************************************************************/

/// role:La fonction permet l'echange de deux elements d'un Tlisteau*/
void EchangeT(Tliste *T, int i, int j)
{
 int echange;

 echange=T->tab[i];
 T->tab[i] = T->tab[j];
 T->tab[j] = echange;
}

/*********************************************************************/
void affichage(Tliste *T)
{   printf("\n");
    int i;
    printf(" La Tliste est : ");
    for(i=0;i<T->nbElem;i++)
    {
        printf(" %d    ",T->tab[i]);
    }
    printf("\n\n");
}

void Tri_Selection_Tab(Tliste *T)
{

 clock_t begin = clock();
  int i;//indice parcourt la Tliste
  int j;//indice pour la partie non triees
  int min;//la valeur minimale
  int indice_min;//l'indice de la valeur minimale
  int k=0;
 for(i=0;i<T->nbElem-1;i++)
  {
    indice_min = i;
    min = T->tab[i];
   //pour chercher la valeur minimale.
  for(j = i+1; j<T->nbElem; j++)
   {
    if(T->tab[j] < min)
    {
      min = T->tab[j];
      indice_min = j;
      EchangeT(T,i,indice_min);
      k++;
      affichage(T);
    }
  }/// fin  for(j = i+1; j<T->nbElem; j++)
 }/// fin  for(i=0;i<T->nbElem-1;i++)
 clock_t end = clock();
 temps(begin,end);
 printf("  \n le nombre d'iterations  : %d ",k);
}

int main()
{
	
	Tliste *maTliste=Creer_Tliste();
	Init_Tliste(maTliste);
	// Insertion d'éléments dans le premier Tlisteleau
    Inserer_Fin_Tliste(maTliste, 5);
    Inserer_Fin_Tliste(maTliste, 0);
    Inserer_Fin_Tliste(maTliste, 30);
	Inserer_Fin_Tliste(maTliste, 2);
	Inserer_Fin_Tliste(maTliste, -1);
//	Inserer_Fin_Tliste(maTliste, 6);
	
	// Affichage du premier Tlisteleau
    printf("Affichage du Tlisteleau: ");
    afficher_Tliste(*maTliste);
    
    
//    printf("\ntrier le Tlisteleau: ");
//    trie_bulle(maTliste);
    
    
    printf("\ntrier le Tlisteleau: ");
	trie_par_insertion(maTliste);
	
    printf("\nAffichage du Tlisteleau apres le trie: ");
    afficher_Tliste(*maTliste);
    
	

	return 0;
}
