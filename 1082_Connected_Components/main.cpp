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

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 30;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M;
vector <int> G[MAXN];
vector<set<int> > S;
set<int>actComp;
bitset <MAXN> Used;

#define fin cin
#define fout cout

void DFs(const int &Node) {
    Used[Node] = true;
    actComp.insert(Node);
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(!Used[*it]) {
            DFs(*it);
        }
}

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        for(int i = 0 ; i < N ; ++ i)
            G[i].clear();
        Used.reset();
        S.clear();
        fin >> N >> M;
        for(int i = 1 ; i <= M ; ++ i) {
            char x, y;
            fin >> x >> y;
            G[x - 'a'].push_back(y - 'a');
            G[y - 'a'].push_back(x - 'a');
        }
        for(int i = 0 ; i < N ; ++ i) {
            if(!Used[i]) {
                actComp.clear();
                DFs(i);
                S.push_back(actComp);
            }
        }
        fout << "Case #" << test << ":\n";
        for(int i = 0 ; i < S.size() ; ++ i) {
            for(set<int> :: iterator it = S[i].begin(), fin = S[i].end(); it != fin ; ++ it)
                fout << (char)(*it + 'a') << ',';
            fout << "\n";
        }
        fout << S.size() << " connected components\n\n";
    }
    return 0;
}
