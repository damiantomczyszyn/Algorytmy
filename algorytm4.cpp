#include <iostream>
using namespace std;
struct pracownik
{
    string name;
     int podwladni;
     int poczatektablicypodwladnych;   
};
void dodajpracownika(pracownik *tab, int *p, int *k, int *n)
{
    int ilopo = 0;
    while (*p <= *k)
    {
        cin >> (tab + *p)->podwladni >> (tab + *p)->name;
        (tab + *p)->poczatektablicypodwladnych = *k + ilopo;
        ilopo += (tab + *p)->podwladni;
        (*p)++;
        (*n)--;    
        if (*n == 0) {
        ilopo = 0;
        return;
    }
    }
    *k += ilopo;

    if (ilopo!=0)
        dodajpracownika(tab, p, k, n );
        return ;
}
void wypisz(pracownik* tab, int* n, int p)
{
    if (p+1 > * n)
        return;    
    if ((tab + p)->podwladni == 0) 
    {
        cout << (tab + p)->name << "\n";
    return;
    }
    for (int i = 1; i <= (tab+p)->podwladni; i++)
    {       
        if (i + (tab + p)->poczatektablicypodwladnych < *n)
        {
        wypisz(tab,n,i+ (tab + p)->poczatektablicypodwladnych); 
        }
   }
    cout << (tab + p)->name<<"\n";
    return;
}
int main()
{
std::ios_base::sync_with_stdio(false);
std::cin.tie(nullptr);
std::cout.tie(nullptr);
int p = 0, k = 0, n{}, po{};
 int ilo = 0;
    string name;
    cin >> n;
    po = n;
    pracownik* tab = new pracownik[n];    
    dodajpracownika(tab, &p, &k, &n);
    wypisz(tab, &po,0);
}

