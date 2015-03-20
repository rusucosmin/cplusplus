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

const char infile[] = "semne3.in";
const char outfile[] = "semne3.out";

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

void Swap(vector <int> &v, int x, int y) {
    reverse(v.begin() + x, v.begin() + y + 1);
}

int main() {
    int N;
    string s;
    fin >> N >> s;
    vector <int> sol(N);
    for(int i = 0 ; i < N ; ++ i)
        sol[i] = i + 1;
    int posx = 0, bug = 0;
    for(int i = 0 ; i < N - 1 ; ++ i)
        if(s[i] == '>') {
            if(!bug) {
                posx = i;
                bug = 1;
            }
        }
        else {
            if(bug > 0) {
                Swap(sol, posx, i);
            }
            bug = 0;
        }
    if(bug) {
        Swap(sol, posx, N - 1);
        bug = 0;
    }
    for(int i = 0 ; i < N ; ++ i)
        fout << sol[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
