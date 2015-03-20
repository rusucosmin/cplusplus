#include<fstream>
using namespace std;
ifstream cin("sticle.in");
ofstream cout("sticle.out");
int n, i, a, contor=-1;
void solve(int a)
{   if(a==1) cout<<"0\n";
    else if(a==2) cout<<"1\n";
    else for(i=1;i<=a;i++)
       if(
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
        {cin>>a;
        solve(a);
        }
return 0;
}
