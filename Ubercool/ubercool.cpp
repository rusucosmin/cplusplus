#include<fstream>
#define rad 1000000000
using namespace std;
ifstream cin("pietre2.in");
ofstream cout("pietre2.out");
int t, ciur[100000005];
long long x;
void ciu()   //0=prim 1=neprim
{
     for(int i=2;i<=rad;i++)
             for(int j=i+i;j<=rad;j+=i)
                 ciur[j]=1;
     } 
int desc(int a)
{
     int i=2;
     bool ok=0;
     while(a>=0)
{     while(ciur[i]==0 && a/i==0)
     {                  
               a=a/i;
               ok=1;                
     }
     i++;
     if(ok=1)
     { cout<<"NU"; return 0;}
     }
     
}
int main()
{
    cin>>t; //numarul de teste
    ciu();
    for(int i=1;i<=t;i++)
    {
            cin>>x;
            desc(x);
            }
    return 0;    
}
