#include <fstream>
#include <bitset>
#include <math.h>
using namespace std;
ifstream cin("difprim.in");
ofstream cout("difprim.out");
bitset <10000005>ciur;
int main() 
{
    long long i,j,nr1=0,nr2=0,dif=0,a,b,sol=0,aux=0,bux=0, dif_precedenta;
    float radical;
    radical=sqrt(b);
    cin>>a>>b;
    for(i=2; i<=b; i++)
             for (j=i+i;j<=b;j=j+i)
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
