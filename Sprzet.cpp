#include "./Header.h"

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
	this->pokaz = true;
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
	this->pokaz = true;
}

Sprzet::~Sprzet()
{
	cout << endl << "Przedmiot " << this->nazwa << " zosta³ usuniêty." << endl;
}

Sprzet* Sprzet::podajDane(int x, int y)
{
	bool flaga = true;
	string nazwa, typ, info, s_temp;
	double wartosc;
	int ilosc, nowy, sprawny, t_x = (x + 27), t_y = (y + 5);
	Sprzet * biezacy;
	Helper * pom = new Helper;

	etykietyDanych();

	pom->gotoxy(t_x, t_y);
	fflush(stdin);
	getline(cin, nazwa);
	pom->gotoxy(t_x, (t_y += 2));
	fflush(stdin);
	getline(cin, typ);

	while (flaga)
	{
		pom->gotoxy(t_x, (t_y += 2));
		fflush(stdin);
		getline(cin, s_temp);
		if (s_temp == "\n") {
			ilosc = -1;
			flaga = false;
		}
		else {
			ilosc = atoi(s_temp.c_str());
			flaga = (ilosc >= 0) ? false : true;
		}
	}

	s_temp = "";
	flaga = true;

	while (flaga)
	{
		pom->gotoxy(t_x, (t_y += 2));
		fflush(stdin);
		getline(cin, s_temp);
		if (s_temp == "\n") {
			wartosc = -1;
			flaga = false;
		}
		else {
			wartosc = atof(s_temp.c_str());
			flaga = (wartosc >= 0) ? false : true;
		}
	}

	if (s_temp == "\n")
	{
		s_temp = "";
	}
	pom->gotoxy(t_x, (t_y += 2));
	fflush(stdin);
	getline(cin, s_temp);
	if (s_temp == "t" || s_temp == "T")
		sprawny = 1;
	else if (s_temp == "n" || s_temp == "N")
		sprawny = 0;
	else
		sprawny = 2;

	pom->gotoxy(t_x, (t_y += 2));
	fflush(stdin);
	getline(cin, s_temp);
	if (s_temp == "t" || s_temp == "T")
		nowy = 1;
	else if (s_temp == "n" || s_temp == "N")
		nowy = 0;
	else
		nowy = 2;

	pom->gotoxy(t_x, (t_y += 2));
	getline(cin, info);

	biezacy = new Sprzet(ilosc, nazwa, typ, info, wartosc, sprawny, nowy);

	return biezacy;
}

void Sprzet::etykietyDanych(int x, int y)
{
	Helper *pom = new Helper;

	pom->gotoxy(x, y++);
	cout << "Podaj dane przedmiotu:";
	pom->gotoxy(x, (y += 4));
	cout << "Nazwa:";
	pom->gotoxy(x, (y += 2));
	cout << "Rodzaj: ";
	pom->gotoxy(x, (y += 2));
	cout << "Iloœæ: ";
	pom->gotoxy(x, (y += 2));
	cout << "Wartoœæ: ";
	pom->gotoxy(x, (y += 2));
	cout << "Sprawny? (t/n):";
	pom->gotoxy(x, (y += 2));
	cout << "Nowy? (t/n):";
	pom->gotoxy(x, (y += 2));
	cout << "Informacje: ";
}

void Sprzet::wypiszDane(int x, int y)
{
	Helper * helper = new Helper;

	helper->gotoxy(x, y++);
	cout << "Dane przedmiotu:" << endl << endl;
	helper->gotoxy(x, (y += 2));
	cout << "ID:             " << this->id_produktu << endl;
	helper->gotoxy(x, (y += 2));
	cout << "Nazwa:          " << this->nazwa << endl;
	helper->gotoxy(x, (y += 2));
	cout << "Rodzaj:         " << this->typ << endl;
	helper->gotoxy(x, (y += 2));
	cout << "Iloœæ:          " << this->ilosc << endl;
	helper->gotoxy(x, (y += 2));
	cout << "Wartoœæ:        " << this->wartosc << endl;
	helper->gotoxy(x, (y += 2));
	cout << "Sprawny:        " << helper->tlumaczKod(this->sprawny) << endl;
	helper->gotoxy(x, (y += 2));
	cout << "Nowy:           " << helper->tlumaczKod(this->nowy) << endl;
	helper->gotoxy(x, (y += 2));
	cout << "Informacje:     " << this->informacje << endl << endl;

	delete helper;
}