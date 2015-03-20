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

const char infile[] = "dreptunghi2.in";
const char outfile[] = "dreptunghi2.out";

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

int T, N, maxx, minx, maxy, miny;

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        int bestdistx = -oo;
        int lowestdistx = oo;
        pair<int, int> bestPointx;
        pair<int, int> lowestPointx;
        int bestdisty = -oo;
        int lowestdisty = oo;
        pair<int, int> bestPointy;
        pair<int, int> lowestPointy;
        fin >> N;
        for(int i = 1 ; i <= N ; ++ i) {
            int x, y;
            fin >> x >> y;
            if(bestdistx < y - x) {
                bestdistx = y - x;
                bestPointx = make_pair(x, y);
            }
            if(lowestdistx > y - x) {
                lowestdistx = y - x;
                lowestPointx = make_pair(x, y);
            }
            if(bestdisty < y + x) {
                bestdisty = y + x;
                bestPointy = make_pair(x, y);
            }
            if(lowestdisty > y + x) {
                lowestdisty = y + x;
                lowestPointy = make_pair(x, y);
            }
        }
        fout << fixed << setprecision(3) << (bestdistx - lowestdistx) * (bestdisty - lowestdisty) / 2.0 << '\n';

    }
    fin.close();
    fout.close();
    return 0;
}
