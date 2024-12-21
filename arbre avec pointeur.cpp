#include <stdio.h>
#include <stdlib.h>

// D�claration des types et des structures
typedef struct ND // D�finition de la structure d'un arbre binaire
{
    int info; // Information
    struct ND *fgc; // Pointeur sur le fils gauche
    struct ND *fdt; // Pointeur sur le fils droit
} Noeud;

// Fonction pour cr�er un nouveau n�ud avec une valeur initiale
Noeud *CreerNoeud(int val) {
    Noeud *NE = (Noeud *)malloc(sizeof(Noeud));
    if (!NE)
	{
        printf("Erreur d'allocation de m�moire");
        return ((Noeud*)NULL);
    }
    NE->info = val; // Vous pouvez initialiser � la valeur que vous pr�f�rez
	NE->fgc = NULL;
    NE->fdt = NULL;
    return ((Noeud*)NE);
}

// Affichage Infixe
void AffichageInfixe(Noeud *Arb)
{
    if (Arb)
    {
        AffichageInfixe(Arb->fgc);
        printf("\n%d", Arb->info);
        AffichageInfixe(Arb->fdt);
    }
    // Fin de la condition (if)
}

// Affichage Pr�fixe
void AffichagePrefixe(Noeud *Arb)
{
    if (Arb)
    {
    	printf("\n%d", Arb->info);
        AffichagePrefixe(Arb->fgc);
        AffichagePrefixe(Arb->fdt);
    }
    // Fin de la condition (if)
}

// Affichage Postfixe
void AffichagePostfixe(Noeud *Arb)
{
    if (Arb)
    {
        AffichagePostfixe(Arb->fgc);
        AffichagePostfixe(Arb->fdt);
        printf("\n%d", Arb->info);
    }
    // Fin de la condition (if)
}

// Fonction qui affiche horizontalement l'arbre
void Aff_Arbre_horiz(Noeud *Arbre, int Niv)
{
    int esp; // Pour l'affichage des espaces
    if (Arbre)  // Condition d'arr�t
    {   
        // Affichage des fils droits
        Aff_Arbre_horiz(Arbre->fdt, Niv + 1);
        printf("\n");
        for (esp = 0; esp < Niv; esp++)
            printf("\t");
        printf("%d", Arbre->info);
        // Affichage des fils gauches
        Aff_Arbre_horiz(Arbre->fgc, Niv + 1);
    }
    // Fin de la condition (if)
}

// Fonction pour trouver le minimum dans un arbre binaire ordonn�
int MinArbreOrdonne(Noeud *Arb, int *Min)
{
    int rt;
    if (!Arb) return ((int)0);
    *Min = Arb->info;
    if (Arb->fgc) rt = MinArbreOrdonne(Arb->fgc, Min);
    // Fin de la condition (if)
    return ((int)1);
}

// Fonction pour trouver le maximum dans un arbre binaire ordonn�
int MaxArbreOrdonne(Noeud *Arb, int *Max)
{
    int rt;
    if (!Arb) return ((int)0);
    *Max = Arb->info;
    if (Arb->fdt) rt = MaxArbreOrdonne(Arb->fdt, Max);
    // Fin de la condition (if)
    return ((int)1);
}

// Fonction pour calculer la taille de l'arbre
int TailleArbre(Noeud *Arb)
{
    if (!Arb) return ((int)0); // Arbre vide
    // 1 pour la racine plus le nombre de n�uds gauches et droits de la racine
    return ((int)(1 + TailleArbre(Arb->fgc) + TailleArbre(Arb->fdt)));
    // Fin de la condition (if)
}

// Fonction pour calculer la hauteur de l'arbre
int HauteurArbre(Noeud *Arb)
{
    int HG = 0, HD = 0; // Hauteur gauche et hauteur droite
    if (!Arb) return ((int)0); // Arbre vide
    if (Arb->fgc) HG = 1 + HauteurArbre(Arb->fgc);
    if (Arb->fdt) HD = 1 + HauteurArbre(Arb->fdt);
    return ((int)((HG < HD) ? HD : HG));
    // Fin de la condition (if)
}

// Fonction pour vider un arbre
Noeud *ViderArbre(Noeud *Arb)
{
    if (!Arb) return ((Noeud *)NULL); // Arbre Vide
    Arb->fgc = ViderArbre(Arb->fgc); // Vider sous-arbre gauche
    Arb->fdt = ViderArbre(Arb->fdt); // Vider sous-arbre droit
    free(Arb); // Lib�rer la m�moire
    return ((Noeud *)NULL);
    // Fin de la condition (if)
}

