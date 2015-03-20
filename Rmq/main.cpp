#include <fstream>
#include <vector>

using namespace std;

ifstream fin("rmq.in");
ofstream fout("rmq.out");

const int maxn = 100005;
const int maxlg = 22;

int n, m, rmq[maxlg][maxn], lg[maxn];

inline int query(int x, int y) {
    int l = lg[y - x + 1];
    return min(rmq[l][x], rmq[l][y - (1 << l) + 1]);
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= n ; ++ i)
        fin >> rmq[0][i];
    for(int i = 2 ; i <= n ; ++ i)
        lg[i] = lg[i >> 1] + 1;
    for(int i = 1 ; (1 << i) <= n ; ++ i)
        for(int j = 1 ; j + (1 << i) - 1 <= n ; ++ j)
            rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        fin >> x >> y;
        fout << query(x, y) << '\n';
    }
}
