#include <stdio.h>
#include <stdlib.h>
#define MaxElm 100

//programme de manipulation d'une liste statique 

//définition de la structure
typedef struct lst
{
	int TabInt[MaxElm];//table des entiers de taille max 100
	int nbElm;//nbr d'element de la table
}Liste;


//allocation de la mémoire
Liste *Creer_Liste()
{
    Liste *p;
    p = (Liste *)malloc(sizeof(Liste)); //allocation de l'espace mémoire  
    if (!p) exit(1); // si l'allocation a échoué
    return ((Liste *)p); //retourne l'adresse de l'espace mémoire réservé
}

//initialisation du tableau
int initListe(Liste *MaListe)
{
    //si MaListe n'existe pas 
    if (!MaListe) 
    {
        printf("\nErreur d'allocation "); return ((int)0);
    }
    //s'il existe, on initialise le nombre d'éléments
    MaListe->nbElm = 0;
    return ((int)1);
}

//tester est-ce que la liste est vide
int EstVide(Liste MaListe)
{
    return ((int)MaListe.nbElm == 0);
}

//tester est-ce que la liste est saturée
int EstSaturee(Liste MaListe)
{
    return ((int)MaListe.nbElm == MaxElm);
}


//fonction d'insertion d'un entier à la fin de la liste
int insererFin(Liste *MaListe, int Elm)
{
    //teste d'existence
    if (!MaListe) 
    {
        printf("\nErreur d'allocation de la mémoire "); 
        return ((int)-1);
    }
    //tester si la liste est saturée
    if (EstSaturee(*MaListe))
    {
        printf("\nTable saturée, vous ne pouvez pas ajouter %d", Elm);
        return ((int)0);
    }
    //si la liste existe et n'est pas saturée
    MaListe->TabInt[MaListe->nbElm] = Elm; //insère l'élément à la fin de la liste
    MaListe->nbElm++; //incrémentation de la taille de la liste
    return ((int)1);
}

//fonction d'insertion d'un élément à une position donnée
int insererPos(Liste *MaListe, int Elm, int pos)
{
    int i;
    //teste d'existence
    if (!MaListe) 
    {
        printf("\nErreur d'allocation de la mémoire "); 
        return ((int)-2);
    }
    //tester si la liste est saturée
    if (EstSaturee(*MaListe))
    {
        printf("\nTable saturée, vous ne pouvez pas ajouter %d", Elm);
        return ((int)-1);
    } 
    
    //tester si la position est une position valide ou non
    if ((pos < 0) || (pos > MaListe->nbElm)) 
    {
        printf("\nPosition non valide");
        exit((int)0);
    }
//    if(pos==MaListe->nbElm)
//    {
//    	printf("\n*\n");
//    	MaListe->TabInt[pos] = Elm; //insère l'élément à la fin de la liste
//    	MaListe->nbElm++; //incrémentation de la taille de la liste
//    	return ((int)1);
//	}
    //si la position est valide
    for (i = MaListe->nbElm - 1; i >= pos; i--) {
        MaListe->TabInt[i + 1] = MaListe->TabInt[i]; //décalage des éléments
    }
    MaListe->TabInt[pos] = Elm; //insère l'élément après le décalage
    MaListe->nbElm++; //incrémentation du nombre d'éléments de la liste
    return ((int)2);	
}


////fonction de suppression dans une position donnée
//int supprimerPos(Tab *MaTab,int pos)
//{	
//	int i;
//	//	test d'existance
//	if(!MaTab)
//	{
//		printf("\nerror d'allocation de la memoire "); 
//		return ((int)-2);
//	}  
//	//	//tester si le tableau est vide
//	if(EstVide(*MaTab))
//	{
//		printf("\nle tableau est vide");
//		return ((int)-1);
//	}
//	//tester si la position est une position valide ou non
//	if((pos<0) || (pos>=MaTab->nbElm))
//	{
//		printf("\nposition non valide");
//		return ((int) 0);  
//	}
//	for(i=pos;i<MaTab->nbElm-1;i++) MaTab->TabInt[i]=MaTab->TabInt[i+1]; //décalage des elements
//	
//	MaTab->nbElm--;//décrémentation du nombre d'elements du tableau
//	return ((int) 1);
//}

//fonction de suppression dans une position donnée
int supprimerPos(Liste *MaListe, int pos)
{	
    int i;
    //	test d'existence
    if (!MaListe)
    {
        printf("\nErreur d'allocation de la mémoire "); 
        return ((int)-2);
    }  
    //	//tester si la liste est vide
    if (EstVide(*MaListe))
    {
        printf("\nLa liste est vide");
        return ((int)-1);
    }
    //tester si la position est une position valide ou non
    if ((pos < 0) || (pos >= MaListe->nbElm))
    {
        printf("\nPosition non valide");
        return ((int)0);  
    }
     //décalage des éléments
    for (i = pos; i < MaListe->nbElm - 1; i++) MaListe->TabInt[i] = MaListe->TabInt[i + 1];
    MaListe->nbElm--; //décrémentation du nombre d'éléments de la liste
    return ((int)2);
}


