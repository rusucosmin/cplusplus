#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "g2mm.in";
const char outfile[] = "g2mm.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 30005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
Graph G;
bitset <MAXN> Covered, Used;
vector <pair<int, int> > Ans;

void DFs(const int &Node) {
    Used[Node] = true;
    vector <int> Sons;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it]) {
            DFs(*it);
            if(!Covered[*it])
                Sons.push_back(*it);
        }
    if(Sons.size() & 1) {
        Sons.push_back(Node);
    }
    for(int i = 0 ; i < Sons.size() ; i += 2) {
        Covered[Sons[i]] = true;
        Covered[Sons[i + 1]] = true;
        Ans.push_back(make_pair(Sons[i], Sons[i+1]));
    }
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1);
    fout << "1\n";
    for(int i = 0 ; i < Ans.size() ; ++ i)
        fout << Ans[i].first << ' ' << Ans[i].second << '\n';
    fin.close();
    fout.close();
    return 0;
}
