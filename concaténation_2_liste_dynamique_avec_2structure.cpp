#include <stdio.h>
#include <stdlib.h>




typedef struct lst{
	int Entier;
	struct lst *svt;
	//struct lst *prd;
}Cellule;


/*maintenant puisque on travaille avec cette liste qu'on on appel fonction concatener la 

liste1 et liste2 seront vider avant qu'on on travaille avec la 1ere liste seulementet on fait

la focntion de concatenation concatener(Cellule *liste1,Cellule *liste2) et on retourn L,

L sera modifier mais la liste1 et liste2 on travaille juste avec des copie c-à-d que donc la 

fontcion les deux liste seront vider car chaque fois on prend la cellule de qui contienne le min 

d'une liste on prend tous la case et on l'insere c-à-d on modifie la liste mais cette modification ne 

prenne pas on consideration car on peut pas retourner trois liste on utilisant une fonction .

juste pour clarifier : c'est pour cela on utilise la structure qui contient les trois liste et passe 

cette liste a tracer notre fonction parceque si on passe un pointeur par une fonction ici on a passage

par valeur pour le pointeur mais pour le contenu c'est un passage par addresse et dans notre 2eme structure 

les trois liste sont le contenu   */ 


typedef struct liste{
	Cellule *liste1;
	Cellule *liste2;
	Cellule *liste3;
}liste;

