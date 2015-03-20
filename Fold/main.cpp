#include <fstream>
using namespace std;

ifstream cin("fold.in");
ofstream cout("fold.out");
/*
    1 ≤ n ≤ 250
    1 ≤ m ≤ 2000
*/
int n, m, a[255][2005], i, j, c, k;
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            cin>>a[i][j];
    for(i=1;i<n;i++)
       for(k=i+1;k<=n;k++)
            for(j=1;j<=m;j++)
                {
                    if(a[i][j]==1 && a[k][j]==1)
                        c++;
                }
    cout<<c<<" ";



    return 0;
}
