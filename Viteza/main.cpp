#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

ofstream cout("viteza.out");

const int MAXN = 100005;
const int MAXL = 20;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

struct qu {
    int x, y, k;
};

Graph G;

int N, M, K, First[MAXN], cst[MAXN], H, FirstLiniarization[MAXN], LastLiniarization[MAXN];
int Euler[MAXN<<1], Level[MAXN<<1], RMQ[MAXL][MAXN << 1], Log[MAXN << 1];
int ind[MAXN << 1], Ans[MAXN], aib[MAXN << 1];

qu query[MAXN << 1];

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        if(query[a].k == query[b].k)
            return a > b;
        return query[a].k < query[b].k;
    }
};

void DFs(int Node, int Father, int actLevel) {
    Euler[++ K] = Node;
    Level[K] = actLevel;
    First[Node] = K;

    FirstLiniarization[Node] = ++ H;

    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node, actLevel + 1);
        Euler[++ K] = Node;
        Level[K] = actLevel;
    }

    LastLiniarization[Node] = ++ H;
}

inline void BuildLog() {
    for(int i = 2 ; i <= K ; ++ i)
        Log[i] = Log[i >> 1] + 1;
}

inline void BuildRMQ() {
    for(int i = 1 ; i <= K ; ++ i)
        RMQ[0][i] = i;
    for(int i = 1 ; (1 << i) <= K ; ++ i)
        for(int j = 1 ; j <= K - ( 1 << i ) + 1 ; ++ j) {
            int l = (1 << (i-1));
            RMQ[i][j] = RMQ[i-1][j];
            if(Level[RMQ[i][j]] > Level[RMQ[i-1][j + l]])
                RMQ[i][j] = RMQ[i-1][j+l];
        }
}

inline int LCA(int a, int b) {
    int A = First[a];
    int B = First[b];
    if(A > B)
        swap(A, B);
    int diff = B - A + 1;
    int logg = Log[diff];
    int sol = RMQ[logg][A];
    int sh = diff - ( 1 << logg );
    if(Level[sol] > Level[RMQ[logg][A + sh]])
        sol = RMQ[logg][A+sh];
    return Euler[sol];
}

inline int lsb(int bit) {
    return bit & ( -bit );
}

inline void Insert(int pos, int value) {
    for(int i = pos ; i <= H ; i += lsb(i))
        aib[i] += value;
}

inline int Query(int x) {
    int rez = 0;
    for(int i = x ; i > 0 ; i -= lsb(i))
        rez += aib[i];
    return rez;
}


//</parsing>


int main() {
    N = getInt();
    M = getInt();
    //cin >> N >> M;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
    //    cin >> x >> y;
        x = getInt();
        y = getInt();
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 1, 0);
    BuildLog();
    BuildRMQ();
    for(int i = 1 ; i <= N ; ++ i) {
        //cin >> cst[i];
        cst[i] = getInt();
        query[i + M].x = i;
        query[i + M].y = i;
        query[i + M].k = cst[i];
        ind[i + M] = i + M;
    }
    for(int i = 1 ; i <= M ; ++ i) {
        query[i].x = getInt();
        query[i].y = getInt();
        query[i].k = getInt();
        ind[i] = i;
    }
    sort(ind + 1, ind + N + M + 1, ClassComp());
    for(int i = 1 ; i <= N + M ; ++ i) {
        int x = query[ind[i]].x;
        int y = query[ind[i]].y;
        int k = query[ind[i]].k;
        if(ind[i] > M) {
            Insert(LastLiniarization[x], -1);
            Insert(FirstLiniarization[x], 1);
            continue;
        }
        int lca = LCA(x, y);
        int q1, q2;
        bool ok = true;
        q1 = Query(FirstLiniarization[x]) - Query(FirstLiniarization[lca] - 1);
        q2 = Query(FirstLiniarization[y]) - Query(FirstLiniarization[lca] - 1);
        Ans[ind[i]] = q1 + q2 - (cst[lca] <= k);
    }
    for(int i = 1 ; i <= M ; ++ i)
        cout << Ans[i] << '\n';
    //cin.close();
    cout.close();
    return 0;
}
