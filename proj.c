//Prêdkoœæ 4800   Liczba bitów miêdzy bajtami: 2
//Polecenie SET - ‘SET00.00.01’ bez spacji pomiêdzy i bez enetra na koñcu
//GET z enterem
//EDIT z enterem
// Klawiatura multipleksowana/matrycowa dzia³a i obs³uguje tylko jeden klawisz jednoczeœnie
// przechowywane 7 ostatnich rozkasów
//wszystkie zadania wykonane




#include <8051.h>

__bit __at(0xB5) kbt1;//p3.5
__sbit __at (0x96) seg;
__sbit __at (0XB5) T1;


__bit recflag=0; // flaga odebrania znaku
__bit sendflag=0; // dane gotowe do transmisji
__bit migflag=0;
__bit edycja=0;
__bit nieodsw=1;
__bit niezmienia=0;
__bit pomock=0;
__bit pom3 = 0;
unsigned char ile=0;
unsigned char indeks = 0,ktoryedytowany=0;
unsigned int licznik=0; 
unsigned char wyswietlana =0;
unsigned char indeks1=0;
short int x=0;
unsigned char znaki_odebrane[15];
unsigned char licznik2=0;
unsigned char licznik3=0;
unsigned char zapiszhistorie; //NOWO DODANA ZA MALO PAMIECI ALE WYMAGANA DO POWROTU BY PONOWNIE WPISYWAC
unsigned char key;//stan klawiatury


short int lcdindeks=0;
unsigned char errindeks=0;

__code unsigned char Cyfry[10]= {0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111};
__data unsigned char trybedycji[6] = {0,0,0,0,0,0};//hhmmss     //równie¿ do wyslania aktualnego czasu
__data unsigned char liczbystartowe[6] = {0,0,0,0,0,0};//hhmmss

unsigned char klawmultiplekss=0;
unsigned char y=0;
__xdata unsigned char* buf_CSDB = (__xdata unsigned char*) 0xff38;
__xdata unsigned char* buf_CSDS = (__xdata unsigned char*) 0xFF30;

__xdata unsigned char * buf_CSKB1 = (__xdata unsigned char*) 0xff22;

__xdata unsigned char* LCDWC = (__xdata unsigned char*) 0xff80;
__xdata unsigned char* LCDWD = (__xdata unsigned char*) 0xff81;
__xdata unsigned char* LCDRC = (__xdata unsigned char*) 0xFF82;

unsigned char i=0;

__bit t0_flag1=0 ;//flag 1 do migania w trybie edycji


__xdata unsigned char* historia = (__xdata unsigned char*) 0x4000;



unsigned char indeksh=0;
unsigned char ilerozkazow=0;
unsigned char histpom=0;
void wypiszh();



void przesun();
unsigned char a=0,b=0;

void sio_int(void) __interrupt(4);
void rec();
void send();
void GET();
void SET();
void zerowanieodbioru();
void _KB();

void poczekaj();
void LCDGET();
void LCDEDIT();
void LCDSET();
void LCDERR();


void _7SEG_REFRESH()
{ 

indeks=0b00000001;
wyswietlana = 0;


	niezmienia=0;
	while(indeks!=0b01000000)
	{

 	if(edycja&&migflag==0) {   //sekundy  TRYB EDYCJi
  if((wyswietlana==0||wyswietlana==1)&&ktoryedytowany==0){
	    	indeks=0b00000100 ;
		wyswietlana=2;   }
  if((wyswietlana==2||wyswietlana==3)&&ktoryedytowany==1) {
indeks=0b00010000  ;
wyswietlana=4;   }
  if((wyswietlana==4||wyswietlana==5)&&ktoryedytowany==2)
	    	break;




		  }
		      //podstawowe wyœwietlanie
                 seg = 1;  //wy³¹cz
		*buf_CSDS = indeks;
		*buf_CSDB = Cyfry[liczbystartowe[wyswietlana]];
	//	if(liczbystartowe[wyswietlana]==10)
	//BUZZER=0;
                seg = 0; //w³¹cz
	     // y=0;
	// while(y<5)
	 // y++;

            	wyswietlana++;

            	indeks = indeks << 1;
		
            	//seg = 0;  //w³¹cz
        }
            seg = 1;  //wy³¹cz
            niezmienia=1;
             

	 }


 void t0_int(void) __interrupt(1) // musi byæ 120-300 na sekunde
{
	licznik++ ;
//	if(licznik==800)
        //  migflag^=1;
	if(licznik == 1200)  {
	  licznik = 0;
           migflag^=1;


	t0_flag1 = 1;             }
           TH0 = 253;
         //  if(edycja==0)
         if(nieodsw)
	  _7SEG_REFRESH();//odœwierzanie tutaj

}



