#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "dosare.in";
const char outfile[] = "dosare.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 16005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
long long cst[MAXN];
Graph G;
long long Ans;

struct classComp {
    inline bool operator () (const int &a, const int &b) {
        return cst[a] > cst[b];
    }
};

void DFs(const int &Node, const int &Level) {
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        DFs(*it, Level + 1);
        cst[Node] += cst[*it];
    }
    sort(G[Node].begin(), G[Node].end(), classComp());
}

void DFs(const int &Node) {
    int deeps = 0;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        Ans += 1LL * (++deeps) * cst[*it];
        DFs(*it);
    }
}

int main() {
    fin >> N;
    for(int i = 2 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        G[x].push_back(i);
    }
    for(int i = 1 ; i <= N ; ++ i)
        fin >> cst[i];
    DFs(1, 1);
    DFs(1);
    fout << Ans + cst[1] << '\n';
    fin.close();
    fout.close();
    return 0;
}
