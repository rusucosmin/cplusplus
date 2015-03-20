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

const char infile[] = "restrictii.in";
const char outfile[] = "restrictii.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, M, VAL;

int main() {
    fin >> N >> M >> VAL;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        G[y].push_back(make_pair(x, z));
    }
    int lastx, lasty, lastz, x, y, z, newz;
    bool ok = 1;
    for(int i = N ; i > 0 && ok ; -- i) {
        int j = G[i].size();
        if(!j)
            continue;
        sort(G[i].begin(), G[i].end());
        -- j;
        lastx = G[i][j].first;
        lastz = G[i][j].second;
        for(-- j ; j >= 0 && ok ; -- j) {
            x = G[i][j].first;
            z = G[i][j].second;
            if(x == lastx) {
                if(z != lastz) {
                    ok = 0;
                    break;
                }
                else -- M;
            }
            else {
                newz = z - lastz;
                if(newz < 0)
                    newz += VAL;
                G[lastx - 1].push_back(make_pair(x, newz));
            }
            lastx = x;
            lastz = z;
        }
        vector <pair<int, int> >().swap(G[i]);
    }
    if(!ok) {
        fout << "0\n";
        return 0;
    }
    int Ans = 1;
    M = N - M;
    for(int i = 1 ; i <= M ; ++ i)
        Ans = (1LL * Ans * VAL) % 666013;
    fout << Ans << '\n';
    return 0;
}