void INIT()
{
zapiszhistorie=(unsigned char)historia ;
TMOD=0b00100001;//T1 off, T0-16bit
TR0=1;
TL0=0b00000000;
TH0 = 253;//pocz¹tkowa wartoœæ licznika
TF0 = 0;

ET0 = 1;


//t1
SCON=0b01010000;
TMOD&=0b00101111;
TMOD|=0b00100000;
TL1=0xFA;
TH1=0xFA;
PCON&=0b01111111;
TR1=1;  //zgoda na zliczanie przez T1
TF1 = 0;  // po przepe³nieniu ustawia 1(flaga)


ES=1;
EA=1;


//LCD

poczekaj();

*LCDWC = 0b00000110;//3

poczekaj();
*LCDWC = 0b00111011; //6

poczekaj();
*LCDWC = 0b00001111;//4
poczekaj();

*LCDWC = 0b00010100; //5
poczekaj();


*LCDWC = 0b00000001;    //clear
poczekaj();





}

void TIME()
{

	if (liczbystartowe[0]==9)          // jeœli 1 zanak sek przeskakuje na 10 to
	{
	liczbystartowe[0]=0;          //zmieñ go na zero      kk

	if(liczbystartowe[1]+1==6)            //i jeœli w tym czasie przeskakuje 2gi znak sek to zmieñ go na zero kk
	{
		liczbystartowe[1]=0;

        if (liczbystartowe[2]+1==10)          // jeœli 1 zanak min przeskakuje na 10 to
	{
		liczbystartowe[2]=0;          //zmieñ go na zero

	if(liczbystartowe[3]+1==6)            //i jeœli w tym czasie przeskakuje 2gi znak min to zmieñ go na zero
	{
		liczbystartowe[3]=0;
		

	if((liczbystartowe[4]+1==4) &&( liczbystartowe[5]==2))//jeœli przeskakuje na 24 to godzina = 00
	{
          liczbystartowe[4]=0 ;
          liczbystartowe[5]=0 ;
	}
	else                  //jeœli nie to


	if (liczbystartowe[4]+1==10)          // jeœli 1 zanak godz przeskakuje na 10 to jeœli przeskakuje na 4 to sprawdz czy nie ma 23
	{
		liczbystartowe[4]=0;          //zmieñ go na zero
	        liczbystartowe[5]++;           //oraz zwiêksz 2gi znak godziny
 	}

	else
	liczbystartowe[4]++;         //gdy przeskakuje pierwszy znak godz bez przepe³nienia



	}
	else     // gdy przeskakuje 2gi znak sek   bez przepe³nienia
	liczbystartowe[3]++;


	}
	else
	liczbystartowe[2]++;         //gdy przeskakuje pierwszy znak sek bez przepe³nienia


	}
	else     // gdy przeskakuje 2gi znak sek   bez przepe³nienia
	liczbystartowe[1]++;

 }
	else                                                                     // kk
	liczbystartowe[0]++;         //gdy przeskakuje pierwszy znak sek bez przepe³nienia

}



