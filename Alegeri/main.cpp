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

const char infile[] = "alegeri.in";
const char outfile[] = "alegeri.out";

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

int N, M, Father[MAXN], T;
vector <pair<int, pair<int, int> > > edges;

int Find(int x) {
    if(Father[x] != x)
        Father[x] = Find(Father[x]);
    return Father[x];
}

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        fin >> N >> M;
        for(int i = 1 ; i <= N ; ++ i)
            Father[i] = i;
        int bagate = 0;
        for(int i = 1 ; i <= M ; ++ i) {
            int op, x, y, z;
            fin >> op >> x >> y;
            if(!op) {
                int tx = Find(x);
                int ty = Find(y);
                if(tx == ty)
                    continue;
                ++ bagate;
                Father[tx] = ty;
            }
            else {
                fin >> z;
                edges.push_back(make_pair(z, make_pair(x, y)));
            }
        }
        sort(edges.begin(), edges.end());
        long long Ans = 0;
        for(vector <pair<int, pair<int, int> > > :: iterator it = edges.begin(), fin = edges.end(); it != fin ; ++ it) {
            int tx = Find(it->second.first);
            int ty = Find(it->second.second);
            if(tx == ty)
                continue;
            ++ bagate;
            Father[tx] = ty;
            Ans += 1LL * it->first;
        }
        if(bagate != N - 1)
            Ans = -1;
        fout << Ans << '\n';
        vector <pair<int, pair<int, int> > > ().swap(edges);
    }
    fin.close();
    fout.close();
    return 0;
}
