#include <iostream>

using namespace std;



int main()
{
    short  n;
    cin >> n;
    short** t = new short* [n + 2];
    for (int k = 0; k < n + 2; k++)
        t[k] = new short[n + 2]{};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> t[i][j];
        }
    }
    return 0;
}