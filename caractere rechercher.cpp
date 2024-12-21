#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RC '\n'


void freq_carac()
{
	int freq=0;
	char carlu,carRch;
	
	//lecture du caractere a rechercher 
	
	printf("Entrer le caractere a rechercher : ");
	scanf("%c",&carRch);
	getchar();
	//traitement de la phrase caractere par caractere
	while((carlu=getchar())!=RC)
	{
		if(carlu==carRch)  freq++;
	}
	printf("le caractere recherche %c est present %d fois",carRch,freq);
	
}

char convertir_maj_min(char c)
{
	if((c>='A') && (c<='Z')) return ((char)('a'+(c-'A')));
}

char convertir_min_maj(char c)
{
	if((c>='a') && (c<='z')) return ((char)('A'+(c-'a')));
}

int type_car(char c)
{
	if((c>='A') && (c<='Z')) return ((int)1);//Maj
	if((c>='a') && (c<='z')) return ((int)2);//Min
	if((c>='0') && (c<='9')) return ((int)3);//Num
	if(c==' ') return ((int)4);//espace
	if(c=='\t') return ((int)5);//tabulation
	
}
void freq_chaque_carac(int freq[37])
{
	char carlu;
	int ind,type;
	for(ind=0;ind<37;freq[ind++]=0);
//	for(ind=0,ind<37,ind++)
//	{
//		freq[ind++]=0;
//	}
	while((carlu=getchar())!=RC)
	{
		type=type_car(carlu);
		switch(type)
		{
			case 1:freq[carlu-'A']++;  break;
			case 2:freq[carlu-'a']++;  break;
			case 3:freq[26+(carlu-'0')]++; break;
			default:freq[36]++;		
		}
	}	
	
}

void convertir_caractere()
{
	char c;
	int type;
	while((c=getchar())!=RC)
	{
		type=type_car(c);
		switch(type)
		{
			case 1:printf("%c",'a'+(c-'A'));
				   break;
			case 2:printf("%c",'A'+(c-'a'));
				   break;
			case 3:printf("%c",'9'-(c-'0'));
				   break;
			case 4:printf("\\BL");
				   break;
			case 5:printf("\\TB");
				   break;
			default:printf("%c",c);
		}
	}
}
int main()
{
	
	
	
	int ind,freq[37];
	char car;
	freq_chaque_carac(freq);
	for(ind=0;ind<37;ind++) printf("%d  ",freq[ind]);
	//convertir_caractere();
	
	//freq_carac();
//	char carRch;
//	//lecture du caractere a rechercher 
//	printf("Entrer le caractere a convertir : ");
//	scanf("%c",&carRch);
//	printf(" la resultat est : %c",convertir_maj_min(carRch));
	return 0;
}

