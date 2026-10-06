#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

// Fonksiyon imzaları
void pushWord(Word** top, char* text);
void popWord(Word** top);
void showWords(Word* top);

void printWordsRecursive(Word* top);

int main() {
    Word* stackTop = NULL;
    char command[20];
    char buffer[50];

    printf("--- Undo (Geri Alma) Simulasyonu ---\n");
    printf("Komutlar:\n");
    printf("  add <kelime> : Kelime ekler\n");
    printf("  undo         : Son eklenen kelimeyi geri alir\n");
    printf("  show         : Metni gosterir\n");
    printf("  exit         : Cikis yapar\n");
    printf("------------------------------------\n");

    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%s", buffer);
            pushWord(&stackTop, buffer);
        } 
        else if (strcmp(command, "undo") == 0) {
            popWord(&stackTop);
        } 
        else if (strcmp(command, "show") == 0) {
            showWords(stackTop);
        } 
        else if (strcmp(command, "exit") == 0) {
            printf("Programdan cikiliyor...\n");
            while (stackTop != NULL) {
                Word* temp = stackTop;
                stackTop = stackTop->next;
                free(temp);
            }
            break;
        } 
        else {
            printf("Gecersiz komut! Lutfen 'add <kelime>', 'undo', 'show' veya 'exit' yazin.\n");
            while(getchar() != '\n'); 
        }
    }

    return 0;
}

// Stack'in en ustune (basa) eleman ekleme (PUSH)
void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));
    strcpy(newWord->text, text);
    
    // Yeni dugumun next'i, mevcut en ustteki dugumu gosterir
    newWord->next = *top;
    
    // Artik en ustteki dugum (top) yeni ekledigimiz dugumdur
    *top = newWord;
}

// Stack'in en ustundeki (bastaki) elemani silme (POP)
void popWord(Word** top) {
    if (*top == NULL) {
        printf("Geri alinacak islem yok!\n");
        return;
    }
    
    Word* temp = *top;
    *top = (*top)->next; 
    
    printf("Undo: '%s' geri alindi.\n", temp->text);
    free(temp); // Bellekten tamamen sil
}
void printWordsRecursive(Word* top) {
    if (top == NULL) {
        return;
    }
    // Once listenin en derinine in, sonra ekrana yazdir
    // Bu sayede yigin (stack) tersine cevrilerek okunmus olur
    printWordsRecursive(top->next);
    printf("%s ", top->text);
}

// Metni ekranda gosterme
void showWords(Word* top) {
    if (top == NULL) {
        printf("-> (Metin bos)\n");
        return;
    }
    
    printf("-> ");
    printWordsRecursive(top);
    printf("\n");
}