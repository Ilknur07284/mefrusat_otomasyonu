#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <locale.h>

/* ��renci no:2312721039   ad-soyad:ilknur �kmen  konu:mefru�at otomasyonu */

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
        cout << "| 1 - �r�n Ekle                     |" << endl;
        cout << "| 2 -  �r�n Listele                  |" << endl;
        cout << "| 3 - �r�n g�ncelle                 |" << endl;
        cout << "| 4 -  �r�n Sil                      |" << endl;
        cout << "| 5 -  �r�n Ara                      |" << endl;
        cout << "| ��kmak i�in 'q' tu�una bas�n.     |" << endl;
        cout << "|-----------------------------------|" << endl;
        cin >> secim;
        
        switch(secim) {
            case '1': urunEkle(); break;
            case '2': urunListele(); break;
            case '3': urunGuncelle(); break;
            case '4': urunSil(); break;
            case '5': urunAra(); break;
            case 'q': break;
            default: cout << "Ge�ersiz se�enek!" << endl;
        }
        
        cout << "Ana men�ye d�nmek i�in 'a', ��kmak i�in 'q' bas�n: ";
        cin >> secim;
    } while (secim != 'q');
    
    return 0;
}

void urunEkle() {
    Mefrusat urun;
    ofstream yaz("mefrusat.dat", ios::binary | ios::app);
    
    char secim;
    do {
        cout << "�r�n Ad�: ";
        cin >> urun.ad;
        cout << "�r�n Kategorisi: ";
        cin >> urun.kategori;
        cout << "�r�n Fiyat�: ";
        cin >> urun.fiyat;
        cout << "�r�n miktar�: ";
        cin >> urun.miktar;
        
        yaz.write((char*)&urun, sizeof(urun));
        cout << "Ba�ka �r�n eklemek ister misiniz? (E/H): ";
        cin >> secim;
    } while (secim == 'e' || secim == 'E');
    
    yaz.close();
}

void urunListele() {
    ifstream oku("mefrusat.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritaban� bulunamad�!" << endl;
        return;
    }
    
    Mefrusat urun;
    int i = 1;
    while (oku.read((char*)&urun, sizeof(urun))) {
        cout << i++ << ". �r�n ad�: " << urun.ad << ", Kategori: " << urun.kategori
             << ", Fiyat: " << urun.fiyat << " TL, Miktar: " << urun.miktar << endl;
    }
    
    oku.close();
}

void urunGuncelle() {
    ifstream oku("mefrusat.dat", ios::binary);
    ofstream gecici("gecici.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritaban� bulunamad�!" << endl;
        return;
    }
    
    char urunAd[80];
    cout << "G�ncellemek istedi�iniz �r�n�n adetini girin: ";
    cin >> urunAd;
    
    Mefrusat urun;
    bool bulundu = false;
    
    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) == 0) {
            bulundu = true;
            cout << "�r�n Bulundu!" << endl;
            cout << "Yeni Fiyat�: ";
            cin >> urun.fiyat;
            cout << "Yeni Miktar�: ";
            cin >> urun.miktar;
            cout << "�r�n g�ncellendi!" << endl;
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
        cout << "Ürün bulunamadı!" << endl;
    }
}

void urunSil() {
    ifstream oku("mefrusat.dat", ios::binary);
    ofstream gecici("gecici.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritaban� bulunamad�!" << endl;
        return;
    }
    
    char urunAd[80];
    cout << "Silmek istedi�iniz �r�n�n ad�n� girin: ";
    cin >> urunAd;
    
    Mefrusat urun;
    bool bulundu = false;
    
    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) != 0) {
            gecici.write((char*)&urun, sizeof(urun));
        } else {
            bulundu = true;
            cout << "�r�n Silindi!" << endl;
        }
    }
    
    oku.close();
    gecici.close();
    
    if (bulundu) {
        remove("mefrusat.dat");
        rename("gecici.dat", "mefrusat.dat");
    } else {
        remove("gecici.dat");
        cout << "�r�n bulunamad�!" << endl;
    }
}

void urunAra() {
    ifstream oku("mefrusat.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritaban� bulunamad�!" << endl;
        return;
    }
    
    char urunAd[80];
    cout << "Aramak istedi�iniz �r�n ad�n� girin: ";
    cin >> urunAd;
    
    Mefrusat urun;
    bool bulundu = false;
    
    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) == 0) {
            bulundu = true;
            cout << "aranan Bulundu!" << endl;
            cout << "�r�n�n ad�: " << urun.ad << ", Kategori: " << urun.kategori
                 << ", Fiyat: " << urun.fiyat << " TL, Miktar: " << urun.miktar << endl;
        }
    }
    
    if (!bulundu) {
        cout << "�r�n bulunamad�!" << endl;
    }
    
    oku.close();
}