void OBSLUGA()
{
edycja=1;      //flagatrybuedycji
trybedycji[0]=liczbystartowe[0]; //zapisanie wartoœci
trybedycji[1]=liczbystartowe[1];
trybedycji[2]=liczbystartowe[2];
trybedycji[3]=liczbystartowe[3];
trybedycji[4]=liczbystartowe[4];
trybedycji[5]=liczbystartowe[5];
ktoryedytowany=0;


 

while(1)  //trybedycjiu
{


	nieodsw=1;
y=0;
while(y<30)
y++;
nieodsw=0;


indeks1=0b00000001;
i = 0;


while(i!=6)
	{


if(niezmienia){
*buf_CSDS = indeks1;

if(klawmultiplekss!=0b00000000) //jeœli cos jest klikniête sprawdzamy czy zosta³o odklikniête
{
if((klawmultiplekss&0b00000001)==(indeks1)&&kbt1==0)//odklikniêty enter
klawmultiplekss&=   0b11111110;




if((klawmultiplekss&0b00000010)==(indeks1)&&kbt1==0)//odklikniêty  esc
klawmultiplekss&=   0b11111101;


if((klawmultiplekss&0b00000100)==(indeks1)&&kbt1==0)//odklikniêty   prawo
klawmultiplekss&=   0b11111011;



if((klawmultiplekss&0b00001000)==(indeks1)&&kbt1==0)//odklikniêty   góra
klawmultiplekss&=   0b11110111;



if((klawmultiplekss&0b00010000)==(indeks1)&&kbt1==0)//odklikniêty  dp;
klawmultiplekss&=   0b11101111;



if((klawmultiplekss&0b00100000)==(indeks1)&&kbt1==0)//odklikniêty   lewo
klawmultiplekss&=   0b11011111;
//nieodsw=1;
}

 else//jeœli ==0 to nic nie jest wciœniête i mo¿emy coœ przycisn¹æ
{   //nieodsw=1;

if(indeks1==    0b00000001&&kbt1==1){  //wciœniêty  enter
klawmultiplekss=0b00000001;
        
//enter wznawia prace na edytowanych wartoœciach
TL0 = 0;
TH0 = 253;
licznik = 0;
edycja=0;
nieodsw=1;
t0_flag1 = 0;
goto wyjdz;
 // break;

 }

if(indeks1==    0b00000010&&kbt1==1){  //wciœniêty  ESC
klawmultiplekss=0b00000010;



liczbystartowe[0]=trybedycji[0]; //wczytanie poprzednich
liczbystartowe[1]=trybedycji[1];
liczbystartowe[2]=trybedycji[2];
liczbystartowe[3]=trybedycji[3];
liczbystartowe[4]=trybedycji[4];
liczbystartowe[5]=trybedycji[5];

        
TH0 = 253;
TL0 = 0;
licznik = 0;
nieodsw=1;
edycja=0;

t0_flag1 = 0;
goto wyjdz;
// break;
}




if(indeks1==    0b00000100&&kbt1==1){  //wciœniêty    PRAWO
klawmultiplekss=0b00000100;



if(ktoryedytowany!=0)
ktoryedytowany--;
        }



if(indeks1==    0b00001000&&kbt1==1){  //wciœniêty     GÓRA
klawmultiplekss=0b00001000;
y=100;
while(y!=0)
y--;
if (ktoryedytowany == 1)
goto minuty;
if (ktoryedytowany == 2)
goto godziny;
if (ktoryedytowany == 0)//to sekundy
{


	if (liczbystartowe[0] + 1 == 10)          // jeœli 1 zanak sek przeskakuje na 10 to
	{     //BUZZER=0;

		liczbystartowe[0] = 0;          //zmieñ go na zero      kk

		if (liczbystartowe[1] + 1 == 6)            //i jeœli w tym czasie przeskakuje 2gi znak sek to zmieñ go na zero kk
		{
			liczbystartowe[1] = 0;
		minuty:
			if (liczbystartowe[2] + 1 == 10)          // jeœli 1 zanak min przeskakuje na 10 to
			{
				liczbystartowe[2] = 0;          //zmieñ go na zero

				if (liczbystartowe[3] + 1 == 6)            //i jeœli w tym czasie przeskakuje 2gi znak min to zmieñ go na zero
				{
					liczbystartowe[3] = 0;

				godziny:
					if ((liczbystartowe[4] + 1 == 4) && (liczbystartowe[5] == 2))//jeœli przeskakuje na 24 to godzina = 00
					{
						liczbystartowe[4] = 0;
						liczbystartowe[5] = 0;
					}
					else                  //jeœli nie to


						if (liczbystartowe[4] + 1 == 10)          // jeœli 1 zanak godz przeskakuje na 10 to jeœli przeskakuje na 4 to sprawdz czy nie ma 23
						{
							liczbystartowe[4] = 0;          //zmieñ go na zero
							liczbystartowe[5]++;           //oraz zwiêksz 2gi znak godziny
						}

						else
							liczbystartowe[4]++;         //gdy przeskakuje pierwszy znak godz bez przepe³nienia



				}
				else     // gdy przeskakuje 2gi znak sek   bez przepe³nienia
					liczbystartowe[3]++;


			}
			else
				liczbystartowe[2]++;         //gdy przeskakuje pierwszy znak sek bez przepe³nienia


		}
		else     // gdy przeskakuje 2gi znak sek   bez przepe³nienia
			liczbystartowe[1]++;

	}
	else                                                                     // kk
		liczbystartowe[0]++;         //gdy przeskakuje pierwszy znak sek bez przepe³nienia
}



    //nieodsw=1;


        }


if(indeks1==    0b00010000&&kbt1==1){  //wciœniêty     DÓ£
klawmultiplekss=0b00010000;
y=100;
while(y!=0)
y--;
if (ktoryedytowany == 1)
goto minutydol;
if (ktoryedytowany == 2)
goto godzinydol;
if (ktoryedytowany == 0)//to sekundy
{


	if (liczbystartowe[0] == 0)          // jeœli 1 zanak sek przeskakuje na 10 to
	{
		liczbystartowe[0] = 9;          //zmieñ go na zero      kk

		if (liczbystartowe[1] == 0)            //i jeœli w tym czasie przeskakuje 2gi znak sek to zmieñ go na zero kk
		{
			liczbystartowe[1] = 5;
		minutydol:
			if (liczbystartowe[2] == 0)          // jeœli 1 zanak min przeskakuje na 10 to
			{
				liczbystartowe[2] = 9;          //zmieñ go na zero

				if (liczbystartowe[3] == 0)            //i jeœli w tym czasie przeskakuje 2gi znak min to zmieñ go na zero
				{
					liczbystartowe[3] = 5;

				godzinydol:
					if ((liczbystartowe[4] == 0) && (liczbystartowe[5] == 0))//jeœli przeskakuje na 24 to godzina = 00
					{
						liczbystartowe[4] = 3;
						liczbystartowe[5] = 2;
					}
					else                  //jeœli nie to


						if (liczbystartowe[4] == 0)          // jeœli 1 zanak godz przeskakuje na 10 to jeœli przeskakuje na 4 to sprawdz czy nie ma 23
						{
							liczbystartowe[4] = 9;          //zmieñ go na zero
							liczbystartowe[5]--;           //oraz zwiêksz 2gi znak godziny
						}

						else
							liczbystartowe[4]--;         //gdy przeskakuje pierwszy znak godz bez przepe³nienia



				}
				else     // gdy przeskakuje 2gi znak sek   bez przepe³nienia
					liczbystartowe[3]--;


			}
			else
				liczbystartowe[2]--;         //gdy przeskakuje pierwszy znak sek bez przepe³nienia


		}
		else     // gdy przeskakuje 2gi znak sek   bez przepe³nienia
			liczbystartowe[1]--;

	}
	else                                                                     // kk
		liczbystartowe[0]--;         //gdy przeskakuje pierwszy znak sek bez przepe³nienia
}

   //nieodsw=1;

          }




if(indeks1==    0b00100000&&kbt1==1){  //wciœniêty       LEWO
klawmultiplekss=0b00100000;
          
if(ktoryedytowany!=2)// bo maj¹ po 2 wyœwietlacze sie edytowaæ sekundyx2 min x2 h x2
ktoryedytowany++;
 }



//nieodsw=1;
}


indeks1 = indeks1 << 1;
i++;
 }
//nieodsw=1;

}
}
wyjdz:
}  //koniec tr edycji-obsluga





