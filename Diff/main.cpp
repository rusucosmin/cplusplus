#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "diff.in";
const char outfile[] = "diff.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100010;
const int DELTA = MAXN - 2;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, maxS, minS, minP, maxP, S;
bitset <(MAXN << 1)> Hash;
pair<int, int> Hash_pos[(MAXN << 1)];

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i) {
        int a;
        fin >> a;
        if(!a)
            -- a;
        S += a;
        if(!Hash[DELTA + S - maxS]) {
            Hash[DELTA + S - maxS] = 1;
            Hash_pos[DELTA + S - maxS] = make_pair(maxP, i);
        }
        if(!Hash[DELTA + S - minS]) {
            Hash[DELTA + S - minS] = 1;
            Hash_pos[DELTA + S - minS] = make_pair(minP, i);
        }
        if(maxS < S) {
            maxS = S;
            maxP = i;
        }
        if(minS > S) {
            minS = S;
            minP = i;
        }
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x;
        fin >> x;
        if(!Hash[DELTA + x]) {
            fout << "-1\n";
            continue;
        }
        fout << Hash_pos[DELTA + x].first + 1 << ' ' << Hash_pos[DELTA + x].second << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
