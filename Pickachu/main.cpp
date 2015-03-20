#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "pikachu.in";
const char outfile[] = "pikachu.out";

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

int N, K;
pair<int, int> arb[MAXN << 2];
int ind[MAXN];
vector<pair<int, int> > a;

int main() {
    fin >> N >> K;
    for(int i = 1 ; i <= K ; ++ i) {
        int x
        cin >> x
        a.push_back(make_pair(x, i));
    }
    sort(a.begin(), a.end());
    for(int i = 1 ; i <= N ; ++ i) {
        Update(1, 1, N, a[ind[i]], 1);
    }
    fin.close();
    fout.close();
    return 0;
}
