#include<iostream>
#include<string>
using namespace std;
struct pracownik
{
    string nazwa;
    pracownik* prc_pre;
    pracownik* prc_post;
};
struct odd
{
    string nazwa;
    short zmiana;
    pracownik* kier{};
    odd* nast{};
};
int main()
{
    ios_base::sync_with_stdio(false);
   //std::cin.tie(nullptr);
    //std::cout.tie(nullptr);
    unsigned  int w, k, i, j, m, id = 0;
    pracownik* ws;
    odd* od = 0, * wsk, * wsk1;
    char q;
    string znak;
    int n = 0;
    cin >> n;
    pracownik* prc = new pracownik[n];
    pracownik* pom;
    for (k = 0; k < n; k++)
    {
        i = 0;                //wyciagniecie instrukcji
        cin >> q;
        w = (int)q * 1000;
        if (w < 109000)
        {
            cin >> q;
            i = (int)q;
            w += i;
        }

        switch (w)
        {
        case 97119:                                         //operacje dodania oddzialu
            if (!od)
            {
                od = new odd;

                cin >> znak;
                od->nazwa = znak;
                    cin >> w;
                    od->zmiana=w;
            }
            else
            {
                wsk = od;
                while (wsk->nast) wsk = wsk->nast;
                wsk1 = new odd;
                cin >> wsk1->nazwa >> wsk1->zmiana;
                wsk->nast = wsk1;
            }
            break;
        case 97101://operacje dodania pracownika
            cin >> znak;
            (prc + id)->nazwa = znak;
                cin>> znak;
            wsk = od;
            while ((wsk->nazwa != znak) and (wsk->nast)) wsk = wsk->nast;
            if (wsk->nazwa == znak) 
            {
                if (!wsk->kier) {
                    wsk->kier = (prc + id);
                    (prc + id)->prc_pre = (prc + id);
                    (prc + id)->prc_post = (prc + id);
                }
                else {
                    wsk->kier->prc_pre->prc_post = (prc + id);
                    (prc + id)->prc_pre = wsk->kier->prc_pre;
                    (prc + id)->prc_post = wsk->kier;
                    wsk->kier->prc_pre = (prc + id);
                }
                id++;
            }
            break;
        case 100119:                                          
            cin >> znak;
            if (od)
            {
                if ((od->nazwa) == znak) {
                    wsk = od->nast;
                    delete od;
                    od = wsk;
                }
                else {
                    wsk = od;
                    while ((wsk->nast->nazwa != znak) && (wsk->nast->nast!=nullptr))

                        wsk = wsk->nast;

                    if (wsk->nast->nazwa == znak)
                    {
                        wsk1 = wsk->nast;
                    wsk->nast = wsk->nast->nast;
                    delete wsk1;
                }
                }
            }
            break;
        case 100101:
            cin >> w;
            pom = (prc + w);
            wsk = od;
            while ((wsk->kier != pom) and (wsk->nast)) wsk = wsk->nast;
            if (wsk->kier == pom)
            {
                if (pom->prc_post == pom)
                {
                    wsk->kier = nullptr;
                }
                else
                {
                    wsk->kier = pom->prc_post;
                }
            }
            pom->prc_pre->prc_post = pom->prc_post;
            pom->prc_post->prc_pre = pom->prc_pre;
          
            break;
        case 109000:                                          //operacje przeniesienia pracownika
            cin >> w;
            pom = (prc + w);
            wsk = od;
            while (wsk->kier != pom and wsk->nast) wsk = wsk->nast;
            if (wsk->kier == pom)
            {
                if (pom->prc_post == pom)
                {
                    wsk->kier = nullptr;
                }
                else
                {
                    wsk->kier = pom->prc_post;
                };
            };
            pom->prc_pre->prc_post = pom->prc_post;
            pom->prc_post->prc_pre = pom->prc_pre;
            cin >> znak;
            wsk = od;
            while (wsk->nazwa != znak and wsk->nast) wsk = wsk->nast;
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
                pom->prc_pre = wsk->kier->prc_pre;
                pom->prc_post = wsk->kier;
                wsk->kier->prc_pre = pom;
            }
            break;

        case 101119:                                          //operacje przemianowanie oddzialu
            cin >> znak;
            wsk = od;
            while ((wsk->nazwa != znak) and (wsk->nast)) wsk = wsk->nast;
            cin >> wsk->nazwa >> wsk->zmiana;
            break;

        case 101101:                                          //operacje przemianowanie pracownika
            cin >> w >> (prc + w)->nazwa;
            break;
        case 115000:                                          //operacje zmiany
            cin >> w;
            wsk = od;
            while (wsk) {
                if (wsk->kier) {
                    ws = wsk->kier;
                    ws = ws->prc_post;
                    i = 1;
                    while (ws != wsk->kier) {
                        ws = ws->prc_post;
                        i++;
                    }
                    j = i;
                    if (i < wsk->zmiana) cout << "(niedobor pracownikow)";
                    cout << wsk->nazwa << ":";
                   // i = ((w > 0) - (w < 0)) * ((w * wsk->zmiana) % i);
                    if (!w)

                        i = 0;
                    else
                        i = ((w * wsk->zmiana) % i);
                    
                    for (m = 0; m < i; m++)
                        ws = ws->prc_post;
                    wsk->kier = ws;
                    if (j > (wsk->zmiana))
                        j = wsk->zmiana;
                    for (m = 0; m < j; m++)
                    {
                        if (m) cout << ",";
                        cout << ws->nazwa;
                        ws = ws->prc_post;
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