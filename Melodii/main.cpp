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

const char infile[] = "melodii.in";
const char outfile[] = "melodii.out";

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

int T, MOD, cnt;
long long N;
bitset <MAXN> Used;
vector <int> v;

int main() {
    fin >> T >> MOD;
    int a = 1, b = 2;
    v.push_back(oo);
    v.push_back(a);
    v.push_back(b);
    cnt ++ ;
    cnt ++ ;
    while(true) {
        int c = (a + b) % MOD;
        if(a == 0 && b == 1)
            break;
        ++ cnt;
        v.push_back(c);
        Used[c] = true;
        a = b;
        b = c;
    }
    while(T -- ) {
        fin >> N;
        fout << v[((N - 1) % cnt) + 1] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
