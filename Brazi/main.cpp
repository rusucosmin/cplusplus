#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "brazi.in";
const char outfile[] = "brazi.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 12;
const int MAXT = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)   { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)   { if( a < b ) a = b; }

char liniarize[MAXT][3*MAXN];
bitset <MAXN> hasDad;
int G[MAXN][2];
int linLevel[MAXT], dp[MAXT];

void DFs(const int &Node, const int &root, const int t) {
    for(int i = 0 ; i < 2 ; ++ i)
        if(G[Node][i]) {
            liniarize[t][linLevel[t]++] = i + 4;
            liniarize[t][linLevel[t]++] = 1;
            DFs(G[Node][i], root, t);
        }
    liniarize[t][linLevel[t]++] = 0;
}

int main() {
    int T;
    cin >> T;
    for(int t = 1 ; t <= T ;  ++ t) {
        int N;
        cin >> N;
        for(int i = 1 ; i <= N ; ++ i)
            G[i][0] = G[i][1] = 0;
        hasDad.reset();
        for(int i = 1 ; i != N ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            G[x][z] = y;
            hasDad[y] = true;
        }
        int root;
        for(root = 1 ; root <= N ; ++ root)
            if(!hasDad[root])
                break;
        int anothert = t;
        DFs(root, root, anothert);
        for(int j = t - 1 ; j >= 1 && !dp[t] ; -- j) {
            if(linLevel[t] != linLevel[j])
                continue;
            bool ok = true;
            for(int i = 0 ; i < linLevel[t] && ok ; ++ i)
                if((int)liniarize[t][i] != (int)liniarize[j][i])
                    ok = false;
            if(ok)
                dp[t] = dp[j] + 1;
        }
        cout << dp[t] << '\n';
    }
    cin.close();
    cout.close();
    return 0;
}
