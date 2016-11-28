#pragma once
class Bruteforce
{
public:
	Bruteforce(int n);
	~Bruteforce();
	void permutation(int Value[], int n);
	void read();
	void algorithm();
	int sums = 0;
	int min = INT_MAX;
	int** paths;
	int* permutations;
	string name;
	int size;
};

