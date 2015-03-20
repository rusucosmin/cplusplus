#include<fstream>
using namespace std;
ifstream cin("euro2.in");
ofstream cout("euro2.out");
int p, n, i,j, maxim, l[100005],maxim2, urm[100005],poz;
float sir[100005],maxi;
int main()
{   
     cin>>n;
     for(i=1;i<=n;i++)
     cin>>sir[i];
     maxi=sir[1];
     for(i=1;i<=n;i++)
       if(sir[i]>=maxi)
          {poz=i;
          maxi=sir[i];}     
     maxim=1;
     urm[poz]=-1;
     l[poz]=1; p=n;
     for(i=poz;i>=1;i--)
       { urm[i]=-1;
         l[i]=1;
       for(j=poz;j>i;j--)
          if(sir[i]<sir[j] && l[i]<l[j]+1)
             { l[i]=l[j]+1;
               urm[i]=j;
               if(l[i]>maxim)
                 maxim=l[i], p=i; }}
    //maxim = primul nr;
    maxim2=1;
     urm[n]=-1;
     l[n]=1; p=n;
     for(i=n;i>poz;i--)
       { urm[i]=-1;
         l[i]=1;
       for(j=n;j>i;j--)
          if(sir[i]>sir[j] && l[i]<l[j]+1)
             { l[i]=l[j]+1;
               urm[i]=j;
               if(l[i]>maxim2)
                 maxim2=l[i], p=i; }}
     cout<<maxim2+maxim<<"\n";
    
    return 0;
}
