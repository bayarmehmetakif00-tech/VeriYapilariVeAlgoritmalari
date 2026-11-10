#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* left;
	struct Node* right;
}Node;

Node* CreateNode(int data){
	Node* newNode= (Node*)malloc(sizeof(Node));
	if(newNode==NULL){
		return NULL;
	}
	newNode->data=data;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}
Node* InsertBST(Node* root,int data){
	if(root==NULL){
		return CreateNode(data);
	}
	if(root->data >data){
		root->left=InsertBST(root->left,data);
	}
	if(root->data <data){
		root->right =InsertBST(root->right,data);
	}
	return root;	
		
}
int height(Node* root){
	if(root==NULL){
		return 0;
	}
	int solSeviye = height(root->left);
    int sagSeviye = height(root->right);
	if (solSeviye > sagSeviye)
        return solSeviye + 1;
    else
        return sagSeviye + 1;
}
int BalanceFactor(Node* root){
	if(root==NULL){
		return 0;
	}
	int solSeviye= height(root->left);
	int sagSeviye= height(root->right);
	int denge=solSeviye-sagSeviye;
	if(denge<-1)
		printf("denge sola dogru denge= %d\n",denge);
	else if(denge>1)
		printf("denge saga dogru denge= %d\n",denge);
	else if(denge <=1 && denge >=-1)
		printf("agac dengeli denge= %d\n",denge);
	return denge;
}
Node* rotateLeft(Node* x){
	Node* y= x->right;
	Node* temp=y->left;
	y->left=x;
	x->right= temp;
	return y;
}
void inOrder(Node* root){
	if(root==NULL){
		return;
	}
	inOrder(root->left);
	printf("%d\n",root->data);
	inOrder(root->right);
}
void preOrder(Node* root){
    if(root==NULL){
        return;
    }
    printf("%d\n",root->data);
    preOrder(root->left);
    preOrder(root->right);
}


int main(void){
	
	Node* root=NULL;
	
	root= InsertBST(root,10);
	root= InsertBST(root,20);
	root= InsertBST(root,30);
	printf("Agac yuksekligi = %d\n",height(root));
	BalanceFactor(root);
	inOrder(root);
    printf("Preorder:\n");
    preOrder(root);
	root= rotateLeft(root);
	printf("Agac yuksekligi = %d\n",height(root));
	BalanceFactor(root);
	inOrder(root);
    printf("Preorder:\n");
    preOrder(root);
	return 0;
	
}