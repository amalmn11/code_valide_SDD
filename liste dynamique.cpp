#include <stdio.h>
#include <stdlib.h>

typedef struct lst{
	int Entier;
	struct lst *svt;
	//struct lst *prd;
}Cellule;

//creer un cellule
Cellule* Creer_cellule(){
	Cellule *NE;
	NE=(Cellule *)malloc(sizeof(Cellule));
	if(!NE)
	{
		printf("probleme de l'allocation");
		exit((int)-1);
		
	}
	NE->svt=NULL;
	return((Cellule*)NE);
}

//tester si la liste est vide 
int Est_vide_liste(Cellule *liste)
{
//	if(!liste)	return((int)1);//si la liste est vide 
//	return((int)0);//si la liste n'est pas vide
	return ((int)!liste);
}

//fonction qui retourne la taille de la liste
int Taille_liste(Cellule *liste)
{
	int taille=0;
	Cellule *tmp;
	tmp=liste;
	//tant que tmp!=NULL 
	while(tmp)
	{
		taille++;//incrementation de taille 
		tmp=tmp->svt;//pointer sur la cellule suivant 
	}
	return((int)taille);//retourner la taille
}


/*La fonction insererPos permet d'ins�rer une cellule au 
d�but, � la fin ou � une position quelconque*/
Cellule *insererPos(Cellule *liste,int pos,Cellule *NE)
{
	Cellule *crt;
	int compt=0;
	if(!NE) return ((Cellule *)liste);
	//insertion au debut de la liste 
	if(pos==0)
	{
		//La nouvelle cellule devient la premi�re cellule de la liste
		NE->svt=liste;
		return((Cellule *)NE);	
	}
	//si la position donn�e est non valide
	if((pos<0) || pos>Taille_liste(liste))
	{
		printf("\nposition non valide");
		return ((Cellule *)liste);
	}
	//si la position valide
	crt=liste;
	while(compt<pos-1)
	{
		compt++;
		crt=crt->svt;
	}
	//Le pointeur 'crt' pointe vers la cellule qui pr�c�de la position de 1.
	NE->svt=crt->svt;
	crt->svt=NE;
	return((Cellule *)liste);	
}

/*La fonction supprimerPos permet de supprimer une cellule au 
d�but, � la fin ou � une position quelconque*/
Cellule *supprimerPos(Cellule *liste,int pos)
{
	Cellule *crt,*tmp;
	int compt=0;
	
	//optionel
	/*	if(!liste)
	{
		printf("\nla list est vide rien a supprimer \n ");
		return((Cellule *)liste);
	} 
	*/

	//Supprimer au d�but de la liste
	if(pos==0)
	{
		//La 2�me cellule devient la premi�re
		crt=liste;
		liste=liste->svt;
		free(crt);
		return((Cellule *)liste);	
	}
	//si la position donn�e est non valide
	if((pos<0) || (pos>Taille_liste(liste)))
	{
		printf("\nposition non valide");
		return ((Cellule *)liste);
	}
	//si la position valide
	crt=liste;
	while(compt<pos-1)
	{
		compt++;//incrementation du compteur
		crt=crt->svt;
	}
	//Le pointeur 'crt' pointe vers la cellule qui pr�c�de la position de 1.
	tmp=crt->svt;//tmp pointe sur la cellule � supprimer
	crt->svt=tmp->svt;//crt pointe sur le suivan de tmp 
	free(tmp);//supprimer et liv=bere l'espace m�moire
	return((Cellule *)liste);
}

Cellule *trier_liste(Cellule *liste)
{
	Cellule *tmp,*crt;
	int a;
	//si la liste est vide 
	if(!liste) return((Cellule*)NULL);
	tmp=liste;
	while(tmp)
	{
		crt=tmp->svt;
		while(crt)
		{
			if(tmp->Entier<crt->Entier)
			{
				/*a=tmp->Entier;
				tmp->Entier=crt->Entier;
				crt->Entier=a;*/
				tmp->Entier=tmp->Entier-crt->Entier;
				crt->Entier=tmp->Entier+crt->Entier;
				tmp->Entier=crt->Entier-tmp->Entier;

			}
			crt=crt->svt;
		}
		tmp=tmp->svt;		
	}
	return((Cellule*)liste);
}


//fonction qui affiche les elements de la liste  
void afficher_liste(Cellule *liste)
{
	Cellule *tmp;
	//si la liste est vide 
	if(!liste)
	{
		printf("\non ne peut pas afficher une liste vide");
	}
	//si la liste n'est pas vide 
	tmp=liste;
	while(tmp)
	{
		//afficher le contenu de la cellule "entier" dont laquel tmp pointe
		printf("| %d |\t",tmp->Entier);
		tmp=tmp->svt;//pointer sur  l'element suivant 
	}
	printf("\n\n");
}

//vider la liste	
Cellule* vider_liste(Cellule *liste)
{
	Cellule *tmp;
	//vider  la liste
	while(liste)
	{
		tmp=liste;//tmp poite sur liste
		liste=liste->svt;//liste pointe sur element suivant
		free(tmp);//liberer l'espace point� par tmp
	}
	/*on peut retourner liste mais c'est mieu de retourner NULL
	pour assurer que liste ne contient pas une adresse que null*/ 
	return((Cellule *)NULL);
	
}	



int main() {
    Cellule *liste = NULL; // Initialisation de la liste � NULL (vide)

    // Cr�ation de quelques cellules pour tester l'insertion
    Cellule *cell1 = Creer_cellule();
    cell1->Entier = 1;

    Cellule *cell2 = Creer_cellule();
    cell2->Entier = 2;

    Cellule *cell3 = Creer_cellule();
    cell3->Entier = 3;
    
    Cellule *cell4= Creer_cellule();
    cell4->Entier = 5;
    
    Cellule *cell5= Creer_cellule();
    cell5->Entier = 11;


	Cellule *cell6= Creer_cellule();
    cell6->Entier = 12;
    
    Cellule *cell7= Creer_cellule();
    cell7->Entier = 13;

	Cellule *cell8= Creer_cellule();
    cell8->Entier = 14;
    
    // Affichage de la liste initiale (devrait �tre vide)
    printf("Liste initiale :\n");
    afficher_liste(liste);

    // Insertion des cellules dans la liste � des positions diff�rentes
    liste = insererPos(liste,0,cell1); // Ins�rer cell1 au d�but
    liste = insererPos(liste,1,cell2); // Ins�rer cell2 � la position 1 (milieu)
    liste = insererPos(liste,2,cell3); // Ins�rer cell3 � la position 2
    liste = insererPos(liste,1,cell4); // Ins�rer cell3 � la fin
    liste = insererPos(liste,2,cell5); // Ins�rer cell3 � la position 2
    
    

    // Affichage de la liste apr�s insertion
    printf("\nListe apres insertion :\n");
    afficher_liste(liste);
    
    liste=insererPos(liste,0,cell7);
	insererPos(liste,4,cell6); // Ins�rer cell3 � la fin
    
	//insererPos(liste,0,cell8); // il va etre inserer dans la copie
    
    afficher_liste(liste);
    
    liste = trier_liste(liste);
    afficher_liste(liste);
    
    // Supprimer un �l�ment � la position donn�e
	liste = supprimerPos(liste,0);

	// Afficher la liste apr�s la suppression
	printf("\nListe apres suppression de l'element a la position 0:\n");
	afficher_liste(liste);


	//Vider la liste
//	liste = vider_liste(liste);
//	printf("\nListe apres vidage :\n");
//	afficher_liste(liste);

    return 0;
}

