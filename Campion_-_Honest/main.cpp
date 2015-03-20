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

const char infile[] = "honest.in";
const char outfile[] = "honest.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
Graph G, Gt;
bitset <MAXN> Used;
int cool[MAXN];
vector <int> tsort;

void DFs(const int &Node) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[it->first])
            DFs(it->first);
    tsort.push_back(Node);
}

void DFs2(const int &Node) {

}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        char s;
        fin >> x >> s >> y;
        if(s == 'c') {
            G[x].push_back(make_pair(y, 1));
            Gt[y].push_back(make_pair(x, 1));
        }
        else {
            G[x].push_back(make_pair(y, -1));
            Gt[y].push_back(make_pair(x, -1));
        }
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFs(i);
    vector <int> :: reverse_iterator it = tsort.rbegin();
    cool[*it] = 1;
    for(++ it ; it != tsort.rend() ; ++ it) {
        int how = 0;
        for(It i = Gt[*it].begin(), fin = Gt[*it].end(); i != fin ; ++ i) {
            if(i->second > 0) {
                if(!how)
                    how = cool[i->first];
                else if(cool[i->first] * how < 0) {
                    fout << "contradictie\n";
                    return 0;
                }
            }
            else {
                if(!how)
                    how = -cool[i->first];
                else if(-cool[i->first] * how < 0) {
                    fout << "contradictie\n";
                    return 0;
                }
            }
        }
        cool[*it] = how;
    }
    int sum = 0;
    for(int i = 1 ; i <= N ; ++ i)
        sum += (cool[i] > 0);
    int sign = 1;
    if(sum < N / 2)
        sign = -1;
    for(int i = 1 ; i <= N ; ++ i)
        if(sign * cool[i] < 0)
            fout << "0\n";
        else fout << "1\n";
    fin.close();
    fout.close();
    return 0;
}
