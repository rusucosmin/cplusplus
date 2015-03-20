#include<fstream>
#include<limits.h>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;
ifstream cin("petrecere2.in");
ofstream cout("petrecere2.out");
struct relatie
{   long secund, prim;
}   a[100000];
struct relatie2
{   long secund, prim;
}   b[100000];
bool t[100000];
long m, n,i,j,contor;
int main()
{
    
    cin>>n>>m;
    for(i=1;i<=m;i++)
    {
      cin>>t[i];
      if(t[i]==1) {cin>>a[i].prim>>a[i].secund; contor++;}
      else cin>>b[i].prim>>b[i].secund;     
      }
    
    for(i=1;i<=m;i++)
       for(j=1;j<=m;j++)
          if(a[i].prim==b[j].prim||a[i].prim==b[j].secund||a[i].secund==b[j].prim||a[i].secund==b[j].secund)
             { contor++; //cout<<a[i].prim<<a[i].secund<<b[i].prim<<b[i].secund;
             }
       cout<<contor;
     
      
    
    return 0;
}
