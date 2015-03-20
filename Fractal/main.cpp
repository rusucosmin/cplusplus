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

const char infile[] = "fractal.in";
const char outfile[] = "fractal.out";

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

int K, y, x;

inline int DEI(int K, int x, int y) {
    if(K == 0)
        return 0;
    -- K;
    int iPow = (1 << K);
    if(x <= iPow && y <= iPow)
        return DEI(K, y, x);
    if(x > iPow && y <= iPow)
        return iPow * iPow + DEI(K, x - iPow, y);
    if(x > iPow && y > iPow)
        return 2 * iPow * iPow + DEI(K, x - iPow, y - iPow);
    return 3 * iPow * iPow + DEI(K, 2 * iPow - y + 1, iPow - x + 1);
}

int main() {
    fin >> K >> y >> x;
    fout << DEI(K, x, y);
    fin.close();
    fout.close();
    return 0;
}
