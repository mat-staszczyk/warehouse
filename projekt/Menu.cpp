#include "./Header.h"

Menu::Menu()
{
	lista = new ListaSprzetu;
	kosz = new ListaSprzetu(false);
}

int Menu::glowne()
{
	string nazwa_pliku;
	char klawisz;
	Sprzet * test;

	do
	{
		system("cls");
		opis_glowne();

		cin >> klawisz;
		cin.ignore();

		switch (klawisz)
		{
		case '1':
			lista->poczatekListy();
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

	return EXIT_SUCCESS;
}

void Menu::zarzadzanieSprzetem()
{
	char klawisz;
	Sprzet *test;

	do
	{
		system("cls");
		opis_zarzadzanie();

		cin >> klawisz;
		cin.ignore();

		switch (klawisz)
		{
		case '1':
			sprzet();
			break;
		case '2':
			system("cls");
			test = new Sprzet;
			test = test->podajDane();
			lista->dodajSprzet(test);
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

	do
	{
		system("cls");
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
			lista->edytujSprzet();
			break;
		case '4':
			sortowanie();
			break;
		case '5':
			lista->przeniesElement(kosz);
			break;
		case '6':
			lista->przeniesWszystko(kosz);
			break;
		default:
			break;
		}

	} while (klawisz != '7');

}

void Menu::wyszukiwanie()
{

	ListaSprzetu::ATR nowy = ListaSprzetu::ATR::nowy;
	ListaSprzetu::ATR sprawny = ListaSprzetu::ATR::sprawny;
	Pomocnik * pom = new Pomocnik;
	string fraza;
	char klawisz;

	do
	{
		system("cls");
		opis_wyszukiwanie();

		cin >> klawisz;
		cin.ignore();

		switch (klawisz)
		{
		case '1':
			int id;
			id = pom->pobierzId();
			lista->wyszukiwanie(id);
			sprzet();
			break;
		case '2':
			fraza = pom->pobierzFraze();
			lista->wyszukiwanie(fraza);
			sprzet();
			break;
		case '3':
			int * liczby;
			liczby = pom->pobierzLiczbe();
			lista->wyszukiwanie(liczby[0], liczby[1]);
			sprzet();
			break;
		case '4':
			double * kwoty;
			kwoty = pom->pobierzKwoty();
			lista->wyszukiwanie(kwoty[0], kwoty[1]);
			sprzet();
			break;
		case '5':
			lista->wyszukiwanie(nowy, true);
			sprzet();
			break;
		case '6':
			lista->wyszukiwanie(sprawny, true);
			sprzet();
			break;
		case '7':
			lista->wyszukiwanie(nowy, false);
			sprzet();
			break;
		case '8':
			lista->wyszukiwanie(sprawny, false);
			sprzet();
			break;
		default:
			break;
		}

		lista->pokazWszystkie();

	} while (klawisz != '9');
}

void Menu::sortowanie()
{
	ListaSprzetu::ATR nazwa = ListaSprzetu::ATR::nazwa;
	ListaSprzetu::ATR typ = ListaSprzetu::ATR::typ;
	ListaSprzetu::ATR info = ListaSprzetu::ATR::info;
	ListaSprzetu::ATR id = ListaSprzetu::ATR::id;
	ListaSprzetu::ATR ilosc = ListaSprzetu::ATR::ilosc;
	ListaSprzetu::ATR wartosc = ListaSprzetu::ATR::wartosc;

	char klawisz;
	bool wybor;


	if (lista->iloscElementow())
	{
		do
		{
			system("cls");
			lista->wypiszElement();
			opis_sortowanie();

			cin >> klawisz;
			cin.ignore();

			switch (klawisz)
			{
			case '1':
				wybor = sortujRosnaco();
				lista->sortowanie(id, wybor);
				return;
			case '2':
				wybor = sortujRosnaco();
				lista->sortowanie(nazwa, wybor);
				return;
			case '3':
				wybor = sortujRosnaco();
				lista->sortowanie(typ, wybor);
				return;
			case '4':
				wybor = sortujRosnaco();
				lista->sortowanie(wartosc, wybor);
				return;
			case '5':
				wybor = sortujRosnaco();
				lista->sortowanie(ilosc, wybor);
				return;
			default:
				break;
			}

		} while (klawisz != '6');
	}
}

void Menu::zarzadzanieKoszem()
{
	char klawisz;

	do
	{
		system("cls");
		kosz->wypiszElement();
		opis_kosz();

		cin >> klawisz;
		cin.ignore();

		switch (klawisz)
		{
		case '1':
			kosz->poprzedniElement();
			break;
		case '2':
			kosz->nastepnyElement();
			break;
		case '3':
			kosz->usunElement();
			break;
		case '4':
			kosz->usunWszystkie();
			break;
		case '5':
			kosz->przeniesElement(lista);
			break;
		case '6':
			kosz->przeniesWszystko(lista);
			break;
		default:
			break;
		}

	} while (klawisz != '7');
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
	cout << "2. Dodaj sprzêt.";
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
	pom->gotoxy((x += 13), y);
	cout << "3. Edycja";
	pom->gotoxy((x += 12), y);
	cout << "4. Sortuj";
	pom->gotoxy((x += 12), y);
	cout << "5. Usuñ";
	pom->gotoxy((x += 11), y);
	cout << "6. Usuñ wszystko";
	pom->gotoxy((x += 20), y);
	cout << "7. Powrót";
	pom->gotoxy(t_x, (y + 1));
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
	cout << "1. ID";
	pom->gotoxy(x, y++);
	cout << "2. Tekst";
	pom->gotoxy(x, y++);
	cout << "3. Licznoœæ";
	pom->gotoxy(x, y++);
	cout << "4. Wartoœæ";
	pom->gotoxy(x, y++);
	cout << "5. Nowe przedmioty";
	pom->gotoxy(x, y++);
	cout << "6. Sprawne przedmioty";
	pom->gotoxy(x, y++);
	cout << "7. U¿ywane przedmioty";
	pom->gotoxy(x, y++);
	cout << "8. Uszkodzone przedmioty";
	pom->gotoxy(x, y++);
	cout << "9. Powrót";
	pom->gotoxy(x, ++y);
	cout << "> ";
}

void Menu::opis_sortowanie(int x, int y)
{
	x += 45;
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

void Menu::opis_kierunekSortowania(int x, int y)
{
	x += 70;
	Pomocnik *pom = new Pomocnik;

	pom->gotoxy(x, y++);
	cout << "Kierunek sortowania:";
	pom->gotoxy(x, y++);
	cout << "1. Rosn¹co";
	pom->gotoxy(x, y++);
	cout << "2. Malej¹co";
	pom->gotoxy(x, ++y);
	cout << "> ";
}

bool Menu::sortujRosnaco()
{
	char klawisz;

	do
	{
		opis_kierunekSortowania();
		cin >> klawisz;
		cin.ignore();

		switch (klawisz)
		{
		case '1':
			return true;
		case '2':
			return false;
		default:
			break;
		}

	} while (true);
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