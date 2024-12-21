#include<stdio.h>
#include<stdlib.h>
#define BL ' '
#define RC '\n'
#define max 10

//char Epurerblanc()
//{
//	char c;
//	c=getchar();
//	while(c == BL)
//	{
//		c=getchar();
//	}
//	return((char)c);
//}


char Epurerblanc()
{
	char c;
	while((c=getchar())== BL);
	return((char)c);
}
 
 
//cette fonction qui lit et afficher en meme temp des le buffer 
//int lire_wthout_stock()
//{
//	char m=Epurerblanc();
//	printf("notre chaine est :");
//	do
//	{
//		printf("%c",m);
//	}while(((m=getchar()) !=RC) && (m!=BL));
//	
//	if(m==BL)
//	{
//		m=Epurerblanc();
//		if(m!=RC) printf("\nle mot que vous aver saisie n'est pas correct\n");
//		printf("\nBravo vous avez saisie le mot correctement\n");
//	}
//	return ((int)1);
//}


////fonction qui lit et stocke le mot dans un tableau comme le fonctionnement de scanf
int lire_with_stock(char Mot[max])
{
	int i;
	printf("saisir un mot :");
	char car=Epurerblanc();
	
	i=0;
	do
	{
		
		Mot[i]=car;
		i++;
			
	}while(((car=getchar())!=RC) && (car!=BL) && (i<max));
//	if(i>max)
//	{
//		printf("vous aver depasse la taille\n");
//		exit((int)0);
//	}
//	if(i==max)
//	{
//		Mot[i-1]='\0';
//	}
	if(car==RC)
	{
		Mot[i-2]='\0';
		return((int)1);
	} 
}




//ça marche avec boucle while
//int lire_with_stock(char Mot[max])
//{
//	int i;
//	printf("saisir un mot :");
//	char car;
//	
//	i=0;
//	car=Epurerblanc();
//	while((car!=RC) && (car!=BL) && (i<max))
//	{
//		Mot[i]=car;
//		i++;
//		car=getchar();	
//	}
//	Mot[i-1]='\0';	
//}

int main()
{
//	printf("le caractere non blanc est : %c",Epurerblanc());
	char Mot[max];
	lire_with_stock(Mot);
	printf("le mot que vous avez saisie est: %s",Mot);
	//lire();
	return 0;
}




//ce code ça marche pas
//int lire_with_stock(char Mot[max])
//{
//	int i;
//	printf("saisir un mot :");
//	char car;
//	
//	i=0;
//	do
//	{
//		car=getchar();
//		Mot[i]=car;
//		i++;
//			
//	}while((car!=RC) && (car!=BL) && i<max-1);
//	Mot[i]='\0';
//	
//}
