//Divizori Primi
#include<fstream>
using namespace std;
   int t,n,j,i,k,a[1000005],v[1000005][11];  
   int main()
{   
    ifstream f("divprim.in");
    ofstream g("divprim.out");
     f>>t;
     v[1][0]=0;
    for (i=2;i<1000005;i++)      
{ 
      if(a[i]==0)
    for (j=i;j<1000005;j++)
      a[j]++;      
    for(j=0;j<=7;j++)
      v[i][j]=v[i-1][j];
    if(a[i]<=7)
      v[i][a[i]]=i;
}      
    for(i=1;i<=t;t++)
{ 
    f>>n>>k;
    g<<v[n][k]<<"\n";
}
    f.close();
    g.close();
    return 0;
}
