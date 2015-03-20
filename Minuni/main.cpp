#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "minuni.in";
const char outfile[] = "minuni.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXM = 100005;
const int oo = 0x3f3f3f3f;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct query {
    int x, index;
    bool op;
    query(int _x, bool _op, int _index) : x(_x), index(_index), op(_op) {}
};

struct classComp {
    inline bool operator () (const query &a, const query &b) {
        return a.x < b.x;
    }
};

int N, M, arb[MAXM * 4], st[MAXM];
vector < pair<int, int> > edges;
long long Ans[MAXM];
vector < query > events;

int Query(int Node, int st, int dr, int a, int b) {
    if(!Node)
        return 0;
    if(a <= st && dr <= b)
        return arb[Node];
    int fiuSt = Node * 2;
    int fiuDr = Node * 2 + 1;
    int mid = ((st + dr) / 2);
    //cout << Node << ' ' << fiuSt << ' ' << fiuDr << '\n';
    int ret = 0;
    if(a <= mid)
        ret = max(ret, Query(fiuSt, st, mid, a, b));
    if(mid < b)
        ret = max(ret, Query(fiuDr, mid + 1, dr, a, b));
    return ret;
}

void Update(int Node, int st, int dr, int pos, int value) {
    if(!Node)
        return;
    if(st == dr) {
        arb[Node] = value;
        return;
    }
    int fiuSt = Node * 2;
    int fiuDr = Node * 2 + 1;
    int mid = ((st + dr) / 2);
    if(pos <= mid)
        Update(fiuSt, st, mid, pos, value);
    else Update(fiuDr, mid + 1, dr, pos, value);
    arb[Node] = max(arb[fiuSt], arb[fiuDr]);
}

int main() {
    cin >> N >> M;
    edges.push_back(make_pair(0, 0));
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        edges.push_back(make_pair(x, y));
        events.push_back(query(x, 0, i));
        events.push_back(query(y, 1, i));
    }
    sort(events.begin(), events.end(), classComp());
    for(int i = 0 ; i < events.size() ; ++ i) {
        if(!events[i].op) {    /// we had to add this to the stack
            int Index = events[i].index;
            int stackIndex = Query(1, 1, M, 1, Index);
            int Father = 0;
            if(stackIndex)
                Father = st[stackIndex];
            if(!Father) {
                long long x = edges[Index].first;
                long long y = edges[Index].second;
                Ans[Index] = x * ( N - y + 1 );
                /// x * ( N - y + 1)
            }
            else {
                /// x*(b-y)+(x-a)*(N-y+1)-(x-a)*(b-y).
                long long a = edges[Father].first;
                long long b = edges[Index].first;
                long long c = edges[Index].second;
                long long d = edges[Father].second;
                Ans[Index] = b * (d - c + 1) - a +
                              (b - a + 1) * (N - c + 1) - (N - d  +1) -
                              (b - a + 1) * (d - c + 1) + 1;
            }
            st[ ++st[0] ] = Index;
            Update(1, 1, M, Index, st[0]);
        }
        else {
            int Index = st[st[0]];
            -- st[0];
            Update(1, 1, M, Index, 0);
        }
    }
    for(int i = 1 ; i <= M ; ++ i)
        cout << Ans[i] << '\n';
    cin.close();
    cout.close();
    return 0;
}
