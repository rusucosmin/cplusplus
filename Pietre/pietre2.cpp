#include<fstream>
using namespace std;
ifstream cin("pietre.in");
ofstream cout("pietre.out");

int main()
{
    int n,i,j,m, a[100], poz[100], l[100],pozmax;
    cin>>n>>m;
    for(i=1;i<=n;i++)
                     cin>>a[i];
    for( i=n;i>0;i--)
    { //int aux=i+1+m;
            for( l[i]=1,poz[i]=-1, j=i+1 ;j<=i+m&&j<=n;j++)
                 if(a[i]<=a[j] && l[i]<1+l[j])
                  { l[i]=1+l[j];
                    poz[i]=j; }}
    
    int maxi=INT_MIN;
    for(i=2;i<=n;i++)
       if(l[i]>maxi)
       { maxi=l[i]; pozmax=i;}
    cout<<maxi<<" ";
    i=pozmax;
    while(i!=-1)
      {  cout<<a[i]<<" ";
         i=poz[i]; }
    if(i+m>n)
    cout<<"poate ajunge";
    else cout<<"nu poate";
    return 0;
}
