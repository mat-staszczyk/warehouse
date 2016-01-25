#include "./Header.h"

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
	aktualny->pokaz = true;

	aktualny->kolejny = NULL;
	if (sprzet) {
		koniecListy();
		sprzet->kolejny = aktualny;
		aktualny->poprzedni = sprzet;
		aktualny->id_produktu = (sprzet->id_produktu) + 1;
		ostatni = aktualny;
	}
	else {
		przedmiot = aktualny;
		przedmiot->poprzedni = NULL;
		aktualny->id_produktu = 1;
		ostatni = pierwszy = przedmiot;
	}
	if (autonumeracja == false) {
		aktualny->id_produktu = id_przedmiotu;
	}

	sprzet = aktualny;
	n++;
}

void ListaSprzetu::edytujSprzet()
{
	if (n)
	{
		Sprzet * temp = new Sprzet;
		temp = temp->podajDane();

		sprzet->nazwa = (temp->nazwa == "") ? sprzet->nazwa : temp->nazwa;
		sprzet->typ = (temp->typ == "") ? sprzet->typ : temp->typ;
		sprzet->informacje = (temp->informacje == "") ? sprzet->informacje : temp->informacje;
		sprzet->sprawny = (temp->sprawny == 2) ? sprzet->sprawny : temp->sprawny;
		sprzet->nowy = (temp->nowy == 2) ? sprzet->nowy : temp->nowy;
		sprzet->ilosc = (temp->ilosc == -1) ? sprzet->ilosc : temp->ilosc;
		sprzet->wartosc = (temp->wartosc == -1) ? sprzet->wartosc : temp->wartosc;
	}
}


Sprzet * ListaSprzetu::pierwszyElement()
{
	if (n)
	{
		if (pierwszy->poprzedni)
		{
			while (pierwszy->poprzedni)
				pierwszy = pierwszy->poprzedni;
		}
	}
	return pierwszy;
}

Sprzet * ListaSprzetu::ostatniElement()
{
	if (n)
	{
		if (ostatni->kolejny)
		{
			while (ostatni->kolejny)
				ostatni = ostatni->kolejny;
		}
	}
	return ostatni;
}

void ListaSprzetu::poczatekListy()
{
	sprzet = pierwszyElement();
}

void ListaSprzetu::koniecListy()
{
	sprzet = ostatniElement();
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
	Sprzet *temp = sprzet;

	if (n)
	{
		do
		{
			sprzet = sprzet->poprzedni;
		} while (sprzet && !sprzet->pokaz);
	}

	if (!sprzet)
		sprzet = temp;
}

void ListaSprzetu::nastepnyElement()
{
	Sprzet *temp = sprzet;

	if (n)
	{
		do
		{
			sprzet = sprzet->kolejny;
		} while (sprzet && !sprzet->pokaz);
	}

	if (!sprzet)
		sprzet = temp;
}

void ListaSprzetu::listaJestPusta(int x, int y)
{
	Pomocnik *pom = new Pomocnik;
	pom->gotoxy((x + 2), (y + 6));
	cout << "Lista jest pusta" << endl;
}

void ListaSprzetu::przeniesElement(ListaSprzetu* innaLista)
{
	if (n)
	{
		Sprzet *nowy(sprzet);
		innaLista->dodajSprzet(nowy);
		usunElement();
	}
}

void ListaSprzetu::przeniesWszystko(ListaSprzetu* innaLinsta)
{
	while (n)
	{
		przeniesElement(innaLinsta);
	}
}

void ListaSprzetu::usunElement()
{
	if (n)
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
}

void ListaSprzetu::usunWszystkie()
{
	while (n)
		usunElement();
}

int ListaSprzetu::wyszukiwanie(string tekst)
{
	Pomocnik * przeszukiwacz = new Pomocnik;
	sprzet = pierwszyElement();
	widoczne = n;

	while (sprzet)
	{
		string nazwa = sprzet->nazwa, rodzaj = sprzet->typ, info = sprzet->informacje;

		if (!(przeszukiwacz->czyZawieraFraze(nazwa, tekst) || przeszukiwacz->czyZawieraFraze(rodzaj, tekst) ||
			przeszukiwacz->czyZawieraFraze(info, tekst)))
		{
			sprzet->pokaz = false;
			widoczne--;
		}


		sprzet = (sprzet->kolejny);
	}
	sprzet = pierwszyElement();

	if (widoczne)
		sprzet = pierwszyWidoczny();

	return widoczne;
}

