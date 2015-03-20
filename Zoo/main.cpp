#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "zoo.in";
const char outfile[] = "zoo.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 16005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
pair<int, int> a[MAXN];
vector <int> arb[MAXN * 3];
vector <int> X;


const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
    x = 0;
    char sgn = '+';
    while(!('0' <= buff[pos] && buff[pos] <= '9')) {
        sgn = buff[pos];
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
    if(sgn == '-')
        x = -x;
}

inline void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node].push_back(a[st].second);
        return ;
    }
    int mid = ((st + dr) >> 1);
    Build(Node << 1, st, mid);
    Build((Node << 1) | 1, mid+1, dr);
    arb[Node].resize(arb[Node << 1].size() + arb[(Node << 1) | 1].size());
    merge(arb[Node << 1].begin(), arb[Node << 1].end(),
          arb[(Node << 1) | 1].begin(), arb[(Node << 1) | 1].end(), arb[Node].begin());
}

inline int Query(int Node, int st, int dr, int x1, int y1, int x2, int y2) {
    if(x1 <= st && dr <= x2) {
        int u = upper_bound(arb[Node].begin(), arb[Node].end(), y2) - arb[Node].begin();
        int l = lower_bound(arb[Node].begin(), arb[Node].end(), y1) - arb[Node].begin();
        return u - l;
    }
    if(st == dr)
        return 0;
    int mid = ((st + dr) >> 1);
    int _real = 0;
    if(x1 <= mid)
        _real += Query(Node << 1, st, mid, x1, y1, x2, y2);
    if(mid < x2)
        _real += Query((Node << 1) | 1, mid+1, dr, x1, y1, x2, y2);
    return _real;
}

int main() {
    freopen(infile, "r", stdin);
    get(N);
    for(int i = 1 ; i <= N ; ++ i) {
        get(a[i].first);
        get(a[i].second);
        X.push_back(a[i].first);
    }
    sort(a + 1, a + N + 1);
    sort(X.begin(), X.end());
    get(M);
    Build(1, 1, N);
    for(int i = 1 ; i <= M ; ++ i) {
        int x1, y1, x2, y2;
        get(x1); get(y1); get(x2); get(y2);
        x1 = lower_bound(X.begin(), X.end(), x1) - X.begin() + 1;
        x2 = upper_bound(X.begin(), X.end(), x2) - X.begin();
        fout << Query(1, 1, N, x1, y1, x2, y2) << '\n';
    }
    fout.close();
    return 0;
}
