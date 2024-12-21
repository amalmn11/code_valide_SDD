#include <stdio.h>

// Déclaration de l'énumération pour les types de valeurs
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
// Définition de la structure qui inclut le type et l'union
typedef struct {
    TypeValeur type;
    valeur val;
}Valeur ;

int main() {
	
	
    // Déclaration d'une variable de type structure
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
            printf("La valeur est un réel : %f\n", maValeur.val.reel);
            break;
        case Caractere:
            printf("La valeur est un caractère : %c\n", maValeur.val.caractere);
            break;
        default:
            printf("Type non géré.\n");
    }

    return 0;
}


//#include <stdio.h>
//
//// Déclaration de l'énumération pour les jours de la semaine
//enum JourSemaine {
//    Lundi, Mardi, Mercredi, Jeudi, Vendredi, Samedi, Dimanche
//};

//int main() {
//    // Boucle pour parcourir chaque élément de l'énumération
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

