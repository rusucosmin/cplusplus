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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, T;
map<string, int> Hash;
string sizes[] = {"XXL", "XL", "L", "M" , "S", "XS"};

#define fin cin
#define fout cout

vector <pair<string, string> > Ts;

bool Back(int p) {
    if(p == M)
        return true;
    bool ret = false;
    if(Hash[Ts[p].first] < N / 6) {/// I still have that tshirt
        ++ Hash[Ts[p].first];
        ret |= Back(p + 1);
        -- Hash[Ts[p].first];
    }
    if(Hash[Ts[p].second] < N / 6) {
        ++ Hash[Ts[p].second];
        ret |= Back(p + 1);
        -- Hash[Ts[p].second];
    }
    return ret;
}

int main() {
    cin.sync_with_stdio(false);
    fin >> T;
    for(int test = 1 ;test <= T ; ++ test) {
        Hash.clear();
        Ts.clear();
        fin >> N >> M;
        for(int i = 1 ; i <= M ; ++ i) {
            string x, y;
            fin >> x >> y;
            Ts.push_back(make_pair(x, y));
        }
        if(Back(0))
            fout << "YES\n";
        else fout << "NO\n";
    }
    return 0;
}
