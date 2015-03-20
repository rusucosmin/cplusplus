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

const char infile[] = "turnuri2.in";
const char outfile[] = "turnuri2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, H[MAXN], K[MAXN], pos[MAXN], best[MAXN], Ans;

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> H[i] >> K[i];
    memset(pos, 0, sizeof(pos));
    Ans = -1;
    for(int i = N ; i > 0 ; -- i) {
        int maxi = K[i];
        int j;
        for(j = i + 1 ; j <= N && H[j] <= H[i] ; j = pos[j])
            maxi = max(maxi, best[j]);
        maxi = max(maxi, K[j]);
        best[i] = maxi;
        pos[i] = j;
    }
    for(int i = 1 ; i <= N ; ++ i) {
        int maxi = K[i];
        int j;
        for(j = i - 1 ; j > 0 && H[j] <= H[i] ; j = pos[j])
            maxi = max(maxi, best[j]);
        maxi = max(maxi, K[j]);
        best[i] = max(maxi, best[i]);
        fout << best[i] << '\n';
        pos[i] = j;
    }
    fin.close();
    fout.close();
    return 0;
}
