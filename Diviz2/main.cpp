#include <cstdio>
#include <cstring>
#define N 202
#define MOD 30103
using namespace std;

int dp[2][N][100], nxt[10][N], r[100][10];
char a[N+5];

int main()
{
    freopen("diviz.in", "r", stdin);
    freopen("diviz.out", "w", stdout);
    int n, k, x, y, i, j, p, u=0, sol=0, ind;
    scanf("%d %d %d\n", &k, &x, &y);
    fgets(a+1, N+5, stdin); a[0]='!'; n=strlen(a)-2;
    for(i=0;i<k;i++)
    {
        for(j=0;j<10;j++)
        {
            r[i][j]=(10*i+j)%k;
        }
    }
    for(i=n;i;i--)
    {
        for(j=9;j>=0;j--)
        {
            if(a[i]-'0'==j) nxt[j][i]=i;
            else nxt[j][i]=nxt[j][i+1];
            printf("%d ", nxt[j][i]);
        }
    }
    for(i=1;i<10;i++)
    {
        dp[0][nxt[i][1]][i%k]=1;
    }
    for(i=1;i<=y;i++, u^=1)
    {
        for(ind=i;ind<=n;ind++)
        {
            if(i>=x) sol=(sol+dp[u][ind][0])%MOD;
            for(j=0;j<k;j++)
            {
                for(p=0;p<10;p++)
                {
                    dp[u^1][nxt[p][ind+1]][r[j][p]]+=dp[u][ind][j];
                    dp[u^1][nxt[p][ind+1]][r[j][p]]%=MOD;
                }
            }
        }
        memset(dp[u], 0, sizeof(dp[u]));
    }
    printf("%d", sol);
}