int ListaSprzetu::wyszukiwanie(int id)
{
	widoczne = n;
	sprzet = pierwszyElement();

	while (sprzet)
	{
		if (sprzet->id_produktu != id)
		{
			sprzet->pokaz = false;
			widoczne--;
		}

		sprzet = (sprzet->kolejny);
	}
	sprzet = pierwszyElement();

	if (widoczne)
		sprzet = pierwszyWidoczny();

	return widoczne;
}

int ListaSprzetu::wyszukiwanie(double kwota_od, double kwota_do)
{
	widoczne = n;
	sprzet = pierwszyElement();

	while (sprzet)
	{
		double wartosc = sprzet->wartosc;
		if (!(wartosc >= kwota_od && wartosc <= kwota_do))
		{
			sprzet->pokaz = false;
			widoczne--;
		}


		sprzet = (sprzet->kolejny);
	}
	sprzet = pierwszyElement();

	if (widoczne)
		sprzet = pierwszyWidoczny();

	return widoczne;
}

int ListaSprzetu::wyszukiwanie(int liczba_od, int liczba_do)
{
	widoczne = n;
	sprzet = pierwszyElement();

	while (sprzet)
	{
		int ilosc = sprzet->ilosc;
		if (!(ilosc >= liczba_od && ilosc <= liczba_do))
		{
			sprzet->pokaz = false;
			widoczne--;
		}

		sprzet = (sprzet->kolejny);
	}
	sprzet = pierwszy;

	if (widoczne)
		sprzet = pierwszyWidoczny();

	return widoczne;
}

int ListaSprzetu::wyszukiwanie(ATR atrybut, bool wartosc)
{
	int warunek;
	widoczne = n;
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

		if (warunek != 1)
		{
			sprzet->pokaz = false;
			widoczne--;
		}

		sprzet = (sprzet->kolejny);
	}
	sprzet = pierwszyElement();

	if (widoczne)
		sprzet = pierwszyWidoczny();

	return widoczne;
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

void ListaSprzetu::sortowanie(ATR atrybut, bool rosnaco)
{
	bool warunek;
	sprzet = pierwszyWidoczny();
	Sprzet * temp = sprzet;
	nastepnyElement();

	while (sprzet)
	{
		warunek = sprawdz_warunek(temp, sprzet, atrybut, rosnaco);

		if (warunek)
		{
			while (temp)
			{
				warunek = sprawdz_warunek(temp, sprzet, atrybut, rosnaco);

				if (warunek)
				{
					zamien(temp);
				}

				sprzet = temp;
				do { temp = temp->poprzedni; } while (temp && !temp->pokaz);
			}
		}

		temp = sprzet;
		sprzet = sprzet->kolejny;
	}

	sprzet = temp;
	sprzet = pierwszyElement();
}

int ListaSprzetu::iloscElementow()
{
	return n;
}

Sprzet * ListaSprzetu::pierwszyWidoczny()
{
	sprzet = pierwszyElement();
	while (!sprzet->pokaz)
	{
		sprzet = sprzet->kolejny;
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
	nazwa_pliku += ".mdat";
	plik.open(nazwa_pliku.c_str(), (ios::in|ios::binary));

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
	if (n)
	{
		ofstream plik;
		plik.open(nazwa_pliku.c_str(), (ios::out | ios::binary)); // trunc?

		if (!plik)
			return 0;

		plik.write((char*)&rozmiar, sizeof(rozmiar));

		do {
			plik.write((char*)sprzet, sizeof(Sprzet));
		} while ((sprzet = sprzet->kolejny));

		plik.close();

		return 1;
	}
}

void ListaSprzetu::pokazWszystkie()
{
	sprzet = pierwszyElement();
	while (sprzet)
	{
		sprzet->pokaz = true;
		sprzet = sprzet->kolejny;
	}

	widoczne = n;
	sprzet = pierwszyElement();
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