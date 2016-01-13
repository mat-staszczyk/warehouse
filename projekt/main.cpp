#include "./Header.h"

int main()
{
	// Dodanie obs³ugi polskich znaków pod Windows (VS2015)
	setlocale(LC_ALL, "polish");

	Pomocnik * pom = new Pomocnik;
	Menu * menu = new Menu;

	menu->glowne();

	return EXIT_FAILURE;
}