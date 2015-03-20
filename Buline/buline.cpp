#include<fstream>
#include<bitset>
using namespace std;
ifstream f("buline.in");
ofstream g("buline.out");
bool culoare[10005];
long long n, a[10005],i, suma[10001], best[10001], bestSum,x,aux;
int main()
{
    //citire
f>>n;
for (i=1;i<=n;i++)
{   
    f>>a[i];
    f>>x;
    if(x==0)
    a[i]=-a[i];
    a[i+n]=a[i];
}
a[2*n]=0;
 bestSum = a[1];
for (i = 1; i <= 2*n; ++ i) {
    best[i] = a[i];
    if (best[i] < best[i-1] + a[i]) 
        best[i] = best[i-1] + a[i];
    if (bestSum < best[i])
        bestSum = best[i];
}


for(i=2*n;i>=1;i--)
  if(best[i]==bestSum)
     aux=i;
g<<bestSum<<" "<<(aux-n+1);    
return 0;
}
