#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello World\n");
    int sayilar[10];
    int i;
    for(i= 0;i<10;i++)
    {
        printf("Lutfen tam sayi giriniz =");
        scanf("%d",&sayilar[i]);
        
    }
    for(i=0;i<10;i++)
    {
        printf("%d\n",sayilar[i]);
    }
    /*T(n) zaman maliyeti her işlemi birer kez saydığımızda çıkar ve doğrusaldır.
     bunun sonucu da A.n +B dir.*/
     /*O(n) zaman karmaşıklığı ise T(n) zaman maliyetindeki en büyük dereceli terim dikkate alınır
     ve sabitler ihmal edilir.Bu yüzden zaman karmaşıklığı O(n)(Doğrusal zaman)'dir*/
     /*n elemanlı sayilar[10] dizisi bellekte n adet tamsayı boyutu kadar yer kaplar.i ve n değişkenleri
     bellekte sabit miktarda yer kaplar. Gereken toplam alan bellekteki eleman sayısına(n) doğrudan 
     bağlıdır.Sabitler göz ardı edildiğinde alan karmaşıklığı O(n) olur.
     */

    int sayi, orijinalSayi, tersSayi = 0, kalan;
    printf("Bir tam sayi girin: ");
    scanf("%d", &sayi);

    orijinalSayi = sayi;

    // Negatif sayılar işaretleri nedeniyle palindrom kabul edilmez
    if (sayi < 0) {
        printf("%d bir palindrom sayi degildir.\n", sayi);
        return 0;
    }

    while (sayi != 0) {
        kalan = sayi % 10;                  
        tersSayi = (tersSayi * 10) + kalan; 
        sayi /= 10;                         
    }
    if (orijinalSayi == tersSayi) {
        printf("%d bir palindrom sayidir.\n", orijinalSayi);
    } else {
        printf("%d bir palindrom sayi degildir.\n", orijinalSayi);
    }




    system("pause");

    return 0;
}