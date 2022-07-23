#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

struct punkt {
	double x, y;

};

void przesiewdo2 (punkt punkty[], double tab[], double dlug[],int roz, int i)
{
    int j=2*i+1;
    while(j<roz)
    {
        if((j < roz-1) && ((tab[j] < tab[j+1]) || ((tab[j]==tab[j+1]) && (dlug[j] > dlug[j+1] )))) j++;
        if((tab[i] < tab[j]) || ((tab[i] == tab[j]) && (dlug[i] > dlug[j])))
        {
            swap(tab[i],tab[j]);
            swap(punkty[i+1], punkty[j+1]);
            swap(dlug[i], dlug[j]);
            i=j;
            j=2*i+1;
        } else break;
    }
}

void selection_sort_kat(punkt punkty[], double tab[], double dlug[], int roz)
//void stogsort2 (punkt tab[], int roz)
{
    for(int j=(roz-2)/2;j>=0;j--) przesiewdo2 (punkty, tab, dlug, roz, j);
    for(int j=roz-1; j>0;j--)
    {
        swap( tab[0], tab[j] );
        swap(punkty[1], punkty[j+1]);
        swap(dlug[0], dlug[j]);
        przesiewdo2 (punkty, tab, dlug, j, 0);
    } 
}

/*

void selection_sort_kat(punkt punkty[], double tab[], double dlug[], int n)
{
	int min;

	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
			if ((tab[j] < tab[min]) || ((tab[j] == tab[min]) && (dlug[j] > dlug[min])))
				min = j;


		swap(tab[i], tab[min]);
		swap(punkty[i + 1], punkty[min + 1]);// od razu zamienimy punkty by miały odpowiadające indeksy || +1 bo 0 to punkt P
		swap(dlug[i], dlug[min]);
	}
}

*/


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
    int det{};
	cin >> n;
	punkt* punkty = new punkt[n];
    cin >> punkty[0].x >> punkty[0].y;
	for (int i = 1; i < n; i++)
		{
		cin >> punkty[i].x >> punkty[i].y;
		if ( (punkty[i].y < punkty[det].y) || ((punkty[i].y == punkty[det].y) && (punkty[i].x < punkty[det].x)) ) det = i;
		}

	// zamieniam minimum by miał indeks 0
	swap(punkty[det], punkty[0]);
	double* katy = new double[n - 1];
    double* dlugosc = new double[n - 1];

	//sortowanie polarne

	for (int i = 0; i < n - 1; i++)//kąty 
	{


		katy[i] = atan2(punkty[i + 1].y - punkty[0].y, punkty[i + 1].x - punkty[0].x);//punkt p do usunięcia z tej tablicy katow
		dlugosc[i] = (punkty[i+1].x - punkty[0].x)*(punkty[i+1].x - punkty[0].x)+(punkty[i+1].y - punkty[0].y)*(punkty[i+1].y - punkty[0].y);

	}

	selection_sort_kat(punkty, katy, dlugosc, n - 1);



	
	int wstaw = 1;
	{
		double	kat{-1};
		for (int i = 0; i < n-1; i++)

			if ( kat < katy[i] )
			{

				punkty[wstaw++] = punkty[i+1];
				kat = katy[i];
			}
	}




///////////////////wyznaczenie obwiedni
	

	    int ostatni{0}, wyznacznik;
	
	    for (int i = 2 ; i< wstaw  ; i++)
	    {
	        wyznacznik = punkty[ostatni].x*punkty[ostatni+1].y-punkty[ostatni].y*punkty[ostatni+1].x;
	        wyznacznik += punkty[ostatni+1].x*punkty[i].y-punkty[ostatni+1].y*punkty[i].x;
	        wyznacznik += punkty[i].x*punkty[ostatni].y-punkty[i].y*punkty[ostatni].x;
	        
	        if( wyznacznik > 0 ) 
	        {
	           punkty[ostatni+2] = punkty[i];
	           
	           ostatni++;
	        }
            else
		    {
		    	ostatni--;
		    	i--;
	    	}
	    }
        
 
        do
        {
        wyznacznik = punkty[ostatni].x*punkty[ostatni+1].y-punkty[ostatni].y*punkty[ostatni+1].x;
	    wyznacznik += punkty[ostatni+1].x*punkty[0].y-punkty[ostatni+1].y*punkty[0].x;
	    wyznacznik += punkty[0].x*punkty[ostatni].y-punkty[0].y*punkty[ostatni].x;
          
         if( wyznacznik > 0 ) 
	        {
	           ostatni++;
	        }
	        else ostatni--;
        } while (wyznacznik<=0);





	///////////////////////////obliczanie pola z trojkatow
	double x0{ punkty[0].x }, y0{ punkty[0].y };
	double x{ punkty[1].x }, y{ punkty[1].y }, pole{};

	for (int i = 2; i < ostatni + 1; i++)
	{
		pole += (x - x0) * (punkty[i].y - y0) - (punkty[i].x - x0) * (y - y0);
		x = punkty[i].x;
		y = punkty[i].y;
	}
    pole=pole/2;

	cout << fixed;
	cout << setprecision(3) << pole;
	return 0;
}