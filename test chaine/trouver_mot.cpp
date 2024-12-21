#include<stdio.h>
#include<string.h>
#define RC '\n'
#define BL ' '
#define MAX 100



char Epurerblanc()
{
	char car;

	while((car = getchar()) == BL);
	return ((char) car);
}
void trouver_mot()
{
	char motrech[MAX],motlu[MAX],car;
	int i , freq = 0;
	//lecture du mot Ã  chercher
	printf("\nentrer le mot a rechercher : ");
	scanf("%s",motrech);
	printf("\nentrer la phrase :");
	getchar();
	
		
		do{
			i=0;
			car=Epurerblanc();
			if(car==RC) break;
			motlu[i++]=car;
		
			/*
			ici si je veux utiliser do while je dois avant faire car=getchar() 
			(le peux pa aussi utiliser car=epurer_blanc car si le caractere suivant
			et un blanc ond oit pas les eliminers on doit le considere commen un mot
			non valide et pass à un autre mot) et si ce caractere est un blanc il 
			va etre enregister dans le tableau est ça c'est pas correct car on trouve
		 	a la fin un mot qui contien un blanc à l'interieur "mot non valide" et 
		 	*/
			
			while(((car=getchar())!=RC) && (car!=BL))
			{
				motlu[i++]=car;
			}
			motlu[i]='\0';
			if(!(strcmp(motlu,motrech))) freq++;
		
		}while(car!=RC);
		if(freq==0) printf("\nle mot n'esiste pas dans la phrase\n");
		printf("\nle mot exsite dans la phrese et il est apparue : %d fois",freq);
	
	return;
}//fin de la fonction trouver_mot


main(){
	trouver_mot();
	
}
