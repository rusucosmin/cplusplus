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

const char infile[] = "subsir1000.in";
const char outfile[] = "subsir1000.out";

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

int N, best[MAXN];
int ans, a;

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> a;
        int aux = a;
        int x = 0;
        for(int j = 2 ; j * j <= aux ; ++ j) {
            if(aux % j)
                continue;
            while(aux % j == 0)
                aux /= j;
            x = max(x, best[j]);
        }
        if(aux > 1)
            x = max(x, best[aux]);
        aux = a;
        for(int j = 2 ; j * j <= aux ; ++ j) {
            if(aux % j)
                continue;
            while(aux % j == 0)
                aux /= j;
            best[j] = x + 1;
        }
        if(aux > 1)
            best[aux] = x + 1;
        ans = max(ans, x + 1);
    }
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
