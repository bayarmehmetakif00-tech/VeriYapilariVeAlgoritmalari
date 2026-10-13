#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    char status[20];
} Patient;

typedef struct Node {
    Patient data;
    struct Node* next;
} Node;

// 1. KUYRUK (Queue) Yapısı ve Fonksiyonları (FIFO)
typedef struct {
    Node* front;
    Node* rear;
} Queue;

void enqueue(Queue* q, Patient p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    strcpy(newNode->data.status, "bekliyor"); // Durum güncellemesi
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

Patient dequeue(Queue* q) {
    Patient emptyPatient = {-1, "", ""};
    if (q->front == NULL) {
        printf("Kuyruk bos, cikarilacak hasta yok.\n");
        return emptyPatient;
    }
    Node* temp = q->front;
    Patient p = temp->data;
    
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return p;
}

void printQueue(Queue* q) {
    if (q->front == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Node* temp = q->front;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->data.id, temp->data.name, temp->data.status);
        temp = temp->next;
    }
}

// 2. YIĞIN (Stack) Yapısı ve Fonksiyonları (LIFO)
typedef struct {
    Node* top;
} Stack;

void push(Stack* s, Patient p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    strcpy(newNode->data.status, "muayenede"); // Durum güncellemesi
    newNode->next = s->top;
    s->top = newNode;
}

Patient pop(Stack* s) {
    Patient emptyPatient = {-1, "", ""};
    if (s->top == NULL) {
        printf("Yigin bos, cikarilacak hasta yok.\n");
        return emptyPatient;
    }
    Node* temp = s->top;
    Patient p = temp->data;
    s->top = s->top->next;
    free(temp);
    return p;
}

void printStack(Stack* s) {
    if (s->top == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Node* temp = s->top;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->data.id, temp->data.name, temp->data.status);
        temp = temp->next;
    }
}

// 3. BAĞLI LİSTE (Linked List) Yapısı ve Fonksiyonları (Geçmiş Kayıtlar)
typedef struct {
    Node* head;
    Node* tail;
} LinkedList;

void addHistory(LinkedList* list, Patient p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    strcpy(newNode->data.status, "tamamlandi"); // Durum güncellemesi
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = list->tail = newNode;
        return;
    }
    list->tail->next = newNode;
    list->tail = newNode;
}

void printHistory(LinkedList* list) {
    if (list->head == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Node* temp = list->head;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->data.id, temp->data.name, temp->data.status);
        temp = temp->next;
    }
}

int main() {
    Queue waitingQueue = {NULL, NULL};
    Stack examinationRoom = {NULL};
    LinkedList historyList = {NULL, NULL};

    Patient p1 = {1, "Ahmet", ""};
    Patient p2 = {2, "Mehmet", ""};
    Patient p3 = {3, "Ayse", ""};

    enqueue(&waitingQueue, p1);
    enqueue(&waitingQueue, p2);
    enqueue(&waitingQueue, p3);

    printf("=== Baslangic Durumu ===\n");
    printf("--- Bekleyen Hastalar ---\n"); printQueue(&waitingQueue);
    printf("--- Muayene Odasindaki Hastalar ---\n"); printStack(&examinationRoom);
    printf("--- Tamamlanan Hastalar ---\n"); printHistory(&historyList);
    printf("\n");

    printf("=== Islem Adimlari ===\n");
    
    Patient currentPatient = dequeue(&waitingQueue); 
    push(&examinationRoom, currentPatient);
    printf("%s muayeneye alindi.\n", currentPatient.name);
    
    currentPatient = pop(&examinationRoom); 
    addHistory(&historyList, currentPatient);
    printf("%s'in muayenesi tamamlandi.\n", currentPatient.name);

    currentPatient = dequeue(&waitingQueue);
    push(&examinationRoom, currentPatient);
    printf("%s muayeneye alindi.\n", currentPatient.name);
    
    currentPatient = pop(&examinationRoom);
    addHistory(&historyList, currentPatient);
    printf("%s'in muayenesi tamamlandi.\n\n", currentPatient.name);

    printf("=== Tum Islemler Sonrasi ===\n");
    printf("--- Bekleyen Hastalar ---\n");
    printQueue(&waitingQueue);
    
    printf("--- Muayene Odasindaki Hastalar ---\n");
    printStack(&examinationRoom);
    
    printf("--- Tamamlanan Hastalar ---\n");
    printHistory(&historyList);

    return 0;
}