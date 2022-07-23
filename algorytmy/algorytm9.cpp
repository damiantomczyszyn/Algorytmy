#include <iostream>
using namespace std;

int main()
{
   std::ios_base::sync_with_stdio(false);
std::cin.tie(nullptr);
std::cout.tie(nullptr);
    unsigned int n, tmp, k, p;
    unsigned int m, q, tym;
    double r;
    cin>>n>>m>>p;
    double d[n][m+1]={};
    for(unsigned int i=0;i<n;i++)
        for(unsigned int j=0;j<m;j++)
            {
                cin>>d[i][j];
                d[i][m]+=d[i][j];
            }
    tmp=(n<m*1000) ? n:1000*m;
    r=(double)m/tmp;
    q=(int)n/tmp;
    
    int t[tmp][q+40]={};
    for(unsigned int i=0; i<n;i++)
    {
        k=d[i][m]/r;
       
        if(k==tmp) k--;
        t[k][0]++;
        t[k][t[k][0]]=i;
    }
 
    tmp--;
    while (p)
    {
        for( unsigned int i=2;i<t[tmp][0]+1;i++)
        {
            r=d[t[tmp][i]][m];
            tym=t[tmp][i];
            q=i-1;
            while(q>0&&r>d[t[tmp][q]][m])
            {
                t[tmp][q+1]=t[tmp][q];
                q--;
            }
            t[tmp][q+1]=tym;
        }
        q=t[tmp][0];
        k=1;
        while(q&&p)
        {
            cout<<d[t[tmp][k]][0];
            for(unsigned int i=1;i<m;i++)
            cout<<" "<<d[t[tmp][k]][i];
            cout<<endl;
            p--;
            q--;
            k++;
        }
    tmp--;
    }
    return 0;
}

