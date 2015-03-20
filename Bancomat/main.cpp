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

const char infile[] = "bancomat.in";
const char outfile[] = "bancomat.out";

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

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int T;
    fin >> T;
    int b[] = {0, 1, 5, 10, 50, 100, 500}, a[10];
    for(int test = 1 ; test <= T ; ++ test) {
        /// 1, 5, 10, 50, 100, 500
        for(int i = 1 ; i <= 6 ; ++ i)
            fin >> a[i];
        int Q;
        fin >> Q;
        int q;
        bool ok = true;
        for(q = 1 ; q <= Q ; ++ q) {
            int x;
            fin >> x;
            for(int i = 6 ; i > 0 && x ; -- i) {
                if(a[i] && x >= b[i]) {
                    int aux = x / b[i];
                    aux = min(aux, a[i]);
                    a[i] -= aux;
                    x -= b[i] * aux;
                }
            }
            if(x != 0)
                ok = false;
        }
        if(ok)
            fout << "YES\n";
        else fout << "NO\n";
    }
    fin.close();
    fout.close();
    return 0;
}
