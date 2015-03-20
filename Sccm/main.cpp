#include <map>
#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 80005;

map<int, int> sccm[N];

map<int, int> :: iterator it, _next, _prev, _end, st;

int n1, n2, hi, n, l[3], pos[N], lmax[N], a[3][N];

pair<int, int> v[N];

void add(int x){
    _next = sccm[x].lower_bound(n1);
    _end = sccm[x].end();
    st =  sccm[x].begin();

    if (_next != st) {
        _prev = --_next;
        ++_next;
    }

    if ((_next != _end && _next->first == n1 && _next->second <= n2) || (_next != st && _prev->second == n2))
        return;
    it = _next;

    while (it->second >= n2)
        ++it;
    sccm[x].erase(_next,it);

    sccm[x][n1] = n2;
    return;
}

inline bool pred(int x){
    bool ok = true;

    st = sccm[x].begin();
    _next = sccm[x].lower_bound(n1);

    if ((_next != st && (--_next)->second < n2))
        ok = false;

    return ok;
}

void insert(){
    int st = 0, dr = hi;

    if (!pred(dr)) {
        sccm[dr + 1][n1] = n2;
        ++hi;
        return;
    }

    while (st < dr) {
        int mid = (dr - st) / 2 + st;

        if (pred(mid))
            dr = mid;
        else
            st = mid + 1;
    }

    if (pred(st))
      add(st);
}


void read() {
  scanf("%d%d", &l[1], &l[2]);

  for (int i = 1; i <= 2; ++i)
    for (int j = 1; j <= l[i]; ++j)
      scanf("%d", &a[i][j]);
}

void init() {
  if (l[1] < l[2]) {
    swap(l[1], l[2]);
    swap(a[1], a[2]);
  }

  for (int j = 1; j <= l[1]; ++j)
    pos[a[1][j]] = j;

  n = l[2];

  for (int j = 1; j <= l[2]; ++j)
    v[j].first = a[2][j], v[j].second = pos[a[2][j]];
}

void solve() {
  sccm[0][v[1].first] = v[1].second;

  for (int i = 2; i <= n; ++i) {
    n1 = v[i].first;
    n2 = v[i].second;

    insert();
  }

  printf("%d\n", hi + 1);
}

int main() {
  freopen("sccm.in", "r", stdin);
  freopen("sccm.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
