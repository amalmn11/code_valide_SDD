#include <stdio.h>
#define RC '\n'

/*le fonction lit le premier caractère du mot, et les caractères suivants du mot seront stockés dans le tampon d'entrée 
(le "buffer"). par exemple Si l'utilisateur entre "Bonjour" en saisissant la lettre "B", seul le "B" sera lu et affiché 
si on veux lire un mot complet otilise boucle comme ceci */
/*

int main() {
	
    char caractere;

    printf("Saisissez un caractère : ");
    //comme ça getchar lit "récuperer le 1ere caractere apres entrer"
    //caractere = getchar()
    while((caractere = getchar())!=RC)

    printf("Le caractère saisi est : %c\n", caractere);

    return 0;
}
*/

/*pour afficher le code ASCII d'un caractere il suffit de l'affiché en utilisant %d

#include <stdio.h>

int main() {
    char caractere;

    printf("Saisissez un caractère : ");
    caractere = getchar(); // On lit un caractère depuis l'entrée standard

    printf("Le code ASCII du caractère saisi est : %d\n", caractere);

    return 0;
}
*/





//affichage des valeur reel de caractere numerique non pas le code ASCII
#include <stdio.h>

int main() {
    char caractere;

    printf("Saisissez un caractère : ");
    caractere = getchar(); // On lit un caractère depuis l'entrée standard
    caractere-='0';

    printf("Le code ASCII du caractère saisi est : %d\n", caractere);

    return 0;
}


/*le contraire ici on donne une valeur nummerique et on affiche le caractere correspond à ce caractère

#include <stdio.h>

int main() {
    int caractere;

    //printf("Saisissez un caractère : ");
    caractere = 65 ; // On lit un caractère depuis l'entrée standard

    printf("Le code ASCII du caractère saisi est : %c\n", caractere);

    return 0;
}
*/

