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

const char infile[] = "piese.in";
const char outfile[] = "piese.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int where[MAXN][MAXN];
int cnt, N, M;

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            if(!where[i][j]) {
                ++ cnt;
                int stp = 1;
                for( ; i + (stp << 1) - 1 <= N && j + (stp << 1) - 1 <= M ; stp <<= 1);
                for(int x = i ; x <= i + stp - 1 ; ++ x)
                    for(int y = j ; y <= j + stp - 1 ; ++ y)
                        where[x][y] = cnt;
            }
    fout << cnt << '\n';
    for(int i = 1 ; i <= N ; ++ i, fout << '\n')
        for(int j = 1 ; j <= M ; ++ j)
            fout << where[i][j] << ' ';
    fin.close();
    fout.close();
    return 0;
}
