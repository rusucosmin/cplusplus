#include<fstream>
#include<mem.h>
#include<stdio.h>
using namespace std;
ifstream cin("recurenta.in");
ofstream cout("recurenta.out");

void Add(Huge A, Huge B)
/* A <- A+B */
{ int i,T=0;

  if (B[0]>A[0])
    { for (i=A[0]+1;i<=B[0];) A[i++]=0;
      A[0]=B[0];
    }
    else for (i=B[0]+1;i<=A[0];) B[i++]=0;
  for (i=1;i<=A[0];i++)
    { A[i]+=B[i]+T;
      T=A[i]/10;
      A[i]%=10;
    }
  if (T) A[++A[0]]=T;
}



long long n, k, a[10006], i, s=0, j;
int main()
{
 cin>>n;
 cin>>k;
 for(i=0;i<=n;i++)
    if(i<k)      a[i]=1;
    else {  for(j=1;j<=k;j++)
            Add(a[i], a[j]);}
 cout<<a[n]<<" ";
 return 0;   
}
