#include <fstream>
using namespace std;
ifstream cin("modulo.in");
ofstream cout("modulo.out");
unsigned long long a, b, c, p=1;
int main()
{
    cin>>a>>b>>c;
    if(b==0)
    {cout<<"1";
    return 0;}
    if(b==1)
    {cout<<a%c;
     return 0;}
    for(int i=1;i<=b%c;i++)
        p=(p*(a%c))%c;
    if(p==0)
    cout<<"0";
    else
    cout<<p%c<<"\n";
    return 0;   
}
    
