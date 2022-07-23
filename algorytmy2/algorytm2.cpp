#include <iostream>

using namespace std;

    
struct pole
{
    pole *nast;
    int bije;
};

    pole ** graf;


class queue
{
  private:
    pole * head;
    pole * tail;

  public:
    queue();
    ~queue();
    bool empty ();
    int  front ();
    void push ( int x );
    void pop ();
};

queue::queue()
{
  head = tail = NULL;
}

queue::~queue()
{
  while( head ) pop();
}


bool queue::empty ()
{
  return !head;
}


int queue::front ()
{
  if( head ) return head->bije;
  else     return 2000000000;
}


void queue::push ( int x )
{
  pole * ws = new pole;
  ws->nast = NULL;
  ws->bije = x;
  if( tail ) tail->nast = ws;
  else head = ws;
  tail = ws;
}


void queue::pop ()
{
  if( head )
  {
    pole *ws = head;
    head = head->nast;
    if( !head ) tail = NULL;
    delete ws;
  }
}


void dopisz (int c, int b)
{
    pole* ws = new pole;
    ws->bije = b;
    ws->nast = graf [ c ];
    graf [ c ] = ws;
    ws = new pole;
    ws->bije = c;
    ws->nast = graf [ b ];
    graf [ b ] = ws;
}


bool istnieje (int c, int b)            // czy w grafie istnieje droga
{
    pole* ws = graf [ c ];
    while( ws )
    {
        if( ws->bije == b) return true;
        ws = ws->nast;
    }
    return false;
}


int main()
{

    queue kol;
    int i,v,x,y,n,nn,*powiazane,*droga;
    pole * wskpl;
    bool *sprawdzone;
    cin>>n;
    nn=n*n;
    
    powiazane = new int [ nn ];       // Skojarzenia
    droga  = new int [ nn ];       // Ścieżka rozszerzająca
    sprawdzone  = new bool [ nn ];      // Odwiedziny
    graf = new pole *[nn];

    int tab[nn]{};

    for( i= 0 ; i<nn ; i++) cin>>tab[i];
    
    for( i = 0 ; i<nn ; i++)
    {
        
        if((i/n)%2==(i%n)%2)                                                             //jeśli czarny
        {
            if(tab[i]%2)                // jesli 1v3
            {
                if((i%n+2<n)&&((i+2-n)>-1)&&tab[i-n+2]) dopisz(i,i-n+2);    //
                if((i%n+2<n)&&((i+2+n)<nn)&&tab[i+n+2]) dopisz(i,i+n+2);    //
            }
            if((tab[i]>1)&&((i+1)/n==(i/n))&&tab[i+1]) dopisz(i,i+1);   //jesli 2v3
            if((tab[i]==1)&&((i+3)/n==(i/n))&&tab[i+3]) dopisz(i,i+3);     //jesli 1
            if(tab[i]==2)                                                           //jesli 2
            {
                if(((i-n)>-1)&&tab[i-n]) dopisz(i,i-n);
                if(((i+n)<nn)&&tab[i+n]) dopisz(i,i+n);
            }
        }
    }

  
    
  for( i = 0; i < nn; i++ )      
    powiazane [ i ] = -1;        

  for( v = 0; v < nn; v++ )      
    if( (graf[v]) && ( powiazane [ v ] == -1 ) && ((v/n)%2==(v%n)%2) ) //jesli wolny czarny
    {
      for( i = 0; i < nn; i++ )
        sprawdzone [ i ] = false;   

      while( !kol.empty() ) kol.pop( ); 

      sprawdzone [ v ] = true;      //  v jako  odwiedzony
      droga [ v ] = -1;        // poprzednikiem v jest nic
      kol.push ( v );             

      while( !kol.empty() )       // uruchamiamy BFS
      {
        x = kol.front();         
        kol.pop();               

        if( !((x/n)%2==(x%n)%2) )
        {                                           // jesli bialy
          if( powiazane [ x ] == -1 )
          {                                           //  wolny
            while( droga [ x ] > -1 )
            {
              if( !((x/n)%2==(x%n)%2) )
              {                                     // Zamieniamy krawędzie skojarzone z nieskojarzonymi
                powiazane [ x ] = droga [ x ];
                powiazane [ droga [ x ] ] = x;
              }
              x = droga [ x ];                      // cofamy po ścieżce rozszerzającej
            }
            break;                                  // Wracamy do pętli głównej
          }
          else
          {                                             // bialy skojarzony
            droga [ powiazane [ x ] ] = x;
            sprawdzone [powiazane [ x ] ] = true;
            kol.push ( powiazane [ x ] );               // W kolejce umieszczamy skojarzony czarny
          }
        }
        else
        {                                               // czarne
          wskpl = graf [ x ];                           // Przeglądamy biale
          while( wskpl )
          {
            y = wskpl->bije;                            // numer bialego
            if( !sprawdzone [ y ] )                     // nieskojarzone do kolejki
            {                    
              sprawdzone [ y ] = true;
              droga [ y ] = x;                          // ścieżka rozszerzającą
              kol.push ( y );
            }
            wskpl = wskpl->nast;
          }
        }
      }
    }
    
//  for( i = 0; i < nn; i++ )
//    if((i/n)%2==(i%n)%2) cout << i << " - " << powiazane [ i ] << endl;  
    
    x=0;
    for(i = 0 ; i < nn ; i++) if( powiazane[i] > -1) x++;
    cout<<nn-x/2;
    return 0;
}