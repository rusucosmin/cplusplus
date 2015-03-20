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

const char infile[] = "holiday.in";
const char outfile[] = "holiday.out";

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

inline int cmmdc(int a, int b) {
    if(b == 0)
        return a;
    return cmmdc(b, a%b);
}

int main() {
    int A, B, X;
    fin >> A >> B >> X;
    //if(abs(B - A) % X == 0)
    //    fout << X << '\n';
    //else
    fout << cmmdc(abs(B - A), X);
    fin.close();
    fout.close();
    return 0;
}
