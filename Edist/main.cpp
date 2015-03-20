#include <fstream>

using namespace std;

ifstream cin("edist.in");
ofstream cout("edist.out");

const short MAXN = 20005;

short N, M, K, D[3][MAXN];
char a[MAXN], b[MAXN];

inline void Levensthein() {
    for(int i = 0 ; i <= M ; ++ i)   D[0][i] = i;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = max(0, i - K) ; j <= i + K && j <= M ; ++ j) {
                D[i & 1][0] = i;
                if(a[i] == b[j])
                    D[i&1][j] = D[!(i & 1)][j-1];
                else D[i&1][j] = min(D[!(i & 1)][j] + 1, min(D[i&1][j-1] + 1, D[!(i & 1)][j-1] + 1));
            }
    }
    cout << D[N & 1][M] << '\n';
}

int main() {
    cin >> N >> M >> K >> (a+1) >> (b+1);
    Levensthein();
    cin.close();
    cout.close();
    return 0;
}
