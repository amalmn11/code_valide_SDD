#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RC '\n'  // Constante pour le caractère de retour à la ligne
#define BL ' '   // Constante pour le caractère espace

// Fonction pour supprimer les caractères blancs inutiles
char Epurerblanc()
{
	char carac;
	while((carac=getchar())==BL); // Ignore les caractères blancs (y compris les espaces et les tabulations)
	return((char) carac);
}

// Vérifie si le caractère est un chiffre
int EstNumerique(char car)
{
	return((int)(('0'<=car)&&(car<='9'))); // Retourne 1 si le caractère est un chiffre, 0 sinon
}

// Vérifie si le caractère est un signe (+ ou -)
int EstSigne(char car)
{
	return((int)((car=='+')||(car=='-'))); // Retourne 1 si le caractère est un signe, 0 sinon
}

// Convertit un caractère en float
float CartoFloat(char car)
{
	return ((float)(car-'0')); // Convertit un caractère numérique en float
}

// Fonction principale pour lire un nombre à virgule flottante
float lire_Entier()
{
	char car, signe;
	float val1=0.0, virgule=0.0, val2=0.0 ;
	car=Epurerblanc(); // Supprime les caractères blancs initiaux

	if(car==RC) 
	{
		printf("\n Erreur : Fin de ligne inattendue");
		exit(-1);
	} //fin de if
	if(EstSigne(car)) // Si le caractère est un signe (+ ou -)
	{
		signe=car; // Stocke le signe
		car=Epurerblanc(); // Supprime les caractères blancs après le signe
	} //fin de if

	do
	{
		if(EstNumerique(car)) val1=val1*10.0+CartoFloat(car); // Construit la partie entière du nombre
		else break; // Quitte la boucle si le caractère n'est pas un chiffre
		//fin de if
	} while((car=getchar())!=RC); //fin de boucle do while

	if(car=='.') // Si le caractère est un point décimal
	{
		car=Epurerblanc(); // Supprime les caractères blancs après le point
		do
		{
			if(EstNumerique(car)) 
			{
				val2=val2*10.0+CartoFloat(car); // Construit la partie décimale
				virgule++; // Incrémente la virgule pour suivre le nombre de chiffres après le point
			}
			else break; // Quitte la boucle si le caractère n'est pas un chiffre
			//fin de if
		} while((car=getchar())!=RC); //fin de boucle do while
	}//fin de if

	if(car==BL) car=Epurerblanc(); // Supprime les caractères blancs après la partie décimale
	//fin de if
	
	if(car==RC) // Si le caractère de retour à la ligne est atteint
	{
		if(val2!=0) val1=val1+val2 * pow(10, -virgule); // Calcul de la partie décimale
		//fin de if
		if(signe=='-') val1*=-1; // Applique le signe négatif si nécessaire
		//fin de if
		return((float)val1); // Retourne le nombre à virgule flottante
	}//fin de if
	printf("\nErreur : Ce n'est pas un nombre");
	exit(-1);
}

int main(int argc, char *argv[]) {
	float val;
	val=lire_Entier();
	printf("\nLa valeur est : %+f", val); // Affiche le nombre à virgule flottante
	return 0;
}
