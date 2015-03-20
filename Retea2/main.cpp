#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <math.h>
#include <set>
#include <tr1/unordered_set>

using namespace std;
using namespace tr1;

string file = "retea2";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 2005;
const int oo = (1<<31)-1;

pair<int, int> p[2*MAXN];
int N, M, n;
double d[MAXN], Cost, m;
unordered_multiset<int> s;

inline double EuclidianDistance(int x, int y, int X, int Y) {
    return sqrt(1LL*(X-x)*(X-x)+1LL*(Y-y)*(Y-y));
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> p[i].first >> p[i].second;
    m = oo;
    for(int i = 1 ; i <= M ; ++ i) {
        cin >> p[i+N].first >> p[i+N].second;
        d[i] = oo;
        for(int j = 1 ; j <= N ; ++ j)
            d[i] = min(d[i], EuclidianDistance(p[i+N].first, p[i+N].second, p[j].first, p[j].second));
        if(m > d[i]) {
            m = d[i];
            n = i;
        }
        s.insert(i);
    }
    while(s.size()) {
        s.erase(s.find(n));
        Cost += m;
        m = oo;
        for(unordered_multiset<int> :: iterator it = s.begin(), fin = s.end() ; it != fin ; ++ it)
            d[*it] = min(d[*it], EuclidianDistance(p[n+N].first, p[n+N].second, p[*it + N].first, p[*it + N].second));
        for(unordered_multiset<int> :: iterator it = s.begin(), fin = s.end() ; it != fin ; ++ it)
            if(m > d[*it]) {
                m = d[*it];
                n = *it;
            }
    }
    cout << fixed << setprecision(7) << Cost << '\n';
    cin.close();
    cout.close();
    return 0;
}
