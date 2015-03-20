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

const char infile[] = "2sec.in";
const char outfile[] = "2sec.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1001005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN];
int a[MAXN], b[MAXN];
int N;

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        s[i] = x;
    }
    int sMax = -oo, sum = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        int nr = -(int)s[i];
        if(sum < 0)
            sum = nr;
        else sum += nr;
        sMax = max(sMax, sum);
        a[i] = -sMax;
    }
    sMax = -oo;
    sum = 0;
    for(int i = N ; i ; -- i) {
        if(sum < 0)
            sum = s[i];
        else sum += s[i];
        sMax =  max(sMax, sum);
        b[i] = sMax;
    }
    int ans = -oo;
    for(int i = 1 ; i <= N ; ++ i)
        ans = max(ans, b[i] - a[i]);
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
