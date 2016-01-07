#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Sprzet
{

private:

    int id_produktu;
    int ilosc;
    string nazwa;
    string typ;
    string informacje;
    float wartosc;
    bool sprawny;
    bool nowy;

    Sprzet *poprzedni;
    Sprzet *kolejny;

    friend class ListaSprzetu;

public:

    Sprzet();
    Sprzet( int, string, string, string, float, bool, bool, int=NULL);
    Sprzet( Sprzet & );
    ~Sprzet();

    Sprzet *dodajDane();
    void wypiszDane();
};

class ListaSprzetu
{

private:

    Sprzet * sprzet;
    Sprzet * pierwszy;
    int n;
    bool autonumeracja;

public:

    ListaSprzetu();
    ListaSprzetu(bool);

    void pokazMenu();
    void dodajSprzet(Sprzet*);
    void poczatekListy();
    void wypiszElement();
    void listaJestPusta();
    void nastepnyElement();
    void poprzedniElement();
    void przeniesElement(ListaSprzetu*);
    void usunElement();
    void wyszukiwanieFrazy(ListaSprzetu*, string);
    void wyszukiwanieKwoty(ListaSprzetu*, float, float);
    void wyszukiwanieLicznosci(ListaSprzetu*, int, int);
    void wyswietlSprawne(ListaSprzetu*);
    void wyswietlUszkodzone(ListaSprzetu*);
    void wyswietlNowe(ListaSprzetu*);
    void wyswietlUzywane(ListaSprzetu*);

    Sprzet * pierwszyElement();
    ListaSprzetu * wczytajZPliku(string);

    int iloscElementow();
    int zapisDoPliku(string, Sprzet*, int);

};

class Pomocnik
{

public:

    string tlumaczBool(bool);
    string pobierzFraze();
    float * pobierzKwoty();
    int * pobierzLiczbe();
    bool czyZawieraFraze(string, string);
};


int main() {

    int n;
    int * liczba;
    string nazwa_pliku, fraza;
    float * kwoty;
    char klawisz;

    ListaSprzetu *lista = new ListaSprzetu;
    ListaSprzetu *kosz = new ListaSprzetu(false);
    ListaSprzetu *wyniki = new ListaSprzetu(false);
    Pomocnik * pom = new Pomocnik;

    Sprzet * test;

    do
    {
        lista->pokazMenu();

        cout << "> ";
        cin >> klawisz;
        cin.ignore();
        switch (klawisz)
        {
            case '1':
                test = new Sprzet;
                test = test->dodajDane();

                lista->dodajSprzet(test);

                cout << "Dodano element: " << endl;
                lista->wypiszElement();
                break;
            case '2':
                lista->wypiszElement();
                break;
            case '3':
                lista->nastepnyElement();
                break;
            case '4':
                lista->poprzedniElement();
                break;
            case '5':
                cout << "Podaj nazwę pliku, z którego mają zostać wczytane dane:" << endl;
                fflush(stdin);
                cin >> nazwa_pliku;
                lista = lista->wczytajZPliku(nazwa_pliku);
                break;
            case '6':
                test = lista->pierwszyElement();
                n = lista->iloscElementow();

                cout << "Podaj nazwę pliku, w którym mają zostać zapisane dane:" << endl;
                fflush(stdin);
                cin >> nazwa_pliku;
                if(!lista->zapisDoPliku(nazwa_pliku, test, n))
                    cout << "Brak dostępu do pliku." << endl;
                else
                    cout << "Dane zostały pomyśle zapisane w pliku \"" << nazwa_pliku << "\"." << endl;
                break;
            case '7':
                lista->usunElement();
                break;
            case '8':
                lista->przeniesElement(kosz);
                kosz->wypiszElement();
                break;
            case '9':
                fraza = pom->pobierzFraze();
                lista->wyszukiwanieFrazy(wyniki, fraza);
                wyniki->wypiszElement();
                break;
            case 'a':
                kwoty = pom->pobierzKwoty();
                lista->wyszukiwanieKwoty(wyniki, kwoty[0], kwoty[1]);
                wyniki->wypiszElement();
                break;
            case 'b':
                liczba = pom->pobierzLiczbe();
                lista->wyszukiwanieLicznosci(wyniki, liczba[0], liczba[1]);
                wyniki->wypiszElement();
                break;
            case 'c':
                lista->wyswietlSprawne(wyniki);
                wyniki->wypiszElement();
                break;
            case 'd':
                lista->wyswietlUszkodzone(wyniki);
                wyniki->wypiszElement();
                break;
            case 'e':
                lista->wyswietlNowe(wyniki);
                wyniki->wypiszElement();
                break;
            case 'f':
                lista->wyswietlUzywane(wyniki);
                wyniki->wypiszElement();
                break;
            default:
                break;

        }

    } while (klawisz != 'e' );

    return 0;
}