void KLAW_MULT()// badanie lewo prawo czy wejsc w tryb edycji
{
indeks1=0b00000001;
 i = 0;

while(i!=6)
	{

*buf_CSDS = indeks1;

if(klawmultiplekss==0);
if((indeks1==0b00000100||indeks1==0b00100000)&&kbt1==1)//klikniêty   LEWO  LUB PRAWO TO TRYB EDYCJI   //czyli edycja ale zapamietujemy co wcisniete
{
klawmultiplekss=indeks1;


OBSLUGA();
 }


indeks1 = indeks1 << 1;
i++;

}



}


void main()
{
	
INIT();
zerowanieodbioru();
	
	
while(1)
{

 	GET();
	SET();

 if(recflag){
  recflag=0;
  rec();
  }

 if(sendflag)
  send();
   if(t0_flag1)
{   t0_flag1=0;
if(licznik3!=0){
ile++;
 	       if(ile%2==0)
 		{
			LCDERR();
		zerowanieodbioru();
	//

		}   }

TIME();

}


_KB();

KLAW_MULT();
}//koniec while


}
   //tr szer nizej


 void sio_int(void) __interrupt(4)
{
if (TI)   {  //jeœli odebrano
TI = 0;  //zerowanie flagi wysy³ania

	  }
else   {
RI =0;      //zerowanie flagi odbioru
recflag =1 ;   //ustawienie flagi odebrania
	}
}

