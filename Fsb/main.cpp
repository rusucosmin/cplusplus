#include <fstream>
using namespace std;

ifstream f("fsb.in");
ofstream g("fsb.out");

int n, s[200005], sol[400010], pozmax;
char c[200005];
long long rez=0;

int main()
{
    f>>n; f>>c;

    for (int i=0; i<n; i++)
    {
        if (c[i]=='1') s[i+1]=s[i]-1;
            else s[i+1]=s[i]+1;
        ++sol[n+s[i+1]];
        if (n+s[i+1]>pozmax) pozmax=n+s[i+1];
    }

    for (int i=0; i<=pozmax; i++)
        if (sol[i]>0) rez+=(sol[i]*(sol[i]-1))/2;
    g<<rez+sol[n]<<'\n';

    return 0;
}
