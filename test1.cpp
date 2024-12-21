#include <stdio.h>
#include <stdlib.h>

// Structure d'une cellule de la liste
typedef struct Cellule {
    int valeur;
    struct Cellule *suivante;
    struct Cellule *precedente;
} Cellule;

// Fonction pour cr�er une nouvelle cellule avec une valeur donn�e
Cellule* initialiserCellule(int valeur) {
    Cellule *nouvelleCellule = (Cellule *)malloc(sizeof(Cellule));
    if (nouvelleCellule == NULL) {
        fprintf(stderr, "Erreur : �chec de l'allocation m�moire pour la cellule\n");
        exit(1);
    }
    nouvelleCellule->valeur = valeur;
    nouvelleCellule->suivante = NULL;
    nouvelleCellule->precedente = NULL;
    return nouvelleCellule;
}

// Fonction pour initialiser une liste vide
Cellule* initialiserListe() {
    return NULL;
}

// Fonction pour ins�rer une cellule au d�but de la liste
Cellule* insererDebut(Cellule *debut, int valeur) {
    Cellule *nouvelleCellule = initialiserCellule(valeur);
    if (debut == NULL) {
        return nouvelleCellule;
    }
    nouvelleCellule->suivante = debut;
    debut->precedente = nouvelleCellule;
    return nouvelleCellule;
}

// Fonction pour ins�rer une cellule � la fin de la liste
Cellule* insererFin(Cellule *debut, int valeur) {
    Cellule *nouvelleCellule = initialiserCellule(valeur);
    if (debut == NULL) {
        return nouvelleCellule;
    }
    Cellule *courante = debut;
    while (courante->suivante != NULL) {
        courante = courante->suivante;
    }
    courante->suivante = nouvelleCellule;
    nouvelleCellule->precedente = courante;
    return debut;
}

// Fonction pour ins�rer une cellule � une position donn�e
Cellule* insererPosition(Cellule *debut, int valeur, int position) {
    if (position < 0) {
        fprintf(stderr, "Erreur : position invalide\n");
        return debut;
    }

    if (position == 0 || debut == NULL) {
        return insererDebut(debut, valeur);
    } else {
        Cellule *nouvelleCellule = initialiserCellule(valeur);
        Cellule *courante = debut;
        int i = 0;
        while (i < position && courante->suivante != NULL) {
            courante = courante->suivante;
            i++;
        }

        nouvelleCellule->precedente = courante->precedente;
        nouvelleCellule->suivante = courante;

        if (courante->precedente != NULL) {
            courante->precedente->suivante = nouvelleCellule;
        } else {
            debut = nouvelleCellule;
        }

        courante->precedente = nouvelleCellule;
        return debut;
    }
}
int taille(Cellule *debut) {
    int taille = 0;
    Cellule *courante = debut;
    while (courante != NULL) {
        taille++;
        courante = courante->suivante;
    }
    return taille;
}

void decouper_liste(Cellule *maliste, int pos, Cellule **maliste1, Cellule **maliste2) {
    if (!maliste || (pos < 0) || (pos >= taille(maliste))) {
        printf("\nPosition non valide\n");
        *maliste1 = NULL;
        *maliste2 = maliste;
        return;
    }

    Cellule *tmp = maliste;
    int compt = 0;

    if (pos == 0) {
        maliste = tmp->suivante;
        if (maliste)
            maliste->precedente = NULL;
        tmp->suivante = NULL;
        *maliste1 = tmp;
        *maliste2 = maliste;
        return;
    }

    while (compt < pos) {
        compt++;
        tmp = tmp->suivante;
    }

    if (tmp->precedente)
        tmp->precedente->suivante = NULL;
    tmp->precedente = NULL;

    *maliste1 = maliste;
    *maliste2 = tmp;
}


// Fonction pour d�couper la liste � une position donn�e
//Cellule* decouper_liste(Cellule *maliste, Cellule *maliste1, int pos) {
//    Cellule *tmp, *crt;
//    int compt = 0;
//    if (!maliste)
//        return maliste1;
//    if (!maliste1)
//        return maliste;
//
//    if (pos < 0 || pos >= taille(maliste)) {
//        printf("\nPosition non valide\n");
//        return maliste;
//    }
//
//    tmp = maliste;
//
//    if (pos == 0) {
//        crt = tmp->suivante;
//        if (crt)
//            crt->precedente = NULL;
//        tmp->suivante = NULL;
//        maliste1 = tmp;
//        return crt;
//    }
//
//    while (compt < pos) {
//        compt++;
//        tmp = tmp->suivante;
//    }
//
//    if (tmp->precedente)
//        tmp->precedente->suivante = NULL;
//    tmp->precedente = NULL;
//    maliste1 = tmp;
//    return crt;
//}

