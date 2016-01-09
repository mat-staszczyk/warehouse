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
    double wartosc;
    bool sprawny;
    bool nowy;

    Sprzet *poprzedni;
    Sprzet *kolejny;

    friend class ListaSprzetu;

public:

    Sprzet();
    Sprzet( int, string, string, string, double, bool, bool, int=NULL);
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

	enum ATR
	{
		nazwa,
		typ,
		info,
		id,
		ilosc,
		wartosc,
		sprawny,
		nowy
	};

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
    void wyszukiwanie(ListaSprzetu*, string); // wyszukaj frazę
	void wyszukiwanie(ListaSprzetu*, int); // wyszukaj id
    void wyszukiwanie(ListaSprzetu*, double, double); // wyszukaj kwotę
    void wyszukiwanie(ListaSprzetu*, int, int); // wyszukaj liczność
	void wyszukiwanie(ListaSprzetu*, ATR, bool); // wyszukaj sprzęt o podanym stanie
    void zamien(Sprzet*);
    void sortowanie(ListaSprzetu*, ATR, bool=true);

    Sprzet * pierwszyElement();
    ListaSprzetu * wczytajZPliku(string);

    int iloscElementow();
    int zapisDoPliku(string, Sprzet*, int);
    
private:
    bool sprawdz_warunek(Sprzet*, Sprzet*, ATR, bool);

};

class Pomocnik
{

public:

    string tlumaczBool(bool);
    string pobierzFraze();
    double * pobierzKwoty();
    int * pobierzLiczbe();
    bool czyZawieraFraze(string, string);
    void * zamien(Sprzet*, Sprzet*);
};


int main() {

    ListaSprzetu::ATR nazwa = ListaSprzetu::ATR::nazwa;
    ListaSprzetu::ATR typ = ListaSprzetu::ATR::typ;
    ListaSprzetu::ATR info = ListaSprzetu::ATR::info;
    ListaSprzetu::ATR id = ListaSprzetu::ATR::id;
    ListaSprzetu::ATR ilosc = ListaSprzetu::ATR::ilosc;
    ListaSprzetu::ATR wartosc = ListaSprzetu::ATR::wartosc;
	ListaSprzetu::ATR nowy = ListaSprzetu::ATR::nowy;
	ListaSprzetu::ATR sprawny = ListaSprzetu::ATR::sprawny;
    
    int n;
    int * liczba;
    string nazwa_pliku, fraza;
    double * kwoty;
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
                lista->wyszukiwanie(wyniki, fraza);
                wyniki->wypiszElement();
                break;
            case 'a':
                kwoty = pom->pobierzKwoty();
                lista->wyszukiwanie(wyniki, kwoty[0], kwoty[1]);
                wyniki->wypiszElement();
                break;
            case 'b':
                liczba = pom->pobierzLiczbe();
                lista->wyszukiwanie(wyniki, liczba[0], liczba[1]);
                wyniki->wypiszElement();
                break;
            case 'c':
                lista->wyszukiwanie(wyniki, sprawny, true);
                wyniki->wypiszElement();
                break;
            case 'd':
				lista->wyszukiwanie(wyniki, sprawny, false);
                wyniki->wypiszElement();
                break;
            case 'e':
				lista->wyszukiwanie(wyniki, nowy, true);
                wyniki->wypiszElement();
                break;
            case 'f':
				lista->wyszukiwanie(wyniki, nowy, false);
                wyniki->wypiszElement();
                break;
			case 'g':
				lista->sortowanie(wyniki, nazwa);
                wyniki->poczatekListy();
				wyniki->wypiszElement();
				wyniki->nastepnyElement();
				wyniki->nastepnyElement();
				break;
            default:
                break;

        }

    } while (klawisz != 'z' );

    return 0;
}


// Sprzet - metody

Sprzet::Sprzet()
{
}

Sprzet::Sprzet( int ilosc, string nazwa, string typ, string informacje, double wartosc, bool sprawny, bool nowy, int id_produktu )
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
    double wartosc;
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
	<< "g. Sortowanie wg nazwy" << endl
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
	sprzet = pierwszyElement();
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
    innaLista->dodajSprzet(nowy);
    usunElement();
}

void ListaSprzetu::usunElement()
{
    Sprzet *temp = sprzet;

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
    delete temp;

}

void ListaSprzetu::wyszukiwanie(ListaSprzetu* wyniki, string tekst)
{
	Sprzet *temp = sprzet;
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
	sprzet = temp;
}

void ListaSprzetu::wyszukiwanie(ListaSprzetu* wyniki, int id)
{
	Sprzet *temp = sprzet;;
	sprzet = pierwszyElement();

	while (sprzet)
	{
		if (sprzet->id_produktu == id)
			wyniki->dodajSprzet(sprzet);

		sprzet = (sprzet->kolejny);
	}
	sprzet = temp;
}

