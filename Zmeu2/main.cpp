#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define MAXP 205
typedef pair<short, short> per;

bool G[MAXP][MAXP];
short N, P, K, d[MAXP], c[MAXP], D[MAXP][MAXP]; //distanta maxima de a ajunge in nodul i cu j capuri taiate :)

class ClassComp {
public:
    bool operator() (const per  &a, const per &b) {
        return D[a.first][a.second]>D[b.first][b.second];
    }
};

priority_queue< per , vector< per > , ClassComp > Q;

inline short Dijkstra() {
    short Ans = 9999;
    for(Q.push(make_pair(1, N-c[1])), D[1][N-c[1]] = d[1] ; !Q.empty() ; Q.pop() ) {
        int Node = Q.top().first;
        int Heads = Q.top().second;
        for(short i = 1 ; i <= P ; ++ i) {
            if(!G[Node][i]) {
                int actHeads = Heads - c[i];
                if(actHeads <= 0)
                    continue;
                if(D[i][actHeads] > D[Node][Heads] + d[i] || D[i][actHeads] == 0) {
                    D[i][actHeads] = D[Node][Heads] + d[i];
                    if( i == P )
                        Ans = min(Ans, D[i][actHeads]);
                    Q.push(make_pair(i, actHeads));
                }
            }
        }
    }
    return Ans;
}

int main() {
    ifstream cin( "zmeu2.in");
    ofstream cout( "zmeu2.out" );
    cin >> N >> P >> K;
    G[1][P] = 1;
    for(short i = 1 ; i <= P ; ++ i)
        cin >> d[i] >> c[i],
        G[i][i] = 1;
    for(short i = 1 ; i <= K ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x][y] = 1;
    }
    cout << Dijkstra();
    cin.close();
    cout.close();
    return 0;
}
