#include<fstream>
#include<math.h>
using namespace std;
ifstream cin("triplet.in");
ofstream cout("triplet.out");
long long n, pp[200000005], i, j, li, ls, mij ;
int cautbin1(int x)
{
    li=1; ls=n;
    while(li<ls)
    { mij=(li+ls)/2;
      if(pp[mij]==x) return 1;
      else if(pp[mij]>x) ls=mij-1;
      else li=mij+1;}
    return 0;
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
       {pp[i]=i*i; //cout<<pp[i]<<" ";}
       }
   for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
            if(cautbin1(n-pp[i]-pp[j]))
            { cout<<i<<" "<<j<<" "<<mij;    return 0; }
}
       
