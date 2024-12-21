#include <stdio.h>
#include <stdlib.h>


typedef struct node 
{
	int data;
	struct node *left;
	struct node *right;
}node;

node* creer_node(int valeur)
{
	node *NE;
	NE=(node*)malloc(sizeof(node));
	if(!NE)  exit((int)-1)
	NE->data=valeur;
	NE->left=NE->right=NULL;
	return((node*)NE);
}

node* inserer_node(node *arbre,int val)
{
	if(!arbre)   return((node *)creer_node(val));
	if(val>arbre->data) arbre->right=inserer_node(arbre->right,int val);
	if(val<arbre->data) arbre->left=inserer_node(arbre->left,int val);
	return ((node *)arbre);
}
