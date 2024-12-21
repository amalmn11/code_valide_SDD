#include <stdio.h>
#define RC '\n'

/*le fonction lit le premier caract�re du mot, et les caract�res suivants du mot seront stock�s dans le tampon d'entr�e 
(le "buffer"). par exemple Si l'utilisateur entre "Bonjour" en saisissant la lettre "B", seul le "B" sera lu et affich� 
si on veux lire un mot complet otilise boucle comme ceci */
/*

int main() {
	
    char caractere;

    printf("Saisissez un caract�re : ");
    //comme �a getchar lit "r�cuperer le 1ere caractere apres entrer"
    //caractere = getchar()
    while((caractere = getchar())!=RC)

    printf("Le caract�re saisi est : %c\n", caractere);

    return 0;
}
*/

/*pour afficher le code ASCII d'un caractere il suffit de l'affich� en utilisant %d

#include <stdio.h>

int main() {
    char caractere;

    printf("Saisissez un caract�re : ");
    caractere = getchar(); // On lit un caract�re depuis l'entr�e standard

    printf("Le code ASCII du caract�re saisi est : %d\n", caractere);

    return 0;
}
*/





//affichage des valeur reel de caractere numerique non pas le code ASCII
#include <stdio.h>

int main() {
    char caractere;

    printf("Saisissez un caract�re : ");
    caractere = getchar(); // On lit un caract�re depuis l'entr�e standard
    caractere-='0';

    printf("Le code ASCII du caract�re saisi est : %d\n", caractere);

    return 0;
}


/*le contraire ici on donne une valeur nummerique et on affiche le caractere correspond � ce caract�re

#include <stdio.h>

int main() {
    int caractere;

    //printf("Saisissez un caract�re : ");
    caractere = 65 ; // On lit un caract�re depuis l'entr�e standard

    printf("Le code ASCII du caract�re saisi est : %c\n", caractere);

    return 0;
}
*/

