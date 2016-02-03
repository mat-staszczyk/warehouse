#include "./Header.h"

string Helper::tlumaczKod(int wartosc)
{
	return (wartosc == 1) ? "tak" : "nie";
}

bool Helper::czyZawieraFraze(string tekst, string nowy_tekst)
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

string Helper::pobierzFraze(int x, int y)
{
	string fraza;

	x += 30;

	gotoxy(x, y++);
	cout << "Szukaj:";
	gotoxy(x, y);
	cout << "> ";
	gotoxy((x + 3), y);
	cin >> fraza;
	return fraza;
}

double * Helper::pobierzKwoty(int x, int y)
{
	double kwoty[2];
	double *wsk_kwoty;

	x += 30;

	gotoxy(x, y++);
	cout << "Proszê podaæ zakres wyszukiwania:";
	gotoxy(x, y);
	cout << "(od:) > ";
	gotoxy((x + 8), y++);
	cin >> kwoty[0];
	gotoxy(x, y);
	cout << "(do:) >";
	gotoxy((x + 8), y++);
	cin >> kwoty[1];

	wsk_kwoty = &(kwoty[0]);
	return wsk_kwoty;
}

int * Helper::pobierzLiczbe(int x, int y)
{
	int licznosc[2];
	int *wsk_licz;

	x += 30;

	gotoxy(x, y++);
	cout << "Proszê podaæ zakres wyszukiwania:";
	gotoxy(x, y);
	cout << "(od:) > ";
	gotoxy((x + 8), y++);
	cin >> licznosc[0];
	gotoxy(x, y);
	cout << "(do:) > ";
	gotoxy((x + 8), y++);
	cin >> licznosc[1];

	wsk_licz = &(licznosc[0]);
	cin.ignore();
	return wsk_licz;
}

int Helper::pobierzId(int x, int y)
{
	int id;

	x += 30;

	gotoxy(x, y++);
	cout << "Proszê podaæ poszukiwany nr ID: \n> ";
	gotoxy(x, y++);
	cin >> id;

	cin.ignore();
	return id;
}

string Helper::podajNazwe()
{
	string nazwa_pliku;

	cout << "Podaj nazwê pliku, w którym maj¹ zostaæ zapisane dane:" << endl;
	fflush(stdin);
	cin >> nazwa_pliku;
	nazwa_pliku += ".mdat";

	return nazwa_pliku;
}

void Helper::gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}