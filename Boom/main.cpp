
/*
            int Nod = i;
            Nod ^= Edge[j].mask;
            int Aux = (Nod >> 1) | (Nod << 1);
            if(Aux & ( 1 << N ))
                Aux -= (1 << N);
*/
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <cassert>

using namespace std;

const char in[] = "boom.in";
const char out[] = "boom.out";

ifstream cin(in);
ofstream cout(out);

const int MAXN = (1<<21) + 10;
const int oo = 0x3f3f3f3f;

struct {
    int c, mask;
} Edge[55];

int N, M;
vector <int> d(MAXN, oo);
priority_queue < pair<int, int> , vector < pair<int, int>  > , greater< pair<int, int>  > > H;
pair<int, int> Next[MAXN];
vector<int> Ans;

inline void Dijkstra() {
    for(H.push(make_pair(0, (1<<N)-1)), d[(1<<N)-1] = 0 ; !H.empty() ; H.pop() ) {
        int Node = H.top().second;
        if(Node == 0)
            return;
        for(int i = 1 ; i <= M ; ++ i) {
            int Aux = Node & Edge[i].mask;
            int actNode = (Aux << 1) | (Aux >> 1);
            assert(actNode >= 0);
            if(d[actNode] > d[Node] + Edge[i].c) {
                d[actNode] = d[Node] + Edge[i].c;
                Next[actNode] = make_pair(Node, i);
                H.push(make_pair(d[actNode], actNode));
            }
        }
    }
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int y;
        cin >> Edge[i].c;
        cin >> y;
        for(int j = 1 ; j <= y ; ++ j) {
            int x;
            cin >> x;
            Edge[i].mask |= (1 << (x-1));
        }
    }
    Dijkstra();
    int Nod = 0;
    while(Nod != (1 << N)-1 && Next[Nod].first) {
        Ans.push_back(Next[Nod].second);
        Nod = Next[Nod].first;
    }
    cout << d[0] << '\n' << Ans.size() << '\n';
    for(vector<int> :: reverse_iterator it = Ans.rbegin() ; it != Ans.rend() ; ++ it)
        cout << *it << '\n';
    cin.close();
    cout.close();
    return 0;
}
