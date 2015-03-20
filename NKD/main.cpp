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

const char infile[] = "nkd.in";
const char outfile[] = "nkd.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 10005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, K, D;
char S[MAXN], st[15];
bitset <MAXN> Used;

void Back(int p, int _hashVal) {
    if(p == K + 1) {
        if(_hashVal == 0) {
            for(int i = 1 ; i <= N - K ; ++ i)
                fout << S[i];
            for(int i = 1 ; i < p ; ++ i)
                fout << st[i];
            exit(0);
        }
        return ;
    }
    for(int i = N - K + 1 ; i <= N ; ++ i)
        if(!Used[i]) {
            Used[i] = true;
            st[p] = S[i];
            Back(p + 1, (_hashVal * 10 + (S[i] - '0')) % D);
            Used[i] = false;
        }
}

int main() {
    fin >> (S + 1) >> K >> D;
    N = strlen(S + 1);
    int _hashVal = 0;
    for(int i = 1 ; i <= N - K ; ++ i)
        _hashVal = (_hashVal * 10 + (S[i] - '0')) % D;
    Back(1, _hashVal);
    fout << "-1\n";
    fin.close();
    fout.close();
    return 0;
}
