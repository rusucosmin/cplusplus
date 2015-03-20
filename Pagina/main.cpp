#include <fstream>

using namespace std;

ifstream cin("pagina.in");
ofstream cout("pagina.out");
int n, x, maxi;
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>x;
        maxi=max(x, maxi);
    }
    cout<<++maxi<<"\n";
    cin.close();
    cout.close();
    return 0;
}
