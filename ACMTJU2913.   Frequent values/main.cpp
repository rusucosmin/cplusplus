#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

const int maxn = 100005;
const int oo = 0x3f3f3f3f;

struct aint {
    int who, fr, s_fr, p_fr;
    aint() {
        who = -oo;
        fr = -oo;
        s_fr = -oo;
        p_fr = -oo;
    }
} arb[maxn << 2];

int n, m, a[maxn];

inline void build(int node, int st, int dr) {
    if(st == dr) {
        arb[node].fr = 1;
        arb[node].who = a[st];
        arb[node].s_fr = 1;
        arb[node].p_fr = 1;
        return ;
    }
    int mid = ((st + dr) >> 1);
    build(node << 1, st, mid);
    build((node << 1) | 1, mid + 1, dr);
    if(a[st] == a[mid] && a[mid] == a[mid + 1])
        arb[node].p_fr = mid - st + 1 + arb[(node << 1) | 1].p_fr;
    else
        arb[node].p_fr = arb[node << 1].p_fr;
    if(a[mid] == a[mid + 1] && a[mid + 1] == a[dr])
        arb[node].s_fr = dr - mid + arb[node << 1].s_fr;
    else
        arb[node].s_fr = arb[(node << 1) | 1].s_fr;

    if(a[mid] == a[mid + 1]) {
        arb[node].fr = arb[node << 1].s_fr + arb[(node << 1) | 1].p_fr;
        arb[node].who = a[mid];
    }
    if(arb[node].fr < arb[node << 1].fr) {
        arb[node].fr = arb[node << 1].fr;
        arb[node].who = arb[node << 1].who;
    }
    if(arb[node].fr < arb[(node << 1) | 1].fr) {
        arb[node].fr = arb[(node << 1) | 1].fr;
        arb[node].who = arb[(node << 1) | 1].who;
    }
}

inline aint query(int node, int st, int dr, int x, int y) {
    if(x <= st && dr <= y)
        return arb[node];
    int mid = ((st + dr) >> 1);
    aint first, second;
    if(x <= mid)
        first = query(node << 1, st, mid, x, y);
    if(mid < y)
        second = query((node << 1)|1, mid + 1, dr, x, y);
    if(first.fr == -oo)
        return second;
    if(second.fr == -oo)
        return first;
    aint father;
    if(a[st] == a[mid] && a[mid] == a[mid + 1])
       father.p_fr = mid - st + 1 + second.p_fr;
    else
        father.p_fr = first.p_fr;
    if(a[mid] == a[mid + 1] && a[mid + 1] == a[dr])
        father.s_fr = dr - mid + first.s_fr;
    else
        father.s_fr = second.s_fr;

    if(a[mid] == a[mid + 1]) {
        father.fr = first.s_fr + second.p_fr;
        father.who = a[mid];
    }
    if(father.fr < first.fr) {
        father.fr = first.fr;
        father.who = first.who;
    }
    if(father.fr < second.fr) {
        father.fr = second.fr;
        father.who = second.who;
    }
    return father;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif
    while(cin >> n) {
        if(n == 0)
            return 0;
        memset(arb, 0, sizeof(arb));
        cin >> m;
        for(int i = 1 ; i <= n ; ++ i)
            cin >> a[i];
        build(1, 1, n);
        for(int i = 1 ; i <= m ; ++ i) {
            int x, y;
            cin >> x >> y;
            cout << query(1, 1, n, x, y).fr << '\n';
        }
    }
}
