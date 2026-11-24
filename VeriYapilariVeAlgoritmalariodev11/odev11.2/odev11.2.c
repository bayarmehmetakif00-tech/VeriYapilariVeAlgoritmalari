#include <stdio.h>
#include <stdbool.h>

#define N 6
#define INF 9999

void kenarEkle(int matris[N][N],int u,int v,int maliyet){
    matris[u][v]=maliyet;
    matris[v][u]=maliyet;
}
int dijkstra(int matris[N][N],int kok,int distance[],int path[],bool tabloYazdir){
    bool known[N];
    int toplam=0;
    int i;
    //sıfırlama fonksiyonu
    for(i=0;i<N;i++){
        known[i]=false;
        distance[i]=INF;
        path[i]=-1;

    }
    distance[kok]=0;
    for(int sayac = 0; sayac < N; sayac++){
    int minMesafe= INF,u=-1,v;
    for(i=0;i<N;i++){
        if(!known[i]&& distance[i]<minMesafe){
            minMesafe=distance[i];
            u=i;
        }
    }
    known[u]=true;
    for(v=0;v<N;v++){
        if(!known[v]&& matris[u][v]>0 && distance[u]+matris[u][v]<distance[v]){
            distance[v]=distance[u]+matris[u][v];
            path[v]=u;
        }
    }
    if(tabloYazdir){
        printf("\n[Adim %d - Secilen: %c]\n",sayac+1,'A'+u);
        for(i=0;i<N;i++){
            printf("Dugum: %c | Known: %-5s | Distance: %-4d | Path: %c\n",'A'+i,known[i] ? "True" : "False"
            ,distance[i],(path[i]== -1) ? '-' : ('A'+ path[i]));
        }
    }
    }
    //distance toplama
    for(i=0;i<N;i++){
        toplam+=distance[i];
    }
    return toplam;
}
void rotaYazdir(int path[],int hedef){
    int rota[N],adim=0;
    int mevcut=hedef;
    while(mevcut !=-1){
        rota[adim++]=mevcut;
        mevcut=path[mevcut];
    }
    for(int i=adim - 1;i>=0;i--){
        printf("%c",'A'+rota[i]);
        if(i>0){
            printf(" -> ");
        }
    }
}
int main(void){
    int matris[N][N]= {0};
    int distance[N],path[N];
    char secim;
    kenarEkle(matris,0,1,7);
    kenarEkle(matris,0,2,5);
    kenarEkle(matris,0,5,1);
    kenarEkle(matris,1,2,1);
    kenarEkle(matris,1,3,1);
    kenarEkle(matris,1,4,3);
    kenarEkle(matris,2,3,2);
    kenarEkle(matris,2,4,1);
    kenarEkle(matris,3,5,7);
    kenarEkle(matris,4,5,2);

    printf("Kok dugumu giriniz(A-F)=");
    scanf("%c",&secim);
    if(secim >='a'&& secim<='f'){
        secim-=32;
    }
    dijkstra(matris,secim-'A',distance,path,true);
    printf("\n KOK A ICIN ROTALAR\n");
    dijkstra(matris,0,distance,path,true);
    printf("A -> B Maliyeti: %d | Rota: ", distance[1]);
    rotaYazdir(path, 1);
    printf("\n");

    printf("A -> D Maliyeti: %d | Rota: ", distance[3]);
    rotaYazdir(path, 3);
    printf("\n");
}