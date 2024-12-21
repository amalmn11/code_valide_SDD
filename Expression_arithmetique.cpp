#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef union opFl
{
    double valeur; //champ operande
    char oper;//champ operateur
}expre;// nom de la tructure
typedef struct Nd
{
   expre info; //etiquette du noeud
   struct Nd* left;//pointeur sur le s a g
   struct Nd* right;//pointeur sur le s a d
}Noeud; //nom de la structure 

/* 1
Nom Fonction  : Creer_Noeud
Entree	      : un element de type expre (union) 
Sortie        :  element de type Noeud 
Description   : la fonction cree un noeud et 
                l'initialise

*/
Noeud *Creer_Noeud( expre elem )
{
    Noeud*NV;// declarer un nouveau noeud
    NV=(Noeud*)malloc(sizeof(Noeud));//allocation de la memoire
    if(!NV) exit(0);//echec d'allocation
    //initialiser le noued 
    NV->info=elem;
    NV->left=NV->right=NULL;
    return (( Noeud *)NV);
}//fin
/* 2
Nom Fonction  : est_num_Un
Entree	      : un element de type expre (union) 
Sortie        : boolien 
Description   : la fonction verifie si l'union 
                est occupe par un operateur si oui 
                retourne 0 sinon 1

*/
int est_num_Un(expre elem)
{//si elem est un operateur retourner 0 
    if((elem.oper=='+')||(elem.oper=='*')||(elem.oper=='/'))
        return 0;
    return 1;
}//fin 
/* 3
Nom Fonction  : est_num
Entree	      : un charactere (char) 
Sortie        : boolien 
Description   : la fonction verifie si le car 
                est une valeur entre 0 ou 9

*/
int est_num(char car)
{//si car est une valeur entre 0 ou 9 retourner 1
    return((int)((car>='0')&&(car<='9')));
}
/* 4
Nom Fonction  : root_be_left
Entree	      : une racine et un noeud  
Sortie        : arbre
Description   : la fonction affecte l'arbre au 
                fils gauche du un noeud passe en argument

*/
Noeud* root_be_left(Noeud *arb,Noeud *nv)
{
    nv->left=arb;//arb devient fils gauche de nv
    return ((Noeud*)nv);//nv devient racine
}
/* 5
Nom Fonction  : inserer_exp_arbre
Entree	      : une racine et une union  
Sortie        : arbre
Description   : la fonction insere un element dans une 
                arbre 

*/
 Noeud* inserer_exp_arbre(Noeud *arb,expre elem)
{
    Noeud *nv=NULL,*tmp=NULL;
    nv=Creer_Noeud(elem);
    if(!arb) return ((Noeud*)nv);//arbre vide    
    //nv est un valeur  
    if(est_num_Un(elem))
    {// si la racine n'as pas de fils froit
        if(!arb->right) arb->right=nv; // nv devient fils dt
        else //sinon il est inserer etant le fils le plus a droite
        {
           tmp=arb->right;
           tmp->right=nv;
        } //(ceci sera a gauche si un opperateur le suive)
    }
    else// si nv est un opperateur
    {   // si la racine est + et nv * ou /
        if ( arb->info.oper=='+'&&(elem.oper=='/' || elem.oper=='*'))
        {
            tmp=arb->right; // garder le fils droit de la racine
            arb->right=nv; // le fils droit devient  nv 
            nv->left=tmp; // le fils gauche de nv recoit tmp
        }
        //sinon il devient racine et l'arbre son fils gauche
        else arb=root_be_left(arb,nv);
    }
    return((Noeud*)arb);
}
/* 6
Nom Fonction  : opper_effect
Entree	      : deux entiers et un caractere  
Sortie        : arbre
Description   : la fonction effectue le calcul 
                selon le caractere passe en argument
                {+,*,/}, et retourne le resultat
*/
double opper_effect(double val1, char operateur,  double val2)
{
    // selon l'opperation on retourne le resultat
    switch(operateur)
    {
        case '*': return((double)val1*val2);
        case '+': return((double)val1+val2);
        case '/': return((double)val1/val2);
    }
    return 0.0;
}
/* 7
Nom Fonction  : calcule_expres
Entree	      : arbre des unions  
Sortie        : un reel
Description   : la fonction permet de calculer 
                une expression arithmetique stocker dans un arbre
*/
double calcule_expres(Noeud* arb)
{
    // si c'est un opperande
    if(est_num_Un(arb->info)) return arb->info.valeur;
    // sinon on fait le calcule entre gauche et droite
    return opper_effect(calcule_expres(arb->left),
                        arb->info.oper,calcule_expres(arb->right));
}

