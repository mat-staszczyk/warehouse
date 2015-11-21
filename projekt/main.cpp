#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int n = 1;

struct Sprzet {
    Sprzet *poprzedni;
    Sprzet *kolejny;
    
    int id_produktu;
    int ilosc;
    string nazwa;
    string typ;
    string informacje;
    float wartosc;
    bool sprawny;
    bool nowy;
};

void pokaz_menu();
Sprzet* dodaj_sprzet(Sprzet*, string, string, string, int, float, bool, bool);
Sprzet* nastepny(Sprzet*);
Sprzet* poprzedni(Sprzet*);

void dodaj_test();
int wyswietl_sprzet(Sprzet*);
void usun_sprzet();
void wyszukiwanie();
void sortowanie();
void kosz();

int wczytaj_z_pliku(string, Sprzet*);
int zapisz_do_pliku(string, Sprzet*, int);

Sprzet * sprzet = new Sprzet;

int main() {
    
    sprzet = NULL;
    string nazwa_pliku;
    int wybor;
    
    int ilosc;
    string nazwa, typ, info;
    float wartosc;
    bool sprawny, nowy;
    char temp;
    
    while (1) {
        
        pokaz_menu();
        
        cout << "> ";
        fflush(stdin);
        cin >> wybor;
        
        switch (wybor)
        {
            case 1:
                cout << "Dodawanie sprzętu." << endl << endl
                << "Nazwa: " << endl << "> ";
                cin >> nazwa;
                cout << "Rodzaj: " << endl << "> ";
                cin >> typ;
                cout << "Wartość: " << endl << "> ";
                cin >> wartosc;
                cout << "Ilość: " << endl << "> ";
                cin >> ilosc;
                cout << "Stan: sprawny (t/n)?" << endl << "> ";
                cin >> temp;
                if (temp == 't' || temp == 'T')
                    sprawny = true;
                else
                    sprawny = false;
                cout << "Stan: nowy (t/n)?" << endl << "> ";
                cin >> temp;
                if (temp == 't' || temp == 'T')
                    nowy = true;
                else
                    nowy = false;
                cout << "Dodatkowe informacje: " << endl << "> ";
                cin >> info;
                
                sprzet = dodaj_sprzet(sprzet, nazwa, typ, info, ilosc, wartosc, sprawny, nowy);
                break;
            case 2:
                if(!wyswietl_sprzet(sprzet))
                    cout << "Lista sprzętu jest pusta." << endl;
                break;
            case 3:
                sprzet = nastepny(sprzet);
                break;
            case 4:
                sprzet = poprzedni(sprzet);
                break;
            case 5:
                kosz();
                break;
            case 6:
                cout << "Podaj nazwę pliku, z którego mają zostać wczytane dane:" << endl;
                fflush(stdin);
                cin >> nazwa_pliku;
                if(!wczytaj_z_pliku(nazwa_pliku, sprzet))
                    cout << "Brak dostępu do pliku." << endl;
                break;
            case 7:
                cout << "Podaj nazwę pliku, w którym mają zostać zapisane dane:" << endl;
                fflush(stdin);
                cin >> nazwa_pliku;
                if(!zapisz_do_pliku(nazwa_pliku, sprzet, n))
                    cout << "Brak dostępu do pliku." << endl;
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
    << "3. Nastepny (test)" << endl
    << "4. Poprzedni (test)" << endl
    << "5. Kosz" << endl
    << "6. Wczytaj z pliku" << endl
    << "7. Zapisz do pliku" << endl
    << endl;
};

Sprzet* dodaj_sprzet(Sprzet *przedmiot, string nazwa, string typ, string info, int ilosc, float wartosc, bool sprawny, bool nowy)
{
    Sprzet *aktualny;
    
    aktualny = new Sprzet;
    aktualny->nazwa = nazwa;
    aktualny->typ = typ;
    aktualny->informacje = info;
    aktualny->ilosc = ilosc;
    aktualny->wartosc = wartosc;
    aktualny->sprawny = sprawny;
    aktualny->nowy = nowy;
    aktualny->kolejny = NULL;
    if (przedmiot!=NULL) {
        przedmiot->kolejny = aktualny;
        aktualny->poprzedni = przedmiot;
        aktualny->id_produktu = (przedmiot->id_produktu) + 1;
    } else {
        przedmiot = aktualny;
        przedmiot->poprzedni = NULL;
        przedmiot->id_produktu = 1;
    }
    
    n++;
    return przedmiot;
};

Sprzet* nastepny(Sprzet *przedmiot)
{
    if (przedmiot->kolejny != NULL)
        przedmiot = przedmiot->kolejny;
    else
        cout << "Brak kolejnych przedmiotów.";
    
    return przedmiot;
}


Sprzet* poprzedni(Sprzet *przedmiot)
{
    if (przedmiot->poprzedni != NULL)
        przedmiot = przedmiot->poprzedni;
    else
        cout << "Brak kolejnych przedmiotów.";
    
    return przedmiot;
}

void dodaj_test() {
    // Testowe dodanie dwóch elementów
    sprzet[0].id_produktu = 1;
    sprzet[0].ilosc = 1;
    sprzet[0].nazwa = "młot";
    sprzet[0].typ = "budowlane";
    sprzet[0].informacje = "bez zastrzeżeń";
    sprzet[0].wartosc = 79.00;
    sprzet[0].sprawny = true;
    sprzet[0].nowy = false;
    
    sprzet[1].id_produktu = 2;
    sprzet[1].ilosc = 5;
    sprzet[1].nazwa = "wiertło";
    sprzet[1].typ = "budowlane";
    sprzet[1].informacje = "słaba jakość";
    sprzet[1].wartosc = 11.00;
    sprzet[1].sprawny = true;
    sprzet[1].nowy = true;
};

int wyswietl_sprzet(Sprzet* towar) {
    
    if (towar == NULL)
        return 0;
    
    cout << "Dane przedmiotu:" << endl;
    cout << "Nazwa: " << towar->nazwa << endl;
    cout << "ID: " << towar->id_produktu << endl;
    cout << "Rodzaj: " << towar->typ << endl;
    cout << "Ilość: " << towar->ilosc << endl;
    cout << "Wartość: " << towar->wartosc << endl;
    cout << "Sprawny: " << towar->sprawny << endl;
    cout << "Nowy: " << towar->nowy << endl << endl;
    
    return 1;
}


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

int wczytaj_z_pliku(string nazwa_pliku, Sprzet *sprzet)
{
    ifstream plik;

    plik.open(nazwa_pliku.c_str(), ios::in|ios::binary);
    
    if(!plik)
        return 0;
    
    plik.read((char*)&n, sizeof(n));
    long rozmiar_struktury = n * sizeof(Sprzet);
    
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
    plik.write((char*)&n, sizeof(n));
    plik.write((char*)sprzet, rozmiar_struktury);
    plik.close();
    
    return 1;
}