// Sprzet - metody

Sprzet::Sprzet()
{
}

Sprzet::Sprzet( int ilosc, string nazwa, string typ, string informacje, float wartosc, bool sprawny, bool nowy, int id_produktu )
{
    this->ilosc = ilosc;
    this->nazwa = nazwa;
    this->typ = typ;
    this->informacje = informacje;
    this->wartosc = wartosc;
    this->sprawny = sprawny;
    this->nowy = nowy;
    this->id_produktu = NULL;
}

Sprzet::Sprzet( Sprzet & inny )
{
    this->ilosc = inny.ilosc;
    this->nazwa = inny.nazwa;
    this->typ = inny.typ;
    this->informacje = inny.informacje;
    this->wartosc = inny.wartosc;
    this->sprawny = inny.sprawny;
    this->nowy = inny.nowy;
    this->id_produktu = inny.id_produktu;
}

Sprzet::~Sprzet()
{
    cout << endl << "Przedmiot " << this->nazwa << " został usunięty." << endl;
}

Sprzet* Sprzet::dodajDane()
{
    int ilosc;
    string nazwa, typ, info;
    float wartosc;
    char temp;
    bool nowy, sprawny;
    Sprzet * biezacy;


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
    cin.ignore();
    temp = getchar();
    sprawny = (temp == 't' || temp == 'T') ? true : false;
    cout << "Stan: nowy (t/n)?" << endl << "> ";
    cin.ignore();
    temp = getchar();
    nowy = (temp == 't' || temp == 'T') ? true : false;
    cout << "Dodatkowe informacje: " << endl << "> ";
    cin >> info;

    biezacy = new Sprzet(ilosc, nazwa, typ, info, wartosc, sprawny, nowy);

    return biezacy;
}

void Sprzet::wypiszDane()
{
    Pomocnik * pomocnik = new Pomocnik;

    cout << "Dane przedmiotu:" << endl;

    cout << "ID: " << this->id_produktu << endl;
    cout << "Nazwa: " << this->nazwa << endl;
    cout << "Rodzaj: " << this->typ << endl;
    cout << "Ilość: " << this->ilosc << endl;
    cout << "Wartość: " << this->wartosc << endl;
    cout << "Sprawny: " << pomocnik->tlumaczBool(this->sprawny) << endl;
    cout << "Nowy: " << pomocnik->tlumaczBool(this->nowy) << endl;
    cout << "Informacje: " << this->informacje << endl << endl;

    delete pomocnik;
}

// ListaSprzetu - metody

ListaSprzetu::ListaSprzetu()
{
    this->autonumeracja = true;
    sprzet = NULL;
    pierwszy = NULL;
    n = 0;
}

ListaSprzetu::ListaSprzetu(bool autonumeracja)
{
    this->autonumeracja = autonumeracja;
}

void ListaSprzetu::pokazMenu() {
    cout << endl << "Menu zarządzania sprzętem:" << endl
    << endl
    << "1. Dodaj sprzęt" << endl
    << "2. Wyswietl sprzęt" << endl
    << "3. Nastepny (test)" << endl
    << "4. Poprzedni (test)" << endl
    << "5. Wczytaj z pliku" << endl
    << "6. Zapis do pliku" << endl
    << "7. Usuń element" << endl
    << "8. Przenieś do kosza" << endl
    << "9. Wyszukaj tekst" << endl
    << "a. Wyszukaj wartość" << endl
    << "b. Wyszukaj liczność" << endl
    << "c. Wyświetl sprawne" << endl
    << "d. Wyświetl uszkodzone" << endl
    << "e. Wyświetl nowe" << endl
    << "f. Wyświetl używane" << endl
    << "z. Wyjdź"
    << endl;
};

