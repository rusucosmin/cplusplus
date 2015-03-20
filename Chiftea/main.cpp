#include <fstream>
#include <math.h>
using namespace std;

ifstream cin("chiftea.in");
ofstream cout("chiftea.out");
int n, t, r;
int main()
{
    cin>>t;
    while(t)
    {
    cin>>n;
    r = (int) sqrt(n);
    //cout<<r<<" ";
    if(r*r==n)
        cout<<4*r<<'\n';
    else if( (n-(r*r)) == r ) cout<<4*(r+1)<<'\n';
        else cout<<4*r+2<<"\n";
    --t;
    }
    cin.close();
    cout.close();
    return 0;
}
