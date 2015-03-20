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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

vector <int> arb[MAXN << 4];
int a[MAXN], N, M;
bool found = true;

void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node].push_back(a[st]);
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid);
    Build(2*Node + 1, mid + 1, dr);
    arb[Node].resize(arb[2*Node].size() + arb[2*Node + 1].size());
    merge(arb[2*Node].begin(), arb[2*Node].end(), arb[2*Node+1].begin(), arb[2*Node + 1].end(), arb[Node].begin());
}

int Query(int Node, int st, int dr, int a, int b, int value) {
    if(a <= st && dr <= b) {
        vector <int> :: iterator it = lower_bound(arb[Node].begin(), arb[Node].end(), value);
        if(*it == value || (it != arb[Node].end() && *(it + 1) == value))
            found = true;
        return it - arb[Node].begin();
    }
    int mid = ((st + dr) >> 1);
    int ans = 0;
    if(a <= mid)
        ans += Query(2*Node, st, mid, a, b, value);
    if(mid < b)
        ans += Query(2*Node + 1, mid + 1, dr, a, b, value);
    return ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d%d", &N, &M);
    for(int i = 1 ; i <= N ; ++ i)
        scanf("%d", &a[i]);
    Build(1, 1, N);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        int st = 0, dr = arb[1].size() - 1;
        int Ans = -1;
        while(st <= dr) {
            int mid = ((st + dr) >> 1);
            found = false;
            int behind = Query(1, 1, N, x, y, arb[1][mid]);
            if(behind == k - 1 && found) {
                Ans = arb[1][mid];
                break;
            }
            if(behind > k - 1)
                dr = mid - 1;
            else st = mid + 1;
        }
        printf("%d\n", Ans);
    }
    return 0;
}
