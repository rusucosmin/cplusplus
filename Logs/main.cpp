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

const char infile[] = "logs.in";
const char outfile[] = "logs.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1505;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
char m[MAXN];
pair<int, int> st[2 * MAXN];

int main() {
    fin >> N >> M;
    int Ans = 0;
    for(int i = 1 ; i <= M ; ++ i)
        st[i] = make_pair(i, 0);
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> (m + 1);
        int indst = 0, indfn = M;
        for(int j = 1 ; j <= M ; ++ j)
            if(m[st[j].first] == '1') {
                st[++ indst] = st[j];
                ++ st[indst].second;
            }
            else st[++ indfn] = st[j];
        for(int j = M + 1 ; j <= indfn ; ++ j)
            if(m[st[j].first] == '0') {
                st[++ indst].second = 0;
                st[indst].first = st[j].first;
            }
        for(int j = 1 ; j <= M ; ++ j)
            Ans = max(Ans, st[j].second * j);
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
