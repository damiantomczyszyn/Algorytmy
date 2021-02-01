#include <queue>
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    std::ios_base::sync_with_stdio(false);
    //std::cin.tie(nullptr);
   // std::cout.tie(nullptr);
    unsigned int dr = 0, m;
    unsigned short  n, s, nowa, w;
   
    queue < unsigned short  > kole;
    cin >> n >> m >> s >> w;
    vector<unsigned short >* t = new vector<unsigned short >[n];
    bool b[n]{ 0 };
    for (dr = 0; dr < m; dr++)
    {
        cin >> n >> nowa;
        
        t[n].push_back(nowa);
      
        t[nowa].push_back(n);
    }
    
    m = 0;
    dr = 0;
    kole.push(s);
    nowa = 0;
    s = 1;
    while (!kole.empty()) {
        n = kole.front();
        kole.pop();


        b[n] = 1;
        if (!s)
        {
            dr++; 
            s = nowa;
            nowa = 0;
        }
        s--;

        if (w < 2 * (dr + 1)) 
        { 
       
        for (vector<unsigned short>::iterator iter = t[n].begin(); iter != t[n].end(); iter++)
                {
            if (!b[*iter])
            {
                kole.push(*iter);
                nowa++;
                b[*iter] = 1;
            }
               }
        }

        else{
            for (vector<unsigned short>::iterator iter = t[n].begin(); iter != t[n].end(); iter++)
            {
                if (!b[*iter])
                {
                    kole.push(*iter);
                    m++;
                    nowa++;
                    b[*iter] = 1;
                }
            }
        }
    }
    cout << dr << " " << m << "\n";
    return 0;
}