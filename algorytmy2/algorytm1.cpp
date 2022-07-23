#include <iostream>


 using namespace std;


struct punkt
{
    unsigned int id, x, y;
};


void przesiewup1 (punkt tb[], int i, int trans[])
{
    int j=(i-1)/2;
    
    while( (i>0) && (tb[j].x>tb[i].x) )
    {
        trans[tb[j].y] = i;
		trans[tb[i].y] = j;
		
		swap( tb[j], tb[i] );
        i=j;
        j=( i - 1 )/2;
    }
    
}

void przesiewdo3 (punkt tab[], int roz, int i, int trans[])
{
    int j=2*i+1;
    while(j<roz)
    {
        if((j<roz-1) && (tab[j].x>tab[j+1].x)) j++;
        if(tab[i].x>tab[j].x)
        {
            trans[tab[i].y] = j;
			trans[tab[j].y] = i;
			swap(tab[i], tab[j]);
            i=j;
            j=2*i+1;
        } else break;
    }
}

void przesiewdo1 (punkt tab[], int roz, int i)
{
    int j=2*i+1;
    while(j<roz)
    {
        if((j<roz-1)&&((tab[j].x>tab[j+1].x)||((tab[j].x==tab[j+1].x)&&(tab[j].y>tab[j+1].y)))) j++;
        if((tab[i].x>tab[j].x)||((tab[i].x==tab[j].x)&&(tab[i].y>tab[j].y)))
        {
            swap(tab[i], tab[j]);
            i=j;
            j=2*i+1;
        } else break;
    }
}

void przesiewdo2 (punkt tab[], int roz, int i)
{
    int j=2*i+1;
    while(j<roz)
    {
        if((j<roz-1)&&((tab[j].y>tab[j+1].y)||((tab[j].y==tab[j+1].y)&&(tab[j].x>tab[j+1].x)))) j++;
        if((tab[i].y>tab[j].y)||((tab[i].y==tab[j].y)&&(tab[i].x>tab[j].x)))
        {
            swap(tab[i],tab[j]);
            i=j;
            j=2*i+1;
        } else break;
    }
}

void stogsort1 (punkt tab[], int roz, int i)
{
    for(int j=(roz-2)/2;j>=0;j--) przesiewdo1 (tab, roz, j);
    for(int j=roz-1; j>0;j--)
    {
        swap(tab[0],tab[j]);
        przesiewdo1 (tab,j,0);
    }
}

void stogsort2 (punkt tab[], int roz, int i)
{
    for(int j=(roz-2)/2;j>=0;j--) przesiewdo2 (tab, roz, j);
    for(int j=roz-1; j>0;j--)
    {
        swap( tab[0], tab[j] );
        przesiewdo2 (tab,j,0);
    } 
}

int main()
{
    
 //   std::ios_base::sync_with_stdio(false);
//	std::cin.tie(nullptr);
//	std::cout.tie(nullptr);

    
    int n,a,b,wsk;
   
    cin>>n;
	int *translate = new int [n];
    punkt* tab=new punkt [n]; 
    int **drogi=new int *[n];
    for(int i=0 ; i<n;i++)
    {
        cin>>tab[i].x>>tab[i].y;
        tab[i].id=i;
        drogi[i]=new int [9];
        drogi[i][0]=0;
    }
    
    
    stogsort1 (tab,n,0);
    
    
    for (int i=0;i<n-1;i++)
    {
        drogi[tab[i+1].id][drogi[tab[i+1].id][0]+1]=drogi[tab[i].id][drogi[tab[i].id][0]+1]=tab[i].x-tab[i+1].x;
        drogi[tab[i+1].id][drogi[tab[i+1].id][0]+2]=tab[i].id;
        drogi[tab[i].id][drogi[tab[i].id][0]+2]=tab[i+1].id;
        drogi[tab[i].id][0]+=2;
        drogi[tab[i+1].id][0]+=2;
    }
    
    stogsort2 (tab,n,0);
    
        
    for (int i=0;i<n-1;i++)
    {
   
        wsk = 1;
        for(int j=0;j<drogi[tab[i].id][0];j+=2)
        {

            if((drogi[tab[i].id][j+2]==tab[i+1].id))
            {
                wsk=0;

                if(drogi[tab[i].id][drogi[tab[i].id][0]+j+1]>tab[i].y-tab[i+1].y)
                {
                    drogi[tab[i].id][drogi[tab[i].id][0]+j-1]=tab[i].y-tab[i+1].y;
                    for(int k=0;k<drogi[tab[i+1].id][0];k+=2)
                    {
                        if(drogi[tab[i+1].id][k+2]==tab[i].id)
                        {
                            drogi[tab[i+1].id][drogi[tab[i+1].id][0]+k+1]=tab[i].y-tab[i+1].y;
                            break;
                        }
                    }
                }
                
                break;
            }
            
        }
        
        if(wsk)
        {
        drogi[tab[i+1].id][drogi[tab[i+1].id][0]+1]=drogi[tab[i].id][drogi[tab[i].id][0]+1]=tab[i].y-tab[i+1].y;
        drogi[tab[i+1].id][drogi[tab[i+1].id][0]+2]=tab[i].id;
        drogi[tab[i].id][drogi[tab[i].id][0]+2]=tab[i+1].id;
        drogi[tab[i].id][0]+=2;
        drogi[tab[i+1].id][0]+=2;
        }
        tab[i].x=2000000000;
        tab[i].y=i;
		translate[i]=i;
    }
    tab[n-1].x=2000000000;
    tab[n-1].y=n-1;
	translate[n-1]=n-1;

    
    // dikstry
    cin>>a>>b;
    tab[0].x=0;
	tab[a].y=0;
    tab[0].y=a;
	translate[0]=a;
	translate[a]=0;

    
    while(n--)
    {
    
		if(tab[0].y==b) {cout<<tab[0].x; return 0;}
		wsk=tab[0].x;
		a = tab[0].y;
		
		translate[tab[0].y]=n;
		translate[tab[n].y]=0;
		swap(tab[0], tab[n]);
		przesiewdo3 (tab, n, 0, translate);

        
        
        for(int i = 0;i<drogi[a][0];i+=2)
        {
            if((translate[drogi[a][i+2]]<n)&&(drogi[a][i+1]+wsk < tab[translate[drogi[a][i+2]]].x))
            {
                tab[translate[drogi[a][i+2]]].x = drogi[a][i+1]+wsk;
				przesiewup1 (tab, translate[drogi[a][i+2]], translate);
            }
        }
        
    }
    

}
