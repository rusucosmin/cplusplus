#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "dist2.in";
const char outfile[] = "dist2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MAXP = 2000015;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
vector <pair<int, int> > V;

inline int myAbs(const int &value) {
    if(value < 0)
        return -value;
    return value;
}

inline bool check(const int &D) {
    int p1 = 0, p2 = 0;
    int maxy = V[0].first;
    int miny = V[0].second;
    while( p1 < N && (V[p1].first <= V[p2].first + D))
        ++ p1;
    while( p1 < N ) {
        while( (p2 + 1) < N && V[p2 + 1].first + D < V[p1].first) {
            ++ p2;
            miny = min(miny, V[p2].second);
            maxy = max(maxy, V[p2].second);
        }
        if(myAbs(V[p1].second - miny) > D)
            return 0;
        if(myAbs(V[p1].second - maxy) > D)
            return 0;
        ++ p1;
    }
    return 1;
}


inline int binarySearch() {
    int li = 0, ls = MAXP, Ans = -1;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(!check(mid)) {
            Ans = mid;
            li = mid + 1;
        }
        else ls = mid - 1;
    }
    return Ans + 1;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        fin >> x >> y;
        V.push_back(make_pair(x, y));
    }
    sort(V.begin(), V.end());
    fout << binarySearch() << '\n';
    fin.close();
    fout.close();
    return 0;
}
