#include <iostream>

using namespace std;

class rbtc

{
  
private:

  struct lista;
  
  struct nod
  {
      nod *up, *left, *right;
      string nazwa;
      bool kolor{}; // 0 czerwony 1- czarny
      lista *list;
  };
  
  struct lista
  {
      nod *wezel;
      lista *nast{}, *poprz;
  };
  
  lista *head, *tail;
  nod *root, *sentinel;
  
/*

    rbtc();
    ~rbtc();
    void dodaj(string name);
    void barwienie(nod *wsk);
    void zamien(string str1, string str2);
    nod* pozycja(string str);
    void przesun(string str, int zmiana );
    void wypisz_liste();
    void barwienie (nod* wsk);
    void ror( nod* wsk);
    void rol( nod* wsk);

*/  
  
  void barwienie(nod *wsk)
  {
      
      if(wsk->up == nullptr) { wsk->kolor = 1; return; } ///czarny korzen
      if(wsk->up->kolor) return;
      if(wsk->up->up->left->kolor == wsk->up->up->right->kolor)
        {
            wsk->up->up->left->kolor = wsk->up->up->right->kolor = 1;
            wsk->up->up->kolor = 0;
            barwienie( wsk->up->up );
            return;
        } else
        {
            if( wsk->up == wsk->up->up->left ) /////ojciec to lewy syn
            {
                if(wsk->up->right == wsk)   ////przysrodkowy
                {
                    rol( wsk->up );
                    wsk = wsk->left;
                }
                ror( wsk->up->up );
                wsk->up->kolor = 1;
                wsk->up->right->kolor = 0;
                return;
            } else                                          //////ojciec to prawy syn
            {
                if( wsk->up->left == wsk )      ////przysrodkowy
                {
                    ror( wsk->up );
                    wsk = wsk->right;
                }
                rol( wsk->up->up );
                wsk->up->kolor = 1;
                wsk->up->left->kolor = 0;
                return;
            }
        }
  }
  
  void ror( nod* wsk)
  {
      if(!wsk->up)
      {
          root = wsk->left;
          wsk->left->up = nullptr;
      } else
      {
          if( wsk->up->left == wsk ) wsk->up->left = wsk->left;
          else                       wsk->up->right = wsk->left;
          wsk->left->up = wsk->up;
      }
      wsk->up = wsk->left;
      wsk->left->right->up = wsk;
      wsk->left = wsk->left->right;
      wsk->up->right = wsk;
  }
  
    void rol( nod* wsk)
  {
     
      if(!wsk->up)
      {
          root = wsk->right;
          wsk->right->up = nullptr;
      } else
      {
          if( wsk->up->right == wsk ) wsk->up->right = wsk->right;
          else                       wsk->up->left = wsk->right;
          wsk->right->up = wsk->up;
      }
      wsk->up = wsk->right;
      wsk->right->left->up = wsk;
      wsk->right = wsk->right->left;
      wsk->up->left = wsk;
  }

  nod* pozycja(string str)
  {
      nod* wsk = root;
      while(wsk->nazwa != str)
        if(str < wsk->nazwa)
            wsk = wsk->left;
        else
            wsk = wsk->right;
      return wsk;
  }
  
public:
  
    rbtc()
  {
      head  = new lista;
      head->poprz=nullptr;
      head->wezel = nullptr;
      tail = new lista;
      tail->poprz = head;
      head->nast = tail;
      tail->wezel = nullptr;
      tail->nast = nullptr;
      sentinel = new nod;
      sentinel->nazwa = "";//straznik
      sentinel->up = nullptr;
      sentinel->left = nullptr;
      sentinel->right = nullptr;
      sentinel->kolor = 1;
      root = sentinel;
  }
  
  ~rbtc()
  {
      lista *wsk;
      while(head)
      {
          if(head->wezel) delete head->wezel;
          wsk = head;
          head = head->nast;
          delete wsk;
      }
     delete sentinel;
  }
  
    void dodaj(string name)
  {
      lista * nlist = new lista;
      nod *nnod = new nod;
      ////wstawienie do listy
      nlist->wezel = nnod;
      nlist->poprz = tail->poprz;
      nlist->nast = tail;
      tail->poprz->nast = nlist;
      tail->poprz = nlist;
      nnod->nazwa = name;
      nnod->list = nlist;
/// wstawianie do drzewa
      {

          nod *wsk{},  *wsk1 = root;
          while(wsk1 != sentinel)
          {
              wsk = wsk1;
              if(nnod->nazwa < wsk1->nazwa)
                wsk1 = wsk1->left;
              else
                wsk1 = wsk1->right;
          }
          nnod->up = wsk;
          if(wsk == nullptr) root = nnod;   // puste drzewo
          else 
            if(nnod->nazwa < wsk->nazwa) wsk->left = nnod;
            else wsk->right = nnod;
          nnod->left = nnod->right = sentinel;
          
      }
      
      barwienie( nnod );
      
  }
  
  void zamien(string str1, string str2)
  {
      nod *napis1 = pozycja( str1 );
      nod *napis2 = pozycja( str2 );
      swap( napis1->list, napis2->list );
      swap(napis1->list->wezel, napis2->list->wezel );
  }
  
  void przesun( string str, int zmiana )
  {
      lista *wsk = pozycja( str )->list, *wskn = wsk;
      if(zmiana>0) zmiana++;
      if(zmiana>0) while(zmiana--) wskn = wskn->poprz;
      else  while(zmiana++) wskn = wskn->nast;
      wsk->nast->poprz = wsk->poprz;
      wsk->poprz->nast = wsk->nast;  ////wyciety
      wsk->nast = wskn->nast;
      wsk->poprz = wskn;
      wskn->nast->poprz = wsk;
      wskn->nast = wsk;  ///wstawiony
  }
  
  void wypisz_liste()
  {
    lista* wsk = head;
    wsk = head->nast;
    while(wsk->nast) 
    {
        cout<<wsk->wezel->nazwa<<"\n";
        wsk = wsk->nast;
    }
  }
 
};


int main()
{
    rbtc *plist = new rbtc;
    string tytu, tytu1;
    char komend;
    int n,a;
    cin>>n;
    while(n--)
    {
        cin>>tytu;
        plist->dodaj( tytu );
    }
    
    cin>>n;
    while(n--)
    {
        cin>>komend;
        if(komend =='a') {cin>>tytu; plist->dodaj( tytu );}
        else if(komend == 'm') {cin>>tytu>>a; plist->przesun( tytu, a );} 
        else if(komend == 'r') { cin>>tytu>>tytu1; plist->zamien( tytu, tytu1 );}

    }

    plist->wypisz_liste();

    return 0;
}