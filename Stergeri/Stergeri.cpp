#include<fstream>

using namespace std;
int a[10000001], i, j, k, m, n,x,y,contor;

ifstream cin("stergeri.in");
ofstream cout("stergeri.out");
int main()
{
    cin>>n>>m>>k;
    for(i=1;i<=m;i++)
      { cin>>x>>y;
        while(x<=y) 
          if(a[x]!=1)
            {a[x]=1;
            x++;}
          else
            {x++;
            y++;} 
               }          
       for(i=1;i<=n ;i++)
          { if(a[i]!=1){ contor++; }
             if(contor==k) {cout<<i; 
                       return 0;}}
}