void send()
{
if(TI)
return;
   x=1;
   while(x!=301)
   x++;

sendflag=0;
SBUF=znaki_odebrane[licznik2];

licznik2++;

	if(licznik2==8)
	{
	zerowanieodbioru();
 licznik2=0;
	}
}

void rec()
{

 ile++;
znaki_odebrane[licznik3]=SBUF;


licznik3++;
 	if(licznik3==12){  //zmien na 11 dla obslugi bledow

       LCDERR();

       zerowanieodbioru();
	}
	if(znaki_odebrane[0]=='E'&&znaki_odebrane[1]=='D'&&znaki_odebrane[2]=='I'&&znaki_odebrane[3]=='T'&&znaki_odebrane[4]==13&&znaki_odebrane[5]==10){
	LCDEDIT();
	OBSLUGA();
	zerowanieodbioru();
	}

}

void GET()
{
if(pomock==0&&znaki_odebrane[0]=='G'&&znaki_odebrane[1]=='E'&&znaki_odebrane[2]=='T'&&znaki_odebrane[3]==13&&znaki_odebrane[4]==10)
{
	znaki_odebrane[7]=liczbystartowe[0]+48;
	znaki_odebrane[6]=liczbystartowe[1]+48;
	znaki_odebrane[5]='.';
	znaki_odebrane[4]=liczbystartowe[2]+48;
	znaki_odebrane[3]=liczbystartowe[3]+48;
	znaki_odebrane[2]='.';
	znaki_odebrane[1]=liczbystartowe[4]+48;
	znaki_odebrane[0]=liczbystartowe[5]+48;
pomock=1;
LCDGET();

}
if(pomock)
sendflag=1;



}

