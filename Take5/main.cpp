#include <stdio.h>
#include <vector>
#define MOD 6007

using namespace std;

int  n, s, a[1030], solution;
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
    freopen("take5.in","r",stdin);
    freopen("take5.out","w",stdout);
    scanf("%d %d",&n , &s);
    int i, j, k;
    for( i=1; i<=n ; ++i) scanf("%d", &a[i]);
    for(i=1; i<n-1; ++i)
        {
            for(j=i+1; j<n; ++j)
                for(k=j+1;k<=n;k++)
                    if(a[i]+a[j]+a[k]<s)
                        update(s-(a[i]+a[j]+a[k]));
        for(k=1; k<i; ++k)
            v[(a[i]+a[k])%MOD].push_back(a[i]+a[k]);
        }
    printf("%d\n", solution);
    return 0;
}
