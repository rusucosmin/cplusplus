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

const char infile[] = "dragonas.in";
const char outfile[] = "dragonas.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int main() {
    int T;
    fin >> T;
    for(int i = 1 ; i <= T ; ++ i) {
        int N, M, ll, cl, ld, cd;
        fin >> N >> M >> ll >> cl >> ld >> cd;
        if(ll==N || ll>=ld || N-ll<(N-ld+abs(cl-cd))) {
            fout << "Lulu\n";
            continue;
        }
        fout << "Smaug\n";
    }
    fin.close();
    fout.close();
    return 0;
}
