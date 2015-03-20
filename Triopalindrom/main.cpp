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

const char infile[] = "triopalindrom.in";
const char outfile[] = "triopalindrom.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 5005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN];
pair<int, int> _hash[MAXN];
int n;

int main() {
    int ans = 0;
    fin >> (s + 1);
    n = strlen(s + 1);
    for(int l = 1 ; l <= n / 3 ; ++ l) {
        for(int i = 1 ; i <= n - l + 1 ; ++ i)
            _hash[i] = make_pair(_hash[i].first * 31 + s[i + l - 1] - 'a', _hash[i].second * 37 + s[i + l - 1] - 'a');
        for(int i = 1 ; i <= n - 2 * l ; ++ i)
            if(_hash[i] == _hash[i + l] && _hash[i + l] == _hash[i + 2*l])
                ++ ans;
    }
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
