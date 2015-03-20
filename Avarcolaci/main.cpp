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

const char infile[] = "avarcolaci.in";
const char outfile[] = "avarcolaci.out";

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

int n, x;
vector <int> answers;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int t;
    fin >> t;
    for(int test = 1 ; test <= t ; test ++ ) {
        fin >> n;
        int elmaj = -1, k = 0;
        for(int i = 1; i <= 2 * n ; i ++ ) {
            fin >> x;
            if(k == 0) {
                elmaj = x;
                k = 1;
            }
            else if(elmaj == x)
                ++ k;
            else
                -- k;
        }
        answers.push_back(elmaj);
    }
    fin.close();
    fin.open("avarcolaci.in");
    fin >> t;
    for(int test = 1 ; test <= t ; ++ test) {
        fin >> n;
        int elmaj = answers[test-1];
        int k = 0;
        for(int i = 1 ; i <= 2 * n ; i ++) {
            fin >> x;
            if(x == elmaj)
                ++ k;
        }
        if(k < n + 1)
            answers[test - 1] = -1;
        if(answers[test - 1] == -1)
            fout << "Mozart\n";
        else
            fout << answers[test - 1] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
