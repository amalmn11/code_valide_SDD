#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i,j;
	int Tab[10][10];
	
	//initialisation de la matrice 
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			Tab[i][j]=0;
		}
	}
	//afiichage de la matrice
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			printf("%d",Tab[i][j]);
		}
	}
	
	return 0;
}
