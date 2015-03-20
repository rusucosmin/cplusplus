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

const char infile[] = "triangles.in";
const char outfile[] = "triangles.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 2000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

pair<int, int> v[150005];
int N, K;

int main() {
    fin >> N >> K;
    N = min(N, 150000);
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> v[i].first;
        v[i].second = i;
    }
    sort(v + 1, v + N + 1);
    for(int i = K ; i <= N ; ++ i)
        if(v[i - K + 1].first + v[i - K + 2].first >= v[i].first) {
            for(int j = i - K + 1 ; j <= i ; ++ j)
                fout << v[j].second << ' ';
            return 0;
        }
    fout << "-1\n";
    return 0;
}
