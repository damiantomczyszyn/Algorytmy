#include <iostream>
#include <string>
using namespace std;

constexpr int t = 10;

class bt
{
    struct Node;
    
struct klucz
{
    Node* syn_wsk{nullptr};
    string key{},opis{};
    klucz* nast{nullptr};
};

struct Node
{
    int n{0}; //ilosc elem
    bool leaf{0}; //czy lisc
    klucz* wsk= new klucz;
};

    void bt_splitchild(Node* ws, klucz* wskey);
    void bt_insertnful(Node* ws, string kluc, string tekst);
    string bt_find_opis(Node* ws, string klu, string tekst);

public:
    Node* root;
    bt();
    ~bt();
    void bt_insert(string kej, string tekst);
    string bt_znajdz_opis( string haslo, string tekst);

};

     bt::bt()
{
    root = new Node;
    root->leaf = true;
}

     bt::~bt()
{
    //kasowanie struktur
}

string bt::bt_znajdz_opis(string haslo, string tekst)
{
    return bt_find_opis(root, haslo, tekst);
}

void bt::bt_insert(string kej, string tekst)
{
    if(root->n == 2*t-1)
    {
        Node* ws = new Node;
        swap(root, ws);
        root->wsk->syn_wsk = ws;
        bt_splitchild(root, root->wsk);
    }
    bt_insertnful(root, kej, tekst);

}

void bt::bt_insertnful(Node* ws, string kluc, string tekst)
{
    klucz* nkl{ws->wsk};
    while((nkl->nast)&&(nkl->key<kluc)) nkl=nkl->nast;
    if(ws->leaf) //jesli lisc to dopisz
    {
        klucz* nnkl = new klucz;
        nnkl->opis = tekst;
        nnkl->key = kluc;
        nnkl->nast = nkl->nast;
        nkl->nast = nnkl;
        swap(nkl->key, nnkl->key);
        swap(nkl->opis, nnkl->opis);
        ws->n++;
    }
    else //jesli nie lisc to przejdz nizej
    {
       
       if(nkl->syn_wsk->n == 2*t-1) //jezeli syn jest maksymalny gdzie jest podziel?????
       {
           bt_splitchild(ws, nkl);
           if(kluc > nkl->key) nkl = nkl->nast; //znajdz odpowiedniego syna
       }
        bt_insertnful(nkl->syn_wsk, kluc, tekst); // i wywolaj wstawienie
    }
}

void bt::bt_splitchild(Node* ws, klucz* wskey)
{
    Node* nnod = new Node;
    nnod->leaf = wskey->syn_wsk->leaf;
    nnod->n = t-1;
    wskey->syn_wsk->n = t-1;
    klucz* wsl = wskey->syn_wsk->wsk;
    for(int i = 1 ; i<t ; i++) wsl = wsl->nast;
    nnod->wsk = wsl->nast; //prawy syn klucz
    klucz* nklu = new klucz;
    nklu->syn_wsk = nnod;//wskey->syn_wsk;
    nklu->key = wsl->key;
    nklu->opis = wsl->opis;
    wsl->opis="";
    wsl->key="";
    wsl->nast = nullptr;
    nklu->nast = wskey->nast;
    wskey->nast = nklu;
    ws->n++;
    swap(nklu->key, wskey->key);
    swap(nklu->opis, wskey->opis);
}

string bt::bt_find_opis(Node* ws, string klu, string tekst)
{
    klucz* nkl = ws->wsk;
    while(1)
    {
        if(nkl->nast == nullptr||klu < nkl->key)
        {
            if(!ws->leaf)  return bt_find_opis(nkl->syn_wsk, klu, tekst);
            else return "BRAK";
        }
        if(nkl->key == klu)
        {
            if(tekst!="") nkl->opis = tekst;
            return nkl->opis;
        }
        nkl=nkl->nast;
    }
}


int main()
{
    int n,i;
    bt btree;
    cin >> n;
    string opi, haslo;
    getline(cin, haslo);
    while(n--)
    {
        getline(cin, haslo);
        i = haslo.find_first_of( ":" );
        if(i==-1) cout<<btree.bt_znajdz_opis(haslo, "")<<"\n";
        else
        {
            opi=haslo.substr(i+1, haslo.length() - i -1);

            haslo=haslo.substr(0, i);

            if(btree.bt_znajdz_opis(haslo, opi)=="BRAK") btree.bt_insert(haslo, opi);
        }
    }
    return 0;
}