void SET()
{

if(znaki_odebrane[0]=='S'&&znaki_odebrane[1]=='E'&&znaki_odebrane[2]=='T'
&&znaki_odebrane[3]-48>=0&&znaki_odebrane[3]-48<=2
&&znaki_odebrane[4]-48>=0&&znaki_odebrane[4]-48<=9
&&znaki_odebrane[5]=='.'
&&znaki_odebrane[6]-48>=0&&znaki_odebrane[6]-48<=5
&&znaki_odebrane[7]-48>=0&&znaki_odebrane[7]-48<=9
&&znaki_odebrane[8]=='.'
&&znaki_odebrane[9]-48>=0&&znaki_odebrane[9]-48<=5
&&znaki_odebrane[10]-48>=0&&znaki_odebrane[10]-48<=9 ){

liczbystartowe[5]=(znaki_odebrane[3]-48);
liczbystartowe[4]=(znaki_odebrane[4]-48);

liczbystartowe[3]=(znaki_odebrane[6]-48);
liczbystartowe[2]=(znaki_odebrane[7]-48);

liczbystartowe[1]=(znaki_odebrane[9]-48);
liczbystartowe[0]=(znaki_odebrane[10]-48);
//
LCDSET();
zerowanieodbioru();

TH0 = 253;
TL0 = 0;
licznik = 0;
nieodsw=1;


t0_flag1 = 0;
}
}
void zerowanieodbioru()
{
	znaki_odebrane[0]='-';
	znaki_odebrane[1]='-';
	znaki_odebrane[2]='-';
	znaki_odebrane[3]='-';
	znaki_odebrane[4]='-';
	znaki_odebrane[5]='-';
	znaki_odebrane[6]='-';
	znaki_odebrane[8]='-';
	znaki_odebrane[7]='-';
	znaki_odebrane[9]='-';
	znaki_odebrane[10]='-';
	znaki_odebrane[11]='-';
	znaki_odebrane[12]='-';

	ile=0;
	licznik3=0;


	licznik2=0;
	pomock=0;

}


 void _KB()
  {
   
 if(*buf_CSKB1!=key)
   pom3=0;

 key=*buf_CSKB1; //wczytujemy co jest wciœniête

if(key==0b01111111&&pom3==0)// F  bit7   ENTER
  {

    pom3=1;

   }

 if(key==0b10111111&&pom3==0)// E  bit 6 ESC
  {

    pom3=1;

   }
else
   if(key==0b11011111&&pom3==0)// dó³ bit 5
  {
    if(indeksh<ilerozkazow-1)//górny ogranicznik iloœci rozkazów
    { indeksh++;
    wypiszh();
  }


    pom3=1;

   }
 else
   if(key==0b11101111&&pom3==0)//   góra dbit 4
  {
    pom3=1;

       if(indeksh!=0)//dolny ogranicznik rozkazów
 { indeksh--;
    wypiszh();
  }
  }
   
 else
   if(key==0b11110111&&pom3==0)//   prawo  bit 3
  {


    pom3=1;
   }
 else
   if(key==0b11111011&&pom3==0)// lewo   bit 2
  {
  	

    pom3=1;
   }

}



void poczekaj(){

while((*LCDRC&0b10000000)==0b10000000)//LCDRC.7
;
}   


void LCDGET()
{
poczekaj();
*LCDWD = 'G'; //1
poczekaj();
*historia='G';
historia++;

*LCDWD = 'E';  //2
poczekaj();
*historia='E';
historia++;

*LCDWD = 'T';    //3
poczekaj();
*historia='T';
historia++;

*LCDWD = ' '; //4
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //5
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //6
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //7
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //8
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //9
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //10
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //11
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //12
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //13
poczekaj();
*historia=' ';
historia++;

*LCDWD = 'O'; //14
poczekaj();
*historia='O';
historia++;

*LCDWD = 'K'; //15
poczekaj();
*historia='K';
historia++;

*LCDWD = ' '; //16
poczekaj();
*historia=' ';
historia++;

przesun();
lcdindeks=0;
poczekaj();
while(lcdindeks!=24 ){
lcdindeks++;
*LCDWD = ' '; //16
poczekaj();
}
if(ilerozkazow<7)
ilerozkazow++;
indeksh=0;

}


void LCDEDIT()
{//indeksh=0;
poczekaj();
*LCDWD = 'E'; //1
poczekaj();

*historia='E';
historia++;

*LCDWD = 'D';  //2
poczekaj();

*historia='D';
historia++;

*LCDWD = 'I';    //3
poczekaj();
*historia='I';
historia++;

*LCDWD = 'T'; //4
poczekaj();
*historia='T';
historia++;
*LCDWD = ' '; //5
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //6
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //7
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //8
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //9
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //10
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //11
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //12
poczekaj();
*historia=' ';
historia++;

*LCDWD = ' '; //13
poczekaj();
*historia=' ';
historia++;

*LCDWD = 'O'; //14
poczekaj();
*historia='O';
historia++;
*LCDWD = 'K'; //15
poczekaj();
*historia='K';
historia++;
*LCDWD = ' '; //16
poczekaj();
*historia=' ';
historia++;

 przesun();
lcdindeks=0;
poczekaj();
while(lcdindeks!=24 ){
lcdindeks++;
*LCDWD = ' '; //16
poczekaj();
}
if(ilerozkazow<7)
ilerozkazow++;
indeksh=0;
//indeksh=ilerozkazow-1;
}


