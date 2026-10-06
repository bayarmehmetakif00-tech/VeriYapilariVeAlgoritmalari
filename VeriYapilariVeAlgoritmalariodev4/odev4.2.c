#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dosya (Düğüm) yapısı
typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front; // Kuyruğun başı (İlk çıkacak olan)
    PrintJob* rear;  // Kuyruğun sonu (Son eklenen)
} Queue;

// Fonksiyon imzaları
void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);

int main() {
    // Kuyruğu ilk başta boş olarak tanımlıyoruz
    Queue q;
    q.front = NULL;
    q.rear = NULL;
    
    int choice;
    char buffer[50];

    while (1) {
        printf("\n=== YAZICI KUYRUGU MENU ===\n");
        printf("1. Yeni dosya ekle\n");
        printf("2. Yazdir (Siradaki isi isleme al)\n");
        printf("3. Kuyrugu goster\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Yazdirilacak dosya adi: ");
                scanf(" %[^\n]", buffer);
                enqueuePrintJob(&q, buffer);
                break;
                
            case 2:
                processNextJob(&q);
                break;
                
            case 3:
                showQueue(q);
                break;
                
            case 0:
                printf("Yazici kapatiliyor. Bekleyen isler iptal ediliyor...\n");
                while (q.front != NULL) {
                    processNextJob(&q); 
                }
                return 0;
                
            default:
                printf("Gecersiz secim!\n");
        }
    }
    return 0;
}

// Kuyruğun sonuna eleman ekleme (Enqueue)
void enqueuePrintJob(Queue* q, char* fileName) {
    // 1. Yeni düğümü oluştur
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    // 2. Eğer kuyruk tamamen boşsa
    if (q->rear == NULL) {
        q->front = newJob;
        q->rear = newJob; 
        printf(">>> '%s' kuyruga eklendi (Ilk sirada).\n", fileName);
        return;
    }

    // 3. Kuyruk boş değilse, mevcut son elemanın arkasına ekle
    q->rear->next = newJob; 
    q->rear = newJob;       // Kuyruğun yeni sonu (rear) artık bu yeni eleman oldu
    
    printf(">>> '%s' kuyruga eklendi.\n", fileName);
}

// Kuyruğun başındaki elemanı işleme/silme (Dequeue)
void processNextJob(Queue* q) {
    // 1. Kuyruk boş mu kontrolü
    if (q->front == NULL) {
        printf("HATA: Kuyruk bos, yazdirilacak dosya yok!\n");
        return;
    }

    // 2. İşlenecek olan en baştaki elemanı geçici bir pointer'da tut
    PrintJob* temp = q->front;
    
    // 3. Kuyruğun başını bir sonraki elemana kaydır
    q->front = q->front->next;

    // 4. Eğer kuyruktan çıkardığımız eleman kuyruktaki TEK elemansa,
    // şu an front NULL oldu demektir. Bu durumda rear'ı da NULL yapmalıyız.
    if (q->front == NULL) {
        q->rear = NULL;
    }

    printf("YAZDIRILIYOR... '%s' basariyla yazdirildi.\n", temp->fileName);
    
    // 5. İşlenen düğümü bellekten sil
    free(temp);
}

// Kuyruktaki elemanları sırayla gösterme
// Burada Queue pointer (Queue*) yerine direkt Queue aldık. 
// Çünkü yapıyı değiştirmeyeceğiz, sadece var olanı okuyacağız.
void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("--- Kuyrukta bekleyen dosya yok. ---\n");
        return;
    }

    printf("--- Bekleyen Isler (Sira ->) ---\n");
    PrintJob* temp = q.front;
    int sira = 1;
    
    while (temp != NULL) {
        printf("%d. %s\n", sira, temp->fileName);
        temp = temp->next;
        sira++;
    }
    printf("--------------------------------\n");
}