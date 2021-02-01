#include <queue>
#include <iostream>
#include <list>

using namespace std;

struct wiezcholek
{
    list<int> lista;
    unsigned int droga = 0;
    bool badany = 0;
};



int main()
{
    std::ios_base::sync_with_stdio(false);

    unsigned short int n, m, s, w, w1 = 0, dr = 0;
    queue < int > kole;
    cin >> n >> m >> s >> w;
    wiezcholek* t = new wiezcholek[n];

    for (dr = 0; dr < m; dr++)
    {
        cin >> n >> w1;
        t[n].lista.push_back(w1);
        t[w1].lista.push_back(n);
    }
    w1 = -1;
    dr = 0;
    kole.push(s);
    while (kole.size())
    {
        n = kole.front();
        kole.pop();

        t[n].badany = 1;
        for (list<int>::iterator iter = t[n].lista.begin(); iter != t[n].lista.end(); iter++)
        {
            if (t[*iter].badany == 0)
            {
                kole.push(*iter);
                t[(*iter)].droga = t[n].droga + 1;
            }
        }
        if (w >= 2 * t[n].droga) w1++;
        if (dr < t[n].droga) dr = t[n].droga;
    }
    cout << "\n" << dr << " " << w1;
    return 0;
}