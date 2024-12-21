#include <stdio.h>
#include <stdlib.h>

#define MaxElem 10 // Nombre maximum d'�l�ments dans la file

//D�claration des structures et types
typedef struct
{
    int Tab[MaxElem];//Tableau de la file
    int debut;       //Indique la t�te de la file
    int fin;         //Indique la queue de la file
} TFile;

//D�finition des fonctions

//fonction qui permet de creer TFile
TFile* creer_TFile()
{
    // Cr�e et alloue de la m�moire pour une file vide
    TFile* F;
    F = (TFile*)malloc(sizeof(TFile));
    //si la file n'existe pas 
    if (!F)
    {
        printf("Erreur ! Impossible de creer la file.\n");
        exit(0);
    }
    return ((TFile*)F);//retourner l'adresse de la file 
}

//fonction qui initialise la file
int initialiser_TFile(TFile* F)
{
    //Initialise une file vide
    if (!F) return ((int)-1); //La file n'existe pas
    //fin de if 
    F->debut=F->fin=-1;
    return ((int)1);
}

//fonction qui retourn la taille du Tab
int taille_TFile(TFile F)
{
    // Retourne la taille de la file
    return ((int)((F.fin)-(F.debut)+1));
}

//on peut travailler avec passage par valeur
//fonction qui teste si la file est vide 
int est_vide_TFile(TFile F)
{
    // V�rifie si la file est vide
    //F->fin == -1 est optionl
    return (int)(F.debut == -1 && F.fin == -1);
}

//on peut travailler avec passage par valeur
int est_sature_TFile(TFile F)
{
    // V�rifie si la file est satur�
    return ((int)(taille_TFile(F) == MaxElem));
}

//un petit peu compliqu�
int tasser_TFile(TFile* F)
{
    // Tasse le tableau de la file
    int indice;
    if (!F)
        return (int)0; // La file n'existe pas
    for (indice = F->debut; indice <= F->fin; indice++)
        F->Tab[indice - F->debut] = F->Tab[indice];
    F->fin = indice - (F->debut) - 1;
    F->debut = 0;
    return (int)1;
}

//un petit peu compliqu�
int enfiler_TFile(TFile* F,int n)
{
    // Enfile un �l�ment dans la file
    if (!F)
    {
        printf("Erreur ! La file n'existe pas.\n");
        exit(0);
    }
    if (est_sature_TFile(*F))
    {
        printf("\nLa file est satur�e, impossible d'enfiler %d.\n", n);
        return (int)0;
    }
    if (F->fin==MaxElem-1)
    {
    	printf("\nla file n'est pas saturee vous devez tasser la file ");
    	tasser_TFile(F);
	}
    if (est_vide_TFile(*F))
    {
        F->fin++;
        F->debut++;
        F->Tab[F->fin] = n;
        return (int)1;
    }
    F->fin++;
    F->Tab[F->fin] = n;
    return (int)1;
}

//tasser_TFile(TFile *Mafile)
//{
//	int i;
//	if(!Mafile)
//	{
//		printf("error d'allocation");
//		return((int)0);
//	}
//	for(i=0;i<taille_TFile(*Mafile);i++)
//	{
//		Mafile->Tab[i]=Mafile->Tab[Mafile->debut++];
//	}
//	Mafile->fin=taille_TFile(*Mafile)-1;
//	Mafile->debut=0;
//	return ((int)1);
//}
//
//
//int enfiler_TFile(TFile *Mafile, int val)
//{
//	//test si la file existe dans la memeoire
//	if(!Mafile) return ((int) -1);
//	
//	//test si satur�e
//	if(est_sature_TFile(*Mafile))
//	{
//		printf("\nla file est sature\n");
//		return((int) 0);
//	} 
//	
//	//test si vide
//	if(est_vide_TFile(*Mafile))
//	{
//		Mafile->Tab[0] = val;
//		Mafile->debut = Mafile->fin =0;
//		return ((int) 1);
//	}
//	//tasser la table si la file n'est pa sature mais l'indice de fin est arriv� au dernier element
//	if(Mafile->fin == MaxElem-1) tasser_TFile(Mafile);
//	//insertion de val et incrementaion de lindice fin
//	Mafile->Tab[++Mafile->fin] = val;
//	return ((int) 1);
//	
//}


