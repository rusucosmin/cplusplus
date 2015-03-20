#include<fstream>
using namespace std;
ifstream cin("carti3.in");
ofstream cout("carti3.out");
int c[2005],d[2002], i, n, C,x, pune,u=0, fi=-1, in=1;
int main()
{
    cin>>n>>C;
    for(i=1;i<=C;i++)
       cin>>c[i];
    while(cin>>x)
         {
         if(x==-1)
            {fi*=-1;
            in*=-1;   }
         else 
            {if(fi==1)
             { n++;
               c[n]=x; }
             else 
              { u++;
                 d[u]=x;}
                 }
             }
   for(i=u;i>=1;i--)
        cout<<d[i]<<"\n";
        for(i=1;i<=n;i++)
      cout<<c[i]<<"      ";
    
    return 0;    
}
