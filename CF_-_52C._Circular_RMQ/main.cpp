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
#include <sstream>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Node {
    long long _add;
    long long _min;
};

Node arb[MAXN << 2];
int A[MAXN], N, M;

inline void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node]._min = A[st];
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(Node << 1, st, mid);
    Build((Node << 1) | 1, mid+1, dr);
    arb[Node]._min = min(arb[Node<<1]._min, arb[(Node << 1) | 1]._min);
}

inline void Update(int Node, int st, int dr, int a, int b, int value) {
    if(a <= st && dr <= b) {
        arb[Node]._add += value;
        arb[Node]._min += value;
        return ;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node]._add) {
        Update(Node << 1, st, mid, st, mid, arb[Node]._add);
        Update((Node << 1) | 1, mid+1, dr, mid+1, dr, arb[Node]._add);
        arb[Node]._add = 0;
    }
    if(a <= mid)
        Update(Node << 1, st, mid, a, b, value);
    if(mid < b)
        Update((Node << 1) | 1, mid + 1, dr, a, b, value);
    arb[Node]._min = min(arb[Node << 1]._min, arb[(Node << 1) | 1]._min);
}

inline long long Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node]._min;
    int mid = ((st + dr) >> 1);
    if(arb[Node]._add) {
        Update(Node << 1, st, mid, st, mid, arb[Node]._add);
        Update((Node << 1) | 1, mid+1, dr, mid+1, dr, arb[Node]._add);
        arb[Node]._add = 0;
    }
    long long ret = oo;
    if(a <= mid)
        ret = min(ret, Query(Node << 1, st, mid, a, b));
    if(mid < b)
        ret = min(ret, Query((Node << 1) | 1, mid+1, dr, a, b));
    return ret;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> A[i];
    Build(1, 1, N);
    cin >> M;
    cin.get();
    for(int i = 1 ; i <= M ; ++ i) {
        int op;
        string s;
        stringstream get;
        vector <int> v;
        getline(cin, s);
        get.str(s);
        int x;
        while(get >> x)
            v.push_back(x);
        /*for(vector <int> :: iterator it = v.begin(), fin = v.end() ; it != fin ; ++ it)
            cerr << *it << ' ';
        cerr << '\n';*/
        ++ v[0];
        ++ v[1];
        if(v.size() == 2) {
            if(v[0] <= v[1])
                cout << Query(1, 1, N, v[0], v[1]) << '\n';
            else cout << min(Query(1, 1, N, 1, v[1]), Query(1, 1, N, v[0], N)) << '\n';
        }
        if(v.size() == 3) {
            if(v[0] <= v[1])
                Update(1, 1, N, v[0], v[1], v[2]);
            else {
                Update(1, 1, N, 1, v[1], v[2]);
                Update(1, 1, N, v[0], N, v[2]);
            }
        }
    }
    return 0;
}
