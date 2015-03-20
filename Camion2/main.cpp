
/// For you : http://www.youtube.com/watch?v=eAbOGuk4CPA

/*#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "camion2.in";
const char outfile[] = "camion2.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 1005;
const int MAXP = 27;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline int min(const int &a, const int &b, const int &c) { return min(a, min(b, c)); }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, P, dp[2][MAXN][MAXP][2];
Graph G;

inline void Memset(int Node) {
    for(int i = 1 ; i <= P ; ++ i)
        for(int j = 0 ; j < 2 ; ++ j)
            dp[j][Node][i][0] = dp[j][Node][i][1] = oo;
}

void DFs(int Node, int Father) {
    int sons = 0, c = 0, a;
    dp[0][Node][0][0] = dp[0][Node][0][1] = dp[1][Node][0][0] = dp[1][Node][0][1] = 0;
    Memset(Node);
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++it) {
        int actSon = it->first;
        int length = it->second;
        if(actSon == Father)
            continue;
        DFs(actSon, Node);
        ++ sons;
        a = c;   c = 1 - c;
        dp[c][Node][0][0] = dp[c][Node][0][1] = oo;
        for(int first = 1 ; first <= P ; ++ first) {
            dp[c][Node][first][0] = dp[c][Node][first][1] = oo;
            for(int second = 1 ; second <= first ; ++ second) {
                Get_min(dp[c][Node][first][0], min(dp[a][Node][first - second][0]     + dp[0][actSon][second][0] + length * second,
                                             dp[a][Node][first - second + 1][1] + dp[0][actSon][second][0] + length * second,
                                             dp[a][Node][first - second + 1][0] + dp[0][actSon][second][1] + length * (second + 1)));
                Get_min(dp[c][Node][first][1], min(dp[a][Node][first - second][0]     + dp[0][actSon][second][1] + length * (second + 1),
                                             dp[a][Node][first - second + 1][1] + dp[0][actSon][second][1] + length * (second + 1)));
            }
        }
    }
    for(int i = 0 ; i <= P ; ++ i)
        for(int j = 0 ; j < 2 ; ++ j)
            dp[1 - c][Node][i][j] = dp[c][Node][i][j];

    if(!sons)
        dp[0][Node][1][0] = dp[0][Node][1][1] = dp[1][Node][1][0] = dp[1][Node][1][1] = 0;

    dp[0][Node][0][0] = dp[0][Node][0][1] = dp[1][Node][0][0] = dp[1][Node][0][1] = oo;
}

int main() {
    cin >> N >> P;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    DFs(1, 0);
    int Ans = oo;
    for(int i = 1 ; i <= P ; ++ i)
        for(int j = 0 ; j < 2 ; ++ j)
            Ans = min(Ans, dp[0][1][i][j]);
    cout << Ans << '\n';
    cin.close();
    cout.close();
    return 0;
}
*/

#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "camion2.in";
const char outfile[] = "camion2.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 1005;
const int MAXP = 27;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline int min(const int &a, const int &b, const int &c) { return min(a, min(b, c)); }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, P, dp[3][MAXN], dad[MAXN], Ans;
Graph G;
bitset <MAXN> used;

void buildDp(int Node, int Father) {
    dad[Node] = Father;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(it->first == Father)   continue;
        dp[0][it->first] = dp[0][Node] + it->second;
        Ans += it->second << 1;
        buildDp(it->first, Node);
    }
}

void DFs(int Node, int Father) {
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(it->first == Father) continue;
        dp[1][it->first] = used[it->first] ? -dp[0][it->first] : dp[1][Node] + it->second;
        DFs(it->first, Node);
    }
}

int main() {
    cin >> N >> P;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    buildDp(1, 0);
    for(int i = 1 ; i <= P ; ++ i) {
        DFs(1, 0);
        int minPos = 0;
        for(int j = 1 ; j <= N ; ++ j)
            if(!used[j] && dp[1][j] > dp[1][minPos])
                minPos = j;
        Ans -= dp[1][minPos];
        for( ; minPos ; minPos = dad[minPos])
            used[minPos] = 1;
    }
    cout << Ans << '\n';
    cin.close();
    cout.close();
    return 0;
}


