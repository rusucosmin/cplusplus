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

int N, M, Father[MAXN];
vector <pair<int, pair<int, int> > > Edges;

int Find(const int &Node) {
    if(Father[Node] != Node)
        Father[Node] = Find(Father[Node]);
    return Father[Node];
}

#define fin cin
#define fout cout

int main() {
    cin.sync_with_stdio(false);
    while(true) {
        Edges.clear();
        fin >> N >> M;
        if(!N && !M)
            return 0;
        long long Total = 0, Ans = 0;
        for(int i = 1 ; i <= N ; ++ i)
            Father[i] = i;
        for(int i = 0 ; i < M ; ++ i) {
            int x, y, z;
            fin >> x >> y >> z;
            ++ x;
            ++ y;
            Total += z;
            Edges.push_back(make_pair(z, make_pair(x, y)));
        }
        sort(Edges.begin(), Edges.end());
        for(vector < pair<int, pair<int, int> > > :: iterator it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it) {
            int Tx = Find(it->second.first);
            int Ty = Find(it->second.second);
            if(Tx == Ty)
                continue;
            Father[Tx] = Ty;
            Ans += it->first;
        }
        fout << Total - Ans << '\n';
    }
    return 0;
}
