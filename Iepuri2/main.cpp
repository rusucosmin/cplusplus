#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "iepuri2";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 105;
const int MOD = 30011;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N, K, Root, T[MAXN][MAXN];
Graph G;
bitset<MAXN> hasDad;

inline void DFs(int Node) {
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        DFs(*it);
    for(int k = K ; k >= 1 ; -- k) {
        T[Node][k] = 1;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            T[*it][k + 1] = (T[*it][k + 1] + T[*it][k + 2]) % MOD;
            long Produs = T[Node][k];
            Produs *= T[*it][k+1];
            T[Node][k] = Produs%MOD;
        }
    }
}

int main() {
    cin >> N >> K;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        hasDad[y] = true;
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!hasDad[i]) {
            Root = i;
            break;
        }
    DFs(Root);
    long Ans = 0;
    for(int i = 1 ; i <= K ; ++ i)
        Ans += T[Root][i], Ans %= MOD;
    /*
    for(int i = 1 ; i <= N ; ++ i, cout << '\n')
        for(int j = 1 ; j <= K ; ++ j)
            cout << T[i][j] << ' ';
    */
    cout << Ans << '\n';
    cin.close();
    cout.close();
    return 0;
}
/*
        #include <fstream>
        #include <vector>
        #include <bitset>
        #include <queue>
        #include <algorithm>
        #include <utility>
        #include <cstring>
        #include <string>
        #include <stack>
        #include <deque>
        #include <iomanip>
        #include <set>
        #include <map>
        #include <cassert>
        #include <ctime>
        #include <list>
        #include <iomanip>

        using namespace std;

        string file = "iepuri2";

        ifstream cin( (file + ".in").c_str() );
        ofstream cout( (file + ".out").c_str() );

        const int MAXN = 105;
        const int MOD = 30011;
        const int oo = (1<<31)-1;

        typedef vector<int> Graph[MAXN];
        typedef vector<int> :: iterator It;

        const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
        const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
        const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
        const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

        struct ClassComp {
            inline bool operator () (const int &a, const int &b) const {
                return a > b;
            }
        };

        int N, K, Root;
        Graph G;
        bitset<MAXN> hasDad;

        inline int DFs(int Node, int Carrots, int Dad) {
            int Sum = 0, Res, Aux, i;
            for(int i = Carrots ; i <= K ; ++ i) {
                Res = 1;
                for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
                    if(*it == Dad)
                        continue;
                    Res = (Res * DFs(*it, i + 1, Node))%MOD;
                }
                //if(Res == 0)
                //    break;
                Sum = (Sum + Res)%MOD;
            }
            return Sum;
        }

        int main() {
            cin >> N >> K;
            for(int i = 1 ; i != N ; ++ i) {
                int x, y;
                cin >> x >> y;
                G[x].push_back(y);
                hasDad[y] = true;
            }
            for(int i = 1 ; i <= N ; ++ i)
                if(!hasDad[i]) {
                    Root = i;
                    break;
                }
            cout << DFs(Root, 1, -1) << '\n';
            cin.close();
            cout.close();
            return 0;
        }


*/
