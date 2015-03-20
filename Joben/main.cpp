#include <fstream>
#include <string.h>
#include <limits.h>
#include <algorithm>

using namespace std;

ifstream cin("joben.in");
ofstream cout("joben.out");
int n;
char s1[100005], s2[100005];
int  f1[30], f2[30], ns1=INT_MIN, ns2=INT_MIN;
bool cmp (int a, int b)
{
    return ( a > b ) ;
}
int main()
{
    cin >> n;
    cin.get();
    for( int i = 1; i <= n; ++i )
    {
        cin.getline(s1, 100005);
        cin.getline(s2, 100005);

        for(int i=0;i<=30;++i)
            f1[i]=f2[i]=0;

        for(int j = 0; s1[j] ; ++j)
            ++f1[ s1[j] - 'a' + 1 ] ;

        for(int j = 0; s2[j] ; ++j)
            ++f2[ s2[j] - 'a' + 1 ] ;

        sort(f1+1, f1+28, cmp);
        sort(f2+1, f2+28, cmp);
        bool ok=1;
        for(int i = 1 ; i <= 28 ; ++i)
            if(f1[i]!=f2[i])
            {
                cout<<"NU\n";
                ok=0;
                break;
            }
        if(ok)
        cout<<"DA\n";
    }
    cin.close();
    cout.close();
    return 0;
}
