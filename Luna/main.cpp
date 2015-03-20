#include <fstream>

using namespace std;

ifstream cin("luna.in");
ofstream cout("luna.out");

inline int min(int a, int b)
{
    if(a<b)
        return a;
    return b;
}

int N, M, a[55][55], K, b[55][55];

int main()
{
    cin >> N >> M ;
    for (int i = 1 ; i <= N; ++i)
        for (int j=1; j <= M; ++j)
            {
                cin >> a[i][j];
                if(a[i][j]==a[i-1][j-1] && a[i][j]==a[i-1][j] && a[i][j]==a[i][j-1])

            }
    for(int i=1;i<=N;++i)
        {for(int j=1;j<=M;++j)
            cout<<b[i][j]<<" ";
        cout<<"\n";}
    cin.close();
    cout.close();
    return 0;
}
