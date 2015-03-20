#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int maxm = 50005;
const int maxn = 7;

int m, n, t[maxm][maxn], finishtime[maxm];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("416b.in", "r", stdin);
    freopen("416b.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> m >> n;
    for(int i = 1 ; i <= m ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
            cin >> t[i][j];
    for(int painter = 1 ; painter <= n ; ++ painter) {
        int freeat = 0;
        for(int j = 1 ; j <= m ; ++ j) {
            int start = max(freeat, finishtime[j]);
            finishtime[j] = start + t[j][painter];
            freeat = finishtime[j];
        }
    }
    for(int i = 1 ; i <= m ; ++ i)
        cout << finishtime[i] << ' ';
}
