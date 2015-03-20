#include<fstream>
using namespace std;
ifstream cin("g2.in");
ofstream cout("g2.out");
int v[100], n,u=0,i,j,aux;
int main()
{   int pval;
    cin>>n;
    i=9;
    while(i>1&&n>0)
    {   
        if(n%i==0)   {u++; v[u]=i; n=n/i;}
        else i--;
    }
    for(i=1;i<u;i++)
       for(j=i+1;j<=u;j++)
         if(v[i]>v[j])
          { 
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
          }
    for(i=1;i<=u;i++)
          cout<<v[i];
   // system("pause");
    return 0;
}
