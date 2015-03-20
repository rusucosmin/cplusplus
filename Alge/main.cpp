#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const char infile[] = "alge.in";
const char outfile[] = "alge.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 36;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int dx[] = {1, -1, 0, 0, 0,  0};
const int dy[] = {0,  0, 1,-1, 0,  0};
const int dz[] = {0,  0, 0, 0, 1, -1};

char d[MAXN][MAXN][MAXN];
pair<char, pair<char, char> > Father[MAXN][MAXN][MAXN];
int N, M, Ans;
queue<pair<int, pair<int, int> > > Q;

inline bool inside(int a, int b, int c) {
    return (a >= 1 && a <= N && b >= 1 && b <= N && c >= 1 && c <= N);
}

inline void BFs() {
    for(Q.push(make_pair(1, make_pair(1, 1))), d[1][1][1] = 1 ; !Q.empty() ; Q.pop()) {
        int x = Q.front().first;
        int y = Q.front().second.first;
        int z = Q.front().second.second;
        for(int i = 0 ; i < 6 ; ++ i) {
            int newx = x + dx[i];
            int newy = y + dy[i];
            int newz = z + dz[i];
            if(inside(newx, newy, newz) && d[newx][newy][newz] == 0 ) {
                d[newx][newy][newz] = d[x][y][z] + 1;
                Father[newx][newy][newz] = make_pair(x, make_pair(y, z));
                Q.push(make_pair(newx, make_pair(newy, newz)));
            }
        }
    }
}

void Write(pair<int, pair<int, int> > x) {
    if(Father[x.first][x.second.first][x.second.second].first)
        Write(Father[x.first][x.second.first][x.second.second]);
        else cout << (int)d[N][N][N] << '\n';
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << '\n';
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        d[x][y][z] = -1;
    }
    BFs();
    Write(make_pair(N, make_pair(N, N)));
    cin.close();
    cout.close();
    return 0;
}
