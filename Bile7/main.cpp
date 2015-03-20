#include <fstream>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <queue>

using namespace std;

const char infile[] = "bile7.in";
const char outfile[] = "bile7.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 5005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, P, K, Father[MAXN], Level[MAXN], Ans;
bitset <MAXN> red;
priority_queue < int, vector<int>, greater <int> > Heap;

void DFs(const int &Node, const int &actLevel) {
    Level[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(*it != Father[Node])
            DFs(*it, actLevel + 1);
}

void pushHeap(const int &Node) {
    if(!red[Node])
        Heap.push(Level[Node]);
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        pushHeap(*it);
}

void buildSolution(const int &Dad, const int &Node) {
    if(!Dad)
        return ;
    for(It it = G[Dad].begin(), fin = G[Dad].end(); it != fin ; ++ it) {
        if(*it == Node)
            continue;
        pushHeap(*it);
    }
    if(red[Dad]) {
        if(Heap.empty()) {
            fout << "-1\n";
            exit(0);
        }
        Ans += (Heap.top() - Level[Dad]);
        Heap.pop();
    }
    buildSolution(Father[Dad], Dad);
}

int main() {
    fin >> N >> P >> K;
    for(int i = 1; i <= N ; ++ i) {
        int x;
        fin >> x;
        for(int j = 1 ; j <= x ; ++ j) {
            int y;
            fin >> y;
            Father[y] = i;
            G[i].push_back(y);
        }
    }
    for(int i = 1 ; i <= K ; ++ i) {
        int x;
        fin >> x;
        red[x] = true;
    }
    DFs(1, 0);
    buildSolution(Father[P], P);
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
