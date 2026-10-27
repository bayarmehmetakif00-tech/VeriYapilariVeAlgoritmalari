#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if(root == NULL) {
        return createNode(value);
    }
    if(value < root->data)
        root->left = insert(root->left, value);
    else if(value > root->data)
        root->right = insert(root->right, value);
    return root;
}

void printBST(Node* root) {
    if(root != NULL) {
        printBST(root->left);
        printf("%d \n", root->data);
        printBST(root->right);
    }
}

int main() {
    srand(time(NULL));
    int hedefHazine = (rand() % 100) + 1;
    Node* root = NULL;
    int tahmin;
    int adimSayisi = 0;
    int minSinir = 1;
    int maxSinir = 100;
    int oyunBitti = 0;

    printf("----------------------------------------\n");
    printf("  KAYIP ADA: BST HAZINE BULMA OYUNU     \n");
    printf("----------------------------------------\n");
    printf("Adada 1 ile 100 arasinda gizli bir hazine var.\n");
    printf("BST (Binary Search Tree) mantigini kullanarak\n");
    printf("araligi daralt ve hazineyi ilk sen bul!\n\n");

    while(!oyunBitti) {
        printf("Aralik [%d - %d] | Tahmininiz nedir? : ", minSinir, maxSinir);

        if (scanf("%d", &tahmin) != 1) {
            printf("Lutfen gecerli bir sayi girin!\n");
            while(getchar() != '\n');
            continue;
        }

        root = insert(root, tahmin);
        adimSayisi++;

        if (tahmin == hedefHazine) {
            printf("\nTEBRIKLER! Hazineyi %d numarali sandikta buldunuz!\n", hedefHazine);
            printf("Toplam adim (tahmin) sayiniz: %d\n", adimSayisi);
            oyunBitti = 1;
        } else if (tahmin < hedefHazine) {
            printf("-> Ipucu: Hazine daha BUYUK bir numarada! (Sag tarafa gitmelisin)\n");
            if (tahmin >= minSinir) {
                minSinir = tahmin + 1;
            }
        } else {
            printf("-> Ipucu: Hazine daha KUCUK bir numarada! (Sol tarafa gitmelisin)\n");
            if (tahmin <= maxSinir) {
                maxSinir = tahmin - 1;
            }
        }
    }

    printf("----------------------------------------\n");
    printf("\nOyun boyunca aradiginiz noktalarin olusturdugu BST Haritasi (Sirali):\n");
    printBST(root);
    printf("\n\nOynadiginiz icin tesekkurler!\n");

    return 0;
}