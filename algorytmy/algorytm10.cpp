#include <iostream>
    using namespace std;

   int main()
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);
         int s, n, k = 0, k1=1023, i, j;
         int d, x, p;
        cin >> s >> d;
        unsigned int *tmp, *tmp1;
        unsigned int* xx=new unsigned int[1023]{};
        unsigned int* px=new unsigned int[1023]{};
        for (unsigned  int d1 = 0; d1 < d; d1++)
        {
            n=0;
            cin >> n;
            for (unsigned int n1 = 0; n1 < n; n1++)
            {
                cin >> x >> p;
                i = k;
                xx[k] = x;
                px[k++] = p;
                //            if(k==5) {for(int t=2;t>0;t++) t--;}
                j = (i - 1) / 2 ;
                while (i && ((px[i] < px[j]) || (px[i] == px[j] && xx[i] < xx[j])))       //przesiew gora
                {
                    swap(px[i], px[j]);
                    swap(xx[i], xx[j]);
                    i = j;
                    j = (i - 1) / 2 ;
                }
                if(k==k1)
                {
                    k1=2*k1+1;
                    tmp=new unsigned int[k1];
                    tmp1=new unsigned int[k1];
                    for(i=0;i<k;i++){ tmp[i]=xx[i]; tmp1[i]=px[i];}
                    delete xx;
                    delete px;
                    xx=tmp;
                    px=tmp1;
                }
            }

            unsigned int s1 = s;
            if (k)
            {
                cout << xx[0];
                px[0] = px[--k];
                xx[0] = xx[k];
                s1--;

                i = 0;
                j = 1;
            while(j<k)
            {
                if((j<k-1)&&((px[j]>px[j+1])||((px[j]==px[j+1])&&(xx[j]>xx[j+1])))) j++;
                if((px[i]>px[j])||((px[i]==px[j])&&(xx[i]>xx[j]))) 
                {
                    swap( px[i] , px[j] );
                    swap( xx[i] , xx[j] );
                    i=j;
                    j=2*i+1;
                } else break;
                }

            }

            while (s1 && k)
            {

                cout << " " << xx[0];
                px[0] = px[--k];
                xx[0] = xx[k];
                s1--;

                i = 0;
                j = 1;
            while(j<k)
            {
                if((j<k-1)&&((px[j]>px[j+1])||((px[j]==px[j+1])&&(xx[j]>xx[j+1])))) j++;
                if((px[i]>px[j])||((px[i]==px[j])&&(xx[i]>xx[j]))) 
                {
                    swap( px[i] , px[j] );
                    swap( xx[i] , xx[j] );
                    i=j;
                    j=2*i+1;
                } else break;
                }
            }

            cout << "\n";
//            if(d1==1) {for(int t=2;t>0;t++) t--;}
        }
        cout<<"\n";

        return 0;
    }
