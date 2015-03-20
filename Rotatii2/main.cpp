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

const char infile[] = "rotatii2.in";
const char outfile[] = "rotatii2.out";

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

int N;
int left[MAXN], right[MAXN];
vector < int > G[3];

inline void rotateRight(int Node) {
    int aux = right[Node];
    right[Node] = left[aux];
    left[aux] = Node;
    Node = aux;
}

inline void solveBST(int type) {
    memset(g, 0, sizeof(g));
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> left[i] >> right[i];
        ++ g[left[i]];
        ++ g[right[i]];
    }
    int root = 0;
    for(root = 1 ; root <= N ; ++ root)
        if(!g[root])
            break;
    while(root) {
        while(right[root]) {
            rotateRight(root);
            G[type].push_back(root);
        }
        root = left[root];
    }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    NIL = new Node(0, 0, 0);
    fin >> N;
    solveBST(1);

    fin.close();
    fout.close();
    return 0;
}
