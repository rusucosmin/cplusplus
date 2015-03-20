#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
 
using namespace std;
 
const int dx[] = {-1, 0, 1, 0};
const int dy[] = { 0,-1, 0, 1};
 
const int maxn = 100005;
 
ifstream fin("rrmst.in");
ofstream fout("rrmst.out");
 
unordered_set<int> smth;
unordered_map<int, int> mymap;
queue<pair<int, int> > q;
vector <pair<int, pair<int, int> > > edges;
int n, father[maxn];
 
inline int getcode(int x, int y) {
    return x * n + y;
}
 
inline bool inside(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}
 
inline int cost(int x1, int y1, int x2, int y2) {
    return max(x1 - x2, x2 - x1) + max(y1 - y2, y2 - y1);
}
 
inline void check(const int node) {
    smth.clear();
    while(!q.empty())
        q.pop();
    int x = node / n;
    int y = node % n;
    q.push(make_pair(x, y));
    while(!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        if(mymap.find(getcode(x, y)) != mymap.end() && node != getcode(x, y)) {
            edges.push_back(make_pair(cost(node / n, node % n, x, y), make_pair(mymap[node], mymap[getcode(x, y)])));
			return;
        }
        for(int d = 0 ; d < 4 ; ++ d) {
            int newx = x + dx[d];
            int newy = y + dy[d];
            if(inside(newx, newy) && smth.find(getcode(newx, newy)) == smth.end()) {
                q.push(make_pair(newx, newy));
                smth.insert(getcode(newx, newy));
            }
        }
    }
}
 
inline int find(int x) {
    if(x != father[x])
        father[x] = find(father[x]);
    return father[x];
}
 
int main() {
    fin >> n;
    mymap.clear();
    for(int i = 1 ; i <= n ; ++ i) {
        int x, y;
        fin >> x >> y;
        -- x;
        -- y;
        mymap.insert(make_pair(getcode(x, y), i));
        father[i] = i;
    }
    for(unordered_map <int, int> :: iterator it = mymap.begin() ; it != mymap.end() ; ++ it) {
        check(it->first);    
    }
    sort(edges.begin(), edges.end());
    int totalcost = 0;
    for(vector <pair<int, pair<int, int> > > :: iterator it = edges.begin() ; it != edges.end() ; ++ it) {
        int tx = find(it->second.first);
        int ty = find(it->second.second);
        int cost = it->first;
        if(tx == ty)
            continue;
        totalcost += cost;
        father[tx] = ty;
    }
    fout << totalcost << '\n';
}
