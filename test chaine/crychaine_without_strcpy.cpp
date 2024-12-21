#include<stdio.h>
#include<stdlib.h>


int main()
{
	char A[10],D[10];
	int i;
	printf("entrer un mot : ");
	gets(A);
	printf("la chaine est : %s\n",A);

	
	for(i=0;A[i]!='\0';i++)
	{
		D[i]=A[i];
	}
	D[i]='\0';
	printf("la chaine est : %s",D);
	
	
	
	
	
	
	return 0;
}
