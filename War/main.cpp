#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>

using namespace std;

const char infile[] = "war.in";
const char outfile[] = "war.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, Father[MAXN];
vector <pair<int, pair<int, int> > > v;
bitset <MANX> used;

inline void Kruskal() {
    sort(v.begin(), v.end());
    for(int i = 0 ; i < M ; ++ i) {

    }
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d %d", &N, &M, &K);
    for(int i = 0 ; i < M ; ++ i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        printf("%d %d %d\n", x, y, z);
    }
    for(int i = 1 ; i <= K ; ++ i) {
        int x;
        scanf("%d", &x);

    }
    return 0;
}
