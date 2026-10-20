# 6. Hafta BST Laboratuvarı — Kısa Değerlendirme Soruları

### 1. 25 değeri eklenirse hangi düğümün altına yerleşir?
**Cevap:** 30 düğümünün soluna yerleşir.
*Açıklama:* 25 < 40 (sola), 25 > 20 (sağa), 25 < 30 (sola). 30 düğümünün solu boş olduğu için buraya eklenir.

### 2. Inorder fonksiyonunda printf() ilk satıra taşınırsa hangi dolaşma elde edilir?
**Cevap:** Preorder (Ön-düzen) dolaşma elde edilir.
*Açıklama:* Dolaşma sırası Kök -> Sol -> Sağ şeklini alır.

### 3. findMin() içinde left yerine right takip edilirse hangi değer bulunur?
**Cevap:** Ağaçtaki **en büyük değer (Maximum)** bulunur.
