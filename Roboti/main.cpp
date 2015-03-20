#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("roboti.in");
ofstream cout("roboti.out");

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector< pair<int, int> > Graph;
typedef vector< pair<int, int> > :: iterator It;

Graph APM;
vector<pair<int, pair<int, int> > >G;
int N, Father[MAXN], Answer;

inline int Find(int x){
    if(Father[x] != x)
        Father[x] = Find(Father[x]);
    return Father[x];
}

int main()
{
    cin >> N;
    ++ N;
    int x, y, z, M;
    while(cin >> x >> y >> z)
        G.push_back(make_pair(z, make_pair(x, y)));
    for(int i = 0 ; i < N ; ++ i)
        Father[i] = i;
    sort(G.begin(), G.end());
    for(int i = 0 ; i < G.size() ; ++ i){
        int x = G[i].second.first;
        int y = G[i].second.second;
        int Tx = Find(x);
        int Ty = Find(y);
        if(Father[Tx] != Father[Ty]){
            cout << "DA";
            Father[Tx] = Ty;
            Answer += G[i].first;
            APM.push_back(G[i].second);
        }
    }
    cout << Answer << "\n";
        for(It it = APM.begin(), fin = APM.end() ; it != fin ; ++ it)
            cout << it->first << " " << it->second << "\n";
    cin.close();
    cout.close();
    return 0;
}
