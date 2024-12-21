#include <stdio.h>
#include <stdlib.h>

//

typedef struct lst {
    int Entier;
    struct lst *svt;
} Cellule;

Cellule *Creer_cellule(int entier) {
    Cellule *NE = (Cellule *)malloc(sizeof(Cellule));
    if (!NE) {
        printf("Problème d'allocation\n");
        exit(EXIT_FAILURE);
    }
    NE->Entier = entier;
    NE->svt = NULL;
    return NE;
}

int Est_vide_liste(Cellule *liste) {
    return !liste;
}

int Taille_liste(Cellule *liste) {
    int taille = 0;
    Cellule *tmp = liste;
    while (tmp) {
        taille++;
        tmp = tmp->svt;
    }
    return taille;
}

Cellule *insererDebut(Cellule *liste, Cellule *NE) {
    if (!NE) return liste;
    NE->svt = liste;
    return NE;
}

Cellule *insererFin(Cellule *liste,Cellule *NE)
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


// tri croissant
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


Cellule *concatener(Cellule *liste1, Cellule *liste2) 
{
    
    Cellule *tmp;
    Cellule *L = NULL; 
	if (!liste1) return trier_liste(liste2);
    if (!liste2) return trier_liste(liste1);

	liste1=trier_liste(liste1);
	liste2=trier_liste(liste2);
    
    

    while (liste1 && liste2) {
        if (liste1->Entier < liste2->Entier) {
            tmp = liste1;
            liste1 = liste1->svt;
        } else {
            tmp = liste2;
            liste2 = liste2->svt;
        }
        tmp->svt = NULL;
        L = insererFin(L, tmp);
    }

    // Ajouter le reste de la liste 1 (si elle n'est pas vide)
    while (liste1) {
        tmp = liste1;
        liste1 = liste1->svt;
        tmp->svt = NULL;
        L = insererFin(L, tmp);
    }

    // Ajouter le reste de la liste 2 (si elle n'est pas vide)
    while (liste2) {
        tmp = liste2;
        liste2 = liste2->svt;
        tmp->svt = NULL;
        L = insererFin(L, tmp);
    }
	return((Cellule*)L);
}

void afficher_liste(Cellule *liste) {
    Cellule *tmp = liste;
    while (tmp) {
        printf("| %d | ", tmp->Entier);
        tmp = tmp->svt;
    }
    printf("\n\n");
}

Cellule *vider_liste(Cellule *liste) {
    Cellule *tmp;
    while (liste) {
        tmp = liste;
        liste = liste->svt;
        free(tmp);
    }
    return NULL;
}

int main() {
    Cellule *liste1 = NULL;
    Cellule *liste2 = NULL;
    Cellule *L;

    liste1 = insererFin(liste1, Creer_cellule(1));
    liste1 = insererFin(liste1, Creer_cellule(2));
    liste1 = insererFin(liste1, Creer_cellule(20));
    liste1 = insererFin(liste1, Creer_cellule(5));
    liste1 = insererFin(liste1, Creer_cellule(11));

    liste2 = insererFin(liste2, Creer_cellule(12));
    liste2 = insererFin(liste2, Creer_cellule(4));
    liste2 = insererFin(liste2, Creer_cellule(0));
    liste2 = insererFin(liste2, Creer_cellule(13));
    liste2 = insererFin(liste2, Creer_cellule(14));

    printf("Affichage de la liste 1:\n");
    afficher_liste(liste1);

    printf("Affichage de la liste 2:\n");
    afficher_liste(liste2);

    printf("Liste 1 apres le tri:\n");
    liste1 = trier_liste(liste1);
    afficher_liste(liste1);

    printf("Liste 2 apres le tri:\n");
    liste2 = trier_liste(liste2);
    afficher_liste(liste2);

    L = concatener(liste1, liste2);
    printf("Liste 3 apres la concatenation:\n");
    afficher_liste(L);
    
    
    // 	imporatnt : la liste liste1 sera pas modifie ici on le retourne pas 
    //	afficher_liste(liste1);
    
    
    

    //L = vider_liste(L); // Libérer la mémoire

    return 0;
}