void ListaSprzetu::dodajSprzet(Sprzet * przedmiot)
{
    Sprzet * aktualny = new Sprzet;
    int id_przedmiotu = przedmiot->id_produktu;

    aktualny->nazwa = przedmiot->nazwa;
    aktualny->typ = przedmiot->typ;
    aktualny->informacje = przedmiot->informacje;
    aktualny->ilosc = przedmiot->ilosc;
    aktualny->wartosc = przedmiot->wartosc;
    aktualny->sprawny = przedmiot->sprawny;
    aktualny->nowy = przedmiot->nowy;

    aktualny->kolejny = NULL;
    if (sprzet) {
        sprzet->kolejny = aktualny;
        aktualny->poprzedni = sprzet;
        aktualny->id_produktu = (sprzet->id_produktu) + 1;
    } else {
        przedmiot = aktualny;
        przedmiot->poprzedni = NULL;
        aktualny->id_produktu = 1;
        pierwszy = przedmiot;
    }
    if (autonumeracja == false) {
        aktualny->id_produktu = id_przedmiotu;
    }

    sprzet = aktualny;
    n++;
}

void ListaSprzetu::poczatekListy()
{
    sprzet = pierwszy;
}

void ListaSprzetu::wypiszElement()
{
    if (n) {
        sprzet->wypiszDane();
    } else {
        listaJestPusta();
    }
}

void ListaSprzetu::listaJestPusta()
{
    cout << "Lista jest pusta" << endl;
}

void ListaSprzetu::nastepnyElement()
{
    if (sprzet->kolejny) {
        sprzet = sprzet->kolejny;
        wypiszElement();
    } else {
        cout << "Brak kolejnych elementów." << endl;
    }
}

void ListaSprzetu::poprzedniElement()
{
    if (sprzet->poprzedni) {
        sprzet = sprzet->poprzedni;
        wypiszElement();
    } else {
        cout << "Brak porzednich elementów.";
    }
}

void ListaSprzetu::przeniesElement(ListaSprzetu* innaLista)
{
    Sprzet *nowy(sprzet);

    if (!sprzet->poprzedni && !sprzet->kolejny) {
        sprzet = NULL;
        pierwszy = NULL;
    } else if (!(sprzet->poprzedni)) {
        sprzet = sprzet->kolejny;
        sprzet->poprzedni = NULL;
    } else if (!(sprzet->kolejny)) {
        sprzet = sprzet->poprzedni;
        sprzet->kolejny = NULL;
    } else {
        (sprzet->poprzedni)->kolejny = sprzet->kolejny;
        (sprzet->kolejny)->poprzedni = sprzet->poprzedni;
        sprzet = sprzet->poprzedni;
    }
    n--;
    innaLista->dodajSprzet(nowy);

}

void ListaSprzetu::usunElement()
{
    Sprzet *temp = sprzet;

    if (!(sprzet->poprzedni)) {
        sprzet = sprzet->kolejny;
        sprzet->poprzedni = NULL;
    } else if (!(sprzet->kolejny)) {
        sprzet = sprzet->poprzedni;
        sprzet->kolejny = NULL;
    } else {
        (sprzet->poprzedni)->kolejny = sprzet->kolejny;
        (sprzet->kolejny)->poprzedni = sprzet->poprzedni;
        sprzet = sprzet->poprzedni;
    }
    n--;
    delete temp;

}

