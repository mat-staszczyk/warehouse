#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <windows.h>
#define XX 8
#define YY 3

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
	int sprawny;
	int nowy;

	Sprzet *poprzedni;
	Sprzet *kolejny;

	friend class ListaSprzetu;

public:
	Sprzet();
	Sprzet(int, string, string, string, double, int, int, int = NULL);
	Sprzet(Sprzet &);
	~Sprzet();

	Sprzet *podajDane();
	void wypiszDane();
};

class ListaSprzetu
{

private:

	Sprzet * sprzet;
	Sprzet * pierwszy;
	int n = 0;
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
	void edytujSprzet(Sprzet*);
	void poczatekListy();
	void wypiszElement();
	void listaJestPusta();
	void nastepnyElement();
	void poprzedniElement();
	void przeniesElement(ListaSprzetu*);
	void usunElement();
	void wyszukiwanie(ListaSprzetu*, string); // wyszukaj frazê
	void wyszukiwanie(ListaSprzetu*, int); // wyszukaj id
	void wyszukiwanie(ListaSprzetu*, double, double); // wyszukaj kwotê
	void wyszukiwanie(ListaSprzetu*, int, int); // wyszukaj licznoœæ
	void wyszukiwanie(ListaSprzetu*, ATR, bool); // wyszukaj sprzêt o podanym stanie
	void sortowanie(ListaSprzetu*, ATR, bool = true);

	Sprzet * pierwszyElement();
	ListaSprzetu * wczytajZPliku(string);

	int iloscElementow();
	int zapisDoPliku(string, Sprzet*, int);

private:
	bool sprawdz_warunek(Sprzet*, Sprzet*, ATR, bool);
	void zamien(Sprzet*);
};

class Menu
{
public:
	ListaSprzetu *lista, *kosz, *wyniki;

	Menu();

	void glowne();
	void zarzadzanieSprzetem();
	void sprzet();
	void wyszukiwanie();
	void sortowanie();
	void zarzadzanieKoszem();
	void wyjscie();

	void opis_glowne(int=XX, int=YY);
	void opis_zarzadzanie(int=XX, int=YY);
	void opis_sprzet(int=XX, int=YY);
	void opis_wyszukiwanie(int=XX, int=YY);
	void opis_sortowanie(int=XX, int=YY);
	void opis_kosz(int=XX, int=YY);
	void opis_wyjscie(int=XX, int=YY);
};

class Pomocnik
{

public:

	string tlumaczKod(int);
	string pobierzFraze();
	double * pobierzKwoty();
	int * pobierzLiczbe();
	bool czyZawieraFraze(string, string);
	void gotoxy(int, int);
};

/*
int main() {

	// Dodanie obs³ugi polskich znaków pod Windows (VS2015)
	setlocale(LC_ALL, "polish");

	ListaSprzetu::ATR nazwa = ListaSprzetu::ATR::nazwa;
	//ListaSprzetu::ATR typ = ListaSprzetu::ATR::typ;
	//ListaSprzetu::ATR info = ListaSprzetu::ATR::info;
	//ListaSprzetu::ATR id = ListaSprzetu::ATR::id;
	//ListaSprzetu::ATR ilosc = ListaSprzetu::ATR::ilosc;
	//ListaSprzetu::ATR wartosc = ListaSprzetu::ATR::wartosc;
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
	Menu * menu = new Menu;

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
			test = test->podajDane();

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
			cout << "Podaj nazwê pliku, z którego maj¹ zostaæ wczytane dane:" << endl;
			fflush(stdin);
			cin >> nazwa_pliku;
			lista = lista->wczytajZPliku(nazwa_pliku);
			break;
		case '6':
			test = lista->pierwszyElement();
			n = lista->iloscElementow();

			cout << "Podaj nazwê pliku, w którym maj¹ zostaæ zapisane dane:" << endl;
			fflush(stdin);
			cin >> nazwa_pliku;
			if (!lista->zapisDoPliku(nazwa_pliku, test, n))
				cout << "Brak dostêpu do pliku." << endl;
			else
				cout << "Dane zosta³y pomyœle zapisane w pliku \"" << nazwa_pliku << "\"." << endl;
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
		case 'h':
			test = new Sprzet;
			test = test->podajDane();
			lista->edytujSprzet(test);
			lista->wypiszElement();
			break;
		case 'i':
			system("cls");
			menu->opis_glowne();
			cin.get();
			break;
		case 'j':
			system("cls");
			menu->opis_zarzadzanie();
			cin.get();
			break;
		case 'k':
			system("cls");
			menu->opis_wyszukiwanie();
			cin.get();
			break;
		case 'l':
			system("cls");
			menu->opis_sortowanie();
			cin.get();
			break;
		case 'm':
			system("cls");
			menu->opis_sprzet();
			cin.get();
			break;
		case 'n':
			system("cls");
			menu->opis_kosz();
			cin.get();
			break;
		case 'o':
			system("cls");
			menu->opis_wyjscie();
			cin.get();
			break;
		default:
			break;

		}

	} while (klawisz != 'z');

	return 0;
}
*/

