#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("aib.in");
ofstream fout("aib.out");

const int maxn = 100005;

int n, m, aib[maxn];

inline int lsb(int x) {
    return (x & (-x));
}

inline void update(int pos, int value) {
    for(int i = pos ; i <= n ; i += lsb(i))
        aib[i] += value;
}

inline int query(int pos) {
    int sum = 0;
    for(int i = pos ; i > 0 ; i -= lsb(i))
        sum += aib[i];
    return sum;
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= n ; ++ i) {
        int x;
        fin >> x;
        update(i, x);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int op, x, y;
        fin >> op;
        if(op == 0) {
            fin >> x >> y;
            update(x, y);
        }
        else if(op == 1) {
            fin >> x >> y;
            fout << query(y) - query(x - 1) << '\n';
        }
        else {
            fin >> x;
            int st = 1, dr = n;
            int ans = -1;
            while(st <= dr) {
                int mid = ((st + dr) >> 1);
                int act = query(mid);
                if(act >= x) {
                    dr = mid - 1;
                    if(act == x)
                        ans = mid;
                }
                else
                    st = mid + 1;
            }
            fout << ans << '\n';
        }
    }
}
