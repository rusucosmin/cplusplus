#include <fstream>
#define min(a , b) ( (a < b) ? a : b )
using namespace std;

int s[1002][1002];
int main()
{
    freopen("ferma2.in", "r", stdin);
    freopen("ferma2.out", "w", stdout);
    int n, k, maxim=0, x;
    scanf("%d %d", &n, &k);
    for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=i;++j)
            {
                scanf("%d", &x);
                s[i][j]=s[i][j-1]+x;
            }
            maxim+=s[i][i];
        }
    fclose(stdin);
    int bestSum=(1<<31)-1;
    for(int i=n-k;i<=n;++i)
        for(int j=n-k;j<=i;++j)
        {
            int sum=0;
            for(int ii=i, jj=j, jj1=1 ; jj1<=n-k ; ++jj1, --ii, --jj)
                sum+=s[ii][jj]-s[ii][jj-(n-k-jj1+1)];
            bestSum=min(bestSum, sum);
        }
    printf("%d\n", maxim-bestSum);
    fclose(stdout);
    return 0;
}
