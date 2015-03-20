#include <fstream>
#include <queue>
using namespace std;
queue <pair <int, int> > Q;
ifstream cin("bemo.in");
ofstream cout("bemo.out");
int n, m, a[1505][1505];
int main()
{
    cin>>n>>m;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
            cin>>a[i][j];
    int x = 1, y=1;
    cout<<a[1][1]<<" ";
    while(x<n && y<m)
    {
        if(a[x+1][y]>a[x][y+1] && y+1<=m)
            cout<<a[x][++y]<<" ";
        else if(x+1<=n) cout<<a[++x][y]<<" ";
    }
    cout<<a[n][m]<<"\n";
    cin.close();
    cout.close();
    return 0;
}
