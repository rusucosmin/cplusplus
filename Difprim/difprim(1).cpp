#include <fstream>
#include <bitset>
#include <math.h>
using namespace std;
ifstream fin("difprim.in");
ofstream fout("difprim.out");
bitset <10000005>ciur ; 
int v[1000005];
long int u,i,j;
int main() 
{
    int nr1=0,nr2=0,dif=0,a,b,sol=0,aux=0,bux=0, dif_precedenta,min=0;
    double radical;
    fin>>a>>b;
    radical=sqrt(b);
    for(i=4;i<=b;i+=2)
       ciur[i]=1;
    for (i=3;i<=radical;i+=2)
        if (ciur[i]==0)
           for (j=i*2;j<=b;j+=i)
             ciur[j]=1;
             
             
     for (i=a+1;i<=b-1;i++)
       if (ciur[i]==0)
       {u++;
                       v[u]=i;}
for (i=1;i<=u-1;i++)
if (v[i+1]-v[i]>min)
{
min=v[i+1]-v[i];
nr1=v[i];
nr2=v[i+1];
}
if(min==0)
fout<<"-1";
else
fout<<nr1<<" "<<nr2<<"\n";     
    fin.close();
    fout.close();
    return 0;
}
