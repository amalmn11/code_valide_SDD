#include<stdio.h>
#include<string.h>
#include<stdlib.h>



int main()
{
	char c1[10],c2[10];
	
	//test de scanf : les caractere apres espace vont etre pas stocker
	printf("entrer un mot : ");
	scanf("%s",c1);
	printf("\nle mot est : %s",c1);
	printf("\nle caractere est : %c\n",c1[9]);
	
	
	//c'est deux sont essentiel pour stopper le programme
	//fflush(stdin);
	getchar();
	
	printf("\n\n******************      ***********************\n");
	
	
	printf("\nentrer un mot : ");	
	gets(c2);
	printf("\nle mot est : %s",c2);
	printf("\nle nombre de caractere est : %d",strlen(c2));
	printf("\nle mot est : %.5s",c2);
	printf("\nle caractere est : %c",c2[9]);
	
	
	
	//test de gets : les caractere apres espace vont etre stocker, gets support les espaces
	
	
	
	//printf("\nentrer un mot : ");	
	//scanf ici c'est pas grave on donne la main au user pour entrer c2
	//	scanf("%s",c2);
	
	
	
	return 0;
}

