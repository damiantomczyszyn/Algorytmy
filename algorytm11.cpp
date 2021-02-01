#include <iostream>
    using namespace std;
    
unsigned int n, m;


struct elem
{
    unsigned int id,nr;
};

struct osoba
{   
    int id;
    string nazwa;
};

struct popraw
{
    int id, idn;
    string nazwa;
};

void sido( elem t3[],  int roz,  int ind)
{
     int j=2*ind+1;

    while(j<roz)
    {
        if((j<roz-1)&&(t3[j].id>t3[j+1].id)) j++;
        if(t3[ind].id>t3[j].id)
        {
            swap( t3[ind], t3[j]);
            ind = j;
            j= 2*ind + 1;

        } else break;
    }
}


elem stog( elem t2[],   int roz,  int poz )
{

    for( int i=(roz-2)/2; i>=0;i--) sido (t2, roz, i);
    for( int i=roz-1;i>0;i--)
    {
        swap( t2[0], t2[i] );
        sido( t2, i, 0 );
    }

    return t2[roz-poz-1];
}


elem m5(elem t1[],  int roz,  int poz)
{
    if(roz<=10) return stog( t1, roz, poz);
    
    unsigned int am, ad, y, x=roz/5;
    elem med, a[x+1], tem[5];
    for(unsigned int i=0;i<x;i++)
    {
        for(unsigned int j=0;j<5;j++)  tem[j]=t1[i*5+j];
        a[i]=stog( tem, 5, 2);
    }    

    if(y=roz%5)
    {
        unsigned int tut=0;
        while(tut<y) 
        {
            tem[tut]=t1[5*x+tut];
            tut++;
        }
        while(tut<5) 
        {
            tem[tut].id = 20000000;
            tem[tut++].nr = 20000000;
        }
    
        a[x]=stog( tem, 5, 2);
        x++;
    }
    med = m5( a , x, (unsigned int)(x/2));
    elem amal[2*roz/3], aduz[2*roz/3];
    am=ad=0;
    for(y=0; y<roz;y++)
    {
        if(t1[y].id<med.id) { amal[am++]=t1[y]; continue;}
        if(t1[y].id>med.id) aduz[ad++]=t1[y];
    }
    if(am==poz) return med;
    else if(am>poz) return m5( amal, am, poz);
    else return m5(aduz , ad, poz-am-1);
}



   int main()
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);
        int s;
        string tmptxt;
        cin>>n>>m;
        elem element, t[n];
        osoba d[n];
        popraw p[m];

        for(int i=0;i<n;i++)
        {
            cin>>d[i].id>>d[i].nazwa>>tmptxt;
            d[i].nazwa+=" "+tmptxt;
        }
        for(int i=0;i<m;i++)
        {
           cin>>p[i].id>>p[i].idn>>p[i].nazwa>>tmptxt;
           p[i].nazwa+=" "+tmptxt;
        }
        for( unsigned int k=0;k<m;k++)
        {
            for(unsigned int i=0;i<n;i++)
            {
                t[i].nr=i;
                t[i].id=d[i].id;
            }
            element=m5 ( t, n, p[k].id );
            s=(element.nr<2) ? 3+element.nr : 5;
            while(s&&element.nr+3-s<n)
            {
                cout<<d[element.nr+3-s].id<<" "<<d[element.nr+3-s].nazwa<<"\n";
                s--;
            }

            d[element.nr].id = p[k].idn;
            d[element.nr].nazwa = p[k].nazwa;
        }
        
        return 0;
    }
