#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "cast.in";
const char outfile[] = "cast.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 12;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, c[MAXN][MAXN], dp[MAXN][1 << MAXN], T;

int Memoization(int Node, int state) {
    if(dp[Node][state] != oo)
        return dp[Node][state];
    vector <int> v;
    for(int i = 0 ; i < N ; ++ i)
        if(state & ( 1 << i ) && i != Node)  /// in state am bit de 1 pe pozitia i
            v.push_back(i);
    for(int i = 0 ; i < ( 1 << v.size() ) ; ++ i) { /// iau toate posibilitatiile de comb a v
        int mask = 0;
        for(int j = 0 ; j < v.size() ; ++ j)
            if(i & (1 << j))
                mask |= (1 << v[j]);
        for(int j = 0 ; j < v.size() ; ++ j)
            if(i & (1 << j))
            dp[Node][state] = min(dp[Node][state],  c[Node][v[j]] +
                                  max( Memoization(v[j], mask),  Memoization(Node, state ^ mask)));
    }
    return dp[Node][state];
}

inline void Solve() {
    fin >> N;
    for(int i = 0 ; i < N ; ++ i) {
        for(int j = 0 ; j < N ; ++ j)
            fin >> c[i][j];
        for(int j = 0 ; j < (1 << N) ; ++ j)
            dp[i][j] = oo;
        dp[i][(1 << i)] = 0;
    }
    fout << Memoization(0, (1  << N) - 1) << '\n';
}

int main() {
    for(fin >> T ; T ; -- T) {
        Solve();
    }
    fin.close();
    fout.close();
    return 0;
}
