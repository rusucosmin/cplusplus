#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "3color.in";
const char outfile[] = "3color.out";

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

int N, M, color[MAXN];
Graph G;
bitset <106> Used;

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        ++ x;
        ++ y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i) {
        Used.reset();
        for(It it = G[i].begin(), fin = G[i].end(); it != fin ; ++ it)
            Used[color[*it]] = true;
        for(int j = 1 ; j <= 100; ++ j)
            if(!Used[j]) {
                color[i] = j;
                break;
            }
    }
    for(int i = 1 ; i <= N ; ++ i)
        fout << color[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
