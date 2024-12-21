#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define RC '\n'
#define BL ' '
#define PL '+'
#define MN '-'
#define ML '*'
#define DV '/'


//************************prototype des fonction*******************************
//Noeud *creer_noeud();
char epurer_blanc();
int est_signe(char c);
double lire_reel(char *caractere);


//************************prototype des fonction*******************************


//def de stuctures 
typedef union
{
	double valeur;
	char caractere;
}valeur;


typedef struct ND
{
	valeur info;
	struct ND *fgch;
	struct ND *fdrt;
}Noeud;

//fonction creer un noeud
Noeud *creer_noeud()
{
	Noeud *NE=(Noeud*)malloc(sizeof(Noeud));
	if(!NE)
	{
		printf("erreur d'allocation !");
		exit(-1);
	}
	NE->fdrt=NE->fgch=NULL;
	return((Noeud*)NE);
}

//--->fct epurer blanc
char epurer_blanc()
{
	char car;
	while((car=getchar())==RC);
	return((char)car);
}


//--->fct de signe 
int est_signe(char c)
{
	switch(c)
	{
		case '-' : return((int) -1);
		case '+' : return((int) 1);
		default  : return((int) 0);
	}
}

//----> fonctionq qui verifier si le caractere saisit est une entier
int est_numerique(char car)
{
	return ((int)(('0'<=car)&&(car<='9')));
}

int char_TO_int(char c)
{
	return((int)(c-'0'));
}

//fonction qui teste est ce qu'un caractere est un operateur
int est_operateur(char car)
{
	if((car=='+') || (car=='/') || (car=='-') || (car=='*')) return((int)1);
	return((int)0);
}
//fonction qui permet de lire un reel 
double lire_reel(char *caractere)
{
	
	char c;
	int i,signe;
	double Ptdecim,Ptent;
	Ptent=0.0;
	Ptdecim=0.0;
	c=epurer_blanc();//lire le premier caractere
	//traiter le signe
	if(!(signe = est_signe(c)))
	{
		if(est_numerique(c))
		Ptent=Ptent*10.0+char_TO_int(c);
		
	}
	//traitement la partie entière 
	while(est_numerique(c=getchar()))
	{
		Ptent=Ptent*10.0+char_TO_int(c);
		
	}
	//traitement de la partie decimale
	if(c == '.')
	{
		i= -1;
		while(est_numerique(c=getchar()))
		{
			
			Ptdecim=Ptdecim + char_TO_int(c)*pow(10,i--);
		}
	}
	
	if(c == BL) c=epurer_blanc();
	if(!signe) signe =1;
	if(c == RC)
	{
//		*caractere=c;
		return((double) (Ptent+Ptdecim)*signe);
	} 
	else
	{
		if(est_operateur(c))
		{
			*caractere=c;
			return((double) (Ptent+Ptdecim)*signe);
		}	
	}
		printf("\nERROR");
		return ((double) -1);
	
}



//fonction qui permet d'inseree les elements saisie par clavier
Noeud *inserer_Exp_Arb(Noeud *Arb,double val,char car)
{
	Noeud *Nop=creer_noeud();
	Noeud *Nval=creer_noeud();
	Nop->info.caractere=car;
	Nval->info.valeur=val;
	Noeud *crt=NULL;
	
	//si l'arbre est vide 
	if(!Arb)
	{
		Nop->fgch=Nval;
		crt=Nop;
		Arb=Nop;
		return((Noeud*)Arb);
	}
	//si l'arbre n'est pas vide
	if((car==PL) || (car==PL)) 
	{
		Nop->fgch=Arb;
		Arb=Nop;
		crt=Nop;
		return((Noeud*)Arb);
	}
	if((car==ML) || (car==DV))
	{
		
		if((crt->info.caractere==PL) || (crt->info.caractere==MN))
		{
			
			crt->fdrt=Nop;
			Nop->fgch=Nval;
			crt=Nop;
			return((Noeud*)Arb);	
		}
		crt->fdrt=Nval;
		if(crt==Arb)
		{
			Nop->fgch=Arb;
		    Arb=Nop;
		    crt=Nop;
		    return((Noeud*)Arb);
		}
		Nop->fgch=crt;
		Arb->fdrt=Nop;
		crt=Nop;
		return((Noeud*)Arb);
	} 
}



//fonction qui permet de faire le calcule 
double Calculer_Exp(double Op1, char operateur, double Op2)
{
    switch (operateur)
    {
        case '+': return ((double)Op1 + Op2);
        case '-': return ((double)Op1 - Op2);
        case '*': return ((double)Op1 * Op2);
        case '/': 
            if (Op2 != 0) return ((double)Op1 / Op2);
            // Cas de division par 0
            printf("\nErreur: Division par 0!!");
            exit(0);
    }
}





//fonction qui lit l'expression arithmatique
void lire_Expression_arith()
{
	Noeud *Arb=NULL;
	char car;
	double val;
	do
	{
		val=lire_reel(&car);
		if(est_operateur(car))
		{
			Arb=inserer_Exp_Arb(Arb,val,car);
		}
		else break;
	}while(car!=RC);
	if(car!=RC)
	{
		printf("\nvous avez pas saisie l'expression correctement !");
		return;
	}
	printf("\nBravooo !vous avez saisie l'expression correctement");
}

//fonction qui permet d'avaluer l'expression et faite le calcule totale
double Evaluer_Arbre_Exp(Noeud *Arb)
{
    if (Arb)
    {
        if (!Arb->fgch && !Arb->fdrt) return ((double)Arb->info.valeur);
        return ((double)Calculer_Exp(Evaluer_Arbre_Exp(Arb->fgch),
                                    Arb->info.caractere,
                                    Evaluer_Arbre_Exp(Arb->fdrt)));
    }
}


int main()
{
//	double b=lire_reel();
//	printf("\n\n%.6f",b);

	Noeud *Arb=NULL;
	double result;
	printf("Entrer une expression arithmetique : ");
	lire_Expression_arith();
//	affichage_horiz(Arb,0);
	
	result=Evaluer_Arbre_Exp(Arb);
	printf("la resultat de l'expression arithmetiqe est : %.3f",result);
	
	return 0;
}
//void lire_exprression()
//{
//	Noeud *Arb=NULL;
//	char car;
//	
//}



