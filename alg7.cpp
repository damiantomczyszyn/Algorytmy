#include <iostream>

using namespace std;
struct kwadrat {
	int poczatek;
	int koniec;

};
 void sortowanie(kwadrat pracownia[], unsigned int n)
{
	kwadrat pom;
for(int i=0; i<n;i++)
	for (int j = 0; j < n - 1; j++)
	{
		
if ((pracownia[j].koniec > pracownia[j+1].koniec)||((pracownia[j].koniec == pracownia[j + 1].koniec)&&(pracownia[j].poczatek > pracownia[j + 1].poczatek))){
		pom = pracownia[j];
			pracownia[j]=pracownia[j+1];
		pracownia[j+1]=pom;
			
	}
	}
}
//sortowanie
 bool sprawdzanie(kwadrat pracownia[], unsigned int n)
 {
	 unsigned int* tab= new unsigned int [n];
	 for (int j = 0; j < n ; j++)
	 {
		 if ((pracownia[j].koniec >= j) && (pracownia[j].poczatek <= j))
			 ;
		 else
		 return false;
	 }
	 return true;
 }

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	 int n;

cin >> t;
for (int i = 0; i < t; i++)
{
	cin >> n;
	kwadrat* pracownia = new kwadrat[n];
	for (int j = 0; j < n; j++) {
		cin >> pracownia[j].poczatek >> pracownia[j].koniec;
}

	sortowanie(pracownia,n);
	if (sprawdzanie(pracownia, n))
		cout << "TAK\n";
	else cout << "NIE\n";

}


}
