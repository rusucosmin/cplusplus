#include <fstream>

using namespace std;

ifstream cin("lumanari.in");
ofstream cout("lumanari.out");
int a[200005];
    int n=0, m, sol=0;
    int ok=0;
int main()
{

    cin>>m;
    for(int i=1;i<=m;++i)
        cin>>a[i];
    for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=m, ok<i ;++j)
                if(a[j])
                    {
                        --a[j];
                        ++ok;
                    }
            if(ok==i)
                ++n;
            else break;
        }
    cout<<n-1<<"\n";
    cin.close();
    cout.close();
    return 0;
}
