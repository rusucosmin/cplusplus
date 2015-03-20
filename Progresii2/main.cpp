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

const char infile[] = "progresii2.in";
const char outfile[] = "progresii2.out";

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

inline long long getAns(long long N, long long V) {
    if(N == 1)
        return V;
    long long nrRatii = (V - 1) / (N - 1);
    long long exclude = (N - 1) * nrRatii * (nrRatii + 1) / 2;
    return V * nrRatii - exclude;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    long long T, N, V;
    fin >> T;
    while(T -- ) {
        fin >> V >> N;
        fout << getAns(N, V) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