// Fonction pour ins�rer un n�ud dans un arbre binaire ordonn�
Noeud *InsererArbBinOrdonne(Noeud *Arb, int val)
{
    Noeud *NE;
    if (!Arb) // Arbre vide
    {
        NE = CreerNoeud(val); // Cr�er un n�ud
        return ((Noeud *)NE);
    }
    // Insertion dans la partie gauche
    if (val < Arb->info) Arb->fgc = InsererArbBinOrdonne(Arb->fgc, val);
    // Insertion dans la partie droite
    else Arb->fdt = InsererArbBinOrdonne(Arb->fdt, val);
    return ((Noeud *)Arb);
    // Fin de la condition (if)
}

// Fonction pour supprimer un n�ud d'un arbre binaire ordonn�
Noeud *SupprimerArbBinOrdonne(Noeud *Arb, int val, int *supp)
{
    Noeud *pred, *courant, *tmp;
    *supp = 0;
    if (!Arb) return ((Noeud *)NULL); // Arbre vide
    if (val < Arb->info) // Recherche dans le sous-arbre gauche
    {
        if (!Arb->fgc) return ((Noeud *)Arb); // Pas de fils gauche
        Arb->fgc = SupprimerArbBinOrdonne(Arb->fgc, val, supp);
    }
    else
    {
        if (Arb->info < val) // Recherche dans le sous-arbre droit
        {
            if (!Arb->fdt) return ((Noeud *)Arb); // Pas de fils droit
            Arb->fdt = SupprimerArbBinOrdonne(Arb->fdt, val, supp);
        }
        else // Valeur trouv�e
        {
            tmp = Arb; // pour lib�rer la m�moire
            if (!Arb->fgc) Arb = Arb->fdt; // Pas de fils gauche
            else
            {
                if (!Arb->fdt) Arb = Arb->fgc; // Pas de fils droit
                else
                {
                    courant = Arb->fgc;
                    if (courant->fdt) // si le fils gauche a un fils droit
                    {
                        pred = Arb;
                        while (courant->fdt) // Tant qu'on a un fils droit
                        {
                            pred = courant;
                            courant = courant->fdt;
                        }
                        pred->fdt = NULL;
                        courant->fgc = Arb->fgc;
                        courant->fdt = Arb->fdt;
                    }
                    courant->fdt = Arb->fdt;
                    Arb = courant;
                }
            }
            free(tmp); // lib�rer la m�moire
            *supp = 1; // Suppression effectu�e
        }
    }
    return ((Noeud *)Arb);
    // Fin de la condition (if)
}

int main() {
    Noeud *racine = NULL; // D�claration d'un pointeur vers la racine de l'arbre
    int val,minVal = 0,maxVal = 0;; // Variable pour stocker une valeur
    int supp = 0; // Variable pour indiquer si la suppression a �t� effectu�e

    // Ins�rer des valeurs dans l'arbre binaire ordonn�
    racine = InsererArbBinOrdonne(racine, 50);
    racine = InsererArbBinOrdonne(racine, 30);
    racine = InsererArbBinOrdonne(racine, 70);
    racine = InsererArbBinOrdonne(racine, 20);
    racine = InsererArbBinOrdonne(racine, 40);


	// Afficher l'arbre en mode Infixe
    printf("Affichage Infixe de l'arbre :\n");
    AffichageInfixe(racine); 

    printf("\n\n");

	// Afficher l'arbre en mode Postfixe
    printf("Affichage Postfixe de l'arbre :\n");
    AffichagePostfixe(racine); 

    printf("\n\n");
    
    
    // Afficher l'arbre en mode Prefixe
    printf("Affichage Prefixe de l'arbre :\n");
    AffichagePrefixe(racine);

    printf("Affichage Horizontal de l'arbre :\n");
    Aff_Arbre_horiz(racine, 0); // Afficher l'arbre horizontalement

    printf("\n\n");

    // Afficher le minimum de l'arbre
    if (MinArbreOrdonne(racine, &minVal)) 
        printf("\nMinimum de l'arbre : %d", minVal); 
    

    // Afficher le maximum de l'arbre
    if (MaxArbreOrdonne(racine, &maxVal)) 
        printf("\nMaximum de l'arbre : %d", maxVal); 
        
	// Calculer la taille de l'arbre
    int taille = TailleArbre(racine); 
    printf("\nTaille de l'arbre : %d", taille);


	// Calculer la hauteur de l'arbre
    int hauteur = HauteurArbre(racine); 
    printf("\nHauteur de l'arbre : %d", hauteur);

    // Supprimer un n�ud sp�cifique de l'arbre
    val = 30;
    racine = SupprimerArbBinOrdonne(racine, val, &supp);
    
    // Afficher si la suppression a �t� effectu�e
    if (supp)
        printf("\nSuppression de %d effectu�e.", val); 


	// Afficher l'arbre en mode Infixe apr�s la suppression
    printf("\nAffichage Infixe de l'arbre apr�s suppression :\n");
    AffichageInfixe(racine); 

    // Lib�rer la m�moire de l'arbre
    racine = ViderArbre(racine); // Lib�rer la m�moire de tous les n�uds de l'arbre

    return ((int)0);
}


