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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G, Gt;
int N, M;
bitset <MAXN> Used;
vector <int> tsort;

#define fin cin
#define fout cout

void DFs(const int &Node) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFs(*it);
    tsort.push_back(Node);
}

void DFs2(const int &Node) {
    Used[Node] = true;
    for(It it = Gt[Node].begin(), fin = Gt[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFs2(*it);
}

int main() {
    cin.sync_with_stdio(false);
    while(true) {
        for(int i = 1 ; i <= N ; ++ i) {
            vector <int>().swap(G[i]);
            vector <int>().swap(Gt[i]);
        }
        tsort.clear();
        Used.reset();
        fin >> N >> M;
        if(!N && !M)
            return 0;
        short ctc = 0;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            fin >> x >> y >> z;
            G[x].push_back(y);
            Gt[y].push_back(x);
            if(z == 2) {
                G[y].push_back(x);
                Gt[x].push_back(y);
            }
        }
        for(int i = 1 ; i <= N ; ++ i)
            if(!Used[i])
                DFs(i);
        Used.reset();
        for(vector <int> :: reverse_iterator it = tsort.rbegin(), fin = tsort.rend() ; it != fin ; ++ it)
            if(!Used[*it]) {
                ++ ctc;
                if(ctc > 1)
                    break;
                DFs2(*it);
            }
        //fout << ctc << ' ';
        if(ctc > 1)
            fout << "0\n";
        else fout << "1\n";
    }
    return 0;
}
