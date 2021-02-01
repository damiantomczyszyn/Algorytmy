#include <iostream>
//#include <string>
using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int t//liczba zesawow danych
		,pom=0, n;//liczba rodzajow aminokwasow
	string pierwszy, drugi;
	int dl1=0, dl2=0;
	cin >> t;
	for (int i = 0; t > i; i++)
	{
		dl1 = 0;
		dl2 = 0;
		int tab[10] = {};
		pom = 0;
		cin >> n;
		while (pom != -1)
		{

			cin >> pom;
			dl1++;
			switch (pom)
			{
			case 0:
				tab[0]++;
				break;
			case 1:
				tab[1]++;
				break;
			case 2:
				tab[2]++;
				break;
			case 3:
				tab[3]++;
				break;
			case 4:
				tab[4]++;
				break;
			case 5:
				tab[5]++;
			case 6:
				tab[6]++;
				break;
			case 7:
				tab[7]++;
				break;
			case 8:
				tab[8]++;
				break;
			case 9:
				tab[9]++;
				break;

			}

		}
		pom = 0;

		while (pom != -1)
		{
			dl2++;
			cin >> pom;
			switch (pom)
			{
			case 0:
				tab[0]--;
				break;
			case 1:
				tab[1]--;
				break;
			case 2:
				tab[2]--;
				break;
			case 3:
				tab[3]--;
				break;
			case 4:
				tab[4]--;
				break;
			case 5:
				tab[5]--;
			case 6:
				tab[6]--;
				break;
			case 7:
				tab[7]--;
				break;
			case 8:
				tab[8]--;
				break;
			case 9:
				tab[9]--;
				break;

			}
		}
		if (dl1 != dl2) {
			cout << "NIE\n";
			continue;
		}
		for (int j = 0; 10 > j; j++) {
			if (tab[j] != 0) {
				cout << "NIE\n";
				break;
			}if(j==9)
			cout << "TAK\n";
									}

				
	}
}
