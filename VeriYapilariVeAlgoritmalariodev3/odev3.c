#include <stdio.h>
#include <stdlib.h>

// Düğüm (Node) yapısının tanımlanması
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// SORU 1: Sirali Ekleme, Silme ve Sayma Islemleri
void addOrdered(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->value >= value) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}
void removeNode(Node** head, int value) {
    if (*head == NULL) return;

    if ((*head)->value == value) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node* current = *head;
    while (current->next != NULL && current->next->value != value) {
        current = current->next;
    }

    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}
int count(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


// SORU 2: Pozisyona Gore Ekleme ve Silme Islemleri
void insertAt(Node** head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (position <= 0 || *head == NULL) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    int currentPos = 0;

    while (current->next != NULL && currentPos < position - 1) {
        current = current->next;
        currentPos++;
    }

    newNode->next = current->next;
    current->next = newNode;
}
void deleteAt(Node** head, int position) {
    if (*head == NULL || position < 0) return; 

    if (position == 0) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node* current = *head;
    int currentPos = 0;

    while (current->next != NULL && currentPos < position - 1) {
        current = current->next;
        currentPos++;
    }

    if (current->next == NULL) {
        return; 
    }

    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
}


// SORU 3: Ortadaki Dugumu Bulma Islemi

Node* findMiddle(Node* head) {
    if (head == NULL) {
        return NULL; 
    }

    Node* slow = head; 
    Node* fast = head; 

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          
        fast = fast->next->next;    
    }

    return slow;
}

// ORTAK FONKSIYONLAR (Yazdirma ve Temizleme)
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}
void clear(Node** head) {
    Node* current = *head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}
int main() {
    Node* head = NULL;

    printf("--- SORU 1: Sirali Ekleme Testi ---\n");
    int sayilar[] = {23, 11, 5, 9, 6, 4, 12, 24};
    int n = sizeof(sayilar) / sizeof(sayilar[0]);
    for (int i = 0; i < n; i++) {
        addOrdered(&head, sayilar[i]);
    }
    
    printf("Sirali Liste: ");
    printList(head);
    clear(&head);    
    printf("\n");

    // ---------------------------------------------------------

    printf("--- SORU 2: Pozisyona Gore Ekleme ve Silme Testi ---\n");
    
    insertAt(&head, 10, 0); 
    insertAt(&head, 20, 1); 
    insertAt(&head, 30, 2); 
    insertAt(&head, 5, -3);  
    insertAt(&head, 99, 100); 
    insertAt(&head, 15, 2);   

    printf("Ekleme islemlerinden sonra liste:\n");
    printList(head);

    deleteAt(&head, 0);  
    deleteAt(&head, 2);  
    deleteAt(&head, 99);

    printf("Silme islemlerinden sonra liste:\n");
    printList(head); 
    printf("\n");

    // ---------------------------------------------------------

    printf("--- SORU 3: Ortadaki Dugumu Bulma Testi ---\n");
    
    Node* ortaCift = findMiddle(head);
    if(ortaCift != NULL) {
        printf("Cift sayida eleman varken orta deger: %d\n", ortaCift->value);
    }

    insertAt(&head, 200, 4);
    printf("Bir eleman eklendikten sonra liste:\n");
    printList(head);

    Node* ortaTek = findMiddle(head);
    if(ortaTek != NULL) {
        printf("Tek sayida eleman varken orta deger: %d\n", ortaTek->value);
    }
    clear(&head);
    printf("\nTum islemler tamamlandi. Liste temizlendi.\n");
    printf("Cikmak icin bir tusa basin...\n");
    getchar();

    return 0;
}