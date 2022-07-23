#include <iostream>
#include <algorithm>
using namespace std;
int m;
void sort( int tab[], int l, int r )
{
    int le = l;
    int ri = r;
    int x = tab[m+(l+r)/2 ];
    do
    {
        while(tab[m+le] < x )
             le++;
        while(tab[m+ri] > x )
             ri--;
        if(le<=ri)
        {
            swap( tab[m+le], tab[m+ri]);
            swap( tab[le], tab[ri]);
            le++;
            ri--;
        }
    } while(le<=ri);
    if( l <ri) sort( tab, l, ri);
    if( r >le ) sort( tab, le, r);
}

int main()
{
    int t,n,i,k,w1,w2;
    cin>>t;//ilość pokoi
    for(i=0;i<t;i++)
    {
        cin>>n;//rozmiar pokoju
            int* d=new int[2*n];
            int* w=new int[n]{};
            for(int j=0;j<n;j++) cin>>d[j]>>d[n+j];
            m=n;
        sort(d,0,n-1);

        for(int j=0;j<n;j++)
        {
            k=d[j];
            while(k<=d[n+j]&&w[k]) k++;
            if(k<=d[n+j]) w[k]++;else {cout<<"NIE\n";goto stop;}
        }
        cout<<"TAK\n";
stop:
    delete [] d;
    delete [] w;
    }
    return 0;
}

