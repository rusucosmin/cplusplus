#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "arbfind.in";
const char outfile[] = "arbfind.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 32005;
const int BASE = 3;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, A, B, S[MAXN << 1];
unsigned long long a[MAXN << 2];
unsigned long long C[MAXN << 2], power[MAXN << 2];
int first;
Graph G, E;
int s;
int First[MAXN];

void DFs(const int &Node, const int &Father, Graph &g, const bool check) {
    a[++s] = 1;
    if(check)
        First[Node] = s;
    for(It it = g[Node].begin(), fin = g[Node].end(); it != fin ; ++ it)
        if(*it != Father)
            DFs(*it, Node, g, check);
    a[++s] = 0;
}

inline unsigned long long Code(const int &_beg, const int &_end) {
    unsigned long long retu = C[_end] - C[_beg - 1] * power[_end - _beg + 1];
    return retu;
}

inline int binarySearch(const int &Pos) {
    int li = 1, ls = first, Ans = 0;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(Pos + mid - 1 <= s && C[mid] == Code(Pos, Pos + mid - 1)) {
            Ans = mid;
            li = mid + 1;
        }
        else ls = mid - 1;
    }
    return Ans;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        for(int j = 1 ; j <= x ; ++ j) {
            int y;
            fin >> y;
            G[i].push_back(y);
        }
    }
    fin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x;
        fin >> x;
        for(int j = 1 ; j <= x ; ++ j) {
            int y;
            fin >> y;
            E[i].push_back(y);
        }
    }
    DFs(1, 0, G, false);
    first = s;
    for(int i = 1 ; i <= s ; ++ i)
        S[i] = S[i-1] + a[i];
    DFs(1, 0, E, true);
    power[0] = 1;
    for(int i = 1 ; i <= s ; ++ i) {
        C[i] = C[i-1] * BASE + a[i];
        power[i] = power[i - 1] * BASE;
    }
    for(int i = 1 ; i <= M ; ++ i)
        fout << S[binarySearch(First[i])] << '\n';
    fin.close();
    fout.close();
    return 0;
}
