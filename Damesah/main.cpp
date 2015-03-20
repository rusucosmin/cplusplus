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

const char infile[] = "damesah.in";
const char outfile[] = "damesah.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 14;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, goodConfs, st[MAXN];
bitset <MAXN> c, firstD, secondaryD;

void Back(const int &k) {
    if(k == N + 1) {
        if(!goodConfs ++ )
            for(int i = 1 ; i <= N ; ++ i)
                fout << st[i] << ' ';
        return;
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!c[i] && !firstD[k - i + N] && !secondaryD[k + i]) {
            c[i] = firstD[k - i + N] = secondaryD[k + i] = true;
            st[k] = i;
            Back(k + 1);
            c[i] = firstD[k - i + N] = secondaryD[k + i] = false;
        }

}

int main() {
    fin >> N;
    Back(1);
    fout << '\n' << goodConfs << '\n';
    fin.close();
    fout.close();
    return 0;
}
