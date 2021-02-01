#include <iostream>

using namespace std;

long unsigned licznik = 0;

void Merge(int lewy, int srodkowy, int prawy, int* tab) {
	int i = lewy, j = srodkowy + 1, k = 0,* pom=new int[prawy - lewy + 1];
	while (j <= prawy && i <= srodkowy) {
		if (tab[i] <= tab[j]) {
			pom[k] = tab[i];
			i++;
		}
		else
		{
			licznik += srodkowy -k;
			pom[k] = tab[j];
			j++;

		}
		k++;
	}
	for (i = i; i <= srodkowy; i++) {
		pom[k] = tab[i];
		k++;
	}

	for (j = j; j <= prawy; j++) {
		pom[k] = tab[j];
		k++;
	}

	for (int i = lewy; i <= prawy; i++) {
		tab[i] = pom[i - lewy];
		i++;
	}

}

void MergeSort(int lewy, int prawy, int* tab) {
	int srodkowy;
	if (lewy < prawy) {
		srodkowy = (lewy + prawy) / 2;
		MergeSort(lewy, srodkowy, tab);
		MergeSort(srodkowy + 1, prawy, tab);
		Merge(lewy, srodkowy, prawy, tab);
	}
}

void wczytaj(int n, int tab[]) {
	for (int i = 0; i < n; i++) {
		cin >> tab[i];
	}
}

int main()
{

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin >> n;
	int* tab=new int[n];
	wczytaj(n, tab);
	MergeSort(0, n - 1, tab);
	cout << licznik;


}

