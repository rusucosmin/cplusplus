#include <fstream>
#include <vector>
#include <bitset>
#include <set>

using namespace std;

const char infile[] = "eliminare.in";
const char outfile[] = "eliminare.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, sum[MAXN << 2], a[MAXN << 2], v[MAXN];

void Update(int Node, int st, int dr, int x, int value) {
    if(st == dr) {
        a[Node] = x;
        sum[Node] = value;
        return;
    }
    int mid = ( (st + dr) >> 1 );
    int fst = (Node << 1);
    int fdr = (fst + 1);
    if(x <= mid)
        Update(fst, st, mid, x, value);
    else Update(fdr, mid + 1, dr, x, value);
    if(v[a[fst]] >= v[a[fdr]])
        a[Node] = a[fst];
    else a[Node] = a[fdr];
    sum[Node] = sum[fst] + sum[fdr];
}

int Query(int Node, int st, int dr, int k) {
    if(st == dr)
        return st;
    int mid = ((st+dr) >> 1);
    int fst = (Node << 1);
    int fdr = fst + 1;
    if(sum[fst] >= k)
        return Query(fst, st, mid, k);
    return Query(fdr, mid+1, dr, k - sum[fst]);
}

int Query_poz(int Node, int st, int dr, int x, int y) {
    if(x <= st && dr <= y)
        return a[Node];
    int ret = 0;
    int poz = 0;
    int mid = ((st+dr) >> 1);
    int fst = (Node << 1);
    int fdr = fst + 1;
    if(x <= mid) {
        int t;
        if(ret < v[t = Query_poz(fst, st, mid, x, y)])
            ret = v[t], poz = t;
    }
    if(mid < y) {
        int t;
        if(ret < v[t = Query_poz(fdr, mid + 1, dr, x, y)])
            ret = v[t], poz = t;
    }
    return poz;
}

int main() {
    fin >> N >> M;
    v[0] = -oo;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> v[i];
        Update(1, 1, N, i, 1);
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        int nrX = Query(1, 1, N, x);
        int nrY = Query(1, 1, N, y);
        int poz = Query_poz(1, 1, N, nrX, nrY);
        v[poz] = -1;
        Update(1, 1, N, poz, 0);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(v[i] != -1)
            fout << v[i] << '\n';
    fin.close();
    fout.close();
    return 0;
}
