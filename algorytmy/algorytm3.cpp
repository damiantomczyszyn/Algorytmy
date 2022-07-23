#include<iostream>

using namespace std;
struct odd;

struct pracownik
{
    string nazwa;
    pracownik* prc_pre=this;
    pracownik* prc_post=this;
    odd* odzial=0;
};
struct odd
{
    string nazwa;
    short zmiana;
    int ilo=0;
    pracownik* kier=0;
    odd* nast = nullptr;
};
int main()
{
std::ios_base::sync_with_stdio(false);
std::cin.tie(nullptr);
std::cout.tie(nullptr);

    unsigned  int w=0,i=0,j,n, m, id = 0;
    odd* od = 0, *od1=0, * wsk, *wsk1;
    char q;
    string znak;
    pracownik* pom, *pom1;   
    cin >> n;
    j=3*n/4;
    pracownik* prc = new pracownik[j];
                od = new odd;
                od->nazwa = "";
                od->zmiana = 0;
                od1=new odd;
                od->nast=od1;
    
    for (unsigned int k = 0; k < n; k++)
    {
                    //wyciagniecie instrukcji
        cin >> q;
         w = q * 1000;
        if (w < 109000)
        {
           
            cin >> q;           
            w +=q;  
        }
        switch (w)
        {
        case 97119:                                         //operacje dodania oddzialu
                wsk1 = new odd;
                cin >> od1->nazwa >> od1->zmiana;
                od1->nast = wsk1;
                od1=wsk1;
            break;
            
        case 97101:                                         //operacje dodania pracownika
            cin>>(prc + id)->nazwa;
            cin >> znak;
            wsk = od->nast;
            while (wsk->nazwa!=znak) wsk = wsk->nast;
                if (!wsk->kier) {
                    wsk->kier = (prc + id);
                    //(prc + id)->prc_pre = (prc + id);
                    //(prc + id)->prc_post = (prc + id);
                }
                else {
                    wsk->kier->prc_pre->prc_post = (prc + id);
                    (prc + id)->prc_pre = wsk->kier->prc_pre;
                    (prc + id)->prc_post = wsk->kier;
                    wsk->kier->prc_pre = (prc + id);
                }
                (prc+id)->odzial=wsk;
                wsk->ilo++;
                id++;
            break;
            
        case 100119:                                    //usuniecie oddzialu
            cin >> znak;
                    wsk1 = od;
                    wsk = od->nast;
                    while (wsk->nazwa != znak){
                        wsk1 = wsk;
                        wsk = wsk->nast;}
                        wsk1->nast = wsk->nast;
                        //delete wsk;
            break;
            
        case 100101://usuniecie pracownika
            cin >> w;
            pom = (prc + w);
            wsk = pom->odzial;
            if (wsk->kier == pom)
		    if (pom->prc_post == pom)
                wsk->kier = nullptr;
            else
                    wsk->kier = pom->prc_post;  
            pom->prc_pre->prc_post = pom->prc_post;
            pom->prc_post->prc_pre = pom->prc_pre;
            wsk->ilo--;
            
            break;
            
        case 109000:                                          //operacje przeniesienia pracownika
            cin >> w;
            pom = (prc + w);
            cin >> znak;
            wsk = pom->odzial;
            if (wsk->kier == pom)
		    if (pom->prc_post == pom)
                wsk->kier = nullptr;
		    else
                    wsk->kier = pom->prc_post;  
            pom->prc_pre->prc_post = pom->prc_post;
            pom->prc_post->prc_pre = pom->prc_pre;
            wsk->ilo--;
            
            wsk = od->nast;
            while (wsk->nazwa!=znak) wsk=wsk->nast;
            if (!wsk->kier)
            {
                wsk->kier = pom;
                pom->prc_pre = pom;
                pom->prc_post = pom;
            }
            else
            {
                wsk->kier->prc_pre->prc_post = pom;
                pom->prc_pre = wsk->kier->prc_pre;
                pom->prc_post = wsk->kier;
                wsk->kier->prc_pre = pom;
            }
                wsk->ilo++;
		        pom->odzial=wsk;
            break;
            
        case 101119:                                          //operacje przemianowanie oddzialu
            cin >> znak;
            wsk = od->nast;
            while (wsk->nazwa != znak) wsk = wsk->nast;
            cin >> wsk->nazwa >> wsk->zmiana;
            break;
        case 101101:                                          //operacje przemianowanie pracownika
            cin >> w;
            cin >> (prc + w)->nazwa;
            break;
        case 115000:                                          //operacje zmiany
            cin >> w;
            wsk = od->nast;
            while (wsk->nast)
                {
	            if (wsk->kier)
                {
                    pom=wsk->kier;
                    i=wsk->ilo;
                    j = (w * wsk->zmiana) % i;
                    if(j){
                    if(i<i-j){
                        for (m = 0; m < i; m++)
                        pom = pom->prc_post;
                    }else {
                        for (m = 0; m < i-j; m++)
                        pom = pom->prc_pre;
                    }}
                    wsk->kier = pom;
                    if (i < wsk->zmiana) cout << "(niedobor pracownikow)"; 
                    else i = wsk->zmiana;
                    cout << wsk->nazwa << ":"<<pom->nazwa;
                    pom = pom->prc_post;
                    for (m = 1; m < i; m++)
                    {
                        cout << ","<< pom->nazwa;
                        pom = pom->prc_post;
                    }
                    cout << ".\n";
                }
                else
                {
                    cout << "(niedobor pracownikow)" << wsk->nazwa << ":.\n";
                }
                wsk = wsk->nast;
            }
            cout << "-\n";
            break;
        }
    }
    return 0;
}
