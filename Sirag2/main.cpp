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

const char infile[] = "sirag2.in";
const char outfile[] = "sirag2.out";

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

int tests;
char s[MAXN];
int N, L, T[MAXN], A[MAXN], Ans;
deque <int> dq;

int main() {
    fin >> tests;
    while(tests -- ) {
        fin >> N >> L >> (s + 1);
        Ans = 1;
        dq.clear();
        for(int i = 1 ; i <= N ; ++ i) {
            if(i > L && s[i] == '*')
                A[i] = A[i - L];
            else A[i] = i;
            T[i] = 1;
            if(i > L && (s[i] == '*' || s[A[i - L]] == '*' || s[i] == s[A[i - L]]))
                T[i] = T[i - L] + 1;
                else if(i > L)
                    T[i] = (i - A[i - L]) / L;
            while(!dq.empty() && T[dq.back()] >= T[i])
                dq.pop_back();
            dq.push_back(i);
            while(!dq.empty() && i - dq.front() > L - 1)
                dq.pop_front();
            Ans = max(Ans, T[dq.front()]);
        }
        fout << L * Ans << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
