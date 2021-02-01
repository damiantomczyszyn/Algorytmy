#include <iostream>
#include <queue>
#include <list>
using namespace std;

struct graf{
    list <int> lista;
    bool badany;
};
unsigned int maxy = 0;
unsigned int licznik = 0;

void bfs(graf* grafy, unsigned int startowy,unsigned int d)
{
    maxy = 0;
    queue < unsigned int > k;
    k.push(startowy);
    while (!k.empty())
    {
        unsigned int pom = k.front();
        k.pop();
        if (!grafy[pom].badany)
        {
            grafy[pom].badany = true;
             

            for (unsigned int i=1; i <= grafy[pom].lista.size(); i++)
            {
                k.push(grafy[pom].lista.front());
             
            }
        }
    }
}

int main()
{
   unsigned int a, b;
   unsigned int n, m, s, d;
    cin >> n >> m >> s >> d;
    graf* grafy = new graf[n];
  
    for (unsigned int i = 0; i < m; i++)
    {
        cin >> a >> b;
       
        grafy[a].lista.push_back(b);//uzupelnianie listy
        grafy[b].lista.push_back(a);//uzupelnianie listy
    }
    bfs(grafy, s, d);
    cout << licznik << "  " << maxy;
    
}

