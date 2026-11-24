#include <stdio.h>
#include <stdbool.h>

#define N 6

void kenarEkle(int matris[N+1][N+1], int u, int v){
    matris[u][v]=1;
    matris[v][u]=1;
}

void matrisYazdir(int matris[N+1][N+1]){
    printf("=======KOMSULUK MATRISI=======\n");
    int i;
    int j;
    for(i=1;i<=N;i++)
        printf("%d",i);
    printf("\n");
    for(i=1;i<=N;i++){
        printf("%d: ",i);
        for(j=1;j<=N;j++){
            printf("%d",matris[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void dereceHesapla(int matris[N+1][N+1]){
    printf("======Dugum derecesi=======\n");
    int toplamDerece=0;
    int i,j;
    for(i=1;i<=N;i++){
        int derece=0;
        for(j=1;j<=N;j++){
            derece+=matris[i][j];
        }
        toplamDerece+=derece;
        printf("Dugum %d derecesi= %d\n",i,derece);
    }
    printf("Grafin Genel (Toplam) Derecesi: %d\n\n", toplamDerece);
}

void bipartiteKontrol(int matris[N+1][N+1], int baslangic){
    printf("--- 3. Bipartite Kontrolu (baslangic: %d) ---\n", baslangic);
    int mesafe[N+1];
    int i,v,u;
    for(i=1;i<=N;i++) mesafe[i]=-1;
    int kuyruk[N+1];
    int on=0,arka=0;
    mesafe[baslangic]=0;
    kuyruk[arka++]=baslangic;
    bool isBipartite=true;
    while(on<arka){
        int u=kuyruk[on++];
        for(v=1;v<=N;v++){
            if(matris[u][v]==1)
            {
                if(mesafe[v]==-1){
                    mesafe[v]=mesafe[u]+1;
                    kuyruk[arka++]=v;
                }
                else if((mesafe[u] % 2)== mesafe[v] % 2){
                    isBipartite=false;
                    printf("[!] Cakisma Tespit Edildi: Dugum %d (Renk %d) ve Dugum %d (Renk %d) bagli!\n",u, mesafe[u] % 2, v, mesafe[v] % 2);
                }
            }
        }
    }
    for(i=1;i<=N;i++){
        int renk= mesafe[i] %2;
        printf("Dugum-> %d uzaklik= %d ,Renk/Parite:%d (%s - Kume %s)\n",i,mesafe[i],renk,renk == 0 ? "Mavi/Cift" : "Kirmizi/Tek",renk == 0 ? "U" : "V");
    }
    if (isBipartite) {
        printf("\nSonuc: Graf IKI PARCALIDIR (Bipartite). Guvenlik politikasi saglandi.\n");
    } else {
        printf("\nSonuc: Graf IKI PARCALI DEGILDIR (Not Bipartite). Guvenlik ihlali var!\n");
    }
}

int main(void){
    int komsulukMatrisi[N+1][N+1]={0};

    kenarEkle(komsulukMatrisi, 1, 2);
    kenarEkle(komsulukMatrisi, 1, 4);
    kenarEkle(komsulukMatrisi, 2, 3);
    kenarEkle(komsulukMatrisi, 3, 4);
    kenarEkle(komsulukMatrisi, 3, 6);
    kenarEkle(komsulukMatrisi, 4, 5);
    kenarEkle(komsulukMatrisi, 5, 6);

    matrisYazdir(komsulukMatrisi);
    dereceHesapla(komsulukMatrisi);
    bipartiteKontrol(komsulukMatrisi,1);
}