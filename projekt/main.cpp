#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int N = 100;

struct Sprzet {
    int id_produktu;
    int ilosc;
    string nazwa;
    string typ;
    string informacje;
    float wartosc;
    bool sprawny;
    bool uzywany;
};

void pokaz_menu();

void dodaj_sprzet();
void wyswietl_sprzet();
void usun_sprzet();
void wyszukiwanie();
void sortowanie();
void kosz();

int wczytaj_z_pliku(string, Sprzet*, int);
int zapisz_do_pliku(string, Sprzet*, int);

Sprzet * sprzet = new Sprzet[N];

int main() {
    
    string nazwa_pliku;
    int wybor;
    
    while (1) {
        
        pokaz_menu();
        
        cout << "> ";
        fflush(stdin);
        cin >> wybor;
        
        switch (wybor)
        {
            case 1:
                dodaj_sprzet();
                break;
            case 2:
                wyswietl_sprzet();
                break;
            case 3:
                wyszukiwanie();
                break;
            case 4:
                sortowanie();
                break;
            case 5:
                kosz();
                break;
            case 6:
                cout << "Podaj nazwę pliku, którego dane mają zostać wczytane:" << endl;
                fflush(stdin);
                cin >> nazwa_pliku;
                if(!wczytaj_z_pliku(nazwa_pliku, sprzet, N))
                    cout << "Błąd dostępu do pliku." << endl;
                break;
            case 7:
                cout << "Podaj nazwę pliku, w którym mają zostać zapisane dane." << endl;
                fflush(stdin);
                cin >> nazwa_pliku;
                if(!zapisz_do_pliku(nazwa_pliku, sprzet, N))
                    cout << "Błąd dostępu do pliku." << endl;
                break;
            case 8:
                cout << "Działanie programu zostało zakończone." << endl;
                return 0;
            default:
                cout << "Błędny wybór." << endl;
                break;
        }
    }
    
    return 0;
}

void pokaz_menu() {
    cout << endl << "Menu zarządzania sprzętem:" << endl
    << endl
    << "1. Dodaj sprzęt" << endl
    << "2. Wyswietl sprzęt" << endl
    << "3. Wyszukaj" << endl
    << "4. Sortowanie" << endl
    << "5. Kosz" << endl
    << "6. Wczytaj z pliku" << endl
    << "7. Zapisz do pliku" << endl
    << endl;
};

void dodaj_sprzet() {
    // Testowe dodanie dwóch elementów
    sprzet[0].id_produktu = 1;
    sprzet[0].ilosc = 1;
    sprzet[0].nazwa = "młot";
    sprzet[0].typ = "budowlane";
    sprzet[0].informacje = "bez zastrzeżeń";
    sprzet[0].wartosc = 79.00;
    sprzet[0].sprawny = true;
    sprzet[0].uzywany = false;
    
    sprzet[1].id_produktu = 2;
    sprzet[1].ilosc = 5;
    sprzet[1].nazwa = "wiertło";
    sprzet[1].typ = "budowlane";
    sprzet[1].informacje = "słaba jakość";
    sprzet[1].wartosc = 11.00;
    sprzet[1].sprawny = true;
    sprzet[1].uzywany = true;
};

void wyswietl_sprzet() {
    cout << "Nazwa: " << sprzet[0].nazwa << endl;
};
void usun_sprzet() {
    cout << "test" << endl;
};
void wyszukiwanie() {
    cout << "test" << endl;
};
void sortowanie() {
    cout << "test" << endl;
};
void kosz() {
    cout << "test" << endl;
};

int wczytaj_z_pliku(string nazwa_pliku, Sprzet *sprzet, int rozmiar)
{
    ifstream plik;
    long rozmiar_struktury = rozmiar * sizeof(Sprzet);

    plik.open(nazwa_pliku.c_str(), ios::in|ios::binary);
    
    if(!plik)
        return 0;
    
    plik.read((char*)sprzet, rozmiar_struktury);
    plik.close();
    
    return 1;
};

int zapisz_do_pliku(string nazwa_pliku, Sprzet *sprzet, int rozmiar)
{
    ofstream plik;
    long rozmiar_struktury = rozmiar * sizeof(Sprzet);
    
    plik.open(nazwa_pliku.c_str(), (ios::out|ios::binary));
    
    if (!plik)
        return 0;
    
    plik.write((char*)sprzet, rozmiar_struktury);
    plik.close();
    
    return 1;
}