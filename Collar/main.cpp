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

const char infile[] = "collar.in";
const char outfile[] = "collar.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 65540;
const long long oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
long long v[2*MAXN];
long long ans[MAXN];

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> v[i];
        v[N + i] = v[i];
    }
    long long Ans = -oo;
    for(int K = 1 ; K <= N ; ++ K) {
        if(N % K == 0) {
            memset(ans, 0, sizeof(ans));
            deque <int> dqmin, dqmax;
            for(int i = 1 ; i < N + min(K, N - K + 1) - 1 ; ++ i) {
                while(!dqmin.empty() && v[dqmin.back()] >= v[i])
                    dqmin.pop_back();

                dqmin.push_back(i);

                if(dqmin.front() <= i - K)
                    dqmin.pop_front();

                while(!dqmax.empty() && v[dqmax.back()] <= v[i])
                    dqmax.pop_back();

                dqmax.push_back(i);

                if(dqmax.front() <= i - K)
                    dqmax.pop_front();

                if(i >= K)
                    ans[i% min(K, N - K + 1)] += (1LL * v[dqmax.front()] - 1LL * v[dqmin.front()]);
            }
            Ans = max(Ans, *max_element(ans, ans + K));
        }
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
