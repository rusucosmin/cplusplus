#include<fstream>
using namespace std;
ifstream cin("sticle.in");
ofstream cout("sticle.out");
int n, i, a, contor=0;
void solve(int x)
{ //if(a==72) cout<<"7\n";
   //else 
   contor=0;
   if(x==1) cout<<"0\n";
    else if(x==2) cout<<"1\n";
     else{ 
     while(x>0)
     {         
               x=x/2;
               contor++;
               }
     cout<<contor<<"\n";
}    
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
        {cin>>a;
        solve(a-1);
        }
return 0;
}
