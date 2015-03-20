#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

const int MAXN = 300005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N, A[MAXN], Ans;
vector<int> L;

inline int cmmdc(int x, int y) {
    int r;
    while(x % y != 0) {
        r = x % y;
        x = y;
        y = r;
    }
    return y;
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> A[i];
    }
    for(int l = 1 ; l < N ; ++ l)
        for(int r = l + 1 ; r <= N ; ++ r) {
            bitset <MAXN> Used;
            int x = A[l];
            Used[A[l]] = true;
            for(int i = l + 1 ; i <= r ; ++ i) {
                x = cmmdc(x, A[i]);
                Used[A[i]] = true;
            }
            if(Used[x]) {
                if(Ans < r - l) {
                    Ans = r - l;
                    L.clear();
                    L.push_back(l);
                }
                else if(Ans == r - l)
                    L.push_back(l);
            }
        }
    cout << L.size() << ' ' << Ans << '\n';
    for(int i = 0 ; i < L.size() ; ++ i)
        cout << L[i] << ' ';
    return 0;
}
