#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cassert>

using namespace std; // }}}

const int maxn = 100005;

int father[maxn], sz[maxn];

inline int find(int x) {
    if(father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}

inline void unite(int x, int y) {
    int tx = find(x);
    int ty = find(y);
    if(tx == ty)
        return ;
    father[tx] = ty;
    sz[ty] += sz[tx];
}

int main()
{
    int N, I;
    cin >> N >> I;
    for(int i = 1 ; i <= N ; ++ i) {
        father[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < I; ++i) {
        int a, b;
        cin >> a >> b;
        ++ a;
        ++ b;
        unite(a, b);
    }

    long long result = 0;

    /** Write code to compute the result using N,I,pairs **/
    for(int i = 1 ; i <= N ; ++ i)
        if(find(i) == i) {
        result = result + 1LL * sz[i] * (N - sz[i]);
    }

    cout << result / 2 << endl;
    return 0;
}
