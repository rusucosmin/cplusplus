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

const char infile[] = "ambuscada.in";
const char outfile[] = "ambuscada.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MAXT = 5 * MAXN;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Soldier {
    int c, t;
} A[MAXN];

struct classComp {
    inline bool operator () (const Soldier &a, const Soldier &b) const {
        return a.t < b.t;

    }
};

int N, K, M, P;
long long Aim[MAXN];
long long S[MAXT];

inline long long Solve(int X) {
    int st = 1, dr = N;
    long long ans = -1;
    while(st <= dr) {
        int mid = ((st + dr) >> 1);
        if(A[mid].t <= X) {
            st = mid + 1;
            ans = S[A[mid].t];
        }
        else dr = mid - 1;
    }
    if(ans <= 0)
        return -1LL;
    long long ret = -1LL;
    st = 1;
    dr = P;
    while(st <= dr) {
        int mid = ((st + dr) >> 1);
        if(Aim[mid] <= ans) {
            st = mid + 1;
            ret = Aim[mid];
        }
        else dr = mid - 1;
    }
    return ret;
}

priority_queue <int, vector <int>, greater <int> > minHeap;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> K >> M >> P;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> A[i].c >> A[i].t;
    for(int i = 1 ; i <= P ; ++ i)
        fin >> Aim[i];
    sort(A + 1, A + N + 1, classComp());
    sort(Aim + 1, Aim + P + 1);
    long long cur = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        if(i <= K) {
            minHeap.push(A[i].c);
            cur += A[i].c; /// retin totalul din heap
            if(i == K)
                S[A[i].t] = cur;
            continue;
        }
        else
            if(minHeap.top() < A[i].c) {
                cur -= minHeap.top();
                minHeap.pop();
                minHeap.push(A[i].c);
                cur += A[i].c;
            }
        S[A[i].t] = cur;
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int X;
        fin >> X;
        fout << Solve(X) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
