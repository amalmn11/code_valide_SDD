#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RC '\n'
#define BL ' '
#define max 50


char Epurerblanc()
{
	char car;

	while((car = getchar()) == BL);
	return ((char) car);
}

int Est_palindrom(char mot[max])
{
	int longeur=strlen(mot);
	int	debut=0,fin=longeur-1;
	while(debut<fin)
	{
		if(mot[debut]!=mot[fin]) return ((int)0);
		debut++;
		fin--;
	}
	return((int)1);
}


int lire()
{
	char car,motlu[max];
	int i;
	printf("entre le texte : ");
	do
	{
		i=0;
		car=Epurerblanc();
		if(car==RC) break;
		motlu[i++]=car;
		while(((car=getchar())!=BL) && (car!=RC)) motlu[i++]=car;
		motlu[i]='\0';
		if(Est_palindrom(motlu))
		{
			printf("| %s |",motlu);
		}
			
	}while(car!=RC);
	
}


int main()
{
	lire();
	return 0;
}
