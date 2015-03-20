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
#include <math.h>

using namespace std;

const char infile[] = "mosia.in";
const char outfile[] = "mosia.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Point {
    double x, y;
    int dist;
};

int N;
Point P[MAXN];
Point G; /// if u know what i mean :))
double addArea[MAXN], Ans, dp[MAXN];

/*
struct classComp {
    inline bool operator () (const Point &A, const Point &B) const {
        return 1LL * (A.y - G.y) * (B.x - G.x) < 1LL * (B.y - G.y) * (A.x - G.x);
        /// A.y / A.x < B.y / B.x
        /// A.y * B.x < B.y * A.x
    }
};
*/

struct classComp {
    inline bool operator()(const Point &A, const Point &B) const {
        return atan2(A.y - G.y , A.x - G.x) < atan2(B.y - G.y,B.x - G.x);
    };
};


struct comp {
    inline bool operator () (const double &a, const double &b) const {
        return 1LL * a * 100000 < 1LL * b * 100000;
    }
};

inline int square(const double &A) {
    return A * A;
}

inline double euclidianDist(const Point &A, const Point &B) {
    return sqrt(square(A.x - B.x) + square(A.y - B.y));
}

int main() {
    fin >> N;
    for(int i = 1; i <= N ; ++ i) {
        fin >> P[i].x >> P[i].y >> P[i].dist;
        G.x += P[i].x;
        G.y += P[i].y;
    }
    G.x /= 1.0 * N;
    G.y /= 1.0 * N;
    sort(P + 1, P + N + 1, classComp());
    addArea[1] = 1.0 * P[1].dist * euclidianDist(P[2], P[N]) / 2.0;
    for(int i = 2 ; i < N ; ++ i)
        addArea[i] = 1.0 * P[i].dist * euclidianDist(P[i + 1], P[i - 1]) / 2.0;
    addArea[N] = 1.0 * P[N].dist * euclidianDist(P[1], P[N - 1]) / 2.0;

    dp[1] = addArea[1];

    for(int i = 1 ; i <= N - 1 ; ++ i)
        dp[i] = max(dp[i - 1], dp[i - 2] + addArea[i], comp());

    Ans = dp[N - 1];

    memset(dp, 0, sizeof(dp));

    dp[1] = 0;

    for(int i = 2 ; i <= N ; ++ i)
        dp[i] = max(dp[i - 1], dp[i - 2] + addArea[i], comp());
    Ans = max(Ans, dp[N], comp());

    fout << fixed << setprecision(6) << Ans << "\n";

    fin.close();
    fout.close();
    return 0;
}
