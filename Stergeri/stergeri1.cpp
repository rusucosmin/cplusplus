#include <fstream>
using namespace std;
int n,m,k,i,a1[100010],a2[100010];
int main()
{ 
ifstream f("stergeri.in");
ofstream g("stergeri.out");
f>>n>>m>>k;
for(i=1;i<=m;i++)
f>>a1[i]>>a2[i];
for (i=m;i>=1;i--)
if (k>=a1[i])
k=k+a2[i]-a1[i]+1;
g<<k<<'\n'; 
f.close();
g.close();
return 0;

}
