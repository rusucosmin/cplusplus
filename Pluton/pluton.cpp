#include<fstream>
using namespace std;
ifstream cin("pluton.in");
ofstream cout("pluton.out");
long Nr[4001];//Nr[k]=nr de identificare al soldatului k

long NrSort[4001];//NrSort[k]=nr de identificare al soldatului k
	  //avand cifrele asezate in ordine descrescatoare - cu ajutorul
	  //acestui vector se va verifica rapid daca doi soldati i si j fac
	  //parte din acelasi pluton (adica au numerele de identificare
	  //Nr[i] si Nr[j] formate din acelasi cifre, insa in alta ordine)'
long n;    //numarul de soldati
long nrp;  //numarul de plutoane refacute
long max;  //numarul maxim de soldati dintr-un pluton refacut
long nrmax;//numarul de plutoane refacute cu numar maxim de soldati (max)
long ordonare(long x)
{  long aux, c,y;
   aux=x;
   y=0;
   for(c=9;c>=0;c--)
      {
                    while(x)
                     {if(x%10==c)  y=y*10+x%10;
                     x=x/10;}
     x=aux;}
            return y;}         
         
         
         
int main()

{int i;
long max, p, j,bux, aux,pmax;
    cin>>n;
      for ( i=1;i<=n;i++)
      { cin>>Nr[i];
        bux=Nr[i];
        NrSort[i]=ordonare(bux);
        }
    i=1;             //pozitia curenta din vectori Nr si NrSort(soldatul curent i)
 nrp=nrmax=max=0;
 while(i<=n)
 {
  p=i;            //se salveaza pozitia curenta i in variabila p
  j=i+1;          //se cauta soldati j din acelasi pluton cu soldatul curent i
  while(j<=n)     //adica soldati pentru care NrSort[j]=NrSort[i]
  {
   if(NrSort[i]==NrSort[j]) //in cazul in care se gaseste un astfel de soldat
   {                        //acesta este adus langa soldatul curent i
    i++;
    aux=Nr[i]; Nr[i]=Nr[j]; Nr[j]=aux;
    aux=NrSort[i]; NrSort[i]=NrSort[j]; NrSort[j]=aux;
   }
   j++;
  }
  i++;        //s-au adus langa soldatul i toti posibilii sai colegi de pluton
  nrp++;      //deci s-a mai refacut un pluton intre pozitiile p si i-1 din
	      //cei doi vectori Nr si NrSort
  if(i-p>max) //daca numarul de soldati din ultimul pluton refacut (adica i-p)
  {           //este mai mare strict decat max se actualizeaza valorile
   max=i-p;   //variabilelor max si nrmax
   nrmax=1;
   pmax=p;    //pmax retine pozitia la care incepe in vectorul Nr plutonul
  }           //cu numar maxim de soldati
  else
   if(i-p==max) nrmax++; //daca numarul de soldati din ultimul pluton refacut
 }                       //este egal cu max se actualizeaza valoarea lui nrmax
 cout<<nrp<<endl<<max<<endl<<nrmax<<endl;
 for(i=pmax;i<pmax+max;i++) cout<<Nr[i]<<" ";
         
    
    
    return 0;
}