liste* Creer_liste(){
	liste *NE;
	NE=(liste *)malloc(sizeof(liste));
	if(!NE)
	{
		printf("probleme de l'allocation");
		exit((int)-1);
		
	}
	NE->liste1=NULL;
	NE->liste2=NULL;
	NE->liste3=NULL;
	return((liste*)NE);
}
//creer un cellule
Cellule* Creer_cellule(){
	Cellule *NE;
	NE=(Cellule *)malloc(sizeof(Cellule));
	if(!NE)
	{
		printf("probleme de l'allocation");
		return((Cellule*)NULL);
		
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


/*La fonction insererPos permet d'insérer une cellule au 
début, à la fin ou à une position quelconque*/
Cellule *insererPos(Cellule *liste,int pos,Cellule *NE)
{
	Cellule *crt;
	int compt=0;
	if(!NE) return ((Cellule *)liste);
	//insertion au debut de la liste 
	if(pos==0)
	{
		//La nouvelle cellule devient la première cellule de la liste
		NE->svt=liste;
		return((Cellule *)NE);	
	}
	//si la position donnée est non valide
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
	//Le pointeur 'crt' pointe vers la cellule qui précède la position de 1.
	NE->svt=crt->svt;
	crt->svt=NE;
	return((Cellule *)liste);	
}

/*La fonction supprimerPos permet de supprimer une cellule au 
début, à la fin ou à une position quelconque*/
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

	//Supprimer au début de la liste
	if(pos==0)
	{
		//La 2ème cellule devient la première
		crt=liste;
		liste=liste->svt;
		free(crt);
		return((Cellule *)liste);	
	}
	//si la position donnée est non valide
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
	//Le pointeur 'crt' pointe vers la cellule qui précède la position de 1.
	tmp=crt->svt;//tmp pointe sur la cellule à supprimer
	crt->svt=tmp->svt;//crt pointe sur le suivan de tmp 
	free(tmp);//supprimer et liv=bere l'espace mémoire
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
			if(tmp->Entier>crt->Entier)
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


Cellule *inserer_fin(Cellule *liste,Cellule *NE)
{
	Cellule *tmp;
	int a;
	//si la liste est vide 
	if(!liste) return((Cellule*)NE);
	tmp=liste;
	while(tmp->svt) tmp=tmp->svt;
	tmp->svt=NE;
	return((Cellule*)liste);
}

//Cellule *concatener(Cellule *liste1, Cellule *liste2) {
//    Cellule *L = NULL;  // Liste résultante
//
//    while (liste1 && liste2) {
//        if (liste1->Entier < liste2->Entier) {
//            L = inserer_fin(L, liste1);
//            liste1 = liste1->svt;
//        } else {
//            L = inserer_fin(L, liste2);
//            liste2 = liste2->svt;
//        }
//    }
//
//    // Ajouter le reste de la liste 1 (si elle n'est pas vide)
//    while (liste1) {
//        L = inserer_fin(L, liste1);
//        liste1 = liste1->svt;
//    }
//
//    // Ajouter le reste de la liste 2 (si elle n'est pas vide)
//    while (liste2) {
//        L = inserer_fin(L, liste2);
//        liste2 = liste2->svt;
//    }
//
//    return L;
//}




Cellule *concatener(liste *L)
{
	Cellule *tmp;
	if(!L->liste1) return((Cellule*)trier_liste(L->liste2));
	if(!L->liste2) return((Cellule*)trier_liste(L->liste1));

	//trier les listes L1 et L2
	L->liste1=trier_liste(L->liste1);
	L->liste2=trier_liste(L->liste2);
	
	
	while((L->liste1) && (L->liste2))
	{
		if(L->liste1->Entier<L->liste2->Entier)
		{
			tmp=L->liste1;
			L->liste1=L->liste1->svt;		
		}
//		if(L->liste1->Entier==L->liste2->Entier)
//		{
//			
//			tmp=L->liste2;	
//			L->liste1=L->liste1->svt;
//			L->liste2=L->liste2->svt;
//			
//		}
//		if(L->liste1->Entier>L->liste2->Entier)
		else
		{			
			tmp=L->liste2;
			L->liste2=L->liste2->svt;
		}
		tmp->svt=NULL;
		L->liste3=inserer_fin(L->liste3,tmp);
		
	}
	
	while (L->liste1) {
		tmp=L->liste1;
		L->liste1=L->liste1->svt;	
		
        
    }
	while(L->liste2) {
        tmp=L->liste2;
		L->liste2=L->liste2->svt;	
        
    }
    tmp->svt=NULL;
    L->liste3= inserer_fin(L->liste3, tmp);
	return((Cellule*)L->liste3);
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
		free(tmp);//liberer l'espace pointé par tmp
	}
	/*on peut retourner liste mais c'est mieu de retourner NULL
	pour assurer que liste ne contient pas une adresse que null*/ 
	return((Cellule *)NULL);
	
}	

int main() {
    liste *L = Creer_liste(); // Créez une structure de liste

    // Créez quelques cellules pour tester l'insertion
    Cellule *cell1 = Creer_cellule();
    cell1->Entier = 1;

    Cellule *cell2 = Creer_cellule();
    cell2->Entier = 2;

    Cellule *cell3 = Creer_cellule();
    cell3->Entier = 20;

    Cellule *cell4 = Creer_cellule();
    cell4->Entier = 5;

    Cellule *cell5 = Creer_cellule();
    cell5->Entier = 11;

    Cellule *cell6 = Creer_cellule();
    cell6->Entier = 12;

    Cellule *cell7 = Creer_cellule();
    cell7->Entier = 13;

    Cellule *cell8 = Creer_cellule();
    cell8->Entier = 20;

    Cellule *cell9 = Creer_cellule();
    cell9->Entier = 2;

    Cellule *cell10 = Creer_cellule();
    cell10->Entier = 0;

    // Affichage de la liste 1
    printf("Affichage de la liste 1 :\n");
    L->liste1 = insererPos(L->liste1, 0, cell1);
    L->liste1 = insererPos(L->liste1, 1, cell2);
    L->liste1 = insererPos(L->liste1, 2, cell3);
    L->liste1 = insererPos(L->liste1, 1, cell4);
    L->liste1 = insererPos(L->liste1, 2, cell5);
    afficher_liste(L->liste1);

    // Tri de la liste 1
    printf("\nListe 1 après le tri :\n\n");
    L->liste1 = trier_liste(L->liste1);
    afficher_liste(L->liste1);

    // Affichage de la liste 2
    printf("Affichage de la liste 2 :\n");
    L->liste2 = insererPos(L->liste2, 0, cell6);
    L->liste2 = insererPos(L->liste2, 1, cell7);
    L->liste2 = insererPos(L->liste2, 2, cell8);
    L->liste2 = insererPos(L->liste2, 1, cell9);
    L->liste2 = insererPos(L->liste2, 2, cell10);
    afficher_liste(L->liste2);

    // Tri de la liste 2
    printf("\nListe 2 après le tri :\n\n");
    L->liste2 = trier_liste(L->liste2);
    afficher_liste(L->liste2);

    // Concaténation des deux listes
    L->liste3 = concatener(L);
    printf("\nListe 3 après la concaténation :\n\n");
    afficher_liste(L->liste3);
    
    
    
    printf("\n********************************\n\n");
    afficher_liste(L->liste1);
    
    printf("\n********************************\n\n");
	afficher_liste(L->liste2);
    

    return 0;
}



