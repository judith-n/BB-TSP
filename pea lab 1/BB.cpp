#include "stdafx.h"
#include "BB.h"


BB::BB(int n)
{
	size = n;
	size2 = n;
	paths = new int*[size];
	paths2 = new int*[size];
	LBr = new int[size];
	LBl = new int[size];
	for (int i = 1; i <= size; i++)
	{
		paths[i] = new int[size];
		paths2[i] = new int[size];
	}

	//usuniete kolumny i wiersze
	removed_col = new bool[size];
	removed_row = new bool[size];
	route = new int[size];
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
		{
			removed_col[j] = false;
			removed_row[j] = false;
			route[j] = 0;
		}
	for (int i = 0; i < size; i++)
	{
		LBr[i] = 0;
		LBl[i] = 0;
	}

}


BB::~BB()
{
}

void BB::read()
{
	ifstream plik;
	plik.open(name);
	plik >> size;
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
		{
			plik >> paths[i][j];
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

void BB::algorithm()
{

	int max = 0;
	//zamienienie zer w tablicy na nieskoncznosci
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (paths[i][j] == 0)
				paths[i][j] = 999;
		}
	}

	//przekopiowanie zawartosci path do path2
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
			paths2[i][j] = paths[i][j]; 


	//zminimalizowanie macierzy w wierszach 
	int *row = new int[size2];
	int *column = new int[size2];
	int distance = 0;
	int licznik = 0;
	while (licznik <size - 2)
	{
		//int minw = 999;
		for (int i = 1; i <= size2; i++)
		{
			int minw = 999;
			for (int j = 1; j <= size2; j++)
			{
				if (paths2[i][j] < minw  && removed_row[i] == false)
				{
					row[i] = paths2[i][j];
					minw = row[i];
				}
				else if (removed_row[i] == true)
				{
					row[i] = 0;
				}
		

			}
			cout << "wiersze:" << row[i];
		}
		cout << endl;
		for (int i = 1; i <= size2; i++)
			for (int j = 1; j <= size2; j++)
				if (row[i]<101)
					paths2[i][j] = paths2[i][j] - row[i];
		//		for (int i = 1; i <= size; i++)
		//{
		//	for (int j = 1; j <= size; j++)
		//	{
		//		cout << setw(6) << paths2[i][j];
		//	}
		//	cout << endl;
		//}
		//cout << endl << endl;

		//zminimalizowanie macierzy w kolumnach

		for (int j = 1; j <= size2; j++)
		{
			int mink = 999;
			for (int i = 1; i <= size2; i++)
			{
				if (paths2[i][j] < mink && removed_col[j] == false)
				{
					column[j] = paths2[i][j];
					mink = column[j];
				}
				else if (removed_col[j] == true)
				{
					column[j] = 0;
				}
				//column[j] = mink;
			}
			cout << "kol"<<column[j];
		}
		cout << endl;

		for (int j = 1; j <= size2; j++)
			for (int i = 1; i <= size2; i++)
				if (column[j]<101)
					paths2[i][j] = paths2[i][j] - column[j];
		//for (int i = 1; i <= size; i++)
		//{
		//	for (int j = 1; j <= size; j++)
		//	{
		//		cout << setw(6) << paths2[i][j];
		//	}
		//	cout << endl;
		//}

		//ograniczenie dolne
		//ograniczenie dolne dla zminimalizowanej macierzy
		if (licznik == 0)
		{
			for (int i = 1; i <= size2; i++)
				LBr[licznik] = LBr[licznik] + row[i] + column[i];
			LBl[licznik] = LBr[licznik];
		}
		//ograniczenie dolne dla kolejnych macierzy prawego poddrzewa (bez wybranego wczesniej luku)
		else
		{
			for (int i = 1; i <= size2; i++)
				LBl[licznik] = LBl[licznik] + row[i] + column[i];
			LBl[licznik] = LBl[licznik] + LBl[licznik - 1];
			LBr[licznik] = max + LBl[licznik - 1];
		}
		//	cout << LB << endl;

		//znalezienie luku wzgledem ktorego nastapi podzial
		for (int i = 1; i <= size2; i++)
		{
			int min = 999;
			for (int j = 1; j <= size2; j++)
			{
				if (paths2[i][j] < min && paths2[i][j] != 0)
				{
					min = paths2[i][j];
					row[i] = min;
				}
	
			}
			for (int i = 1; i <= size; i++)
				if (removed_row[i] == true)
					row[i] = 0;
			cout << "min z row" << row[i];
		}

		//znalezienie luku wzgledem ktorego nastapi podzial
		for (int j = 1; j <= size2; j++)
		{
			int min = 999;
			for (int i = 1; i <= size2; i++)
			{
				if (paths2[i][j] < min && paths2[i][j] != 0)
				{
					min = paths2[i][j];
					column[j] = min;
				}
	
			}
			for (int i = 1; i <= size; i++)
				if (removed_col[i] == true)
					column[i] = 0;
			cout << "min z col" <<column[j];
		}

		//luk wzgledem ktorego nastepuje podzial
		int m_cost = 0;
		int n_cost = 0;
		max = 0;
		for (int i = 1; i <= size2; i++)
		{
			if (row[i] > max &&row[i] < 101)
			{
				max = row[i];
				m_cost = i;
			}
		}

		for (int i = 1; i <= size2; i++)
		{
			if (column[i] > max && column[i] < 101)
			{
				max = column[i];
				m_cost = i + size2; //dodanie rozmiaru tablicy by bylo wiadomo ze to z tablicy column
			}
		}
		
		//zablokowanie przejscia w wybranym miejscu i skrocenie macierzy o wybrany wiersz i kolumne
		if (m_cost > (size2)) //najwiekszy koszt znajduje sie w tablicy column
		{
			//nalezy teraz znalezc w ktorym wierszy tej kolumny znajduje sie 0
			cout << "tutaj" << m_cost << endl;
			for (int i = 1; i <= size2; i++)
			{
				if (paths2[i][m_cost - size2] == 0)
					n_cost = i;
			}
			paths2[m_cost - size2][n_cost] = 999;
			removed_col[m_cost - size2] = true;
			for (int i = 1; i <= size; i++)
			{
				paths2[i][m_cost - size] = 888;
				paths2[n_cost][i] = 888;
			}
			removed_row[n_cost] = true;
			m_cost -= size;
			cout << "\nWAZNE"<<n_cost << " " << m_cost << endl;
		
			route[n_cost] = m_cost;
			distance += paths[n_cost][m_cost];
		}

		else
		{
			for (int i = 1; i <= size2; i++)
			{
				if (paths2[m_cost][i] == 0)
					n_cost = i;
			}
			cout << "\nWAZNE" << m_cost << " " << n_cost << endl;
			paths2[n_cost][m_cost] = 999;
			removed_col[n_cost] = true;
			removed_row[m_cost] = true;
			for (int i = 1; i <= size; i++)
			{
				paths2[i][n_cost] = 888;
				paths2[m_cost][i] = 888;
			}
			cout <<"\nWAZNE"<< m_cost << " " << n_cost << endl;
			route[m_cost] = n_cost;
			distance += paths[m_cost][n_cost];
		}
		//zawartosc macierzy po zmianach:
		for (int i = 1; i <= size2; i++)
		{
			for (int j = 1; j <= size2; j++)
				if (removed_row[i] == false && removed_col[j] == false)
					cout << setw(6) << paths2[i][j];
			cout << endl;
		}
		cout << endl << endl;
		//for (int i = 1; i <= size; i++)
		//{
		//	for (int j = 1; j <= size; j++)
		//	{
		//		cout << setw(6) << paths2[i][j];
		//	}
		//	cout << endl;
		//}
		cout << endl;
		licznik++;

	}

	int r[2];
	int c[2];

	int k = 0;
	for (int i = 1; i <= size2; i++)
	{
		if (removed_row[i] == false)//wyszukiwanie nieusunietych wierszy
		{
			r[k] = i;
			k++;
		}
	}
	int l = 0;
	for (int i = 1; i <= size2; i++)
	{
		if (removed_col[i] == false)//wyszukiwanie nieusunietych kolumn
		{
			c[l] = i;
			l++;
		}
	}

	//wyznaczenie drogi na podstawie usuwanych wierszy i kolumn oraz indeksow pozostalych w macierzy 2x2
	bool condition = true;
	route[r[0]] = c[0];
	route[r[1]] = c[1];
	int tmp;
	int z = 1;
	int m = 0;
	//wyznaczenie LB
	int max_l = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (paths2[r[i]][c[j]] != 0 && paths2[r[i]][c[j]] <101 && paths2[r[i]][c[j]] > max_l)
				max_l = paths2[r[i]][c[j]];
		}
	}
	LBl[size - 2] = LBl[size - 3] + max_l;
	LBr[size - 2] = LBl[size - 3] + max;
	int* visited = new int[size];
	for (int i = 1; i <= size; i++)
		visited[i] = false;

	for (int i = 1; i <= size; i++)
	{
		tmp = route[z];
		visited[tmp] = true;
		z = tmp;
	}

	for (int i = 1; i <= size; i++)
	{
		if (visited[i] == true)
			m++;
	}

	if (m != size)
		condition = false;
	if (condition)
	{
		distance += paths[r[0]][c[0]];
		distance += paths[r[1]][c[1]];
		cout << r[0] << c[0] << endl << r[0] << c[0] << endl;
	}
	else
	{
		route[r[0]] = c[1];
		route[r[1]] = c[0];
		cout << r[0] << c[1] << endl << r[1] << c[0] << endl;
		distance += paths[r[0]][c[1]];
		distance += paths[r[1]][c[0]];
	}

	//wyswietlanie wynikow:
	cout << "najkrotsza sciezka wg metody podzialu i ograniczen:\n";
	//distance += paths[route[1]][1];
	cout << "Dystans: " << distance << endl << endl;
	int j = 1;
	for (int i = 1; i <= size; i++)
	{
		cout << j << " --- ";
		j = route[j];
	}
	cout << "1";
	cout << endl;
	//LB kolejne
	for (int i = 0; i < size; i++)
		cout << LBr[i] <<"  " << LBl[i]<< endl;
}