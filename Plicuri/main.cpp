#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin( "plicuri.in" );
ofstream cout( "plicuri.out" );

const int MAXN = 100005;

#define x first
#define y second

pair<int, int> box[MAXN];
int N, aib[MAXN], best[MAXN];

class ClassComp {
public:
    inline bool operator () (const pair<int, int> & a, const pair<int, int>  &b ) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

inline void Read() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> box[i].x >> box[i].y;
        if(box[i].x > box[i].y)
            swap(box[i].x, box[i].y);
    }
}

inline int lsb(int bit) {
    return (bit ^ (bit-1) & bit);
}

inline int query(int x) {
    int Ans = 0;
    for(int i = x ; i > 0 ; i -= lsb(i))
        Ans = max(Ans, aib[i]);
    return Ans;
}

inline void update(int x, int value) {
    for(int i = x ; i <= MAXN - 5 ; i += lsb(i))
        aib[i] = max(aib[i], value);
}

inline void Solve() {
    sort(box + 1, box + N + 1);
    int Answer = 0;
    for(int i = 1 ; i <= N ; ) {
        const int st = box[i].x;
        int j = i;
        for(  ; j <= N && box[j].x == st ; ++ j) {
            best[j] = query(box[j].y - 1) + 1;
            if(best[j] > Answer)
                Answer = best[j];
        }
        for(int k = i ; k < j ; ++ k) {
            update(box[k].y, best[k]);
        }
        i = j;
    }
    cout << Answer << '\n';
}

int main() {
    Read();
    Solve();
    cin.close();
    cout.close();
    return 0;
}
