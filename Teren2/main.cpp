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

const char infile[] = "teren2.in";
const char outfile[] = "teren2.out";

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

#define x first
#define y second

int N, D;
pair<int, int> v[MAXN];
double area;

int main() {
    fin >> N >> D;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> v[i].first >> v[i].second;
    v[N + 1] = v[1];
    for(int i = 1 ; i <= N ; ++ i)
        area = (area + (v[i + 1].x * v[i].y - v[i].x * v[i + 1].y));
    double ans = area;
    for(int i = 1 ; i <= N ; ++ i) {
        area -= v[i-1].x*(v[i].y-v[i-2].y)+v[i+1].x*(v[i+2].y-v[i].y)+v[i].x*(v[i+1].y-v[i-1].y);
        v[i].x += D;
        area += v[i-1].x*(v[i].y-v[i-2].y)+v[i+1].x*(v[i+2].y-v[i].y)+v[i].x*(v[i+1].y-v[i-1].y);
        v[i].x -= D;
        ans = max(ans, area);
        area -= v[i-1].x*(v[i].y-v[i-2].y)+v[i+1].x*(v[i+2].y-v[i].y)+v[i].x*(v[i+1].y-v[i-1].y);
        v[i].x -= D;
        area += v[i-1].x*(v[i].y-v[i-2].y)+v[i+1].x*(v[i+2].y-v[i].y)+v[i].x*(v[i+1].y-v[i-1].y);
        v[i].x += D;
        ans = max(ans, area);
        area -= v[i-1].x*(v[i].y-v[i-2].y)+v[i+1].x*(v[i+2].y-v[i].y)+v[i].x*(v[i+1].y-v[i-1].y);
        v[i].y += D;
        area += v[i-1].x*(v[i].y-v[i-2].y)+v[i+1].x*(v[i+2].y-v[i].y)+v[i].x*(v[i+1].y-v[i-1].y);
        v[i].y -= D;
        ans = max(ans, area);
        area -= v[i-1].x*(v[i].y-v[i-2].y)+v[i+1].x*(v[i+2].y-v[i].y)+v[i].x*(v[i+1].y-v[i-1].y);
        v[i].y -= D;
        area += v[i-1].x*(v[i].y-v[i-2].y)+v[i+1].x*(v[i+2].y-v[i].y)+v[i].x*(v[i+1].y-v[i-1].y);
        v[i].y += D;
        ans = max(ans, area);
    }
    fout << fixed << setprecision(6) << ans / 2.0 << '\n';
    fin.close();
    fout.close();
    return 0;
}
