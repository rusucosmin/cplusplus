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

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 305;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long double A, D;
long long N;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> A >> D >> N;
    long double _zero = 0;
    for(long long i = 1 ; i <= N ; ++ i) {
        long double x = ((1.0 * i * D) / (1.0 * A));
        int aux = floor(x);
        long double chestie = 1.0 * i * D - 1.0 * aux * A;
        aux %= 4;
        cout << fixed << setprecision(10);
        if(aux == 0) {
            cout << chestie << " " << _zero << '\n';
        }
        if(aux == 1) {
            cout << A << " " << chestie << '\n';
        }
        if(aux == 2) {
            cout << A - chestie << " " << A << '\n';
        }
        if(aux == 3) {
            cout << _zero << " " << A - chestie<< '\n';
        }
    }
    fin.close();
    fout.close();
    return 0;
}
