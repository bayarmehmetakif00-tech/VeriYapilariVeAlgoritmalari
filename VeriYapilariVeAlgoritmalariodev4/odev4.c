#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;
void addSongToEnd(Song** head,char* name)
{
    Song* newSong= (Song*)malloc(sizeof(Song));
    strcpy(newSong->name,name);
    newSong->next=NULL;
    newSong->prev=NULL;

    if(*head==NULL)
    {
        *head=newSong;
        printf("Sarki listeye eklendi\n");
        return;
    }
    Song* temp=*head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=newSong;
    newSong->prev=temp;
    printf("Listeye eklendi.\n");
}
void removeSong(Song** head,char* name)
{
    if(*head ==NULL)
    {
        printf("Liste bos.");
        return;
    }
    Song* temp= *head;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }
    if(temp==NULL)
    {
        printf("Sarki bulunamadi");
        return;
    }
    if (temp == *head) {
        *head = temp->next;
    }
    if(temp->prev !=NULL)
    {
        temp->prev->next=temp->next;
    }
    if(temp->next !=NULL)
    {
        temp->next->prev=temp->prev;
    }
    free(temp);
    printf("Basariyla silindi");

}
void playNext(Song** current)
{
    if(*current ==NULL)
    {
        printf("Suan calan veya listede olan bir sarki yok");
        return;
    }
    if((*current)->next !=NULL)
    {
        *current=(*current)->next;
        printf("Suan calan sarki %s",(*current)->name);
    }else {
        printf("Dikkat:Listenin sonundasiniz,sonraki sarki yok.\n");
    }

}
void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("Su an calan veya listede olan bir sarki yok.\n");
        return;
    }

    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf(">>> Su an caliyor: %s <<<\n", (*current)->name);
    } else {
        printf("Dikkat: Listenin basindasiniz, onceki sarki yok!\n");
    }
}
void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("Liste bos.\n");
        return;
    }

    printf("\n--- CALMA LISTESI ---\n");
    Song* temp = head;
    while (temp != NULL) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
    printf("---------------------\n");
}

int main(void)
{
    Song* playlist = NULL;
    Song* currentSong = NULL;
    int choice;
    char buffer[50];

    while (1) {
        printf("\n=== MUZIK CALAR MENU ===\n");
        printf("1. Sarki Ekle\n");
        printf("2. Sarki Sil\n");
        printf("3. Sonraki Sarkiyi Cal\n");
        printf("4. Onceki Sarkiyi Cal\n");
        printf("5. Calma Listesini Goster\n");
        printf("6. Su An Calan Sarki\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                printf("Eklenecek sarki adi: ");
                scanf(" %[^\n]", buffer);
                addSongToEnd(&playlist, buffer);
                if (currentSong == NULL) {
                    currentSong = playlist;
                }
                break;
                
            case 2:
                printf("Silinecek sarki adi: ");
                scanf(" %[^\n]", buffer);
                
                
                if (currentSong != NULL && strcmp(currentSong->name, buffer) == 0) {
                    if (currentSong->next != NULL) {
                        currentSong = currentSong->next; 
                    } else if (currentSong->prev != NULL) {
                        currentSong = currentSong->prev; 
                    } else {
                        currentSong = NULL; 
                    }
                }
                
                removeSong(&playlist, buffer);
                break;
                
            case 3:
                playNext(&currentSong);
                break;
                
            case 4:
                playPrevious(&currentSong);
                break;
                
            case 5:
                displayPlaylist(playlist);
                break;
                
            case 6:
                if (currentSong != NULL) {
                    printf(">>> Su an caliyor: %s <<<\n", currentSong->name);
                } else {
                    printf("Su an calan bir sarki yok.\n");
                }
                break;
                
            case 0:
                printf("Muzik calar kapatiliyor...\n");
                while (playlist != NULL) {
                    Song* temp = playlist;
                    playlist = playlist->next;
                    free(temp);
                }
                return 0;
                
            default:
                printf("Gecersiz secim, lutfen tekrar deneyin.\n");
        }
    }
    return 0;
}