#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string.h>

using namespace std;

const char infile[] = "ghicit.in";
const char outfile[] = "ghicit.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 50320;
const int MAXLG = 20;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct entry {
    int p, nr[2];
}L[MAXN];

char s[MAXN];
int P[MAXLG][MAXN], stp, cnt, N;

struct classComp {
    inline bool operator () (const entry &a, const entry &b) {
        return a.nr[0] < b.nr[0] || (a.nr[0] == b.nr[0] && a.nr[1] < b.nr[1]);
    }
};

inline int LCP(int X, int Y) {
    int k, ret = 0;
    if(X == Y)
        return N - X;
    for(k = stp - 1; k >= 0 && X < N && Y < N ; -- k)
        if(P[k][X] == P[k][Y])
            X += (1 << k), Y += (1 << k), ret += (1 << k);
    return ret;
}

int main() {
    fin.getline(s, MAXN);
    N = strlen(s);
    for(int i = 0 ; i < N ; ++ i)
        P[0][i] = (int)s[i];
    for(stp = 1 , cnt = 1 ; (cnt >> 1) < N ; ++stp, cnt <<= 1) {
        for(int i = 0 ; i < N ; ++ i) {
            L[i].nr[0] = P[stp-1][i];
            L[i].nr[1] = i + cnt < N ? P[stp-1][i + cnt] : -1;
            L[i].p = i;
        }
        sort(L, L + N, classComp());
        for(int i = 0 ; i < N ; ++ i)
            P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i-1].nr[0] && L[i].nr[1] == L[i-1].nr[1] ? P[stp][L[i-1].p] : i;
    }
    int Ans = N - L[0].p;
    int i;
    for(i = 1 ; i < N ; ++ i) {
        int lcp = LCP(L[i-1].p, L[i].p);
        Ans = Ans + (N - L[i].p) - lcp;
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