//fonction qui supprime toute les occurances d'u element dans le tableau
int supprimer_T_occ(Liste *MaListe,int Elm)
{
	int i=0,j;
	//	test d'existance
	if(!MaListe)
	{
		printf("\nerror d'allocation de la memoire "); 
		return ((int)-1);
	}  
	//	//tester si le tableau est vide
	if(EstVide(*MaListe))
	{
		printf("\nle tableau est vide");
		return ((int)0);
	}
	//suppression de toutes les occurances 
//	while(i<MaListe->nbElm)
//	{
//		//tester si l'element égale à MaTab->TabInt[i]
//		if(MaListe->TabInt[i]==Elm)
//		{
//			supprimerPos(MaListe,i);
//			i--;//si on a deux elements contigues qui sont les égaux
//		}
//		i++;//sinon incrémenter i
//	}
//	return ((int) 1);
	for(i=0;i<MaListe->nbElm;i++)
	{
		if(MaListe->TabInt[i]==Elm)
		{
//			for (j = i; j < MaListe->nbElm - 1; j++) MaListe->TabInt[j] = MaListe->TabInt[j + 1];
//			MaListe->nbElm--;
			supprimerPos(MaListe,i);
			i--;//si on a deux elements contigues qui sont les égaux
		}
		
	}
	return ((int) 1);	
		
}

//fonction d'affichage des elements du tableau
void afficher(Liste MaListe)
{
	int i;
	for(i=0;i<MaListe.nbElm;i++){
		printf("\nTableau[%d] = %3d\n",i+1,MaListe.TabInt[i]);
	}
}

//fonction qui retourne le nombre d'element de la liste
int nbrElm(Liste MaListe){
	return((int)MaListe.nbElm);
}

//fonction qui supprime la 1ere occurance d'un element donnée
int supprimer_1ere_occ(Liste *MaListe,int Elm){
	int i=0;
	//	test d'existance
	if(!MaListe)
	{
		printf("\nerror d'allocation de la memoire "); 
		return ((int)0);
	} 
	//suppression de la 1ere occurance 
	while(i<MaListe->nbElm)
	{
		if(MaListe->TabInt[i]==Elm){
			supprimerPos(MaListe,i);
			break;
		}
		i++;
	}
	return ((int)1);
}

int main()
{
    Liste *MaListe = Creer_Liste(); // Création de la liste

    // Initialisation de la liste
    if (initListe(MaListe) == 0)
    {
        printf("\nErreur lors de l'initialisation de la liste");
        return 1;
    }
    printf("\nListe initialisee avec succes!");
    // Tester si la liste est vide
    if (EstVide(*MaListe))
    {
        printf("\nLa liste est vide.");
    }

    // Tester si la liste est saturée
    if (EstSaturee(*MaListe))
    {
        printf("\nLa liste est saturee.");
    }

    // Ajouter des éléments à la fin de la liste
    insererFin(MaListe, 10);
    insererFin(MaListe, 20);
    insererFin(MaListe, 30);
    insererFin(MaListe, 10);
    insererFin(MaListe, 30);
    insererFin(MaListe, 30);
    insererFin(MaListe, 20);

    // Afficher les éléments de la liste
    printf("\nListe apres insertion a la fin :");
    afficher(*MaListe);

    // Ajouter un élément à une position donnée
    //insererPos(MaListe, 11, 0);
    //insererPos(MaListe, 11, 1);
//    insererPos(MaListe, 22, 2);
//    insererPos(MaListe, 1, 3);
//    insererPos(MaListe, 13, 4);
//    insererPos(MaListe, 15, 5);

    // Afficher les éléments de la liste après l'insertion
    printf("\nListe apres insertion de l'element 11 a la position 1 :");
    afficher(*MaListe);

    // Supprimer un élément à une position donnée
    supprimerPos(MaListe, 7);

    // Afficher les éléments de la liste après la suppression
    printf("\nListe apres suppression a la position 2 :");
    afficher(*MaListe);

    // Supprimer toutes les occurrences d'un élément
    supprimer_T_occ(MaListe, 30);

    // Afficher les éléments de la liste après la suppression des occurrences
    printf("\nListe apres suppression de toutes les occurrences de 30 :");
    afficher(*MaListe);

    // Supprimer la première occurrence d'un élément
    supprimer_1ere_occ(MaListe, 20);

    // Afficher les éléments de la liste après la suppression de la première occurrence
    printf("\nListe apres suppression de la premiere occurrence de 20 :");
    afficher(*MaListe);

    // Afficher le nombre d'éléments de la liste
    printf("\nNombre d'elements dans la liste : %d", nbrElm(*MaListe));

    // Libérer la mémoire
    free(MaListe);

    return 0;
}
