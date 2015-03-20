#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <fstream>

using namespace std;

const char infile[] = "cristal.in";
const char outfile[] = "cristal.out";

const int MAXN = 55;
const int oo = 0x3f3f3f3f;

ifstream fin(infile);
ofstream fout(outfile);

int N, M, dfLevel[MAXN], lowLink[MAXN];
vector <int> G[MAXN];
bitset <MAXN> critical;

void DFs(int Node, int Father, int actLevel) {
    dfLevel[Node] = lowLink[Node] = actLevel;
    bool critic = false;
    int sons = 0;
    for(vector<int> :: iterator it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!dfLevel[*it]) {
            ++ sons;
            DFs(*it, Node, actLevel + 1);
            lowLink[Node] = min(lowLink[Node], lowLink[*it]);
            critic |= (lowLink[*it] >= dfLevel[Node]);
        }
        else lowLink[Node] = min(lowLink[Node], dfLevel[*it]);
    }
    if(Father == Node) { /// root of biconnected component
        if(sons > 1)
            critical[Node] = true;
    }
    else critical[Node] = critic;
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 1, 1);
    for(int i = 1 ; i <= N ; ++ i)
        if(!critical[i])
            fout << i << ' ';
    fin.close();
    fout.close();
    return 0;
}
