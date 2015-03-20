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

const char infile[] = "cai.in";
const char outfile[] = "cai.out";

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

int T, N;

inline int whoWillWin(const int &gigel, const int &ionel) {
    if(gigel > ionel)
        return 1;
    if(gigel == ionel)
        return 0;
    return -1;
}

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        fin >> N;
        vector <int> gigelHorses, ionelHorses;
        gigelHorses.resize(N, 0);
        ionelHorses.resize(N, 0);
        vector <vector <int> >dp(N, vector <int>(N, 0));
        for(int i = 0 ; i < N ; ++ i)
            fin >> gigelHorses[i];
        for(int i = 0 ; i < N ; ++ i)
            fin >> ionelHorses[i];
        sort(gigelHorses.begin(), gigelHorses.end(), greater<int>());
        sort(ionelHorses.begin(), ionelHorses.end(), greater<int>());
        for(int i = 0 ; i < N ; ++ i)
            dp[i][i] = whoWillWin(gigelHorses[i], ionelHorses[N - 1]);
        for(int i = 1 ; i < N ; ++ i)
            for(int j = 0 ; j < N - i ; ++ j) {
                int ind1 = j;
                int ind2 = i + j;
                dp[ind1][ind2] = max(dp[ind1 + 1][ind2] + whoWillWin(gigelHorses[ind1], ionelHorses[ind1 + N - ind2 - 1]),
                                     dp[ind1][ind2 - 1] + whoWillWin(gigelHorses[ind2], ionelHorses[ind1 + N - ind2 - 1]));
            }
        fout << dp[0][N-1] * 200 << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
