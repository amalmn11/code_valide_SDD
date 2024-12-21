#include <stdio.h>
#include <stdlib.h>

// Structure d'une cellule de la liste
typedef struct Cellule {
    int data;
    struct Cellule* next;
} Cellule;

// Fonction pour créer une nouvelle cellule
Cellule* CreerCellule(int data) {
    Cellule* newCell = (Cellule*)malloc(sizeof(Cellule));
    if (!newCell) {
        perror("Problème d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    newCell->data = data;
    newCell->next = NULL;
    return newCell;
}

// Fonction pour insérer une cellule en tête de la liste
Cellule* InsererEnTete(Cellule* head, int data) {
    Cellule* newCell = CreerCellule(data);
    newCell->next = head;
    return newCell;
}

// Fonction pour supprimer tous les doublons dans la liste
Cellule* SupprimerDoublons(Cellule* head) {
    if (head == NULL) {
        return NULL; // Rien à faire si la liste est vide
    }

    Cellule* current = head;

    while (current != NULL) {
        Cellule* comparer = current;

        while (comparer->next != NULL) {
            if (current->data == comparer->next->data) {
                // Supprimer le doublon
                Cellule* temp = comparer->next;
                comparer->next = temp->next;
                free(temp);
            } else {
                comparer = comparer->next;
            }
        }

        current = current->next;
    }

    return head;
}

// Fonction pour afficher les éléments de la liste
void AfficherListe(Cellule* head) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    Cellule* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Fonction pour vider la liste
void ViderListe(Cellule* head) {
    Cellule* current = head;
    while (current != NULL) {
        Cellule* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Cellule* liste = NULL;
    liste = InsererEnTete(liste, 4);
    liste = InsererEnTete(liste, 3);
    liste = InsererEnTete(liste, 2);
    liste = InsererEnTete(liste, 2);
    liste = InsererEnTete(liste, 1);
    liste = InsererEnTete(liste, 3);
    liste = InsererEnTete(liste, 4);

    printf("Liste avant la suppression des doublons : ");
    AfficherListe(liste);

    liste = SupprimerDoublons(liste);

    printf("Liste après la suppression des doublons : ");
    AfficherListe(liste);

    ViderListe(liste);

    return 0;
}

