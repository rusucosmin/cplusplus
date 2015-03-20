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

const char infile[] = "switch.in";
const char outfile[] = "switch.out";

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

void longest_palind(const string &s) {
    // Write your code here
    // To print results to the standard output you can use the cout stream
    // Example: cout << "Hello world!";
    string ans = "";
    for(int len = 1 ; len < s.size(); ++ len) {
        for(int i = 0; i + len - 1 < s.size() ; ++ i) {
            string aux = s.substr(i, len);
            cerr << i << ' ' << len << ' ' << aux << '\n';
            string bux = aux;
            reverse(bux.begin(), bux.end());
            if(aux == bux && ans.size() < len)
                ans = aux;
        }
    }
    cerr << ans << '\n';
}

int main() {
    longest_palind("abcdxyzyxabcdaaa");
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int T, a[2][2][2], nr[2];
    fin >> T;
    for(int t = 1 ; t <= T ; ++ t) {
        nr[0] = nr[1] = 0;
        for(int k = 0 ; k < 2 ; ++ k)
            for(int i = 0 ; i < 2 ; ++ i)
                for(int j = 0 ; j < 2 ; ++ j)
                    fin >> a[k][i][j],
                    nr[k] += a[k][i][j];
        if(abs(nr[0] - nr[1]) & 1)
            fout << "NU\n";
        else
            fout << "DA\n";

    }
    fin.close();
    fout.close();
    return 0;
}
