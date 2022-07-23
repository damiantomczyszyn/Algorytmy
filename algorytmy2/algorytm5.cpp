#include <iostream>

using namespace std;

constexpr int l_pier{10210031}, mno{101};

int f_hash(char tab[], int r)
{
    int w{};
    while(--r)
    {
        w += tab[r];
        w *= mno;
    }
    return (w+tab[0])%l_pier;
}

bool spr(char tab[], char wzor[], int x, int r)
{
    while(r&&(tab[x+r-1]==wzor[r-1])) r--;
    return !r;
}

int main()
{
    int p,v,a;
    bool b{};
    cin>>p;
    char* sekw = new char[p];
    for(int i =0;i<p;i++) {cin>>a; sekw[i]=a;}// sekw[i]-=48;}
    a=0;
    cin>>v;
    int hashmax{1};
    char* sub = new char[v];
    for(int i=0; i<v ; i++) {cin>>a; sub[i]=a; hashmax *= mno;}// ; sub[i]-=48
    hashmax /= mno;
    int hash = f_hash(sub, v);
    int hash_t = f_hash(sekw, v);
    for( int i=0 ; i<p-v+1; i++ )
    {
        if((hash==hash_t)&&spr(sekw, sub, i, v)) //jezeli rowne hasae to sprawdz dokladnie
        {
           if(!b) {a=i; b=true; for(int c=0;c<v-1;c++){hash_t = ((hash_t - sekw[i+c])/mno + hashmax * sekw[i+v+c])%l_pier; };i+=(v-1);} //jesli jest to zapamietaj pozycje i przeskocz caly subsekwens
           else
           {
               v=i;
               break;
           }
        }
        hash_t = ((hash_t - sekw[i])/mno + hashmax * sekw[i+v])%l_pier;//obliczenie kolejnego hasa'a
    }
    while(p>v)
    {
        v+=a;
        a=v-a;
    }
    cout<<v-p;

    return 0;
}