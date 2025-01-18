#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <locale.h>

/* öðrenci no:2312721039   ad-soyad:ilknur ökmen  konu:mefruþat otomasyonu */

using namespace std;


struct Mefrusat {
    char ad[80];
    char kategori[50];
    float fiyat;
    int miktar;
};

void urunEkle();
void urunListele();
void urunGuncelle();
void urunSil();
void urunAra();

int main() {
	setlocale(LC_ALL,"Turkish");
    char secim;
    do {
        system("cls");
        cout << "|------- Mefrusat Otomasyonu -------|" << endl;
        cout << "| 1 - ürün Ekle                     |" << endl;
        cout << "| 2 -  ürün Listele                  |" << endl;
        cout << "| 3 - ürün güncelle                 |" << endl;
        cout << "| 4 -  ürün Sil                      |" << endl;
        cout << "| 5 -  ürün Ara                      |" << endl;
        cout << "| çýkmak için 'q' tuþuna basýn.     |" << endl;
        cout << "|-----------------------------------|" << endl;
        cin >> secim;
        
        switch(secim) {
            case '1': urunEkle(); break;
            case '2': urunListele(); break;
            case '3': urunGuncelle(); break;
            case '4': urunSil(); break;
            case '5': urunAra(); break;
            case 'q': break;
            default: cout << "Geçersiz seçenek!" << endl;
        }
        
        cout << "Ana menüye dönmek için 'a', çýkmak için 'q' basýn: ";
        cin >> secim;
    } while (secim != 'q');
    
    return 0;
}

void urunEkle() {
    Mefrusat urun;
    ofstream yaz("mefrusat.dat", ios::binary | ios::app);
    
    char secim;
    do {
        cout << "Ürün Adý: ";
        cin >> urun.ad;
        cout << "Ürün Kategorisi: ";
        cin >> urun.kategori;
        cout << "Ürün Fiyatý: ";
        cin >> urun.fiyat;
        cout << "Ürün miktarý: ";
        cin >> urun.miktar;
        
        yaz.write((char*)&urun, sizeof(urun));
        cout << "Baþka ürün eklemek ister misiniz? (E/H): ";
        cin >> secim;
    } while (secim == 'e' || secim == 'E');
    
    yaz.close();
}

void urunListele() {
    ifstream oku("mefrusat.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritabaný bulunamadý!" << endl;
        return;
    }
    
    Mefrusat urun;
    int i = 1;
    while (oku.read((char*)&urun, sizeof(urun))) {
        cout << i++ << ". Ürün adý: " << urun.ad << ", Kategori: " << urun.kategori
             << ", Fiyat: " << urun.fiyat << " TL, Miktar: " << urun.miktar << endl;
    }
    
    oku.close();
}

void urunGuncelle() {
    ifstream oku("mefrusat.dat", ios::binary);
    ofstream gecici("gecici.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritabaný bulunamadý!" << endl;
        return;
    }
    
    char urunAd[80];
    cout << "Güncellemek istediðiniz ürünün adetini girin: ";
    cin >> urunAd;
    
    Mefrusat urun;
    bool bulundu = false;
    
    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) == 0) {
            bulundu = true;
            cout << "Ürün Bulundu!" << endl;
            cout << "Yeni Fiyatý: ";
            cin >> urun.fiyat;
            cout << "Yeni Miktarý: ";
            cin >> urun.miktar;
            cout << "Ürün güncellendi!" << endl;
        }
        gecici.write((char*)&urun, sizeof(urun));
    }
    
    oku.close();
    gecici.close();
    
    if (bulundu) {
        remove("mefrusat.dat");
        rename("gecici.dat", "mefrusat.dat");
    } else {
        remove("gecici.dat");
        cout << "ÃœrÃ¼n bulunamadÄ±!" << endl;
    }
}

void urunSil() {
    ifstream oku("mefrusat.dat", ios::binary);
    ofstream gecici("gecici.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritabaný bulunamadý!" << endl;
        return;
    }
    
    char urunAd[80];
    cout << "Silmek istediðiniz ürünün adýný girin: ";
    cin >> urunAd;
    
    Mefrusat urun;
    bool bulundu = false;
    
    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) != 0) {
            gecici.write((char*)&urun, sizeof(urun));
        } else {
            bulundu = true;
            cout << "Ürün Silindi!" << endl;
        }
    }
    
    oku.close();
    gecici.close();
    
    if (bulundu) {
        remove("mefrusat.dat");
        rename("gecici.dat", "mefrusat.dat");
    } else {
        remove("gecici.dat");
        cout << "Ürün bulunamadý!" << endl;
    }
}

void urunAra() {
    ifstream oku("mefrusat.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritabaný bulunamadý!" << endl;
        return;
    }
    
    char urunAd[80];
    cout << "Aramak istediðiniz ürün adýný girin: ";
    cin >> urunAd;
    
    Mefrusat urun;
    bool bulundu = false;
    
    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) == 0) {
            bulundu = true;
            cout << "aranan Bulundu!" << endl;
            cout << "ürünün adý: " << urun.ad << ", Kategori: " << urun.kategori
                 << ", Fiyat: " << urun.fiyat << " TL, Miktar: " << urun.miktar << endl;
        }
    }
    
    if (!bulundu) {
        cout << "ürün bulunamadý!" << endl;
    }
    
    oku.close();
}