//validation de la chaine 
/* 8
Nom Fonction  : est_oper
Entree	      : un caractere 
Sortie        : boolien 
Description   : la fonction verifie si le car 
                est un operateur si oui 
                retourne 1 sinon 0
*/
int est_oper(char car)
{
    if(car=='+' || car=='-' || car=='/' || car=='*')
        return 1;
    return 0;
}
/* 9
Nom Fonction  : car_inconu
Entree	      : une chaine de caracteres 
Sortie        : boolien 
Description   : la fonction verifie si la chaine 
                contient un caractere different de l'un
                des composantes d'une expression arithmetique
*/
int car_inconu(char*opperation)
{
    int i;
    for(i=0;i<strlen(opperation); i++)
    {   if(opperation[i]=='.') continue;
        if((!est_num(opperation[i])) && (!est_oper(opperation[i])))
            return 1;//caractere inconnu
    }
    return 0;
}
/* 10
Nom Fonction  : est_valide
Entree	      : une chaine de caracteres 
Sortie        : boolien 
Description   : la fonction verifie si la chaine 
               est valide comme expression arithmetique 
               ou non 
*/
int est_valide(char *opperation)
{
    int ind;
    if(car_inconu(opperation)) return 0;
    // si la chaine comence ou termine par une opperation * ou /
    if ( opperation[0]== '*' || opperation[0]== '/'||
         opperation[strlen(opperation)-1]== '*'
         || opperation[strlen(opperation)-1]== '/'
        ) return((int)0);
    // on parcours la chaine element par element
    for(ind=1;ind<strlen(opperation)-1; ind++)
    {
        // si c'est un opperant
        if (!est_num(opperation[ind]))
            // si il est suivie par * ou / alors non valide
            if(opperation[ind+1]== '*' || opperation[ind+1]== '/' ) return((int)0);
        // si on a une devision sur 0 donc la caine est non valide
        if(opperation[ind]== '/')
            if(opperation[ind+1]== '0') return((int)0);
    }
    // sinon la caine est valide on retourne 1
    return((int)1);
}


