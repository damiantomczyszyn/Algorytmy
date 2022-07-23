#include <iostream>

using namespace std;

short cel = 10000;

void kolum(short** t, short k, short w, short tmp)
{    

    if (k == w)
    {
        for (short j = 0; j < w; j++) t[w + 1][j] = t[w][j];
        cel = tmp;
        return;
    }
    for (short i = 0; i < w; i++)
    {
        if (t[i][w] == 0)
        {
            t[i][w] = 1;
            t[w][k] = i;
            tmp += t[i][k];
           if(cel>tmp) kolum(t, k + 1, w, tmp);
            t[i][w] = 0;
            tmp -= t[i][k];
        }
    }
    return;
}



int main()
{
    short  n;
    cin >> n;
    short** t = new short* [n + 2];
    for (int k = 0; k < n + 2; k++)
        t[k] = new short[n + 1]{};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> t[i][j];
        }
    }


    kolum(t, 0, n, 0);
    cout<<t[n + 1][0];
    for (int i = 1; i < n; i++)
        cout <<" "<< t[n + 1][i];
   

    return 0;
}

