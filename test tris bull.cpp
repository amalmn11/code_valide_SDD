#include<stdio.h>
#include<stdlib.h>
#define MaxElem 100
#include <time.h>



typedef struct TB
{
 int TabInt[MaxElem]; /* Tbleau des donn�es */
 int NbElem; /* Nombre d'�lemnts dans le tableau */
}Tab;

/// Fonction du temps d'execution
void temps(clock_t begin ,clock_t end)
   {
    unsigned long tmp;
    tmp = (end -  begin) * 1000 / CLOCKS_PER_SEC; /// temps en ms
    printf("\n le programme a pris comme temps d'execution : %ld ms \n ",tmp);
   }


//fonction qui permet de creer la liste 
Tab *Creer_Tab()
{
    Tab *matab;
    /**allocation dynamique du pointeur*/
    matab = (Tab*)malloc(sizeof(Tab));
    /** Echec d'allocation de m�moire */
    if (!matab)
    {
        /** afficher un message d'erreur */
        printf("\nErreur d allocation de m�moire!!!");
        exit(-1);
    }
    /** si l'allocation est bien fait on retourne le pointeur */
    return ((Tab*)matab);
}

//fonction qui permet d'nitialiser la liste 
int Init_Tab(Tab *matab)
{
    /** V�rification de l'existence du tableau */
    if (!matab) /** cas o� le tab n'existe pas */
    {
        printf("\nErreur d allocation memoire!!!");
        exit(-1);/** quitter le programme */
    }//Fin if
    matab->NbElem = 0; /** Initialiser le nombre d'�lement � 0 */
    return ((int)1);
}

//fonction qui permet de tester si la liste est saturer on non
int Est_Saturee_Tab(Tab matab)
{
    return ((int)(matab.NbElem == MaxElem));
}

//fonction qui permet de tester si la liste est vide on non
int Est_Vide_Tab(Tab matab)
{
    return ((int)(matab.NbElem == 0));
}



/* Affiche les �l�ments du tableau Tab */
void afficher_Tab(Tab matab)
{
    int i;
//    printf("\nLes elements actuels du tableau:");
    if (Est_Vide_Tab(matab))/** si le tableau est vide */
        printf("\nLa table est vide.");/** message d'erreur */
    /** boucle pour parcourir le tableau case par case */
    for (i = 0; i < matab.NbElem; i++)
        printf("|  %d  |", matab.TabInt[i]);/** afficher l'element */
}


//fonction qui permet d'inserer un element a la fin de la liste "la fin du tableau"
int Inserer_Fin_Tab(Tab *matab, int val)
{
    /** v�rification de l'existance de tableau */
    if (!matab)/** s'il n'existe pas */
    {
        printf("\nErreur d'allocation!!!");//afficher message d'erreur
        return ((int)-1);
    }
    if (Est_Saturee_Tab(*matab)) /*Si La table est satur�e */
    {
        printf("\nLe tableau est satur� !!!");//message d'erreur
        return ((int)0);
    }
    /* Insertion r�ussie (il y a de la place) */
    matab->TabInt[matab->NbElem++] = val;
    /* Insertion r�ussie */
    return 1;
}


void echange(int *a,int *b)
{
	
	*a=*a+*b;
	*b=*a-*b;
	*a=*a-*b;
					
}
void trie_bulle(Tab *matab)
{
	int i;
	int n=matab->NbElem;
	int a,k=0;
	clock_t begin = clock();
	while(n>0)
	{
		for(i=0;i<matab->NbElem-1;i++)
		{
			if(matab->TabInt[i]>matab->TabInt[i+1]) 
			{
				k++;
				echange(&matab->TabInt[i],&matab->TabInt[i+1]);
			}
		}
		n--;
	}
	printf("  \n le nombre d'iterations  : %d ",k);
  	clock_t end = clock();
  	temps(begin,end);	
}


//foction qui permet de trier le tableau par trie par insertion
int trie_par_insertion(Tab *matab)
{
	int i,j,crt,k=0;
	if (!matab)/** s'il n'existe pas */
    {
        printf("\nErreur d'allocation!! la liste n'existe pas !!");//afficher message d'erreur
        return ((int)0);
	}
	clock_t begin = clock();
	for(i=1;i<matab->NbElem;i++)
	{
		crt=matab->TabInt[i];
		for(j=i-1;j>=0 && matab->TabInt[j]>crt;j--)
		{
			matab->TabInt[j+1]=matab->TabInt[j];
			k++;
		}	

		matab->TabInt[j+1]=crt;
	}
	printf("  \n le nombre d'iterations  : %d ",k);
  	clock_t end = clock();
  	temps(begin,end);	
	return ((int)1);
}

int main()
{
	
	Tab *matab=Creer_Tab();
	Init_Tab(matab);
	// Insertion d'�l�ments dans le premier tableau
    Inserer_Fin_Tab(matab, 1);
    Inserer_Fin_Tab(matab, 0);
    Inserer_Fin_Tab(matab, 30);
	Inserer_Fin_Tab(matab, 2);
	Inserer_Fin_Tab(matab, 17);
	Inserer_Fin_Tab(matab, 6);
	
	// Affichage du premier tableau
    printf("Affichage du tableau: ");
    afficher_Tab(*matab);
    
    
//    printf("\ntrier le tableau: ");
//    trie_bulle(matab);
    
    
    printf("\ntrier le tableau: ");
	trie_par_insertion(matab);
	
    printf("\nAffichage du tableau apres le trie: ");
    afficher_Tab(*matab);
    
	

	return 0;
}
