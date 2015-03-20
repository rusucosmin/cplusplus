#include <fstream>
using namespace std;
ifstream cin("buline.in");
ofstream cout("buline.out");
unsigned long  a[200005],s,smax=0,PozitiabarajosInitiala,PozitiabarajosFinala,pozitia,n,i,j,k,sum;
int max(int unu,int doi)
{
    if(unu>doi)
    return unu;
    else 
    return doi;
    }
int main ()
{
    cin>>n;
    for(i=1;i<=n;i++)
    cin>>a[i];
s = smax = 0;
for(i = 1;i<=n;i++) 
{
s = max(s+a[i], a[i]);
smax = max(smax, s);
}

cout<<smax<<" "<<i<<" "<<i+n-1;
return 0;
}
