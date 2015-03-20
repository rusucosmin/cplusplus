#include <fstream>
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

string file = "dusman";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 1005;

bitset <MAXN> A[MAXN];
bitset <MAXN> Used;
int N, K, M, st[MAXN];

inline void Print() {
    for(int i = 1 ; i <= N ; ++ i)
        cout << st[i] << ' ';
}

inline void Back(int k) {
    if( K <= 0 )
        return ;
    if(k > N) {
        -- K;
        if(!K) {
            Print();
        }
        return;
    }
    for(int i = 1 ; i <= N ; ++ i) {
        if(!Used[i] && !A[st[k-1]][i]) {
            st[k] = i;
            Used[i] = 1;
            Back(k+1);
            Used[i] = 0;
        }
    }
}

int main() {
    cin >> N >> K >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        A[x][y] = A[y][x] = 1;
    }
    Back(1);
    cin.close();
    cout.close();
    return 0;
}
