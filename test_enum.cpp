#include <stdio.h>

// D�claration de l'�num�ration pour les types de valeurs
typedef enum
{
    Entier,
    Reel,
    Caractere
}TypeValeur;

typedef union
{
        int entier;
        float reel;
        char caractere;
}valeur;
// D�finition de la structure qui inclut le type et l'union
typedef struct {
    TypeValeur type;
    valeur val;
}Valeur ;

int main() {
	
	
    // D�claration d'une variable de type structure
    Valeur maValeur;

    // Utilisation de la structure pour stocker un entier
//    maValeur.type = Enti;
    maValeur.val.entier = 42;

//	error
//	printf("%s",maValeur[1]);
    // Affichage de la valeur en fonction du type
    switch (maValeur.type) {
        case Entier:
            printf("La valeur est un entier : %d\n", maValeur.val.entier);
            break;
        case Reel:
            printf("La valeur est un r�el : %f\n", maValeur.val.reel);
            break;
        case Caractere:
            printf("La valeur est un caract�re : %c\n", maValeur.val.caractere);
            break;
        default:
            printf("Type non g�r�.\n");
    }

    return 0;
}


//#include <stdio.h>
//
//// D�claration de l'�num�ration pour les jours de la semaine
//enum JourSemaine {
//    Lundi, Mardi, Mercredi, Jeudi, Vendredi, Samedi, Dimanche
//};

//int main() {
//    // Boucle pour parcourir chaque �l�ment de l'�num�ration
//    for (enum JourSemaine jour = Lundi; jour <= Dimanche; jour++)
//	{
//        // Utilisation d'une instruction switch pour afficher chaque jour
//        switch (jour) {
//            case Lundi:
//                printf("Lundi\n");
//                break;
//            case Mardi:
//                printf("Mardi\n");
//                break;
//            case Mercredi:
//                printf("Mercredi\n");
//                break;
//            case Jeudi:
//                printf("Jeudi\n");
//                break;
//            case Vendredi:
//                printf("Vendredi\n");
//                break;
//            case Samedi:
//                printf("Samedi\n");
//                break;
//            case Dimanche:
//                printf("Dimanche\n");
//                break;
//            default:
//                printf("Jour non valide\n");
//        }
//    }
//
//    return 0;
//}

