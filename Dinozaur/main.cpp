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

const char infile[] = "dinozaur.in";
const char outfile[] = "dinozaur.out";

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

bool fr[30];
string s;

int main() {
    fin >> s;
    for(int i = 0 ; i < s.size() ; ++ i) {
        if(fr[s[i] - 'a']) {
            fout << "1\n";
            return 0;
        }
        fr[s[i] - 'a'] = true;
    }
    fout << "0\n";
    return 0;
}
