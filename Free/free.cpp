//#include<iostream> //  free
#include<fstream>
#include<math.h>
using namespace std;
ifstream cin("free.in");
ofstream cout("free.out");
int s[100], i, j, n, contor=0, contor2=0,k;
int divizori(int i)
{
    if(i==1) return 1;
   // if(i==2||i==3) return 2;
    contor=2;
    k=2;
    while (k<=i/2)
         {if (i%k==0) contor++;
           else k++;}
   return contor;
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
       if(divizori(i)%2!=0)
          contor2++;
cout<<n-contor2;
//system("pause");
return 0;
}