/* 11
Nom Fonction  : entier
Entree	      : une chaine de caracteres ,un entier
Sortie        : boolien, reel 
Description   : la fonction calcule la 
                partie entier d'un reel
*/
//partie entier
int entier(double *chifre,char *chain,int deb)
{
    int j=deb;// deb l'indice du debut de la partie entier 
    while((chain[j]!='.')&&(chain[j]!='\0'))
    {
        if(est_num(chain[j]))
        {
            (*chifre)=(((*chifre)*10.0)+(double)(chain[j]-'0'));
            j++;
        }
        else return-1;//un car inconnu
    }
    return j;
}
/* 12
Nom Fonction  : signe_num
Entree	      : une chaine de caracteres 
Sortie        : boolien, reel 
Description   : la fonction calcule la 
                determine le signe d'un reel
*/
int signe_num(double *signe, char *chain)
{
    int i=0;//pour parcourir la chaine
    while((chain[i]=='-')|| (chain[i]=='+'))
    {
       if(chain[i]=='-')
       {    //si c'est negatif on multiplie sign par -1
           (*signe)*=-1.0;
       }
       i++;
    }
    return i;
}//fin
/* 13
Nom Fonction  : decimale
Entree	      : une chaine de caracteres 
Sortie        : boolien, reel 
Description   : la fonction calcule la 
                determine le signe d'un reel
*/
int decimale(double *chifre,char *chain,int deb)
{
    int i=0;
    int j=deb+1;// deb l'indice du debut de la partie entier 
    // j pour parcourir la chaine (deb+1) pour depasse (.)
    while((chain[j]!='\0'))
    {
        if(est_num(chain[j]))
        { //calcule
            (*chifre)=((*chifre)+(double)((chain[j]-'0')*pow(10,--i)));
            j++;
        }
        else return -1;// un virgule ou un car inconnu
    }
    return j;
}
/* 14
Nom Fonction  : chifre_extraire
Entree	      : une chaine de caracteres 
Sortie        : un reel 
Description   : la fonction extrait un reel
                a partier d'une chaine  
*/
double chifre_extraire(char *chain)
{
    
    double chifre=0.0,signe=1.0;
    int ind1=0;
    //determiner le signe
    if((chain[0]=='-')|| (chain[0]=='+'))
       ind1=signe_num(&signe,chain);
    //caractere non numerique
    if(!est_num(chain[ind1]))
    {
        printf("caractere inconnu au debut\n");
        exit(0);
    }
    //calcule de la partie entier
    ind1=entier(&chifre,chain,ind1);
    if(ind1==-1)//caractere non numerique
    { 
        printf("un caractere inconu inserer \n");
        exit(0);
        
    }
    //si c'est un entier simple
    if(chain[ind1]=='\0') return((double)(signe*chifre));//entier simple
    //calcule de la partie decimale
    ind1=decimale(&chifre,chain,ind1);
    if(ind1==-1)//caractere non numerique
    {
        printf("un virgule de plus ou un car inconnu \n");
        exit(0);
        
    }
    return((double)(signe*chifre));

}//fin 
/* 15
Nom Fonction  : insere_tmp
Entree	      : une chaine de caracteres 
Sortie        : un reel 
Description   : la fonction insere les elements d'un 
            seule opperande dans une chaine des caracteres  
*/
void insere_tmp(char* opperation, char *tmp,int *ind1,int *indT)
{
    // tantqu'on a pas atteint la fin de la chaine
    while(opperation[*ind1]!='\0')
    {
        /*si le dernier caractere enregistrer dans tmp une opperation
        et que le suivant a stocker n'est pas un . */
        if(est_num(tmp[*indT])|| tmp[*indT]=='.')
        {
            if(est_num(opperation[*ind1]) || opperation[*ind1]=='.')
                 tmp[++(*indT)]=opperation[(*ind1)++]; // on le stock
            else break;
        }
        else tmp[++(*indT)]=opperation[(*ind1)++];
            /* si on arrive a une opperateur apres l'insertion
            d'une valeur on quite*/
                
    }

}
/* 16
Nom Fonction  : chaine_vers_tab
Entree	      : une chaine de caracteres, un tableau des unions 
Sortie        : un reel 
Description   : la fonction insere les elements d'une 
            expression arithmetique dans un tableau 
            apres l'extraction des elements  
*/
int chaine_vers_tab(char* opperation, expre tableau[100])
{
    int ind1=0,ind2=0,indT=0; 
    //ind1 pour la chaine, indT chaine tmp et ind2 tableau d'union
    double var=0.0;
    char tmp[10]; // tableau de caractere temporaire
    /** debut de recuperation du premier opperant */
         // on insere dans le tmp le 1er caractere
        tmp[indT]=opperation[ind1++];
        insere_tmp(opperation,tmp,&ind1,&indT);
        tmp[++indT]='\0'; // on ajoute le caractere de fin de chaine
        indT=0; // on remis l'indice du parcous du tempat a 0
        var=chifre_extraire(tmp); // on recupere l'opperant
        tableau[ind2++].valeur=var; // on le stocke dans le tableau d'union
    /** fin de recuperation du premier opperant**/
      while(opperation[ind1]!='\0')
      {
        // l'element a inserer est surrement un opperateur
        if(opperation[ind1]=='-')
        {   //le signe moins toujours inserer avec une valeur
            tmp[indT]=opperation[ind1++];
            tableau[ind2++].oper='+';
        }
        else
        {
            tableau[ind2++].oper=opperation[ind1++];
            // suivant un opperant qui peut etre signe ou nn
             // on insere dans le tmp le 1er caractere
            tmp[indT]=opperation[ind1++];
        }
        insere_tmp(opperation,tmp,&ind1,&indT);//inserer dans tmp
        tmp[++indT]='\0'; // on ajoute le caractere de fin de chaine
        indT=0; // on remis l'indice du parcous du temp a 0
        var=chifre_extraire(tmp); // on recupere la valeur
        // on le stocke dans le tableau d'union
        tableau[ind2++].valeur=var;
    }
    // on retourne la taille du tableau finale
    return ((int)ind2);

}
/* 17
Nom Fonction  : inserer_smp_arb
Entree	      : une chaine de caracteres, arbre 
Sortie        : arbre
Description   : la fonction insere les elements d'une 
            expression arithmetique dans un arbre  
*/
Noeud*inserer_smp_arb(Noeud *arb,expre tab[100],int taille)
{
    int ind;
    for(ind=0; ind<taille ; ind ++)
        arb=inserer_exp_arbre(arb,tab[ind]);
    return arb;
}
/* 18
Nom Fonction  : inserer_arbre
Entree	      : une chaine de caracteres, arbre 
Sortie        : arbre
Description   : la fonction insere les elements d'une 
            expression arithmetique dans un arbre  
*/
Noeud* inserer_arbre(Noeud *arb,char *expression)
{
    expre T[100];
    int ind,mil,taille;
    //extraction des elements
    taille=chaine_vers_tab(expression,T);
    mil= taille/2;
    //milieu une operateur de periorite 
    if(T[mil].oper=='*' || T[mil].oper=='/')
            return inserer_smp_arb(arb,T,taille);
     //milieu une operande 
    if(est_num_Un(T[mil]))
    {   //l'operateur avant et apres (* ou /)
        if(T[mil+1].oper!='+' || T[mil-1].oper!='+')
            return inserer_smp_arb(arb,T,taille);
        //prendre l'operateur +
        (T[mil+1].oper=='+')?(mil++):(mil--);
    } 
    //inserer le milieu comme racine
    arb=inserer_exp_arbre(arb,T[mil]);
    //inserer les element avant mil a gauche
    for(ind=0; ind<mil ; ind ++)
    {
        arb->left=inserer_exp_arbre(arb->left,T[ind]);
    }
    //inserer les element avant mil a droite
    for(ind=mil+1; ind<taille ; ind ++)
    {
        arb->right=inserer_exp_arbre(arb->right,T[ind]);
    }
    return ((Noeud *)arb);
}
/* 19
Nom Fonction  : inserer_arbre
Entree	      : arbre, entier 
Sortie        : 
Description   : la fonction affiche un arbre
                horizontalement
*/
void affichage_horiz(Noeud *monArb, int niveau)
{
    int i=0;
    // afficher le sous arbre droit
    if (monArb->right) affichage_horiz(monArb->right, niveau + 1);
    // afficher la racine
    for (i=0; i < niveau; i++)
    {
        printf(" \t");
    }
    // c'est c'est un flottant
    if(est_num_Un(monArb->info))
        printf("(%.3f)\n", monArb->info.valeur);
    // sinon
    else printf("(%c)\n", monArb->info.oper);
    // afficher le sous arbre gauche de la meme maniere
    if (monArb->left) affichage_horiz(monArb->left, niveau+1 );

}
/* 20
Nom Fonction  : traitement
Entree	      : chaine de caractere 
Sortie        : 
Description   : la fonction calcule une expression 
                arithmetique et affiche le resultat
*/
void traitement(char*chaine)
{
    Noeud *monArb=NULL;
    int taille,ind=0;
    expre T[100];   
        if(est_valide(chaine))
        {
            monArb=inserer_arbre(monArb,chaine);
            affichage_horiz(monArb,0);
            printf("\n %s = %f\n\n",chaine,calcule_expres(monArb));
        }
        else
            printf("Opperation inacceptable");
}
void lire(char*chaine)
{   int i=0;
    char car;
    car=getchar();
    while(car!='\n')
    {
        if(car==' ')
        { 
            car=getchar();
            continue;
        }
        chaine[i++]=car;
        car=getchar();
    }
    chaine[i]='\0';
}
int main()
{
    char chaine[100];
    printf("\n donnez une oppertation :");
    lire(chaine);
    printf("\n\n");
    traitement(chaine);
    return 0;
}
