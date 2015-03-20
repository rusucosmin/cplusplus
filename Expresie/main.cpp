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

const char infile[] = "expresie.in";
const char outfile[] = "expresie.out";

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

int N, v[MAXN];
long long best, sum, _actbest;

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> v[i];
        sum += 1LL * v[i];
    }
    for(int i = 1 ; i < N ; ++ i)
        for(int j = i + 1 ; j <= N ; ++ j) {
            if(j != i + 1)
                _actbest = sum-v[i-1]-v[i]-v[j-1]-v[j] + 1LL*v[i-1]*v[i] + 1LL*v[j-1]*v[j];
            else _actbest = sum-v[i-1]-v[i]-v[j]+v[i-1]*1LL*v[i]*v[j];
            best = max(best, _actbest);
        }
    fout << best << '\n';
    fin.close();
    fout.close();
    return 0;
}
