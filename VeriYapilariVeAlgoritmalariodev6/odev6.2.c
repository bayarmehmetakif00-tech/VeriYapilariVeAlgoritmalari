#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

}Node;

Node* createNode(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data=value;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}
Node* insert(Node* root,int value)
{
    if(root==NULL)
        return createNode(value);
    if(value<root->data)
        root->left =insert(root->left,value);
    else if(value>root->data)
        root->right=insert(root->right,value);
    return root;
}
int search(Node* root,int value)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->data == value)
    {
        return 1;
    }
    if(value < root->data)
    {
        return search(root->left,value);
    }else
    {
        return search(root->right,value);
    }
}
int findMin(Node* root)
{
    Node* current=root;
    while(current->left != NULL)
    {
        current=current->left;
    }
    return current->data;
}
int main(void)
{
    Node* root=NULL;
    int numbers[]={40,20,50,30,60,70,10};
    for(int i=0;i<7;i++){
        root=insert(root,numbers[i]);
    }
    if(search(root,30))
        printf("30 agacta bulundu");
    else
        printf("30 agacta bulunamadı");
    if(search(root,90))
        printf("90 agacta bulundu");
    else
        printf("90 agacta bulunamadı");
    if(root!=NULL)
    {
        printf("En kucuk eleman %d\n",findMin(root));
    }
    return 0;
}