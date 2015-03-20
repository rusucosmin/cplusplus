#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

#define x first
#define y second

using namespace std;

const char infile[] = "cadrane.in";
const char outfile[] = "cadrane.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, ind[MAXN], arb[MAXN << 2], marb[MAXN << 2], s[MAXN];
pair<int, int> P[MAXN];

struct classComp1 {
    inline bool operator () (const int &a, const int &b) const {
        return P[a].y < P[b].y;
    }
};

void Normalize(void) {
    int value = 1;
    for(int i = 1 ; i <= N ; ++ i) {
        while(i + 1 <= N && P[ind[i]].y == P[ind[i + 1]].y) {
            P[ind[i]].y = value;
            ++ i;
        }
        P[ind[i]].y = value;
        ++ value;
    }
}

void Update(const int &Node, const int &st, const int &dr, const int &a, const int &b, const int value) {
    if(a <= st && dr <= b) {
        arb[Node] += value * (dr - st + 1);
        marb[Node] += value;
        return;
    }
    int mid = (st + dr) >> 1;
    int fst = Node << 1;
    int fdr = fst | 1;
    if(arb[Node] != arb[fst] + arb[fdr]) {
        int aux = (arb[Node] - arb[fst] - arb[fdr]) / (dr - st + 1);
        arb[fst] += aux * (mid - st + 1);
        arb[fdr] += aux * (dr - mid - 1 + 1);
        marb[fst] += aux;
        marb[fdr] += aux;
    }
    if(a <= mid)
        Update(fst, st, mid, a, b, value);
    if(mid < b)
        Update(fdr, mid + 1, dr, a, b, value);
    marb[Node] = min(marb[fst], marb[fdr]);
    arb[Node] = arb[fst] + arb[fdr];
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> P[i].x >> P[i].y;
        ind[i] = i;
    }
    sort(P + 1, P + N + 1);
    sort(ind + 1, ind + N + 1, classComp1());
    Normalize();
    for(int i = 1 ; i <= N ; ++ i)
        ++ s[P[i].y];
    for(int i = 1 ; i <= N ; ++ i)
        s[i] += s[i-1];
    for(int i = 1 ; i <= N ; ++ i)
        Update(1, 1, N, i, i, N - s[i - 1]);
    int act = 1, ans = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        while(P[act].x < P[i].x) {
            Update(1, 1, N, 1, P[act].y , -1);
            ++ act;
        }
        while(i + 1 <= N && P[i].x == P[i+1].x) {
            Update(1, 1, N, P[i].y, N, 1);
            ++ i;
        }
        Update(1, 1, N, P[i].y, N, 1);

        ans = max(ans, marb[1]);
    }
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
