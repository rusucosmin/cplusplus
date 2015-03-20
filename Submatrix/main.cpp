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
#include <unordered_map>

using namespace std;

const char infile[] = "submatrix.in";
const char outfile[] = "submatrix.out";

ofstream fout(outfile);

const int MAXN = 305;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

unordered_map<int, int> values;
int cntValues;
int N, M, A[MAXN][MAXN], fr[MAXN * MAXN], distinct, K;

inline void normalizeValues() {
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < M ; ++ j)
            if(!values[A[i][j]])
                values[A[i][j]] = ++ cntValues;
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < M ; ++ j)
            A[i][j] = values[A[i][j]];
}

inline void _insert(int x, int y) {
    ++ fr[A[x][y]];
    distinct += (fr[A[x][y]] == 1);
}

inline void _remove(int x, int y) {
    -- fr[A[x][y]];
    distinct -= (fr[A[x][y]] == 0);
}

#define get(N) scanf("%d", &N);

int main() {
    freopen(infile, "r", stdin);
    get(N);
    get(M);
    get(K);
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < M ; ++ j)
            get(A[i][j]);
    normalizeValues();
    int ans = 0;
    pair<int, int> beg = make_pair(N, 1);
    for(int diag = 0 ; diag < N + M - 1; ++ diag) {
        pair<int, int> st = beg;
        pair<int, int> fn = beg;
        memset(fr, 0, sizeof(fr));
        distinct = 0;
        while(st.first <= N && st.second <= M) {
            for(int i = 0 ; i <= (st.first - fn.first) ; ++ i)
                _insert(st.first - i, st.second);
            for(int i = 1 ; i <= (st.first - fn.first) ; ++ i)
                _insert(st.first, st.second - i);
            while(distinct > K) {
                for(int i = 0 ; i <= (st.first - fn.first) ; ++ i)
                    _remove(fn.first + i, fn.second);
                for(int i = 1 ; i <= (st.first - fn.first) ; ++ i)
                    _remove(fn.first, fn.second + i);
                ++ fn.first;
                ++ fn.second;
            }
            ans = max(ans, st.first - fn.first + 1);
            ++ st.first;
            ++ st.second;
        }
        if (beg.first == 0) ++beg.second;
        else --beg.first;
    }
    fout << ans << '\n';
    fout.close();
    return 0;
}
