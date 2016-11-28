#include "stdafx.h"
#include "Bruteforce.h"


Bruteforce::Bruteforce(int n)
{
	size = n;
	paths = new int*[size];
	for (int i = 1; i <= size; i++)
	{
		paths[i] = new int[size];
	}
}


Bruteforce::~Bruteforce()
{
}


void Bruteforce::permutation(int Value[], int n)
{
	static int level = -1;
	level++;
	Value[n] = level;
	sums = 0;
	if (level == size) //skonczyliscmy generowac dana permutacje
	{
		if (Value != 0)
		{
			for (int i = 0; i < size; i++)
			{
				//sprawdzamy czy suma drog jest mniejsza od tej poprzedniej
				sums = sums + paths[Value[i%size]][Value[(i + 1) % size]];
			}
			//cout << sumy << endl;

			if (sums< min)
			{
				min = sums;
				for (int i = 0; i < size; i++)
					permutations[i] = Value[i];//wstawiamy ja do tablicy
			}
		}

	}
	else
		for (int i = 0; i < size; i++)
			if (Value[i] == 0)
				permutation(Value, i);
	level--;
	Value[n] = 0;
}

void Bruteforce::read()
{
	ifstream plik;
	plik.open(name);
	plik >> size;
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
		{
			plik >>paths[i][j];
		}

	cout << "Drogi:" << endl;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			cout << setw(6) << paths[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Bruteforce::algorithm()
{
	long silnia = 1;
	int indeks = 0;
	//tablica do permutacji
	int* miasta = new int[size];
	for (int i = 0; i < size; i++)
	{
		miasta[i] = 0;
	}
	//wszystkie permutacje zbioru umieszczamy w tablicy jest ich ilosc!
	for (int i = 1; i <= size; i++)
	{
		silnia = silnia*i;
	}


	permutations = new int[size];

	permutation(miasta, 0);//w ten sposob mamy tablice wypelniona permutacjami


	cout << "najkrotsza sciezka wg przegladu zupelnego:\n";
	cout << "Dystans: " << min << endl << endl;
	cout << "Trasa: " << endl;
	for (int i = 0; i < size; i++)
		cout << permutations[i] << " --- ";
	cout << permutations[0];
	cout << endl;



	delete[]permutations;
}