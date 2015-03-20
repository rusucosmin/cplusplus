#include <fstream>
#include <vector>
#include <bitset>
#include <map>
#include <math.h>
#include <string.h>
#include <iomanip>

using namespace std;

const char infile[] = "seg.in";
const char outfile[] = "seg.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 18;
const double oo = 1.0*100000;

typedef vector< int > Graph[MAXN];
typedef vector< int > :: iterator It;

map<pair<double, double> , int> mymap;
double dist[MAXN][MAXN];
double dp[1 << MAXN][MAXN];
Graph G;
int Nodes = -1, N;


inline double euclidianDistance(const pair<double, double> &a, const pair<double, double> &b) {
    return sqrt( (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
}

inline void Read() {
    fin >> N;
    Nodes = -1;
    memset(dist, oo, sizeof(dist));
    for(int i = 0 ; i < N ; ++ i){
        double x, y, a, b;
        fin >> x >> y >> a >> b;
        if(mymap.find(make_pair(x, y)) == mymap.end() )
            mymap.insert(make_pair(make_pair(x, y), ++ Nodes));
        if(mymap.find(make_pair(a, b)) == mymap.end() )
            mymap.insert(make_pair(make_pair(a, b), ++ Nodes));
        int n1 = mymap.find(make_pair(x, y)) -> second;
        int n2 = mymap.find(make_pair(a, b)) -> second;
        G[n1].push_back(n2);
        G[n2].push_back(n1);
        dist[n1][n2] = dist[n2][n1] = euclidianDistance(make_pair(x, y), make_pair(a, b));
    }
}

inline void Solve() {
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0;
    N = Nodes;
    for(int i = 0 ; i < (1 << N ) ; ++ i)
        for(int j = 0 ; j < N ; ++ j)
            if(i & ( 1 << j ))
                for(It it = G[j].begin(), fin = G[j].end() ; it != fin ; ++ it)
                    if(i & ( 1 << (*it)))
                        dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)][*it] + dist[*it][j]);
    double Ans = oo;
    for(int i = 0 ; i < G[0].size() ; ++ i)
        Ans = min(Ans, dp[(1 << N) - 1][ G[0][i] ] + dist[ G[0][i] ][0]);
    fout << fixed << setprecision(6) << Ans << '\n';
}

inline void Clear() {
    for(int i = 0 ; i < N ; ++ i)
        G[i].clear();
}

int main() {
    int T;
    fin >> T;
    for(int t = 1 ; t <= T ; ++ t) {
        Read();
        Solve();
        Clear();
    }
    fin.close();
    fout.close();
    return 0;
}
