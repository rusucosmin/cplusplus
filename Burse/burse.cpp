#include<fstream>
using namespace std;
ifstream cin("burse.in");
ofstream cout("burse.out");
int n, s, i, p[500005], maxim, minim;
int main()
{
    cin>>n>>s;
    for(i=1;i<=n;i++)
       {cin>>p[i];
         if(p[i]>p[i-1])
             maxim=p[i];
         if(p[i]<p[i-1])
              minim=p[i];
              }
    cout<<((s/minim)*maxim)-s;
    
    
    
    
    
    
    return 0;
}
