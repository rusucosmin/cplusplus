#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const char infile[] = "imunitate.in";
const char outfile[] = "imunitate.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 18;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

bitset < (1 << MAXN) > Used;
int G[MAXN];

inline int nrBiti(int conf) {
    int ret = 0;
    while(conf) {
        conf &= (conf - 1);
        ++ ret;
    }
    return ret;
}

int main() {
    int T;
    fin >> T;
    while(T -- ) {
        queue <int> Q;
        int N, M;
        fin >> N >> M;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            fin >> x >> y;
            -- x;
            -- y;
            G[x] |= (1 << y);
            G[y] |= (1 << x);
        }
        int maxConf = (1 << N);
        int Ans = 0;
        Q.push(maxConf - 1);
        while(!Q.empty()) {
            int actConf = Q.front(); /// 1 pentru neeliminat - pentru eliminat
            int actNum = nrBiti(actConf);
            Used[actConf] = true;
            Q.pop();
            bool okConf = true;
            for(int i = 0 ; i < N ; ++ i)
                if(actConf & (1 << i)) {
                    /// acum am in G[i] bitii de 1 daca am vecin de la i la positie
                    /// deci daca fac G[i] & actConf atunci voi avea lista de adicenta in conf binara
                    /// a nodurilor neeliminate
                    if(2*nrBiti(G[i] & actConf) >= actNum) {
                        okConf = false;
                        if(!Used[actConf ^ (1 << i)]) {
                            Used[actConf ^ (1 << i )] = true;
                            Q.push(actConf ^ (1 << i));
                        }
                    }
                }
            Ans += okConf;
        }
        fout << Ans << '\n';
        for(int i = 0 ; i < N ; ++ i)
            G[i] = 0;
        Used.reset();
    }
    fin.close();
    fout.close();
    return 0;
}
