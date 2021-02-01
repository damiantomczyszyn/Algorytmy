#include <iostream>

using namespace std;
struct probowka {
    string nazwa_p;
    int czas_p = 0;
};
void wyswietlanie(probowka zestaw[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << zestaw[i].nazwa_p << "-" << zestaw[i].czas_p << " ";
    }
}
void iinsertSort(probowka* zestaw, int n)
{
    probowka key;
    int i, j;
    for (i = 1; i < n; i++)
    {
        key = zestaw[i];
        j = i - 1;
        while (((j >= 0) && (zestaw[j].czas_p < key.czas_p)) || ((j >= 0) && (zestaw[j].czas_p == key.czas_p) && (zestaw[j].nazwa_p > key.nazwa_p)))

        {
            zestaw[j + 1] = zestaw[j];

            j = j - 1;
        }
        zestaw[j + 1] = key;
    }
}


void sinsertSort(probowka* zestaw, int n)
{
    probowka key;
    int i, j;
    for (i = 1; i < n; i++)
    {
        key = zestaw[i];
        j = i - 1;
        while (((j >= 0) && (zestaw[j].nazwa_p > key.nazwa_p)) || ((j >= 0) && (zestaw[j].nazwa_p == key.nazwa_p) && (zestaw[j].czas_p < key.czas_p)))  
        {
            zestaw[j + 1] = zestaw[j];

            j = j - 1;
        }
        zestaw[j + 1] = key;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    int t, n, k;

    probowka pom;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> n;

        probowka* zestaw = new probowka[n];

        for (int j = 0; j < n; j++)
        {

            cin >> zestaw[j].nazwa_p;
            cin >> zestaw[j].czas_p;


        }
        cin >> k;
        if (k == 0)
        
            sinsertSort(zestaw,n);
       
       else
            iinsertSort(zestaw,n);
           
        cout << endl;
        wyswietlanie(zestaw, n);
        
    }
    return 0;
}
