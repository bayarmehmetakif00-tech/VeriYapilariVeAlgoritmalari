#include <stdio.h>
#include <stdbool.h>

#define DERS_SAYISI 6
#define OGRENCI_SAYISI 4

// Öğrenci kayıt listesinden otomatik olarak çakışma (komşuluk) matrisi oluşturur
void grafOlustur(int kayitlar[OGRENCI_SAYISI][DERS_SAYISI], int matris[DERS_SAYISI][DERS_SAYISI]) {
    int i, j, ogr;

    // Matrisi sıfırla
    for (i = 0; i < DERS_SAYISI; i++) {
        for (j = 0; j < DERS_SAYISI; j++) {
            matris[i][j] = 0;
        }
    }

    // Aynı öğrencinin aldığı ders çiftleri arasına kenar (1) ekle
    for (ogr = 0; ogr < OGRENCI_SAYISI; ogr++) {
        for (i = 0; i < DERS_SAYISI; i++) {
            if (kayitlar[ogr][i] == 1) {
                for (j = i + 1; j < DERS_SAYISI; j++) {
                    if (kayitlar[ogr][j] == 1) {
                        matris[i][j] = 1;
                        matris[j][i] = 1;
                    }
                }
            }
        }
    }
}

// Çakışma matrisini ekrana yazdırır
void matrisYazdir(int matris[DERS_SAYISI][DERS_SAYISI]) {
    int i, j;
    printf("--- Cakisma (Komsuluk) Matrisi ---\n    ");
    for (i = 0; i < DERS_SAYISI; i++) printf("d%d ", i);
    printf("\n");

    for (i = 0; i < DERS_SAYISI; i++) {
        printf("d%d: ", i);
        for (j = 0; j < DERS_SAYISI; j++) {
            printf(" %d ", matris[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Welch-Powell Algoritması ile renklendirme ve raporlama
void welchPowell(int matris[DERS_SAYISI][DERS_SAYISI]) {
    int derece[DERS_SAYISI] = {0};
    int siraliDugumler[DERS_SAYISI];
    int renk[DERS_SAYISI];
    int i, j, k, temp;

    // 1. Düğüm derecelerini hesapla ve başlangıç dizilerini kur
    for (i = 0; i < DERS_SAYISI; i++) {
        siraliDugumler[i] = i;
        renk[i] = 0; 
        for (j = 0; j < DERS_SAYISI; j++) {
            derece[i] += matris[i][j];
        }
    }

    // 2. Düğümleri derecelerine göre büyükten küçüğe sırala
    for (i = 0; i < DERS_SAYISI - 1; i++) {
        for (j = 0; j < DERS_SAYISI - i - 1; j++) {
            int d1 = siraliDugumler[j];
            int d2 = siraliDugumler[j + 1];
            if (derece[d1] < derece[d2]) {
                temp = siraliDugumler[j];
                siraliDugumler[j] = siraliDugumler[j + 1];
                siraliDugumler[j + 1] = temp;
            }
        }
    }

    printf("Dereceye Gore Siralama: ");
    for (i = 0; i < DERS_SAYISI; i++) {
        int d = siraliDugumler[i];
        printf("d%d(der:%d) ", d, derece[d]);
    }
    printf("\n\n");

    // 3. Welch-Powell Renklendirme Döngüsü
    int mevcutRenk = 0;
    int boyananSayisi = 0;

    while (boyananSayisi < DERS_SAYISI) {
        mevcutRenk++;
        for (i = 0; i < DERS_SAYISI; i++) {
            int aday = siraliDugumler[i];
            if (renk[aday] == 0) {
                bool komsuVar = false;
                // Şu anki renge boyanmış düğümlerle komşuluğu var mı kontrol et
                for (k = 0; k < DERS_SAYISI; k++) {
                    if (renk[k] == mevcutRenk && matris[aday][k] == 1) {
                        komsuVar = true;
                        break;
                    }
                }
                if (!komsuVar) {
                    renk[aday] = mevcutRenk;
                    boyananSayisi++;
                }
            }
        }
    }

    // 4. Raporlama: Kromatik Sayı ve Oturum Grupları
    printf("Minimum Sinav Oturumu Sayisi (Kromatik Sayi): %d\n", mevcutRenk);
    for (int r = 1; r <= mevcutRenk; r++) {
        printf("Oturum %d: ", r);
        for (i = 0; i < DERS_SAYISI; i++) {
            if (renk[i] == r) {
                printf("d%d ", i);
            }
        }
        printf("\n");
    }
}

int main(void) {
    int kayitlar[OGRENCI_SAYISI][DERS_SAYISI] = {
        {1, 1, 0, 0, 1, 0}, // Ogrenci-1: d0, d1, d4
        {1, 0, 1, 0, 1, 0}, // Ogrenci-2: d0, d2, d4
        {0, 0, 1, 1, 0, 1}, // Ogrenci-3: d2, d3, d5
        {0, 0, 0, 1, 1, 1}  // Ogrenci-4: d3, d4, d5
    };

    int matris[DERS_SAYISI][DERS_SAYISI];

    printf("==================================================\n");
    printf("1. MEVCUT KAYIT LISTESI ILE SINAV TAKVIMI\n");
    printf("==================================================\n");
    grafOlustur(kayitlar, matris);
    matrisYazdir(matris);
    welchPowell(matris);

    printf("\n==================================================\n");
    printf("2. DINAMIK GUNCELLEME (Ogrenci-4 d4 dersini birakti)\n");
    printf("==================================================\n");
    kayitlar[3][4] = 0; // Ogrenci-4 (indeks 3), d4 (indeks 4) dersini bıraktı
    grafOlustur(kayitlar, matris);
    matrisYazdir(matris);
    welchPowell(matris);

    return 0;
}