#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 1005;

int N, Min = 1;
pair<int, int> P[MAXN];

#define x first
#define y second

inline long long crossProduct(pair<int, int> A,pair<int, int> B,pair<int, int> C){
    return 1LL*A.x*B.y+1LL*B.x*C.y+1LL*C.x*A.y-1LL*A.y*B.x-1LL*B.y*C.x-1LL*C.y*A.x;
}

struct cmp {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> & b) {
        return crossProduct(P[1], a, b) < 0;
    }
};

int St[MAXN], head;
map <pair<int, int> , int> mp;

int main() {
    ifstream fin("mission.in");
    ofstream fout("mission.out");
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> P[i].first >> P[i].second;
        if(P[Min] > P[i])
            Min = i;
        mp[P[i]] = i - 1;
    }
    swap(P[Min], P[1]);
    sort(P + 2, P + N + 1, cmp());

    for(int i = 1 ; i <= N ; ++ i) {
        St[++ head] = mp[P[i]];
    }
    int found = 0;
    for(int i = 1 ; i <= head ; ++ i) {
        if(St[i] == 0) {
            found = i;
        }
        if(found)
            fout << St[i] << ' ';
    }
    for(int i = 1 ; i < found ; ++ i)
        fout << St[i] << ' ';
    return 0;
}
