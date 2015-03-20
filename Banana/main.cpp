#include <fstream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

ifstream cin("banana.in");
ofstream cout("banana.out");

int N, K, now, nrc, sol, Father[16005], Fr[16005];

priority_queue<int> H;
pair<int, int> p, px;
map<pair<int, int> , int> M;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

inline int Find(int x){
    if(Father[x] != x)
        Father[x] = Find(Father[x]);
    return Father[x];
}

inline void Unite(int x, int y){
    Father[x] = y;
}

int main() {
    cin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i)
        Father[i] = i;
    for(int i = 1 ; i <= N ; ++ i){
        cin >> p.first >> p.second;
        M[p] = i;
        for(int d = 0 ; d < 4 ; ++ d){
            px.first = p.first + dx[d], px.second = p.second + dy[d];
            if(px.first<1 || px.second<1 || M.find(px) == M.end()) continue;
            Unite(Find(i), Find(M[px]));
        }
    }
    for(int i = 1 ; i <= N ; ++ i)
        ++ Fr[Find(i)];
    for(int i = 1 ; i <= N ; ++ i)
        if(Fr[i])
            H.push(Fr[i]);
    for(int i = 1 ; i <= K ; ++ i)
        sol += H.top(), H.pop();
    cout << sol << "\n";
    cin.close();
    cout.close();
    return 0;
}