int main()
{
	// Dodanie obs³ugi polskich znaków pod Windows (VS2015)
	setlocale(LC_ALL, "polish");

	ListaSprzetu::ATR nazwa = ListaSprzetu::ATR::nazwa;
	//ListaSprzetu::ATR typ = ListaSprzetu::ATR::typ;
	//ListaSprzetu::ATR info = ListaSprzetu::ATR::info;
	//ListaSprzetu::ATR id = ListaSprzetu::ATR::id;
	//ListaSprzetu::ATR ilosc = ListaSprzetu::ATR::ilosc;
	//ListaSprzetu::ATR wartosc = ListaSprzetu::ATR::wartosc;
	ListaSprzetu::ATR nowy = ListaSprzetu::ATR::nowy;
	ListaSprzetu::ATR sprawny = ListaSprzetu::ATR::sprawny;

	int * liczba;
	string fraza;
	double * kwoty;
	char klawisz;

	Pomocnik * pom = new Pomocnik;
	Menu * menu = new Menu;

	menu->glowne();

	return 0;
}

// Sprzet - metody

Sprzet::Sprzet()
{
}

Sprzet::Sprzet(int ilosc, string nazwa, string typ, string informacje, double wartosc, int sprawny, int nowy, int id_produktu)
{
	this->nazwa = nazwa;
	this->typ = typ;
	this->informacje = informacje;
	this->wartosc = (wartosc == -1) ? 0 : wartosc;
	this->ilosc = (ilosc == -1) ? 0 : ilosc;
	this->sprawny = sprawny;
	this->nowy = nowy;
	this->id_produktu = NULL;
}

Sprzet::Sprzet(Sprzet & inny)
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
	cout << endl << "Przedmiot " << this->nazwa << " zosta³ usuniêty." << endl;
}

Sprzet* Sprzet::podajDane()
{
	bool flaga = true;
	string nazwa, typ, info, s_temp;
	double wartosc;
	int ilosc, nowy, sprawny;
	Sprzet * biezacy;

	cout << endl << "Nazwa: " << endl << "> ";
	fflush(stdin);
	getline(cin, nazwa);
	cout << "Rodzaj: " << endl << "> ";
	fflush(stdin);
	getline(cin, typ);

	while (flaga)
	{
		cout << "Wartoœæ: " << endl << "> ";
		fflush(stdin);
		getline(cin, s_temp);
		if (s_temp == "\n") {
			wartosc = -1;
			flaga = false;
		} else {
			wartosc = atof(s_temp.c_str());
			flaga = (wartosc >= 0) ? false : true;
		}
	}
	s_temp = "";
	flaga = true;

	while (flaga)
	{
		cout << "Iloœæ: " << endl << "> ";
		fflush(stdin);
		getline(cin, s_temp);
		if (s_temp == "\n") {
			ilosc = -1;
			flaga = false;
		} else {
			ilosc = atoi(s_temp.c_str());
			flaga = (ilosc >= 0) ? false : true;
		}
	}
	if (s_temp == "\n")
	{
		s_temp = "";
	}
	cout << "Stan: sprawny (t/n)?" << endl << "> ";
	fflush(stdin);
	getline(cin, s_temp);
	if (s_temp == "t" || s_temp == "T")
		sprawny = 1;
	else if (s_temp == "n" || s_temp == "N")
		sprawny = 0;
	else
		sprawny = 2;

	cout << "Stan: nowy (t/n)?" << endl << "> ";
	fflush(stdin);
	getline(cin, s_temp);
	if (s_temp == "t" || s_temp == "T")
		nowy = 1;
	else if (s_temp == "n" || s_temp == "N")
		nowy = 0;
	else
		nowy = 2;

	cout << "Dodatkowe informacje: " << endl << "> ";
	getline(cin, info);

	biezacy = new Sprzet(ilosc, nazwa, typ, info, wartosc, sprawny, nowy);

	return biezacy;
}

