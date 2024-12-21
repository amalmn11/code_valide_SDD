#include<stdio.h>
#define MAXELEM 10



//definition de la structure de file 
typedef struct tfl
{
	int TabInt[MAXELEM];
	signed int debut;
	signed int fin;
}TFILE;

//definition des fonctions de manipulation de file mise en oeuvre à l'aide d'un tableau
//1 initialisation de la tab a vide
int initialiser_tfile(TFILE *Mafile)
{
	if(!Mafile) 
	{
		return ((int) 0);
    }
	Mafile->debut = -1;
	Mafile->fin = -1;
	return ((int) 1);
}

//2 fonction de vérification si la file est vide

int est_vide(TFILE Mafile)
{
	return ((int)(Mafile.debut== -1));
}

//3 fonction de vider la file 
int raz_tfile(TFILE *Mafile)
{
//	test si la file existe dans la memoire
	if(!Mafile) return ((int) 0);
	Mafile->debut = Mafile->fin = -1;
	return ((int) 1);
}


//4 fonction de defiler
int defiler_tfile(TFILE *Mafile)
{
	//test si la file existe dans la memoire
	if(!Mafile) return ((int) -1);
	//test si vide 
	if(est_vide(*Mafile)) return ((int) 0);
	// test si elle contient au moin un element
	if(Mafile->debut == Mafile->fin) return((int) raz_tfile(Mafile));
	//si il ya plusieurs elements
	Mafile->debut++;
	return((int) 1);
}

//5 fonction qui retourne la taille de la file
int taille_tfile(TFILE Mafile)
{
	//test si la file est vide pour retouner zero comme taille
	if(est_vide(Mafile)) return ((int) 0);
	//si la file n'est pas vide on retourne fin - debut +1
	return ((int) Mafile.fin - Mafile.debut +1);
}


//6 fonction de tasser tableau  
int tasser_tfile(TFILE *Mafile)
{
	int i ; 
	int taille = taille_tfile(*Mafile);
	//file n'exist pas
	if(!Mafile) return ((int) 0);
	for (i = 0; i<taille; i++){
		Mafile->TabInt[i] = Mafile->TabInt[Mafile->debut++];
	}
	Mafile->fin = taille-1;
	Mafile->debut = 0;  
	return ((int) 1);
	
}

int est_sature_TFile(TFILE Mafile)
{
    // V�rifie si la file est satur�
    return ((int)(taille_tfile(Mafile) == MAXELEM));
}

//7 fonction enfiler  file 
int enfiler_tfile(TFILE *Mafile, int val)
{
	//test si la file existe dans la memeoire
	if(!Mafile) return ((int) -1);
	//test si saturée
	if(est_sature_TFile(*Mafile)) return((int) 0);
	//test si vide
	if(est_vide(*Mafile))
	{
		Mafile->TabInt[0] = val;
		Mafile->debut = Mafile->fin =0;
		return ((int) 1);
	}
	//tasser la table si la file n'est pa sature mais l'indice de fin est arrivé au dernier element
	if(Mafile->fin == MAXELEM-1) tasser_tfile(Mafile);
	//insertion de val et incrementaion de lindice fin
	Mafile->TabInt[++Mafile->fin] = val;
	return ((int) 1);
	
}

//8 fonction d'afficher file 
void afficher(TFILE Mafile){
	
	if(est_vide(Mafile)){
		printf("\nla file est vide!");
		return;
	}
	for(int i = Mafile.debut; i <=Mafile.fin;i++) printf("| %d |\t",Mafile.TabInt[i]);
}

main(){
	
	/*
	=> Tous les fonctions
	initialiser_tfile(TFILE *Mafile)
	raz_tfile(TFILE *Mafile)
	defiler_tfile(TFILE *Mafile)
	taille_tfile(TFILE Mafile)
	enfiler_tfile(TFILE *Mafile, int val)
	afficher(TFILE Mafile)
	*/
	TFILE Mafile;
	initialiser_tfile(&Mafile);
	
	printf("\nenfiler  1 2 3 4 5 6 7 8 9 10");
	enfiler_tfile(&Mafile,1);

	enfiler_tfile(&Mafile,2);

	enfiler_tfile(&Mafile,3);

	enfiler_tfile(&Mafile,4);
	
	enfiler_tfile(&Mafile,5);
	
		enfiler_tfile(&Mafile,6);
			enfiler_tfile(&Mafile,7);
				enfiler_tfile(&Mafile,8);
					enfiler_tfile(&Mafile,9);
						enfiler_tfile(&Mafile,10);
	
	
	
	printf("\n\n***** affichage de la file *****\n");
	afficher(Mafile);
	
	
	//afficher taille
	printf("\n\n-->la taille de la liste est %d",taille_tfile(Mafile));


	//defiler 1
	printf("\n\ndefiler un element ");
	defiler_tfile(&Mafile);	
	printf("\n\n***** affichage de la file *****\n");
	afficher(Mafile);
	
		
	//afficher taille
	printf("\n\n-->la taille de la liste est %d",taille_tfile(Mafile));


	//defiler 2
	printf("\n\ndefiler un element ");	
	defiler_tfile(&Mafile);
	printf("\n\n***** affichage de la file *****\n");
	afficher(Mafile);


	//enfiler 5
    enfiler_tfile(&Mafile,5);
	printf("\n\n***** affichage de la file *****\n");
	afficher(Mafile);

	//enfiler 6
 	enfiler_tfile(&Mafile,6);
	printf("\n\n***** affichage de la file *****\n");
	afficher(Mafile);//	printf("\n\ndefiler un element ");
	
	
//	defiler_tfile(&Mafile);
//	printf("\n\n***** affichage de la file *****\n");
//	afficher(Mafile);
	
//	enfiler_tfile(&Mafile,4);
//	printf("\n\n***** affichage de la file *****\n");
//	afficher(Mafile);
	
//	printf("\n\n-->la taille de la liste est %d",taille_tfile(Mafile));
//	printf("\n\nVider la file");
	
	
//	raz_tfile(&Mafile);
//	printf("\n\n***** affichage de la file *****\n");
//	afficher(Mafile);
//	printf("\n\n-->la taille de la liste est %d",taille_tfile(Mafile));
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//	int choix ;
//	char c ;  
//do{
//	printf("\n**********************************************************************************************");
//	printf("\n\t\tMENU\n ");
////	printf("\n\t0- initialiser");
//	printf("\n\t1- Enfiler");
//	printf("\n\t2- Taille");
//	printf("\n\t3- Defiler");
//	printf("\n\t4- Vider la file");
//	printf("\n\t5- Afficher");	
////	printf("\n**********************************************************************************************\n");
//
//	printf("\n\n\tChoisir un nombre : ");
//	scanf("%d",&choix);
//	switch(choix)
//	{
////		case 0: initialiser_tfile(Mafile);break;
//		case 1: {
//			int val;
//			printf("\n\tentrer un element pour inserer dans table : ");
//			scanf("%d",&val);
//			
//				enfiler_tfile(&Mafile,val);
//			break;
//		}
//		case 2: {
//			printf("\n\tla taille de la file est : %d",taille_tfile(Mafile));
//			break;
//		}
//		case 3: {
//			defiler_tfile(&Mafile);
//			break;
//		}
//		case 4: {
//			raz_tfile(&Mafile);
//			break;
//		}
//		case 5: {
//			afficher(Mafile);
//			break;
//		} 
//	
//		default: printf("\n\tERROR");break;
//	 }
//	 
//	 printf("\n\tVoulez vous continuer (y/n) : ");
//	 scanf(" %c", &c); 
//	
//}while(c == 'Y');
//	
}
