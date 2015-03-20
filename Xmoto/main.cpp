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

const char infile[] = "xmoto.in";
const char outfile[] = "xmoto.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 50005;
const double EPS = 0.0000001;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct tronson {
    double a, b, k, q;
    int v;
} T[MAXN], S[MAXN];
int N;
double L;

struct classComp {
    inline bool operator () (const tronson &A, const tronson &B) const {
        return A.v < B.v;
    }
};

inline double myAbs(const double &value) {
    if(value > 0)
        return value;
    return -value;
}

int main() {
    fin >> N >> L;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> T[i].a >> T[i].b >> T[i].k >> T[i].q >> T[i].v;
    sort(T + 1, T + N + 1, classComp());
    for(int i = 1 ; i <= N ; ++ i) {
        S[i].a = S[i-1].a + T[i].a;
        S[i].b = S[i-1].b + T[i].b;
        S[i].k = S[i-1].k + T[i].k;
        S[i].q = S[i-1].q + T[i].q;
    }
    T[0].v = 0;
    T[N + 1].v = 10005;
    vector <double> Sol;
    for(int i = 0 ; i <= N ; ++ i) {
        double sc = L;
        sc -= (S[i].q + (S[N].k - S[i].k));
        sc /= (S[i].b + (S[N].a - S[i].a));
        if(sc > T[i].v && (sc < T[i + 1].v || (myAbs(sc - T[i + 1].v) < EPS)))
            Sol.push_back(sc);
    }
    fout << Sol.size() << '\n';
    for(vector <double> :: iterator it = Sol.begin(), fin = Sol.end(); it != fin ; ++ it)
        fout << fixed << setprecision() << *it << '\n';
    fin.close();
    fout.close();
    return 0;
}
