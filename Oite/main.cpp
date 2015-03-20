#include <stdio.h>
#include <vector>
#define MOD 10007
using namespace std;
int c, l, lana[1030], solution;
vector <int> v[MOD];

void update(int x)
{
    int i;
    int y=x%MOD;
    for (i=0; i<v[y].size(); i++)
        if (v[y][i]==x)
        {
            ++solution;
        }
}
int main()
{
    freopen("oite.in","r",stdin);
    freopen("oite.out","w",stdout);
    scanf("%d %d",&c , &l);
    int i, j, k;
    for( i=1; i<=c ; ++i) scanf("%d", lana+i);
    for(i=1; i<c; ++i)
    {
        for(j=i+1; j<=c; ++j)
            if(lana[i]+lana[j]<l)
                update(l-(lana[i]+lana[j]));
        for(k=1; k<i; ++k)
            v[(lana[i]+lana[k])%MOD].push_back(lana[i]+lana[k]);
    }
    printf("%d\n", solution);
    return 0;
}
