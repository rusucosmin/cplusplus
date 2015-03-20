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

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

vector <pair<int, int> > Edges;
int aib[MAXN];
int N, M;

inline int lsb(int x) {
    return x & (-x);
}

inline void Update(int nod, int value) {
    for(int i = nod ; i <= N ; i += lsb(i))
        aib[i] += value;
}

inline int Query(int nod) {
    int Ans = 0;
    for(int i = nod ; i > 0 ; i -= lsb(i))
        Ans += aib[i];
    return Ans;
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y;
        cin >> op;
        if(op == 1) {
            cin >> x >> y;
            Update(x, 1);
            Update(y, 1);
            Edges.push_back(make_pair(x, y));
        }
        if(op == 2) {
            cin >> x;
            Update(Edges[x - 1].first, -1);
            Update(Edges[x - 1].second, -1);
        }
        if(op == 3) {
            cin >> x >> y;
            if(Query(N) == Query(y) - Query(x - 1))
                cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
