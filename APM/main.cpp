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

const char infile[] = "apm.in";
const char outfile[] = "apm.out";

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


class DisjointSets {
public:
    DisjointSets() {
    }
    DisjointSets(int _N) {
        father.resize(_N + 1);
        N = _N;
        for(int i = 1 ; i <= N ; ++ i)
            father[i] = i;
    }
    int Unite(int x, int y) {
        int Tx = Find(x);
        int Ty = Find(y);
        if(Tx == Ty)
            return 0;
        father[Find(x)] = Find(y);
        return 1;
    }
    int Find(int x) {
        if(father[x] != x)
            father[x] = Find(father[x]);
        return father[x];
    }
private:
    vector <int> father;
    int N;
};

class UndirectedGraph {
private:
    vector <pair<int, pair<int, int> > > Edges;
public:
    int N;
    DisjointSets *D;
    UndirectedGraph(int N) {
        D = new DisjointSets(N);
    }
    void addEdge(int x, int y, int cost) {
        Edges.push_back(make_pair(cost, make_pair(x, y)));
    }
    void getAPM() {
        vector <pair<int, int> > treeEdges;
        sort(Edges.begin(), Edges.end());
        int ans = 0;
        for(auto it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it) {
            int x = it->second.first;
            int y = it->second.second;
            int cost = it->first;
            if(D->Unite(x, y)) {
                ans += cost;
                treeEdges.push_back(make_pair(x, y));
            }
        }
        fout << ans << '\n' << treeEdges.size() << '\n';
        for(auto it : treeEdges)
            fout << it.first << ' ' << it.second << '\n';
    }
};

int main() {
    int N, M;
    fin >> N >> M;
    UndirectedGraph G(N);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        G.addEdge(x, y, z);
    }
    G.getAPM();
    fin.close();
    fout.close();
    return 0;
}
