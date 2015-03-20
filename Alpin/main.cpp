#include <fstream>
#include <queue>
#include <stack>

#define FOR(i, l, n) for(int i = l ; i <= n ; ++ i )
using namespace std;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1,  0,-1};
int maxim = -((1<<31)-1), maxi, maxj;
queue < pair<int, int> > Q;
stack < pair<int, int> > st;
ifstream cin("alpin.in");
ofstream cout("alpin.out");

int n, a[1030][1030], d[1030][1030];
char parse[100000], *now;

inline void verify()
{
    if ( *now == 0 )
    {
        cin.get(parse, sizeof(parse), '\0');
        now = parse;
    }
}
int get()
{
    while (*now < '0' || *now > '9')
    {
        ++now;
        verify();
    }
    int num = 0;
    while (*now >= '0' && *now <= '9')
    {
        num = num * 10 + (*now - '0');
        ++now;
        verify();
    }
    return num;
}
int main()
{
    cin>>n;
    cin.get();
    now = parse;
    verify();
    FOR(i, 1, n)
        FOR(j, 1, n)
            a[i][j] = get();
    FOR(i, 1, n)
        FOR(j, 1, n)
        {
            int xnou, ynou;
            bool ok=true;
            for( int ii = 0 ; ii < 4 ; ++ ii )
            {
                xnou = i + dx[ii];
                ynou = j + dy[ii];
                if( a[xnou][ynou]<a[i][j] && a[xnou][ynou] )
                    ok=false;
            }
            if( ok )
                Q.push(make_pair(i, j)), d[i][j]=1;
        }
    for(;!Q.empty(); Q.pop())
    {
        int x = Q.front().first;
        int y = Q.front().second;
        for(int i = 0 ; i < 4; ++i)
        {
            int xnou = x + dx[i];
            int ynou = y + dy[i];
            if(xnou>=1 && xnou<=n && ynou>=1 && ynou<=n)
                if(a[xnou][ynou]>a[x][y] && (d[xnou][ynou]<d[x][y]+1 || d[xnou][ynou]==0))
                {
                    d[xnou][ynou]=d[x][y]+1;
                    if(maxim < d[xnou][ynou] )
                    {
                        maxim=d[xnou][ynou];
                        maxi=xnou;
                        maxj=ynou;
                    }
                    Q.push(make_pair(xnou, ynou));
                }
        }
    }
    cout<<maxim<<"\n";
    st.push(make_pair(maxi, maxj));
    do {
        for(int i = 0 ; i < 4 ; ++i)
        {
            int xnou = maxi + dx[i];
            int ynou = maxj + dy[i];
            if(d[xnou][ynou]==maxim-1)
            {
                --maxim;
                maxi=xnou;
                maxj=ynou;
                break;
            }
        }
        st.push(make_pair(maxi, maxj));
    } while(maxim!=1);
    while(st.size())
    {
        cout<<st.top().first<<" "<<st.top().second<<"\n";
        st.pop();
    }
    cin.close();
    cout.close();
    return 0;
}
