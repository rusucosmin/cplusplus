#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "albinuta.in";
const char outfile[] = "albinuta.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 55;
const int MAXM = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, Q, LCM = 1, st, fn;
Graph G;
short L[MAXN], Ans[MAXN * MAXM], used[MAXM][MAXN];

int GCD(const int &a, const int &b) {
    if(b == 0)
        return a;
    return GCD(b, a % b);
}

int main() {
    fin >> N >> Q;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> L[i];
        LCM = (LCM * L[i]) / GCD(LCM, L[i]);
        for(int j = 1 ; j <= L[i] ; ++ j) {
            int y;
            fin >> y;
            G[i].push_back(y);
        }
    }
    Ans[1] = 1;
    int T = 1;
    int nr = 1;
    int Node = 1;
    used[1][1] = 1;
    while(true) {
        if(T == 0)
            T = LCM;
        Node = G[Node][(T - 1) % L[Node]];
        T = (T + 1) % LCM;
        if(used[T][Node]) {
            st = used[T][Node] - 1;
            fn = nr - st;
            break;
        }
        Ans[++ nr] = Node;
        used[T][Node] = nr;
    }
    for(int i = 1 ; i <= Q ; ++ i) {
        int x;
        fin >> x;
        if(x > st + fn)
            x = st + 1 + ( x - st - 1 ) % fn;
        fout << Ans[x] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
