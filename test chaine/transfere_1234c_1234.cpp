#include<stdio.h>
#include<stdlib.h>
#define RC '\n'
#define BL ' '
#define MAX 100

char Epurerblanc()
{
	char car;

	while((car = getchar()) == BL);
	return ((char) car);
}

int Est_numerique(char c)
{
	if(c>='0' && c<='9') return ((int)c-'0');
	return((int)-1);	
}


void transfere()
{
	char car;
	int n=0;
	
	car=Epurerblanc();
	
	do
	{
		
		if(car==RC || Est_numerique(car)==-1) break;
		n=n*10+Est_numerique(car);
		
		
	}while((car=getchar())!=RC);
	if(car==RC)
	{
		if(n==0)
		{
			printf("la chaine que vous avez saisie est pas une chaine numerique");
			return;
		} 
		printf("\nla valeur entier est : %d",n);
		return;
	} 
	if(car==BL)
	{
		car=Epurerblanc();
		if(car==RC)
		{
			printf("\nla valeur entier est : %d",n); 
			
		} 
	} 
	
	printf("la chaine que vous avez saisie est pas une chaine numerique");
	
}

int main()
{
	transfere();
	return ((int)0);
}