//
int vider_TFile(TFile* F)
{
	if(!F) return((int)-1);
	F->debut=F->fin=-1;
	return ((int)1);
}
int defiler_TFile(TFile* F)
{
    // D�file un �l�ment de la file
    if (!F) return ((int)-1); // La file n'existe pas
    if (est_vide_TFile(*F)) return (int)0; // La file est vide
    if (F->debut == F->fin)
    {
        return ((int)vider_TFile(F));
    }
    F->debut++;
    return (int)1;
}

void afficher_TFile(TFile* F)
{
    // Affiche les �l�ments de la file
    if (est_vide_TFile(*F))
    {
        printf("La file est vide.\n");
        return;
    }
    int i;
    //on commence par debut pour afficher juste les element r�el dans le tableua
    for (i = F->debut; i <= F->fin; i++)
        printf(" | %d |\t", F->Tab[i]);
    printf("\n\n");
}

//int inserer_TFile_pos(TFile* F, int pos, int valeur)
//{
//    // Ins�re un �l�ment � une position donn�e dans la file
//    int valdefi, taille = taille_TFile(F), cpt = 1;
//    if (!F)
//        return (int)-1;
//    if (!taille && pos == 1)
//    {
//        enfiler_TFile(F, valeur);
//        return (int)1;
//    }
//    if (pos < 1 || pos > taille)
//        return (int)-2; // Position invalide
//    while (cpt <= taille)
//    {
//        valdefi = F->Tab[F->debut];
//        defiler_TFile(F);
//        if (cpt == pos)
//        {
//            enfiler_TFile(F, valeur);
//        }
//        enfiler_TFile(F, valdefi);
//        cpt++;
//    }
//    return (int)1;
//}

int main()
{
    TFile* F = creer_TFile();
    initialiser_TFile(F);

    // Cr�e et initialise une file vide
    printf("File cree et initialisee.\n");

    // Ajoute des �l�ments � la file
    enfiler_TFile(F, 1);
    enfiler_TFile(F, 2);
    enfiler_TFile(F, 3);
	enfiler_TFile(F, 4);
	enfiler_TFile(F, 5);
	enfiler_TFile(F, 6);
	enfiler_TFile(F, 7);
	enfiler_TFile(F, 8);
	enfiler_TFile(F, 9);
	enfiler_TFile(F, 10);
	
    printf("\nelements ajoutes a la file : 4, 5 et 6.\n");

    // Affiche la file actuelle
//    printf("\nFile actuelle : \n");
//    afficher_TFile(F);
//
//    // Affiche la taille de la file
//    printf("\nLa taille de la file est de %d elements.\n", taille_TFile(*F));
//
//    // V�rifie si la file est vide
//    printf("\nLa file est %s.\n", est_vide_TFile(*F) ? "vide" : "non vide");
//
//    // V�rifie si la file est satur�e
//    printf("\nLa file est %s.\n", est_sature_TFile(*F) ? "saturee" : "non saturee");
//
//    
    // Affiche la file apr�s les insertions
    printf("\nFile actuelle : \n");
    afficher_TFile(F);

//    // Recherche la position d'�l�ments dans la file
//    printf("\nPosition de 4 dans la file : %d\n", chercher_pos_TFile(F, 4));
//    printf("\nPosition de 7 dans la file : %d\n", chercher_pos_TFile(F, 7));

    // D�file un �l�ment de la file
    
    defiler_TFile(F);

    printf("\n\n**********elements defile**************.\n");
    
    printf("File actuelle : \n");
    afficher_TFile(F);
	
	defiler_TFile(F);

    printf("\n\n**********elements defile**************.\n");
    
    printf("File actuelle : \n");
    afficher_TFile(F);
	

	enfiler_TFile(F, 5);  
 

    // Affiche la file apr�s le d�filement
    printf("\nFile actuelle : \n");
    afficher_TFile(F);
    
    // Affiche la file apr�s le tassage
//    printf("File actuelle : \n");
//    afficher_TFile(F);

    // Lib�re la m�moire
    free(F);

    return (int)0;
}
