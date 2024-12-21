#include <stdio.h>
#include <stdlib.h>

// Définition de la structure TreeNode pour un arbre multiple
typedef struct TreeNode {
    int data; // Données du nœud
    struct TreeNode* firstChild; // Pointeur vers le premier enfant
    struct TreeNode* nextSibling; // Pointeur vers le frère suivant
} TreeNode;

// Fonction pour créer un nouveau nœud
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Fonction pour afficher l'arbre de manière récursive
void printTree(TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }

    // Afficher le nœud actuel avec indentation basée sur le niveau
    for (int i = 0; i < level; ++i) {
        printf(" "); // Pour l'indentation
    }
    printf("%d\n", root->data);

    // Appeler récursivement la fonction pour les enfants et les frères
    printTree(root->firstChild, level + 1);
    printTree(root->nextSibling, level);
}

int main() {
    // Création de l'arbre multiple
    TreeNode* root = createNode(1);
    root->firstChild = createNode(2);
    root->firstChild->nextSibling = createNode(3);
    root->firstChild->nextSibling->nextSibling = createNode(4);
    root->firstChild->firstChild = createNode(5);
    root->firstChild->firstChild->firstChild = createNode(6);
    root->firstChild->firstChild->firstChild->nextSibling = createNode(7);

    // Affichage de l'arbre
    printf("Arbre :\n");
    printTree(root, 0);

    // Libération de la mémoire
    // (Dans une application réelle, cela devrait être fait de manière plus complète)
    free(root);

    return 0;
}

