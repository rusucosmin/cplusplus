#include <stdio.h>

using namespace std;


int n, a[250][250], b[250][250], i, j, maxi=-((1<<31)-1);
int max(int a, int b){
if(a>b) return a;
return b;
}
void start()
{
    freopen("sotron.in", "r", stdin);
    freopen("sotron.out", "w", stdout);
    scanf("%d", &n);
    for(i=1;i<=n;++i)
        for(j=1;j<=n;++j)
            {
                scanf("%d", &a[i][j]);
                if(i%2==j%2)
                    b[i][j]=max(b[i-1][j]+a[i][j], a[i][j]);
                else b[i][j]=max(b[i][j-1]+a[i][j], a[i][j]);
                maxi=max(maxi, b[i][j]);
            }
 /*    for(i=1;i<=n;++i)
        {for(j=1;j<=n;++j)
          printf("%d ", b[i][j]);
        printf("\n");}
   */ printf("%d\n", maxi);
}
int main()
{
    start();
    return 0;
}