void ListaSprzetu::wyszukiwanie(ListaSprzetu* wyniki, double kwota_od, double kwota_do)
{
	Sprzet *temp = sprzet;;
    sprzet = pierwszyElement();

    while (sprzet)
    {
        double wartosc = sprzet->wartosc;
        if (wartosc >= kwota_od && wartosc <= kwota_do)
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
	sprzet = temp;
}

void ListaSprzetu::wyszukiwanie(ListaSprzetu* wyniki, int liczba_od, int liczba_do)
{
	Sprzet *temp = sprzet;;
    sprzet = pierwszyElement();

    while (sprzet)
    {
        int ilosc = sprzet->ilosc;
        if (ilosc >= liczba_od && ilosc <= liczba_do)
            wyniki->dodajSprzet(sprzet);

        sprzet = (sprzet->kolejny);
    }
	sprzet = temp;
}

void ListaSprzetu::wyszukiwanie(ListaSprzetu* wyniki, ATR atrybut, bool wartosc)
{
	bool warunek;
	Sprzet *temp = sprzet;;
	sprzet = pierwszyElement();

	while (sprzet)
	{
		switch (atrybut)
		{
		case nowy:
			warunek = wartosc ? (sprzet->nowy) : (!(sprzet->nowy));
			break;
		case sprawny:
			warunek = wartosc ? (sprzet->sprawny) : (!(sprzet->sprawny));
			break;
		default:
            warunek = false;
			break;
		}

		if (warunek)
			wyniki->dodajSprzet(sprzet);

		sprzet = (sprzet->kolejny);
	}

	sprzet = temp;
}

void ListaSprzetu::zamien(Sprzet * temp)
{

    if (temp->poprzedni)
        (temp->poprzedni)->kolejny = sprzet;
    
    if (sprzet->kolejny)
        (sprzet->kolejny)->poprzedni = temp;
    
    sprzet->poprzedni = temp->poprzedni;
    temp->poprzedni = sprzet;
    temp->kolejny = sprzet->kolejny;
    sprzet->kolejny = temp;
    
}


void ListaSprzetu::sortowanie(ListaSprzetu *wyniki, ATR atrybut, bool rosnaco)
{
    bool warunek;
    sprzet = pierwszyElement();
    Sprzet * temp = sprzet;
    sprzet = temp->kolejny;

 
    while (sprzet)
    {
        warunek = sprawdz_warunek(temp, sprzet, atrybut, rosnaco);
        
        if (warunek)
        {
            while (temp)
            {
                warunek = sprawdz_warunek(temp, sprzet, atrybut, rosnaco);
                
                if (warunek)
                    zamien(temp);
                
                sprzet = temp;
                temp = temp->poprzedni;
            }
        }
        
        temp = sprzet;
        sprzet = sprzet->kolejny;
    }
    
    sprzet = temp;
    sprzet = pierwszyElement();
    
    while (sprzet)
    {
        wyniki->dodajSprzet(sprzet);
        sprzet = sprzet->kolejny;
    }
    
    sprzet = temp;
    sprzet = pierwszyElement();
}


int ListaSprzetu::iloscElementow()
{
    return n;
}

Sprzet * ListaSprzetu::pierwszyElement()
{
	while (sprzet->poprzedni)
	{
		sprzet = sprzet->poprzedni;
	}

	return sprzet;
}

ListaSprzetu * ListaSprzetu::wczytajZPliku(string nazwa_pliku)
{
    int id, ilosc, rozmiar;
    double wartosc;
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

bool ListaSprzetu::sprawdz_warunek(Sprzet *temp, Sprzet *sprzet, ATR atrybut, bool rosnaco)
{
    bool warunek;
    
    switch (atrybut)
    {
        case nazwa:
            warunek = (temp->nazwa > sprzet->nazwa);
            break;
        case typ:
            warunek = (temp->typ > sprzet->typ);
            break;
        case info:
            warunek = (temp->informacje > sprzet->informacje);
            break;
        case id:
            warunek = (temp->id_produktu > sprzet->id_produktu);
            break;
        case ilosc:
            warunek = (temp->ilosc > sprzet->ilosc);
            break;
        case wartosc:
            warunek = (temp->wartosc > sprzet->wartosc);
            break;
        default:
            warunek = false;
            break;
    }
    
    if (!rosnaco)
        warunek = !warunek;
    
    return warunek;
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

    for (size_t i = 0; i < t_len && (t_len - i) >= n_len; i++)
    {
        if (nowy_tekst[0] == tekst[i])
        {
            flaga = true;

            for (size_t j = 0; j < n_len; j++)
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

double * Pomocnik::pobierzKwoty()
{
    double kwoty[2];
	double *wsk_kwoty;

    cout << "Proszę podać zakres wyszukiwania: \n> (od:) ";
    cin >> kwoty[0];
    cout << "> (do:) ";
    cin >> kwoty[1];

	wsk_kwoty = &(kwoty[0]);
    return wsk_kwoty;
}

int * Pomocnik::pobierzLiczbe()
{
    int licznosc[2];
	int *wsk_licz;

    cout << "Proszę podać zakres wyszukiwania: \n> (od:) ";
    cin >> licznosc[0];
    cout << "> (do:) ";
    cin >> licznosc[1];

	wsk_licz = &(licznosc[0]);
    return wsk_licz;
}