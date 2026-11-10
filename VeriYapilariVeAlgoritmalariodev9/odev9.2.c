#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
int height(Node* root) {
    if (root == NULL) return 0;
    int solSeviye = height(root->left);
    int sagSeviye = height(root->right);
    return (solSeviye > sagSeviye ? solSeviye : sagSeviye) + 1;
}

int balanceFactor(Node* root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}
Node* rotateRight(Node* y) {
    Node* x = y->left;      
    Node* temp = x->right;  

    x->right = y;           
    y->left = temp;         

    return x;               
}
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    return y;
}
void preOrder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
Node* insertAVL(Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insertAVL(node->left, data);
    } else if (data > node->data) {
        node->right = insertAVL(node->right, data);
    } else {
        return node;
    }

    int balance = balanceFactor(node);


    // LL Durumu (Sol-Sol)
    if (balance > 1 && data < node->left->data) {
        return rotateRight(node);
    }

    // RR Durumu (Sağ-Sağ)
    if (balance < -1 && data > node->right->data) {
        return rotateLeft(node);
    }

    // LR Durumu (Sol-Sağ)
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // RL Durumu (Sağ-Sol)
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
int main(void){
    Node* rootA= NULL;
    rootA= insertAVL(rootA,30);
    rootA= insertAVL(rootA,20);
    rootA= insertAVL(rootA,10);
    printf("--- Test A (LL: 30, 20, 10) ---\n");
    printf("Kok Degeri: %d\n", rootA->data);
    printf("Preorder: ");
    preOrder(rootA);
    printf("\n\n");


    Node* rootB = NULL;
    rootB = insertAVL(rootB, 10);
    rootB = insertAVL(rootB, 20);
    rootB = insertAVL(rootB, 30);
    printf("--- Test B (RR: 10, 20, 30) ---\n");
    printf("Kok Degeri: %d\n", rootB->data);
    printf("Preorder: ");
    preOrder(rootB);
    printf("\n\n");



    Node* rootC = NULL;
    rootC = insertAVL(rootC, 30);
    rootC = insertAVL(rootC, 10);
    rootC = insertAVL(rootC, 20);
    printf("--- Test C (LR: 30, 10, 20) ---\n");
    printf("Kok Degeri: %d\n", rootC->data);
    printf("Preorder: ");
    preOrder(rootC);
    printf("\n\n");



    Node* rootD = NULL;
    rootD = insertAVL(rootD, 10);
    rootD = insertAVL(rootD, 30);
    rootD = insertAVL(rootD, 20);
    printf("--- Test D (RL: 10, 30, 20) ---\n");
    printf("Kok Degeri: %d\n", rootD->data);
    printf("Preorder: ");
    preOrder(rootD);
    printf("\n\n");

    freeTree(rootA);
    freeTree(rootB);
    freeTree(rootC);
    freeTree(rootD);

    return 0;
}