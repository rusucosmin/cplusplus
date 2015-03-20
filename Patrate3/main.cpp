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

string file = "patrate3";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
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

#define x first
#define y second

#define p Points

vector< pair< int,  int> > Points;
int N;

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        float x, y;
        cin >> x >> y;
        x *= 10000;
        y *= 10000;
        Points.push_back(make_pair((int)(x+(x<0?-0.5:0.5)), (int)(y+(y<0?-0.5:0.5))));
    }
    int Sol = 0;
    sort(Points.begin(), Points.end());
    for(int i = 0 ; i < N ; ++ i)
        for(int j = i + 1 ; j < N ; ++ j) {
            pair< int,  int> A, B;
            A.x=p[i].x+p[i].y-p[j].y;
            A.y=p[i].y+p[j].x-p[i].x;
            B.x=p[i].y+p[j].x-p[j].y;
            B.y=p[j].x+p[j].y-p[i].x;
            if(binary_search(Points.begin(), Points.end(), A))
                if(binary_search(Points.begin(), Points.end(), B))
                    ++ Sol;
        }
    cout << (Sol >> 1) << '\n';
    cin.close();
    cout.close();
    return 0;
}
