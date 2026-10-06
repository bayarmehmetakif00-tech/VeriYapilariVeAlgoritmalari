#include <stdio.h>
#include <stdlib.h>

// Temel Node yapısı
struct Node {
    int data;
    struct Node *next;
};

int main() {
    // ---------------------------------------------------------
    printf("--- SORU 1: Tek Node Olusturma ---\n");
    struct Node node1; 
    node1.data = 10;
    node1.next = NULL;
    printf("[%d] -> NULL\n", node1.data);

    // ---------------------------------------------------------
    printf("\n--- SORU 2 ve 3: Iki/Uc Node Baglama ve Yazdirma ---\n");
    struct Node node2, node3;
    node2.data = 20;
    node3.data = 30;
    
    node1.next = &node2;
    node2.next = &node3;
    node3.next = NULL;

    struct Node *temp = &node1;
    while (temp != NULL) {
        printf("[%d] -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    // ---------------------------------------------------------
    printf("\n--- SORU 4: malloc Kullanarak Linked List Olusturma ---\n");
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    struct Node *n2 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *n3 = (struct Node *)malloc(sizeof(struct Node));

    head->data = 10;  head->next = n2;
    n2->data = 20;    n2->next = n3;
    n3->data = 30;    n3->next = NULL;

    struct Node *current = head;
    while (current != NULL) {
        printf("[%d] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    // ---------------------------------------------------------
    printf("\n--- SORU 5: Listenin Eleman Sayisini Bulma ---\n");
    int count = 0;
    current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Listenin eleman sayisi: %d\n", count);

    // ---------------------------------------------------------
    printf("\n--- SORU 6: Listenin Elemanlarini Toplama ---\n");
    int sum = 0;
    current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    printf("Elemanlarin toplami: %d\n", sum);

    // ---------------------------------------------------------
    printf("\n--- SORU 7: Linked List'te Eleman Arama ---\n");
    int aranan = 20; 
    int bulundu = 0;
    current = head;
    while (current != NULL) {
        if (current->data == aranan) {
            bulundu = 1;
            break;
        }
        current = current->next;
    }
    if (bulundu == 1) printf("%d degeri listede bulundu.\n", aranan);
    else printf("%d degeri listede yok.\n", aranan);

    // ---------------------------------------------------------
    printf("\n--- SORU 8: Listenin Basina Eleman Ekleme (5) ---\n");
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = 5;
    newNode->next = head; 
    head = newNode;       

    current = head;
    while (current != NULL) { printf("[%d] -> ", current->data); current = current->next; }
    printf("NULL\n");

    // ---------------------------------------------------------
    printf("\n--- SORU 9: Listenin Sonuna Eleman Ekleme (40) ---\n");
    struct Node *lastNode = (struct Node *)malloc(sizeof(struct Node));
    lastNode->data = 40;
    lastNode->next = NULL;

    current = head;
    while (current->next != NULL) { 
        current = current->next;
    }
    current->next = lastNode;

    current = head;
    while (current != NULL) { printf("[%d] -> ", current->data); current = current->next; }
    printf("NULL\n");

    // ---------------------------------------------------------
    printf("\n--- SORU 10: Belirli Bir Elemani Silme (Ornek: 20'yi siliyoruz) ---\n");
    int silinecek = 20; 
    current = head;
    struct Node *previous = NULL;

    if (current != NULL && current->data == silinecek) {
        head = current->next;
        free(current);
    } else {
        while (current != NULL && current->data != silinecek) {
            previous = current;
            current = current->next;
        }
        if (current != NULL) { 
            previous->next = current->next;
            free(current);
        }
    }

    current = head;
    while (current != NULL) { printf("[%d] -> ", current->data); current = current->next; }
    printf("NULL\n");

    // ---------------------------------------------------------
    printf("\nIslem bitti. Cikmak icin bir tusa basin...\n");
    system("pause");
    return 0;
}
