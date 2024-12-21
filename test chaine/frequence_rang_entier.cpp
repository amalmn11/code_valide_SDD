#include <stdio.h>
#include <stdlib.h>
#define RC '\n'
#define BL ' '

char Epurer_blanc()
{
	char car;
	while((car=getchar())==BL);
	return ((char)car);
}

int Est_numerique(char c)
{
	if(c>='0' && c<='9') return ((int)c-'0');
	return((int)-1);	
}

int frequence_rang_entier()
{
	int a,freq=0,i=0,n;
	char car;
	printf("entrer l'entier :");
	scanf("%d",&a);
	getchar();
	printf("entrer la serie des entiers :");
	
	do
	{
		n=0;
		car=Epurer_blanc();
		i++;
		if(car==RC) break;
		n=n*10+Est_numerique(car);
		while((car=getchar())!=BL && (car!=RC)) n=n*10+Est_numerique(car);
		if(n==a)
		{
			//freq++;
			printf("la frequence de l'entier est :%d  ||  son rang est :%d\n",++freq,i);
		} 
		
		//car=getchar();
		
	}while(car!=RC);
	return ((int)1);
}

int main()
{
	frequence_rang_entier();
	return ((int)0);
}
