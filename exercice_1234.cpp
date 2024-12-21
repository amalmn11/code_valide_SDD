#include <stdio.h>
#define RC '\n'
#define BL ' '

int main() {
    int intValue = 0;
    int sign = 1;
    int c;

    printf("Entrez une chaine de chiffres : ");

    // Lire les caract�res un par un
    while ((c = getchar()) != RC && c != BL) {
        if (c == '-') {
            sign = -1; // Si le caract�re est un signe n�gatif, on note le signe
        } else if (c >= '0' && c <= '9') {
            // Si le caract�re est un chiffre, on le convertit en entier
            intValue = intValue * 10 + (c - '0');
        } else {
            // G�rer les caract�res non num�riques (erreur)
            printf("Caractere non valide : '%c'\n", c);
            return 1; // Sortie avec code d'erreur
        }
    }

    // Appliquer le signe si c'est un nombre n�gatif
    intValue *= sign;

    printf("La valeur entiere est : %d\n", intValue);

    return 0;
}

