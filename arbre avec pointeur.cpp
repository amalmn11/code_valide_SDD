#include <stdio.h>
#include <stdlib.h>

// Déclaration des types et des structures
typedef struct ND // Définition de la structure d'un arbre binaire
{
    int info; // Information
    struct ND *fgc; // Pointeur sur le fils gauche
    struct ND *fdt; // Pointeur sur le fils droit
} Noeud;

// Fonction pour créer un nouveau nœud avec une valeur initiale
Noeud *CreerNoeud(int val) {
    Noeud *NE = (Noeud *)malloc(sizeof(Noeud));
    if (!NE)
	{
        printf("Erreur d'allocation de mémoire");
        return ((Noeud*)NULL);
    }
    NE->info = val; // Vous pouvez initialiser à la valeur que vous préférez
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

// Affichage Préfixe
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
    if (Arbre)  // Condition d'arrêt
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

// Fonction pour trouver le minimum dans un arbre binaire ordonné
int MinArbreOrdonne(Noeud *Arb, int *Min)
{
    int rt;
    if (!Arb) return ((int)0);
    *Min = Arb->info;
    if (Arb->fgc) rt = MinArbreOrdonne(Arb->fgc, Min);
    // Fin de la condition (if)
    return ((int)1);
}

// Fonction pour trouver le maximum dans un arbre binaire ordonné
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
    // 1 pour la racine plus le nombre de nœuds gauches et droits de la racine
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
    free(Arb); // Libérer la mémoire
    return ((Noeud *)NULL);
    // Fin de la condition (if)
}

// Fonction pour insérer un nœud dans un arbre binaire ordonné
Noeud *InsererArbBinOrdonne(Noeud *Arb, int val)
{
    Noeud *NE;
    if (!Arb) // Arbre vide
    {
        NE = CreerNoeud(val); // Créer un nœud
        return ((Noeud *)NE);
    }
    // Insertion dans la partie gauche
    if (val < Arb->info) Arb->fgc = InsererArbBinOrdonne(Arb->fgc, val);
    // Insertion dans la partie droite
    else Arb->fdt = InsererArbBinOrdonne(Arb->fdt, val);
    return ((Noeud *)Arb);
    // Fin de la condition (if)
}

// Fonction pour supprimer un nœud d'un arbre binaire ordonné
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
        else // Valeur trouvée
        {
            tmp = Arb; // pour libérer la mémoire
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
            free(tmp); // libérer la mémoire
            *supp = 1; // Suppression effectuée
        }
    }
    return ((Noeud *)Arb);
    // Fin de la condition (if)
}

int main() {
    Noeud *racine = NULL; // Déclaration d'un pointeur vers la racine de l'arbre
    int val,minVal = 0,maxVal = 0;; // Variable pour stocker une valeur
    int supp = 0; // Variable pour indiquer si la suppression a été effectuée

    // Insérer des valeurs dans l'arbre binaire ordonné
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

    // Supprimer un nœud spécifique de l'arbre
    val = 30;
    racine = SupprimerArbBinOrdonne(racine, val, &supp);
    
    // Afficher si la suppression a été effectuée
    if (supp)
        printf("\nSuppression de %d effectuée.", val); 


	// Afficher l'arbre en mode Infixe après la suppression
    printf("\nAffichage Infixe de l'arbre après suppression :\n");
    AffichageInfixe(racine); 

    // Libérer la mémoire de l'arbre
    racine = ViderArbre(racine); // Libérer la mémoire de tous les nœuds de l'arbre

    return ((int)0);
}