void ListaSprzetu::wyszukiwanieFrazy(ListaSprzetu* wyniki, string tekst)
{
    Pomocnik * przeszukiwacz = new Pomocnik;
    sprzet = pierwszyElement();

    while (sprzet)
    {
        string nazwa = sprzet->nazwa, rodzaj = sprzet->typ, info = sprzet->informacje;

        if (przeszukiwacz->czyZawieraFraze(nazwa, tekst) || przeszukiwacz->czyZawieraFraze(rodzaj, tekst) ||
        przeszukiwacz->czyZawieraFraze(info, tekst))
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
}

void ListaSprzetu::wyszukiwanieKwoty(ListaSprzetu* wyniki, float kwota_od, float kwota_do)
{
    sprzet = pierwszyElement();

    while (sprzet)
    {
        float wartosc = sprzet->wartosc;
        if (wartosc >= kwota_od && wartosc <= kwota_do)
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
}

void ListaSprzetu::wyszukiwanieLicznosci(ListaSprzetu* wyniki, int liczba_od, int liczba_do)
{
    sprzet = pierwszyElement();

    while (sprzet)
    {
        float ilosc = sprzet->ilosc;
        if (ilosc >= liczba_od && ilosc <= liczba_do)
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
}

void ListaSprzetu::wyswietlSprawne(ListaSprzetu* wyniki)
{
    sprzet = pierwszyElement();

    while (sprzet)
    {
        if (sprzet->sprawny)
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
}
void ListaSprzetu::wyswietlUszkodzone(ListaSprzetu* wyniki)
{
    sprzet = pierwszyElement();

    while (sprzet)
    {
        if (!(sprzet->sprawny))
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
}
void ListaSprzetu::wyswietlNowe(ListaSprzetu* wyniki)
{
    sprzet = pierwszyElement();

    while (sprzet)
    {
        if (sprzet->nowy)
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
}

void ListaSprzetu::wyswietlUzywane(ListaSprzetu* wyniki)
{
    sprzet = pierwszyElement();

    while (sprzet)
    {
        if (!(sprzet->nowy))
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
}

int ListaSprzetu::iloscElementow()
{
    return n;
}

Sprzet * ListaSprzetu::pierwszyElement()
{
    return pierwszy;
}

ListaSprzetu * ListaSprzetu::wczytajZPliku(string nazwa_pliku)
{
    int id, ilosc, rozmiar;
    float wartosc;
    bool sprawny, nowy;
    string nazwa, typ, info;

    ifstream plik;
    plik.open(nazwa_pliku.c_str(), ios::in|ios::binary);

    plik.read((char*)&n, sizeof(n));
    Sprzet *temp = new Sprzet;
    ListaSprzetu *lista = new ListaSprzetu;
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

        temp = new Sprzet(ilosc, nazwa, typ, info, wartosc, sprawny, nowy, id);
        lista->dodajSprzet(temp);
    }

    plik.close();

    return lista;
};

int ListaSprzetu::zapisDoPliku(string nazwa_pliku, Sprzet *sprzet, int rozmiar)
{
    ofstream plik;
    plik.open(nazwa_pliku.c_str(), (ios::out|ios::binary));

    if (!plik)
        return 0;

    plik.write((char*)&rozmiar, sizeof(rozmiar));

    do {
        plik.write((char*)sprzet, sizeof(Sprzet));
    } while ((sprzet = sprzet->kolejny));

    plik.close();

    return 1;
}

// Pomocnik - metody

string Pomocnik::tlumaczBool(bool wartosc)
{
    return wartosc ? "tak" : "nie";
}

bool Pomocnik::czyZawieraFraze(string tekst, string nowy_tekst)
{
    unsigned long t_len = tekst.length();
    unsigned long n_len = nowy_tekst.length();
    bool flaga = false;

    for (int i = 0; i < t_len; i++)
    {
        if (nowy_tekst[0] == tekst[i])
        {
            flaga = true;

            for (int j = 0; j < n_len; j++)
            {
                if (nowy_tekst[j] != tekst[i+j])
                    flaga = false;
            }
        }
    }

    return (flaga == true);
}

string Pomocnik::pobierzFraze()
{
    string fraza;

    cout << "Szukaj: \n> ";
    cin >> fraza;
    return fraza;
}

float * Pomocnik::pobierzKwoty()
{
    float *kwoty;

    cout << "Proszę podać zakres wyszukiwania: \n> (od:) ";
    cin >> kwoty[0];
    cout << "> (do:) ";
    cin >> kwoty[1];

    return kwoty;
}

int * Pomocnik::pobierzLiczbe()
{
    int *licznosc;

    cout << "Proszę podać zakres wyszukiwania: \n> (od:) ";
    cin >> licznosc[0];
    cout << "> (do:) ";
    cin >> licznosc[1];

    return licznosc;
}