void Sprzet::wypiszDane()
{
	Pomocnik * pomocnik = new Pomocnik;

	cout << "Dane przedmiotu:" << endl << endl;
	cout << "ID:         " << this->id_produktu << endl;
	cout << "Nazwa:      " << this->nazwa << endl;
	cout << "Rodzaj:     " << this->typ << endl;
	cout << "Iloœæ:      " << this->ilosc << endl;
	cout << "Wartoœæ:    " << this->wartosc << endl;
	cout << "Sprawny:    " << pomocnik->tlumaczKod(this->sprawny) << endl;
	cout << "Nowy:       " << pomocnik->tlumaczKod(this->nowy) << endl;
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
	sprzet = NULL;
	pierwszy = NULL;
	n = 0;
}

void ListaSprzetu::pokazMenu() {
	cout << endl << "Menu zarz¹dzania sprzêtem:" << endl
		<< endl
		<< "1. Dodaj sprzêt" << endl
		<< "2. Wyswietl sprzêt" << endl
		<< "3. Nastepny (test)" << endl
		<< "4. Poprzedni (test)" << endl
		<< "5. Wczytaj z pliku" << endl
		<< "6. Zapis do pliku" << endl
		<< "7. Usuñ element" << endl
		<< "8. Przenieœ do kosza" << endl
		<< "9. Wyszukaj tekst" << endl
		<< "a. Wyszukaj wartoœæ" << endl
		<< "b. Wyszukaj licznoœæ" << endl
		<< "c. Wyœwietl sprawne" << endl
		<< "d. Wyœwietl uszkodzone" << endl
		<< "e. Wyœwietl nowe" << endl
		<< "f. Wyœwietl u¿ywane" << endl
		<< "g. Sortowanie wg nazwy" << endl
		<< "h. Edycja elementu" << endl
		<< "z. WyjdŸ"
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
	}
	else {
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

void ListaSprzetu::edytujSprzet(Sprzet* temp)
{
	sprzet->nazwa = (temp->nazwa == "") ? sprzet->nazwa : temp->nazwa;
	sprzet->typ = (temp->typ == "") ? sprzet->typ : temp->typ;
	sprzet->informacje = (temp->informacje == "") ? sprzet->informacje : temp->informacje;
	sprzet->sprawny = (temp->sprawny == 2) ? sprzet->sprawny : temp->sprawny;
	sprzet->nowy = (temp->nowy == 2) ? sprzet->nowy : temp->nowy;
	sprzet->ilosc = (temp->ilosc == -1) ? sprzet->ilosc : temp->ilosc;
	sprzet->wartosc = (temp->wartosc == -1) ? sprzet->wartosc : temp->wartosc;
}

void ListaSprzetu::poczatekListy()
{
	sprzet = pierwszyElement();
}

void ListaSprzetu::wypiszElement()
{
	if (n) {
		sprzet->wypiszDane();
	}
	else {
		listaJestPusta();
	}
}

void ListaSprzetu::poprzedniElement()
{
	if (sprzet->poprzedni) {
		sprzet = sprzet->poprzedni;
	}
	else {
		cout << "Brak porzednich elementów.";
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
	} else {
		cout << "Brak kolejnych elementów." << endl;
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
	}
	else if (!(sprzet->poprzedni)) {
		sprzet = sprzet->kolejny;
		sprzet->poprzedni = NULL;
	}
	else if (!(sprzet->kolejny)) {
		sprzet = sprzet->poprzedni;
		sprzet->kolejny = NULL;
	}
	else {
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
	Sprzet *temp = sprzet;
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
	Sprzet *temp = sprzet;
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
	Sprzet *temp = sprzet;
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
	int warunek;
	Sprzet *temp = sprzet;
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

		if (warunek == 1)
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
	int sprawny, nowy;
	string nazwa, typ, info;

	ifstream plik;
	plik.open(nazwa_pliku.c_str(), ios::in | ios::binary);

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
	plik.open(nazwa_pliku.c_str(), (ios::out | ios::binary));

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

// Menu - metody

Menu::Menu()
{
	lista = new ListaSprzetu;
	kosz = new ListaSprzetu(false);
	wyniki = new ListaSprzetu(false);
}

void Menu::glowne()
{
	string nazwa_pliku;
	char klawisz;

	Sprzet * test;

	system("cls");
	do
	{
		opis_glowne();

		cin >> klawisz;
		cin.ignore();

		switch (klawisz)
		{
		case '1':
			zarzadzanieSprzetem();
			break;
		case '2':
			cout << "Podaj nazwê pliku, z którego maj¹ zostaæ wczytane dane:" << endl;
			fflush(stdin);
			cin >> nazwa_pliku;
			lista = lista->wczytajZPliku(nazwa_pliku);
			break;
		case '3':
			int n;
			test = lista->pierwszyElement();
			n = lista->iloscElementow();

			cout << "Podaj nazwê pliku, w którym maj¹ zostaæ zapisane dane:" << endl;
			fflush(stdin);
			cin >> nazwa_pliku;
			if (!lista->zapisDoPliku(nazwa_pliku, test, n))
				cout << "Brak dostêpu do pliku." << endl;
			else
				cout << "Dane zosta³y pomyœle zapisane w pliku \"" << nazwa_pliku << "\"." << endl;
			break;
		default:
			break;

		}

	} while (klawisz != '4');
}

void Menu::zarzadzanieSprzetem()
{
	char klawisz;
	Sprzet *test;

	system("cls");
	do
	{
		
		opis_zarzadzanie();

		cin >> klawisz;
		cin.ignore();

		switch (klawisz)
		{
		case '1':
			sprzet();
			break;
		case '2':
			test = new Sprzet;
			test = test->podajDane();
			lista->dodajSprzet(test);
			cout << "Dodano element: " << endl;
			lista->wypiszElement();
			break;
		case '3':
			wyszukiwanie();
			break;
		case '4':
			zarzadzanieKoszem();
			break;
		default:
			break;

		}

	} while (klawisz != '5');
}

void Menu::sprzet()
{
	char klawisz;
	Sprzet *test;

	system("cls");
	do
	{
		lista->wypiszElement();
		opis_sprzet();
		
		cin >> klawisz;
		cin.ignore();

		switch (klawisz)
		{
		case '1':
			lista->poprzedniElement();
			break;
		case '2':
			lista->nastepnyElement();
			break;
		case '3':
			lista->przeniesElement(kosz);
			kosz->wypiszElement();
			break;
		case '4':
			zarzadzanieKoszem();
			break;
		default:
			break;

		}

	} while (klawisz != '5');
}

void Menu::wyszukiwanie()
{
	opis_wyszukiwanie();
}

void Menu::sortowanie()
{
	opis_sortowanie();
}

void Menu::zarzadzanieKoszem()
{
	kosz->wypiszElement();
	opis_kosz();
}

void Menu::wyjscie()
{

}

void Menu::opis_glowne(int x, int y)
{
	Pomocnik *pom = new Pomocnik;

	pom->gotoxy(x, y++);
	cout << "###################";
	pom->gotoxy(x, y++);
	cout << "### MENU G£ÓWNE ###";
	pom->gotoxy(x, y++); y++;
	cout << "###################";
	pom->gotoxy(x, y++);
	cout << "Wybierz jedn¹ z opcji:";
	pom->gotoxy(x, y++);
	cout << "1. Zarz¹dzanie magazynem";
	pom->gotoxy(x, y++);
	cout << "2. Wczytaj dane z pliku";
	pom->gotoxy(x, y++);
	cout << "3. Zapisz dane do pliku";
	pom->gotoxy(x, y++); y++;
	cout << "4. Zakoñcz";
	pom->gotoxy(x, ++y);
	cout << "> ";
}

void Menu::opis_zarzadzanie(int x, int y)
{
	Pomocnik *pom = new Pomocnik;

	pom->gotoxy(x, y++);
	cout << "############################";
	pom->gotoxy(x, y++);
	cout << "### ZARZ¥DZANIE SPRZÊTEM ###";
	pom->gotoxy(x, y++); y++;
	cout << "############################";
	pom->gotoxy(x, y++); 
	cout << "Wybierz jedn¹ z opcji:";
	pom->gotoxy(x, y++);
	cout << "1. Wyœwietl dane sprzêtu";
	pom->gotoxy(x, y++);
	cout << "2. Dodaj sprzêtu.";
	pom->gotoxy(x, y++);
	cout << "3. Wyszukaj";
	pom->gotoxy(x, y++);
	cout << "4. Wyœwietl zawartoœæ kosza";
	pom->gotoxy(x, y++);
	cout << "5. Powrót";
	pom->gotoxy(x, ++y); 
	cout << "> ";
}

void Menu::opis_sprzet(int x, int y)
{
	int t_x = XX;
	y += 23;
	Pomocnik *pom = new Pomocnik;

	pom->gotoxy(x, y);
	cout << "1. Poprzedni";
	pom->gotoxy((x += 15), y);
	cout << "2. Nastêpny";
	pom->gotoxy((x += 15), y);
	cout << "3. Edycja";
	pom->gotoxy((x += 13), y);
	cout << "4. Sortuj";
	pom->gotoxy((x += 13), y);
	cout << "5. Do kosza";
	pom->gotoxy((x += 15), y);
	cout << "6. Powrót";
	pom->gotoxy(t_x, (y+1));
	cout << "> ";
}

void Menu::opis_wyszukiwanie(int x, int y)
{
	Pomocnik *pom = new Pomocnik;

	pom->gotoxy(x, y++);
	cout << "####################";
	pom->gotoxy(x, y++);
	cout << "### WYSZUKIWANIE ###";
	pom->gotoxy(x, y++); y++;
	cout << "####################";
	pom->gotoxy(x, y++);
	cout << "Kryterium wyszukiwania:";
	pom->gotoxy(x, y++);
	cout << "1. Tekst";
	pom->gotoxy(x, y++);
	cout << "2. Licznoœæ";
	pom->gotoxy(x, y++);
	cout << "3. Wartoœæ";
	pom->gotoxy(x, y++);
	cout << "4. Nowe przedmioty";
	pom->gotoxy(x, y++);
	cout << "5. Sprawne przedmioty";
	pom->gotoxy(x, y++);
	cout << "6. U¿ywane przedmioty";
	pom->gotoxy(x, y++);
	cout << "7. Uszkodzone przedmioty";
	pom->gotoxy(x, y++);
	cout << "8. Powrót";
	pom->gotoxy(x, ++y);
	cout << "> ";
}

void Menu::opis_sortowanie(int x, int y)
{
	x += 50;
	Pomocnik *pom = new Pomocnik;

	pom->gotoxy(x, y++);
	cout << "####################";
	pom->gotoxy(x, y++);
	cout << "#### SORTOWANIE ####";
	pom->gotoxy(x, y++); y++;
	cout << "####################";
	pom->gotoxy(x, y++);
	cout << "Kryterium sortowania:";
	pom->gotoxy(x, y++);
	cout << "1. ID";
	pom->gotoxy(x, y++);
	cout << "2. Nazwa";
	pom->gotoxy(x, y++);
	cout << "3. Typ";
	pom->gotoxy(x, y++);
	cout << "4. Wartoœæ";
	pom->gotoxy(x, y++);
	cout << "5. Iloœæ";
	pom->gotoxy(x, y++);
	cout << "6. Powrót";
	pom->gotoxy(x, ++y);
	cout << "> ";
}

void Menu::opis_kosz(int x, int y)
{
	int t_x = XX;
	y += 23;
	Pomocnik *pom = new Pomocnik;

	pom->gotoxy(x, y);
	cout << "1. Poprzedni";
	pom->gotoxy((x += 14), y);
	cout << "2. Nastêpny";
	pom->gotoxy((x += 13), y);
	cout << "3. Usuñ";
	pom->gotoxy((x += 9), y);
	cout << "4. Usuñ wszystkie";
	pom->gotoxy((x += 19), y);
	cout << "5. Przywróæ";
	pom->gotoxy((x += 13), y);
	cout << "6. Przywróc wszystkie";
	pom->gotoxy((x += 23), y);
	cout << "7. Powrót";
	pom->gotoxy(t_x, (y + 1));
	cout << "> ";
}

void Menu::opis_wyjscie(int x, int y)
{
	Pomocnik *pom = new Pomocnik;

	x += 15;
	y += 5;

	pom->gotoxy(x, y++); y++;
	cout << "Czy chcesz zapisaæ dane przed wyjœciem?";
	pom->gotoxy(x, y++);
	cout << "1. Tak ";
	pom->gotoxy(x, y++);
	cout << "2. Nie";
	pom->gotoxy(x, y++);
	cout << "3. Anuluj";
	pom->gotoxy(x, ++y);
	cout << "> ";
}

// Pomocnik - metody

string Pomocnik::tlumaczKod(int wartosc)
{
	return (wartosc == 1) ? "tak" : "nie";
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
				if (nowy_tekst[j] != tekst[i + j])
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

	cout << "Proszê podaæ zakres wyszukiwania: \n> (od:) ";
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

	cout << "Proszê podaæ zakres wyszukiwania: \n> (od:) ";
	cin >> licznosc[0];
	cout << "> (do:) ";
	cin >> licznosc[1];

	wsk_licz = &(licznosc[0]);
	return wsk_licz;
}

void Pomocnik::gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}