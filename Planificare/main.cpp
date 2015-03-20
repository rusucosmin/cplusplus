#include <fstream>
#include <vector>
#include <bitset>
#include <set>
#include <algorithm>

using namespace std;

const char infile[] = "planificare.in";
const char outfile[] = "planificare.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 4005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int main() {
    int N, K;
    multiset <int> S;
    fin >> N >> K;
    vector < pair<int, int> > v;
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        fin >> x >> y;
        v.push_back(make_pair(y, x));
    }
    sort(v.begin(), v.end());
    for(int i = 1 ; i <= K ; ++ i)
        S.insert(0);
    int Ans = 0;
    for(int i = 0 ; i < N ; ++ i) {
        multiset <int> :: iterator it = S.lower_bound(-v[i].second);
        if(it != S.end()) {
            ++ Ans;
            S.erase(it);
            S.insert(-v[i].first);
        }
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
