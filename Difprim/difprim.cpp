#include <fstream>
#include <bitset>
#include <math.h>
using namespace std;
ifstream cin("difprim.in");
ofstream cout("difprim.out");
bitset <10000005>ciur;
int main() 
{
    int i,j,nr1=0,nr2=0,dif=0,a,b,sol=0,aux=0,bux=0, dif_precedenta;
    cin>>a>>b;
    for(i=4;i<=b;i++)
          ciur[i]=1;
    for (i=3;i<=sqrt( b );i+=2)
        if (ciur[j]==0)
           for (j=i*2;j<=b;j+=i)
             ciur[j]=1;
    for(i=a;i<=b;i++)
    { dif_precedenta=aux-bux;
     if(ciur[i]==0)
                 {aux=nr1;
                  bux=aux-dif_precedenta;
                  nr2=nr1;
                  nr1=i;
                  dif=nr1-nr2;
                  sol=1;}
     if(dif_precedenta>dif)
                  {nr1=aux;
                  nr2=bux;}
}                               
    if(sol==0) cout<<-1<<"\n";
    else cout<<nr1<<" "<<nr2<<"\n";      
    cin.close();
    cout.close();
    return 0;
}
