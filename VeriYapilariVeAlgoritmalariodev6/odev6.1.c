#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;

}Node;

Node* createnode(int value)
{
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=value;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

Node* insert(Node* root,int value)
{
    if(root==NULL)
        return createnode(value);

    if(value<root->data)
        root->left=insert(root->left,value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;  
}
void inorder(Node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
int main() {
    Node* root = NULL;
    int numbers[] = {40, 20, 60, 10, 30, 50, 70};

    for (int i = 0; i < 7; i++) {
        root = insert(root, numbers[i]);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    return 0;
}