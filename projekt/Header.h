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

	bool pokaz;

	Sprzet *poprzedni;
	Sprzet *kolejny;

	friend class ListaSprzetu;

public:
	Sprzet();
	Sprzet(int, string, string, string, double, int, int, int = NULL);
	Sprzet(Sprzet &);
	~Sprzet();

	Sprzet *podajDane(int = XX, int = YY);
	void etykietyDanych(int x = XX, int y = YY);
	void wypiszDane(int = XX, int = YY);
};

class ListaSprzetu
{

private:

	Sprzet * sprzet;
	Sprzet * pierwszy;
	Sprzet * ostatni;
	int n = 0;
	int widoczne = 0;
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

	void dodajSprzet(Sprzet*);
	void edytujSprzet();
	void poczatekListy();
	void koniecListy();
	void wypiszElement();
	void listaJestPusta(int = XX, int = YY);
	void nastepnyElement();
	void poprzedniElement();
	void przeniesElement(ListaSprzetu*);
	void przeniesWszystko(ListaSprzetu*);
	void usunElement();
	void usunWszystkie();
	void pokazWszystkie();
	int wyszukiwanie(string); // wyszukaj frazê
	int wyszukiwanie(int); // wyszukaj id
	int wyszukiwanie(double, double); // wyszukaj kwotê
	int wyszukiwanie(int, int); // wyszukaj licznoœæ
	int wyszukiwanie(ATR, bool); // wyszukaj sprzêt o podanym stanie
	void sortowanie(ATR, bool = true);

	Sprzet * pierwszyElement();
	Sprzet * ostatniElement();
	Sprzet * pierwszyWidoczny();
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
	bool wyjscie();

	void opis_glowne(int = XX, int = YY);
	void opis_zarzadzanie(int = XX, int = YY);
	void opis_sprzet(int = XX, int = YY);
	void opis_wyszukiwanie(int = XX, int = YY);
	void opis_sortowanie(int = XX, int = YY);
	void opis_kosz(int = XX, int = YY);
	void opis_wyjscie(int = XX, int = YY);
	void opis_kierunekSortowania(int = XX, int = YY);
	bool sortujRosnaco();
};

class Pomocnik
{

public:

	string tlumaczKod(int);
	string podajNazwe();
	string pobierzFraze(int = XX, int = YY);
	double * pobierzKwoty(int = XX, int = YY);
	int * pobierzLiczbe(int = XX, int = YY);
	int pobierzId(int = XX, int = YY);
	bool czyZawieraFraze(string, string);
	void gotoxy(int, int);
};