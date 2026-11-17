#include <stdio.h>
#include <stdbool.h>
#define SEHIR_SAYISI 5


const char *sehirler[SEHIR_SAYISI]={
    "A (Istanbul)",
    "B (Ankara)",
    "C (Izmir)",
    "D (Bursa)",
    "E (Antalya)"
};

int graf[SEHIR_SAYISI][SEHIR_SAYISI]={
    {0,1,0,1,0},// A: İstanbul - Ankara, Bursa
    {1,0,1,0,1},// B: Ankara   - İstanbul, İzmir, Antalya
    {0,1,0,0,0},// C: İzmir    - Ankara
    {1,0,0,0,1},// D: Bursa    - İstanbul, Antalya
    {0,1,0,1,0}// E: Antalya  - Ankara, Bursa
};


void BFS(int baslangic){
    bool ziyaretEdildi[SEHIR_SAYISI]= {false};
    int kuyruk[SEHIR_SAYISI];
    int on=0,arka=0;
    ziyaretEdildi[baslangic]=true;
    kuyruk[arka++]=baslangic;
    printf("BFS dolasma sirasi= \n");
    while(on<arka){
        int mevcut=kuyruk[on++];
        printf("%s",sehirler[mevcut]);
        if(on<SEHIR_SAYISI)
        printf(" -> ");
        
        for(int i=0;i<SEHIR_SAYISI;i++){
            if(graf[mevcut][i]== 1 && !ziyaretEdildi[i]){
                ziyaretEdildi[i]=true;
                kuyruk[arka++]=i;
            }
        }
    }
    printf("\n\n");
}
void DFS_Yardimci(int dugum, bool ziyaretEdildi[], int *sayac) {
    ziyaretEdildi[dugum] = true;
    (*sayac)++;
    
    printf("%s", sehirler[dugum]);
    if (*sayac < SEHIR_SAYISI) printf(" -> ");

    for (int i = 0; i < SEHIR_SAYISI; i++) {
        if (graf[dugum][i] == 1 && !ziyaretEdildi[i]) {
            DFS_Yardimci(i, ziyaretEdildi, sayac);
        }
    }
}
void DFS(int baslangic) {
    bool ziyaretEdildi[SEHIR_SAYISI] = {false};
    int sayac = 0;
    
    printf("DFS Dolasma Sirasi:\n");
    DFS_Yardimci(baslangic, ziyaretEdildi, &sayac);
    printf("\n");
}
int main(void){
    int baslangicSehri=0;   
    BFS(baslangicSehri);
    DFS(baslangicSehri);
    return 0;
}