void LCDSET()
{
//	indeksh=0;
poczekaj();
*LCDWD = 'S'; //1
poczekaj();

*historia='S';
historia++;

*LCDWD = 'E';  //2
poczekaj();

*historia='E';
historia++;

*LCDWD = 'T';    //3
poczekaj();


*historia='T';
historia++;





*LCDWD = znaki_odebrane[3]; //4
poczekaj();

*historia=znaki_odebrane[3];
historia++;


*LCDWD = znaki_odebrane[4]; //5
poczekaj();

*historia=znaki_odebrane[4];
historia++;

*LCDWD = '.'; //6
poczekaj();

*historia='.';
historia++;

*LCDWD =znaki_odebrane[6];
poczekaj();

*historia=znaki_odebrane[6];
historia++;

*LCDWD = znaki_odebrane[7]; //8
poczekaj();

*historia=znaki_odebrane[7];
historia++;

*LCDWD = '.'; //9
poczekaj();

*historia='.';
historia++;


*LCDWD = znaki_odebrane[9]; //10
poczekaj();

*historia=znaki_odebrane[9];
historia++;


*LCDWD = znaki_odebrane[10]; //11
poczekaj();
*historia=znaki_odebrane[10];
historia++;


*LCDWD = ' '; //12
poczekaj();

*historia=' ';
historia++;


*LCDWD = ' '; //13
poczekaj();

*historia=' ';
historia++;

*LCDWD = 'O'; //14
poczekaj();
*historia='O';
historia++;

*LCDWD = 'K'; //15
poczekaj();
*historia='K';
historia++;

*LCDWD = ' '; //16
*historia=' ';
historia++;
poczekaj();

przesun();

lcdindeks=0;
poczekaj();
while(lcdindeks!=24 ){
lcdindeks++;
*LCDWD = ' '; //16
poczekaj();
}
if(ilerozkazow<7)
ilerozkazow++;
indeksh=0;
//indeksh=ilerozkazow-1;
}

void LCDERR()
{// indeksh=0;
historia=(__xdata unsigned char*) zapiszhistorie;
errindeks=0;
indeksh=0;//przeniesienie tego nic nie zmienilo
if(ilerozkazow<7)
ilerozkazow++;
poczekaj();
while(znaki_odebrane[errindeks]!='-')
{
*historia=znaki_odebrane[errindeks];
historia++;
*LCDWD = znaki_odebrane[errindeks];  //2
poczekaj();
errindeks++;
}
while(errindeks!=13){
*historia=' ';
historia++;
*LCDWD = ' '; //14
poczekaj();
errindeks++;
}
*historia='E';
historia++;

*historia='R';
historia++;

*historia='R';
historia++;      //ustawia na kolejnym

*LCDWD = 'E'; //14
poczekaj();
*LCDWD = 'R'; //15
poczekaj();
*LCDWD = 'R'; //16
poczekaj();

//
   przesun();
  //
lcdindeks=0;
while(lcdindeks!=24 ){
lcdindeks++;
*LCDWD = ' '; //16
poczekaj();
}
if(ilerozkazow<7)
ilerozkazow++;
zapiszhistorie=(unsigned char)historia;

}

void wypiszh()
{
//histpom=(unsigned char)historia;
//historia-=16;
historia=(__xdata unsigned char*)0x4010;
historia+=(indeksh*16);
histpom=(unsigned char)(historia+16);
//historia-=16;
while((unsigned char)historia!=histpom)
{
poczekaj();
*LCDWD = *historia;

historia++;
}

lcdindeks=0;
while(lcdindeks!=24 ){
lcdindeks++;
poczekaj();
*LCDWD = ' '; //16
 }
//historia--;
//if(historia)
//poczekaj();
//*LCDWD = 'R'; //16
historia++; //niezbedne ustawienie na pierwszym wolnym

}
void przesun()
{

b=9;
historia=(__xdata unsigned char*)0x4080 ;

while(b--)
{  a=16;
	while(a--)
	{
	*(historia+16)=*historia;
	historia++;

	}
historia-=32;

}
historia+=16;
//if(historia==(__xdata unsigned char*)0x4000)
//BUZZER=0;
}

