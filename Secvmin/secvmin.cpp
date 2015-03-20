#include<fstream>
using namespace std;
ifstream cin("secvmin.in");
ofstream cout("secvmin.out");
long long A[100005], B[100005], n, m, i, j, sol[100005], u , maximul=1000005;
int main()
{
    
    cin>>n>>m;
    for(i=1;i<=n;i++)
    cin>>A[i];
    for(j=1;j<=m;j++)
    cin>>B[j];
    j=1;
       for(i=1;i<=n;i++)
          if(B[j]==A[i])
                         { j++;
                           u++; 
                           sol[u]=i;
                           if(u==m) {if(maximul>(sol[u]-sol[1]+1)) maximul=((sol[u]-sol[1])+1); u=0;j=1;i=sol[1]+1;   }
                         }
   
if(maximul==10005) cout<<"-1";
   else                      
cout<<maximul; 
return 0;
}
