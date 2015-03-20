#include <fstream>
#include <string.h>
#include <set>
#include <queue>

using namespace std;

queue<int> Q;
set <int> s[302*302];

ifstream cin("zone2.in");
ofstream cout("zone2.out");

int n, m, k, b[302][302], w[302*302],  nb, XXX, sol, iv, jv;
bool v[302*302];
char a[302][302];

int di[] = {-1,1,0,0};
int dj[] = {0,0,1,-1};

void fill(int i, int j, int k)
{
    b[i][j] = k;
    w[k]++;
    for (int d=0;d<4;d++)
    {
        iv = i + di[d];
        jv = j + dj[d];
        if ( b[iv][jv]==0 && a[iv][jv]!=0 && a[iv][jv] == a[i][j] )
            fill(iv,jv,k);
    }
}
void fil(int i)
{
    XXX += w[i];
    v[i] = 1;
    for(set<int>::iterator it = s[i].begin(); it!=s[i].end(); ++it)
    {
        int j = *it;
        if(v[j] == 0)
        {
            v[j] = 1;
            fil(j);
        }
    }
}
int main()
{
    cin >> n >> m >> k;
    cin.get();

    for(int i = 1; i <= n; ++ i)
        cin.getline(a[i]+1, m+2);

    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(!b[i][j])
                    fill(i, j, ++nb);

    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ;  j <= m ; ++j)
            for(int d = 0 ; d < 4 ;++d)
            {
                int xnou, ynou;
                xnou = i + di[d];
                ynou = j + dj[d];
                if(xnou > 0 && ynou > 0 && xnou <= n && ynou <= m && b[xnou][ynou] != b[i][j])
                {
                    s[b[xnou][ynou]].insert(b[i][j]);
                    s[b[i][j]].insert(b[xnou][ynou]);
                }
            }

    for(int i = 1 ; i <= nb ; ++ i)
    {
        if(s[i].size() < k)
            Q.push(i),
            v[i] = 1;
    }

    while(!Q.empty())
    {
        int shadow = Q.front();
        Q.pop();
        for ( set<int>::iterator it = s[shadow].begin() ; it!=s[shadow].end(); ++it)
        {
            int j = *it;
            s[j].erase(shadow);
            if(s[j].size() < k && v[j] == 0)
                Q.push(j),
                v[j] = 1;
        }
    }

    for (int i = 1 ; i <= nb; ++ i)
        if(v[i] == 0)
        {
            XXX = 0;
            fil(i);
            if(sol<XXX)
                sol = XXX;
        }
    cout<<sol<<"\n";
    cin.close();
    cout.close();
    return 0;
}
