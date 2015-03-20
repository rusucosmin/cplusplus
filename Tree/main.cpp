#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "tree.in";
const char outfile[] = "tree.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, root, Ans;
Graph G;
bitset <MAXN> Used;

void DFs(const int &Node, const int &Father) {
    int sons = 0, erasedsons = 0;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        DFs(*it, Node);
        if(!Used[*it])
            ++ sons;
    }
    if(sons > 1) {
        Ans += (sons - 1);
        Used[Node] = true;
    }
    if(sons == 1 && Node == root)
        ++ Ans;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        if(!x) {
            root = i;
            continue;
        }
        G[x].push_back(i);
    }
    DFs(root, 0);
    fout << 2*Ans-1 << '\n';
    fin.close();
    fout.close();
    return 0;
}