// Fonction pour d�couper la liste � une position donn�e
//Cellule* decouper_liste(Cellule *maliste, Cellule *maliste1, int pos) {
//    if (!maliste || pos < 0 || pos >= taille(maliste)) {
//        printf("\nPosition non valide\n");
//        return maliste;
//    }
//
//    Cellule *tmp = maliste;
//    int compt = 0;
//
//    while (compt < pos) {
//        tmp = tmp->suivante;
//        compt++;
//    }
//
//    if (tmp->precedente) {
//        tmp->precedente->suivante = NULL;
//        tmp->precedente = NULL;
//    } else {
//        maliste = NULL; // Si la position est 0, maliste devient NULL
//    }
//
//    maliste1 = tmp;
//
//    return maliste;
//}

// Fonction pour d�couper la liste � une position donn�e


//Cellule *decouper_liste(Cellule *maliste,Cellule *maliste1,int pos)
//{
//	Cellule *tmp,*crt;
//	int compt=0;
//	if(!maliste) return((Cellule*)maliste1);
//	if(!maliste1) return((Cellule*)maliste);	
//	if((pos<0) && (pos>taille(maliste)))
//	{
//		printf("\nposition non valide\n");
//		return ((Cellule*)maliste);
//	}
//	tmp=maliste;
//	 if (pos == 0) {
//        crt = tmp->suivante;
//        if (crt)
//            crt->precedente = NULL;
//        tmp->suivante = NULL;
//        maliste1 = crt;
//        return maliste;
//    }
//	while(compt<pos)
//	{
//		compt++;
//		tmp=tmp->suivante;		
//	}
//	if (tmp->precedente)
//        tmp->precedente->suivante = NULL;
//	tmp->precedente=NULL;
//	maliste1=tmp;
//	return ((Cellule*)maliste);
//	
//}

Cellule* decouper_liste(Cellule *maliste, int pos, Cellule *maliste1) {
	maliste1=maliste;
//    if (!maliste || (pos < 0) || (pos >= taille(maliste))) {
//        printf("\nPosition non valide\n");
////        maliste1 = maliste;
////        return;
//    }
//
//    Cellule *tmp = maliste;
//    int compt = 0;
//
//    if (pos == 0) {
//        maliste1 = NULL;
//        return;
//    }
//
//    while (compt < pos) {
//        compt++;
//        tmp = tmp->suivante;
//    }
//
//    if (tmp->precedente)
//        tmp->precedente->suivante = NULL;
//
//    maliste1 = tmp->suivante;
//    tmp->suivante = NULL;
}


//Cellule *decouper_liste(Cellule *maliste, Cellule *maliste1, int pos) {
//    if (!maliste || (pos < 0) || (pos >= taille(maliste))) {
//        printf("\nPosition non valide\n");
//        return maliste;
//    }
//
//    Cellule *tmp = maliste;
//    int compt = 0;
//
//    if (pos == 0) {
//        maliste = tmp->suivante;
//        if (maliste)
//            maliste->precedente = NULL;
//        tmp->suivante = NULL;
//        maliste1 = tmp;
//        return maliste;
//    }
//
//    while (compt < pos) {
//        compt++;
//        tmp = tmp->suivante;
//    }
//
//    if (tmp->precedente)
//        tmp->precedente->suivante = NULL;
//    tmp->precedente = NULL;
//    maliste1 = tmp;
//
//    return maliste;
//}


// Fonction pour afficher la liste
void afficherListe(Cellule *debut) {
    Cellule *courante = debut;
    while (courante != NULL) {
        printf("| %d | ", courante->valeur);
        courante = courante->suivante;
    }
    printf("\n");
    
}

// Fonction principale
int main() {
    Cellule *maListe = initialiserListe();

    maListe = insererDebut(maListe, 1);
    maListe = insererDebut(maListe, 2);
    maListe = insererFin(maListe, 3);
    maListe = insererPosition(maListe, 4, 1);
    
    maListe = insererPosition(maListe, 9, 0);
    maListe = insererPosition(maListe, 9, 1);
    maListe = insererPosition(maListe, 4, 2);
    maListe = insererPosition(maListe, 11, 3);
    maListe = insererPosition(maListe, 5, 4);
    maListe = insererPosition(maListe, 4, 5);
    maListe = insererPosition(maListe, 3, 2);

    afficherListe(maListe);
    
    int laTaille = taille(maListe);
    printf("Taille de la liste : %d\n", laTaille);
    
//    Cellule *maListe1 = initialiserListe();
//    maListe = decouper_liste(maListe, maListe1, 4);
//	
//	Cellule *maListe1=initialiserListe();
//	decouper_liste(maListe,maListe1,3);
	
	Cellule *maListe1;
	decouper_liste(maListe, 3, maListe1);
	
	printf("*    lokpok%d",maListe1->valeur);
//
//    printf("\nListe 1 apres decoupage : ");
//    afficherListe(maListe);
//    printf("\nListe 2 apres decoupage : ");
//    afficherListe(maListe1);

//	Cellule *maListe1 = NULL;
//	maListe = decouper_liste(maListe,5, maListe1);
//printf("\nListe 1 apres decoupage : ");
//    afficherListe(maListe);
//    printf("\nListe 2 apres decoupage : ");
//    afficherListe(maListe1);


    return 0;
}

