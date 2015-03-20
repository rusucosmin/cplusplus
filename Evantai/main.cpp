#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char outfile[] = "evantai.out";

const int MAXN = 701;
const int MOD = 30103;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, A[MAXN], dp[MAXN][MAXN], aib[MAXN][MAXN];

inline int lsb(int a) {
    return a & (-a);
}

inline void Update(int x, int y, int value) {
    for(int i = x ; i <= N ; i += lsb(i))
        for(int j = y ; j <= N ; j += lsb(j)) {
            aib[i][j] += value;
            if(aib[i][j] > MOD)
                aib[i][j] -= MOD;
    }
}

inline int Query(int x, int y) {
    int ret = 0;
    for( int i = x ; i > 0 ; i -= lsb(i))
        for( int j = y ; j > 0 ; j -= lsb(j)) {
            ret += aib[i][j];
            if(ret > MOD)
                ret -= MOD;
        }
    return ret;
}

FILE* fin=fopen("evantai.in","r");
const unsigned maxb=8192;
char buf[maxb];
unsigned ptr=maxb;

inline unsigned getInt(){
    unsigned nr=0;
    while(buf[ptr]<'0'||'9'<buf[ptr])
            if(++ptr>=maxb)
                    fread(buf,maxb,1,fin),ptr=0;
    while('0'<=buf[ptr]&&buf[ptr]<='9'){
            nr=nr*10+buf[ptr]-'0';
            if(++ptr>=maxb)
                    fread(buf,maxb,1,fin),ptr=0;
    }
    return nr;
}

int main() {
    vector<pair<int, pair<int, int> > > v;
    N = getInt();
    for(int i = 1 ; i <= N ; ++ i)
        A[i] = getInt();
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = i + 1 ; j <= N ; ++ j)
            v.push_back(make_pair(A[i] + A[j], make_pair(i, j)));
    sort(v.begin(), v.end());
    for(int i = 0, M = v.size() ; i < M ; ++ i) {
        int newx = v[i].second.first;
        int newy = v[i].second.second;
        int aux = Query(newy - 1, newy - 1) + Query(newx, newx) - Query(newy - 1, newx) - Query(newx, newy - 1) + 1;
        if(aux < 0)
            aux += MOD;
        Update(newx, newy, aux);
        dp[newx][newy] = aux;
    }
    int Ans = 0;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = i + 1 ; j <= N ; ++ j) {
            Ans += dp[i][j];
            if(Ans > MOD)
                Ans -= MOD;
        }
    ofstream cout(outfile);
    cout << Ans << '\n';
    cout.close();
    return 0;
}
