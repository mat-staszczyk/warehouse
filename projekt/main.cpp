#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int n = 0;

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
Sprzet* pierwszy(Sprzet*);

void dodaj_test();
int wyswietl_sprzet(Sprzet*);

Sprzet *wczytaj_z_pliku(string, Sprzet*);
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
                fflush(stdin);
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
                dodaj_test();
                break;
            case 6:
                cout << "Podaj nazwę pliku, z którego mają zostać wczytane dane:" << endl;
                fflush(stdin);
                cin >> nazwa_pliku;
                
                sprzet = wczytaj_z_pliku(nazwa_pliku, sprzet);
                
                break;
            case 7:
                cout << "Podaj nazwę pliku, w którym mają zostać zapisane dane:" << endl;
                fflush(stdin);
                cin >> nazwa_pliku;
                if(!zapisz_do_pliku(nazwa_pliku, sprzet, n))
                    cout << "Brak dostępu do pliku." << endl;
                else
                    cout << "Dane zostały pomyśle zapisane w pliku \"" << nazwa_pliku << "\"." << endl;
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

Sprzet *pierwszy(Sprzet *towar) {
    if (!(towar->poprzedni))
        return towar;
    
    while(towar->poprzedni)
        towar = towar->poprzedni;
    
    return towar;
}

void pokaz_menu() {
    cout << endl << "Menu zarządzania sprzętem:" << endl
    << endl
    << "1. Dodaj sprzęt" << endl
    << "2. Wyswietl sprzęt" << endl
    << "3. Nastepny (test)" << endl
    << "4. Poprzedni (test)" << endl
    << "5. wczytaj test" << endl
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
    return aktualny;
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
    sprzet = dodaj_sprzet(sprzet, "młot", "budowlane", "bez zastrzezen", 1, 149.99, true, true);
    sprzet = dodaj_sprzet(sprzet, "szpadel", "budowlane", "bez zastrzezen", 1, 49.99, true, true);
    sprzet = dodaj_sprzet(sprzet, "wiertło", "budowlane", "wysoka jakość", 1, 19.99, true, true);
    sprzet = dodaj_sprzet(sprzet, "wkrętarka", "budowlane", "bez zastrzezen", 1, 49.99, true, true);
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

Sprzet *wczytaj_z_pliku(string nazwa_pliku, Sprzet *sprzet)
{
    int id, ilosc, rozmiar;
    float wartosc;
    bool sprawny, nowy;
    string nazwa, typ, info;
    
    ifstream plik;
    plik.open(nazwa_pliku.c_str(), ios::in|ios::binary);
    
    plik.read((char*)&n, sizeof(n));
    Sprzet *temp = new Sprzet;
    rozmiar = n;
    
    for (int i = 0; i < rozmiar; i++)
    {
        plik.read((char*)temp, sizeof(Sprzet));
        id = temp->id_produktu;
        ilosc = temp->ilosc;
        wartosc = temp->wartosc;
        sprawny = temp->sprawny;
        nowy = temp->nowy;
        nazwa = temp->nazwa;
        typ = temp->typ;
        info = temp->informacje;

        sprzet = dodaj_sprzet(sprzet, nazwa, typ, info, ilosc, wartosc, sprawny, nowy);
    }
    
    plik.close();
    
    return sprzet;
};

int zapisz_do_pliku(string nazwa_pliku, Sprzet *sprzet, int rozmiar)
{
    ofstream plik;
    plik.open(nazwa_pliku.c_str(), (ios::out|ios::binary));

    if (!plik)
        return 0;
    
    plik.write((char*)&rozmiar, sizeof(rozmiar));

    sprzet = pierwszy(sprzet);
    
    do {
        plik.write((char*)sprzet, sizeof(Sprzet));
        cout << sprzet->nazwa;
    } while ((sprzet = sprzet->kolejny));
    
    plik.close();
    
    return 1;
}