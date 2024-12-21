#include <stdio.h>
#include <stdlib.h>

// D�finition de la structure TreeNode pour un arbre multiple
typedef struct TreeNode {
    int data; // Donn�es du n�ud
    struct TreeNode* firstChild; // Pointeur vers le premier enfant
    struct TreeNode* nextSibling; // Pointeur vers le fr�re suivant
} TreeNode;

// Fonction pour cr�er un nouveau n�ud
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Fonction pour afficher l'arbre de mani�re r�cursive
void printTree(TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }

    // Afficher le n�ud actuel avec indentation bas�e sur le niveau
    for (int i = 0; i < level; ++i) {
        printf(" "); // Pour l'indentation
    }
    printf("%d\n", root->data);

    // Appeler r�cursivement la fonction pour les enfants et les fr�res
    printTree(root->firstChild, level + 1);
    printTree(root->nextSibling, level);
}

int main() {
    // Cr�ation de l'arbre multiple
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

    // Lib�ration de la m�moire
    // (Dans une application r�elle, cela devrait �tre fait de mani�re plus compl�te)
    free(root);

    return 0;
}

