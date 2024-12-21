#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RC '\n'  // Constante pour le caract�re de retour � la ligne
#define BL ' '   // Constante pour le caract�re espace

// Fonction pour supprimer les caract�res blancs inutiles
char Epurerblanc()
{
	char carac;
	while((carac=getchar())==BL); // Ignore les caract�res blancs (y compris les espaces et les tabulations)
	return((char) carac);
}

// V�rifie si le caract�re est un chiffre
int EstNumerique(char car)
{
	return((int)(('0'<=car)&&(car<='9'))); // Retourne 1 si le caract�re est un chiffre, 0 sinon
}

// V�rifie si le caract�re est un signe (+ ou -)
int EstSigne(char car)
{
	return((int)((car=='+')||(car=='-'))); // Retourne 1 si le caract�re est un signe, 0 sinon
}

// Convertit un caract�re en float
float CartoFloat(char car)
{
	return ((float)(car-'0')); // Convertit un caract�re num�rique en float
}

// Fonction principale pour lire un nombre � virgule flottante
float lire_Entier()
{
	char car, signe;
	float val1=0.0, virgule=0.0, val2=0.0 ;
	car=Epurerblanc(); // Supprime les caract�res blancs initiaux

	if(car==RC) 
	{
		printf("\n Erreur : Fin de ligne inattendue");
		exit(-1);
	} //fin de if
	if(EstSigne(car)) // Si le caract�re est un signe (+ ou -)
	{
		signe=car; // Stocke le signe
		car=Epurerblanc(); // Supprime les caract�res blancs apr�s le signe
	} //fin de if

	do
	{
		if(EstNumerique(car)) val1=val1*10.0+CartoFloat(car); // Construit la partie enti�re du nombre
		else break; // Quitte la boucle si le caract�re n'est pas un chiffre
		//fin de if
	} while((car=getchar())!=RC); //fin de boucle do while

	if(car=='.') // Si le caract�re est un point d�cimal
	{
		car=Epurerblanc(); // Supprime les caract�res blancs apr�s le point
		do
		{
			if(EstNumerique(car)) 
			{
				val2=val2*10.0+CartoFloat(car); // Construit la partie d�cimale
				virgule++; // Incr�mente la virgule pour suivre le nombre de chiffres apr�s le point
			}
			else break; // Quitte la boucle si le caract�re n'est pas un chiffre
			//fin de if
		} while((car=getchar())!=RC); //fin de boucle do while
	}//fin de if

	if(car==BL) car=Epurerblanc(); // Supprime les caract�res blancs apr�s la partie d�cimale
	//fin de if
	
	if(car==RC) // Si le caract�re de retour � la ligne est atteint
	{
		if(val2!=0) val1=val1+val2 * pow(10, -virgule); // Calcul de la partie d�cimale
		//fin de if
		if(signe=='-') val1*=-1; // Applique le signe n�gatif si n�cessaire
		//fin de if
		return((float)val1); // Retourne le nombre � virgule flottante
	}//fin de if
	printf("\nErreur : Ce n'est pas un nombre");
	exit(-1);
}

int main(int argc, char *argv[]) {
	float val;
	val=lire_Entier();
	printf("\nLa valeur est : %+f", val); // Affiche le nombre � virgule flottante
	return 0;
}
