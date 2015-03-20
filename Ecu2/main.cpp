#include <fstream>

using namespace std;

ifstream cin("ecu2.in");
ofstream cout("ecu2.out");
int t, a, b, c, delta;
int main()
{
    cin>>t;
    while( t-- )
    {
        cin>>a>>b>>c;
        if(a == 0 )
            if( b == 0 )
                if ( c == 0)
                    cout<<"INF\n";
                else cout<<"0\n";
            else cout<<"1\n";
        else
        {
        delta = b*b - 4*a*c;
        if(delta < 0)
            cout<<"0\n";
        else if( delta == 0 )
                    cout<<"1\n";
                else  cout<<"2\n";
        }
    }
    cin.close();
    cout.close();
    return 0;
}
