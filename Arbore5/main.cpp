#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "arbore5.in";
const char outfile[] = "arbore5.out";

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

int dp[MAXN], Ans, N, M;
Graph G;

void DFs(const int &Node, const int &Father) {
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(*it != Father) {
            DFs(*it, Node);
            dp[Node] += dp[*it];
        }
    if(Node != 1)
        Ans += (!(dp[Node] % 2));
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        ++ dp[x];
        ++ dp[y];
    }
    DFs(1, 0);
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
