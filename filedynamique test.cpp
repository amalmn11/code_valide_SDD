#include <stdio.h>
#include <stdlib.h>

// Définition de la structure de la cellule
typedef struct Cellule
{
    int entier;
    struct Cellule *svt; // Pointeur vers la cellule suivante
} Cellule;

// Définition de la structure de la file
typedef struct File
{
    Cellule *debut; // Pointeur vers le début de la file
    Cellule *fin;   // Pointeur vers la fin de la file
} PTFile;

//fonction d'allocation d'espace memoire pour la ma file
PTFile* creer_Ptfile()
{
	PTFile *NF;
	NF=(PTFile *)malloc(sizeof(PTFile));//allocation de l'espace mémoire  
	// si l'allocation a echoué
	if(!NF)
	{
		printf("\nErreur d'allocation");
		exit(1); // si l'allocation a echoué	
	}
	NF->debut=NF->fin=NULL;//initialiser les elements de la structue PTFile
	return ((PTFile*)NF);//retourne l'adresse de l'espace mémoire reservé 
}


//creer une cellule
Cellule* creer_Cellule()
{
	Cellule *Cl;
	Cl=(Cellule *)malloc(sizeof(Cellule));//allocation de l'espace mémoire  
	// si l'allocation a echoué
	if(!Cl)
	{
		printf("\nErreur d'allocation");
		exit(1); // si l'allocation a echoué	
	}
	Cl->svt=NULL;//initialiser les elements de la structue PTFile
	return ((Cellule*)Cl);//retourne l'adresse de l'espace mémoire reservé 
}



// Fonction pour vérifier si la file est vide
int EstVide_File(PTFile Mafile)
{
	return((int)!Mafile.debut);
}


// Fonction pour vider la file
int Razer_PTfile(PTFile *Mafile)
{
	PTFile *tmp;
	//teste d'existance
	if(!Mafile) 
	{
		printf("\nerror de l'allocation "); return ((int)0);
	}
	//supprimer tous les elements de la file 
	while(Mafile->debut)
	{	
		tmp=Mafile;//tmp pointe sur la cellule pointé par Mafile
		Mafile->debut=Mafile->debut->svt;//Mafile pointe sur la cellule suivant
		free(tmp);//liberer l'espace mémoire pointé par tmp
	}
	//affecter NULL au pointeur fin pour s'assurer que fin ne contient aucune adresse
	Mafile->fin=NULL;
	return ((int)1);
}


// Fonction pour enfiler une cellule dans la file
int enfiler(PTFile *Mafile,Cellule *NF)
{
	//si Mafile ou NF n'existe pas 
	if(!Mafile || !NF)
	{
		/*error d'allocation de l'espace memoire 
		ou bien la cellule n'exite pas*/
		printf("n\error de l'allocation");
		return ((int)0);
	}
	//si Mafile existe mais il est vide
	if(EstVide_File(*Mafile))
	{
		/*La cellule pointé par debut et fin va 
		etre la 1ere cellule */
		Mafile->debut=Mafile->fin=NF;
	}
	//si la file n'est pas vide 
	Mafile->fin->svt=NF;
	Mafile->fin=NF;
	return((int)1);
}


// Fonction pour défiler une cellule de la file
int defiler(PTFile *Mafile)
{
	Cellule *tmp;
	//si la file n'existe pas
	if(!Mafile)
	{
		printf("\nerror d'adllocation e l'espace memoire");
		return ((int)-2);
	}
	//si la file existe mais il est vide 
	if(EstVide_File(*Mafile))
	{
		printf("\nla file existe mais il est vide");
		return ((int)-1);
	}
	//si la file contient un seul element 
	if(Mafile->debut==Mafile->fin)
	{
		return ((int)Razer_PTfile(Mafile));
	}
	//si la file contient plusieur cellule 
	tmp=Mafile->debut;//tmp pointe sur la cellule pointé par Mafile
	Mafile->debut=Mafile->debut->svt;//Mafile pointe sur la cellule suivant
	free(tmp);//liberer l'espace mémoire pointe par tmp
	return ((int)1);
}

// Fonction pour afficher tous les éléments de la file
/*on peut ici travailer par pasage par adresse et tmp 
de type cellule qui qui pointe sur debut */
void afficher(PTFile *Mafile)
{
	Cellule *tmp;
	//si la file est vide 
	if(EstVide_File(*Mafile))
	{
		printf("\non peut pas afficher une file vide");
	}
	//si la file n'est pas vide 
	tmp=Mafile->debut;
	while(tmp)
	{
		printf("%d\t",tmp->entier);
		tmp=tmp->svt;
	}
}

int main()
{
    PTFile *Mafile = creer_Ptfile();

    // Crée et initialise une file vide
    printf("File cree et initialisee.\n");

    // Ajoute des éléments à la file
    Cellule *cel1 = creer_Cellule();
    cel1->entier = 4;
    enfiler(Mafile, cel1);

    Cellule *cel2 = creer_Cellule();
    cel2->entier = 5;
    enfiler(Mafile, cel2);

    Cellule *cel3 = creer_Cellule();
    cel3->entier = 6;
    enfiler(Mafile, cel3);

    printf("Elements ajoutes a la file : 4, 5 et 6.\n");

    // Affiche les éléments de la file
    printf("File actuelle : \n");
    afficher(Mafile);

    // Vérifie si la file est vide
    printf("\nLa file est %s.\n", EstVide_File(*Mafile) ? "vide" : "non vide");

    // Vérifie si la file est saturée (dans ce cas, elle ne peut pas l'être)
    printf("La file est non saturee.\n");
    
    // Défile un élément de la file
    defiler(Mafile);
    printf("Element defile.\n");

    // Affiche la file après le défilement
    printf("File actuelle : \n");
    afficher(Mafile);

    // Libère la mémoire
    Razer_PTfile(Mafile);
    printf("\nAffichage de la file apres le vidage de la file : ");
    afficher(Mafile);
    free(Mafile);

    return 0;
}

