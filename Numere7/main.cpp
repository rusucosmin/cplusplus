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

const char infile[] = "numere7.in";
const char outfile[] = "numere7.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 25;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long N;
char S[MAXN];
long long fact[MAXN];
int fr[MAXN];

inline long long getPermutationNumber(void) {
    long long sum = 0;
    for(int i = 0 ; i < 10 ; ++ i)
        sum += fr[i];
    long long nc = fact[sum];
    for(int i = 0 ; i < 10 ; ++ i)
        if(fr[i])
            nc /= fact[fr[i]];
    return nc;
}

string Solve(const long long &N) {
    long long nr = 0, temp;
    for(int i = 0 ; i < 10 ; ++ i)
        if(fr[i]){
            -- fr[i];
            temp = getPermutationNumber();
            nr += temp;
            if(nr >= N)
                return (char) (i + '0') + Solve(N - nr + temp);
            else ++ fr[i];
        }
    return "";
}

int main() {
    fin >> N >> S;
    fact[0] = 1;
    for(int i = 1 ; i < MAXN ; ++ i)
        fact[i] = fact[i - 1] * i;
    for(int i = 0 ; S[i] ; ++ i)
        ++ fr[S[i] - '0'];
    fout << Solve(N) << '\n';
    fin.close();
    fout.close();
    return 0;
}
