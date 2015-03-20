#include <fstream>
using namespace std;
int main()
{   int n, k, xjos[100], yjos[100], xsus[100],ysus[100], log, i, t, j, aux;
    ifstream in("dreptunghiuri4.in");
    ofstream out("dreptunghiuri4.out");
    in>>n;
    in>>k;
    for(i=1;i<=n;i++)
     {in>>xjos[i];
      in>>yjos[i];
      in>>xsus[i];
      in>>ysus[i];}
         
while (log!=0);
{
log=0;
for (j=0;k<n-1;k++)
if (xjos[k]>xjos[k+1])
{
aux=xjos[k+1];
xjos[k+1]=xjos[k];
xjos[k]=aux;
log=1;
}
}

for(i=1;i<=n;i++)
out<<xjos[i];

/*do
{
log=0;
for (j=0;k<n-1;k++)
if (xsus[k]>xsus[k+1])
{
aux=xsus[k+1];
xsus[k+1]=xsus[k];
xsus[k]=aux;
log=1;
}
}
while (log==0);
for(i=1;i<=n;i++)
out<<yjos[i];*/
return 0;
}
