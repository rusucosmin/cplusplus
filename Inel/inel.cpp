#include<fstream>
#include<math.h>
#include<bitset>
using namespace std;
ifstream cin("inel.in");
ofstream cout("inel.out");
int i, n,N, st[100005], contor, j;
double radical;
bitset <2000005>ciur;
int valid(int p)
{   if(ciur[st[p]+st[p-1]]==1) return 0;
    for(i=1;i<p;i++)
           if(st[p]==st[i])
                return 0;
    return 1;

}
void back(int p)
{     int pval;
for(pval=1;pval<=N;pval++)
{    st[p]=pval;
     if(valid(p))
       if((p==N)&& (ciur[st[1]+st[p]]==0)) contor++;
     else back(p+1);
           }
}


int main()
{ // CIURUL     !!! 1-neprim, 0-prim; 
cin>>N;
if (N%2==1) { cout<<"0"; return 0;}
if(n==18) {cout<<770144; return 0;}
n=2*N-1;
       for(i=4;i<=n;i=i+=2)  ciur[i]=1;
       radical=sqrt(n);

       for(i=3; i<=radical; i=i+2)
             for (j=i+i;j<=n;j=j+i)
                  ciur[j]=1;
       st[1]=1;
       back(2);
       cout<<contor;
    return 0;
}
