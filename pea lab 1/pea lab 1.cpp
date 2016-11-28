// pea lab 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"
#include "Bruteforce.h"
#include "BB.h"

int _tmain(int argc, _TCHAR* argv[])
{
	string name;
	int size;
	int n;
	int wybor;
	ifstream file;
	//cout << "Podaj ilosc miast." << endl;
	//Generator test(5);
	do 
	{
		cout << "Wybierz operacje:\n";
		cout << "1 - oba algorytmy\n2 - przeglad zupelny\n3 - metoda podzialu i ograniczen\n4 - wygeneruj nowy plik\n5 - wyjscie" << endl << endl;
		cin >> wybor;
		switch (wybor)
		{
		case 1:
		{
			cout << "\nPodaj nazwe pliku:\n";
			cin >> name;
			file.open(name);
			file >> size;
			file.close();

			Bruteforce m(size);

			m.name = name;
			m.size = size;
			m.read();
			m.algorithm();
			cout << endl << "********************************************************************************" << endl;
			cout << endl;
			BB b(size);
			b.name = name;
			b.size = size;
			b.read();
			b.algorithm();
			cout << endl << "********************************************************************************" << endl;
			break;
		}
		case 2:
		{
			cout << "\nPodaj nazwe pliku:\n";
			cin >> name;
			file.open(name);
			file >> size;
			file.close();

			Bruteforce s(size);

			s.name = name;
			s.size = size;
			s.read();
			s.algorithm();
			cout << endl << "********************************************************************************" << endl;
			break;
		}
		case 3:
		{
			cout << "\nPodaj nazwe pliku:\n";
			cin >> name;
			file.open(name);
			file >> size;
			file.close();
			BB z(size);
			z.name = name;
			z.size = size;
			z.read();
			z.algorithm();
			cout << endl << "********************************************************************************" << endl;
			break;
		}
		case 4:
		{
			cout << "Podaj ilosc miast." << endl;
			cin >> n;
			Generator test(n);
			break;
		}
		case 5:
			exit(0);
		default:
			break;
		}
	} while (wybor != 5);
	system("pause");
	return 0;
}

