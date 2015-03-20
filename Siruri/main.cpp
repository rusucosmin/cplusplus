#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "siruri.in";
const char outfile[] = "siruri.out";

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

struct entry {
    int nr[2], p;
} L[2*MAXN];

int P[25][2*MAXN], stp, cnt;
int N, x[MAXN], M;
int auxPos;

struct classComp {
    inline bool operator () (const entry &A, const entry &B) const {
        if(A.nr[0] == B.nr[0])
            return A.nr[1] < B.nr[1];
        return A.nr[0] < B.nr[0];
    }
};

inline void buildSuffixArray() {
    for(stp = 1, cnt = 1 ; (cnt >> 1) <= N ; ++ stp, cnt <<= 1) {
        for(int i = 1 ; i <= N ; ++ i) {
            L[i].nr[0] = P[stp - 1][i];
            L[i].nr[1] = i + cnt <= N ?  P[stp - 1][i + cnt] : -1;
            L[i].p = i;
        }
        sort(L + 1, L + N + 1, classComp());
        for(int i = 1 ; i <= N ; ++ i)
            P[stp][L[i].p] = i > 1 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;
    }
}

inline int LCP(int x, int y) {
    int k, ret = 0;
    if(x == y)
        return N - x;
    for(k = stp - 1; k >= 0 && x <= N && y <= N ; -- k)
        if(P[k][x] == P[k][y]) {
            ret += (1 << k);
            x += (1 << k);
            y += (1 << k);
        }
    return ret;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> x[i];
    for(int i = 1 ; i + 1 <= N ; ++ i)
        P[0][i] = x[i + 1] - x[i];
    fin >> M;
    for(int i = 1 ; i <= M ; ++ i)
        fin >> x[i];
    -- N;
    auxPos = N;
    for(int i = 1 ; i + 1 <= M ; ++ i)
        P[0][++ N] = x[i] - x[i + 1];
    buildSuffixArray();
    int Ans = 0;
    int xst = 0, yst = 0;
    int last = 0;
    for(int i = 1 ; i + 1 <= N ; ++ i)
        if((L[i].p <= auxPos && L[i + 1].p > auxPos) || (L[i].p > auxPos && L[i + 1].p <= auxPos)) {
            int temp = LCP(L[i].p, L[i + 1].p);
            if(temp > Ans) {
                Ans = temp;
                if(L[i].p <= auxPos && L[i + 1].p > auxPos) {
                    xst = L[i].p;
                    yst = L[i + 1].p;
                }
                else {
                    yst = L[i].p;
                    xst = L[i + 1].p;
                }
            }
        }
    fout << Ans + 1 << ' ' << xst << ' ' << yst - auxPos << '\n';
    fin.close();
    fout.close();
    return 0;
}
