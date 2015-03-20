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

const char infile[] = "gsr.in";
const char outfile[] = "gsr.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char S;
int B, K;
int rest = 0;
int nr = 0;

int conv(char c) {
    if(c >= '0' && c <= '9')
        return c - '0';
    return 10 + c - 'A';
}

int main() {
    fin >> B >> K;
    while(fin >> S)
        rest = (1LL * rest * B + conv(S)) % K;
    fout << rest << '\n';
    fin.close();
    fout.close();
    return 0;
}
