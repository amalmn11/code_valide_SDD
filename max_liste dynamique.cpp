#include <stdio.h>
#include <stdlib.h>

// Structure d'un n�ud dans la liste cha�n�e
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Fonction pour ajouter un n�ud � la fin de la liste cha�n�e
void append(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Fonction pour r�cup�rer et supprimer la cellule contenant la valeur maximale
Node* popMaxNode(Node** head) {
    if (*head == NULL) {
        return NULL; // La liste est vide
    }

    Node* maxNode = *head;
    Node* current = *head;
    Node* previous = NULL;
    Node* previousMax = NULL;

    while (current != NULL) {
        if (current->value > maxNode->value) {
            maxNode = current;
            previousMax = previous;
        }
        previous = current;
        current = current->next;
    }

    if (previousMax == NULL) {
        *head = maxNode->next;
    } else {
        previousMax->next = maxNode->next;
    }

    return maxNode;
}

// Fonction pour afficher le contenu de la liste cha�n�e
void printList(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    // Ajoutez des �l�ments � la liste cha�n�e
    append(&head, 10);
    append(&head, 25);
    append(&head, 5);
    append(&head, 30);
    append(&head, 15);

    printf("Liste avant la suppression :\n");
    printList(head);

    Node* maxNode = popMaxNode(&head);

    if (maxNode != NULL) {
        printf("La cellule contenant la valeur maximale est : %d\n", maxNode->value);
        free(maxNode); // N'oubliez pas de lib�rer la m�moire de la cellule supprim�e
    } else {
        printf("La liste est vide.\n");
    }

    printf("Liste apr�s la suppression :\n");
    printList(head);

    // Lib�rez la m�moire de la liste
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

