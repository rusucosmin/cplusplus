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

const char infile[] = "aria.in";
const char outfile[] = "aria.out";

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

int N;
pair<double, double> P[MAXN];

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> P[i].first >> P[i].second;
    P[N + 1] = P[1];
    double _area = 0;
    for(int i = 1 ; i <= N ; ++ i)
        _area += P[i].first * P[i + 1].second - P[i + 1].first * P[i].second;
    fout << fixed << setprecision(6) << _area * 0.5 << '\n';
    fin.close();
    fout.close();
    return 0;
}

