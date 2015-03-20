# include <fstream>
using namespace std;

ifstream f ("culori3.in");
ofstream g ("culori3.out");

int n, t, k, i, j, p, y, x;
short a[1301];

int main()
{
    f>>n;
    if (n==1)
    {
        g<<5<<'\n';
        return 0;
    }

    if (n%2) p = (n-3)/2, a[1] = 4, a[2] = 1, k = 2;
        else p = (n-2)/2, a[1] = 8, k = 1;

    t = 0;
    for (i=1; i<=p; ++i)
    {
        for (j=1; j<=k; ++j)
            {
                x = a[j] * 3 + t;
                a[j] = x%10; t=x/10;
            }
        while (t)
        {
            a[++k] = t%10;
            t = t/10;
        }
    }

    for (i=k; i>1; --i)
        g<<a[i];
    g<<a[1]<<'\n';

    return 0;
}

