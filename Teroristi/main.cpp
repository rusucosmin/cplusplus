#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const char infile[] = "teroristi.in";
const char outfile[] = "teroristi.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1000005;
const int MAXM = 26 + 26 * 27 / 2 + 5;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXM];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int Source = 0, Sink;
int N, M, maxFlow;
char S[MAXN];
int key[28][28], Father[MAXM];
Graph G;
int C[MAXM][MAXM], F[MAXM][MAXM], fr1[28], fr2[MAXM];
vector <pair<char, char> > pairs;
bitset <MAXN> Used;
queue <int> Q;

inline int getCharKeyValue(const char &c) {
    return 1 + c - 'a';
}

inline int getPairCharKey(const pair<char, char> &c) {
    return 27 + key[min(c.first - 'a', c.second - 'a')][max(c.first - 'a', c.second - 'a')];
}

inline void buildNetwork() {
    for(int i = 0 ; i < M ; ++ i) {
        int key = getPairCharKey(pairs[i]);
        G[key].push_back(Sink);
        G[Sink].push_back(key);
        C[key][Sink] = fr2[key];
    }
    for(char i = 'a' ; i <= 'z' ; ++ i)
        for(char j = i ; j <= 'z' ; ++ j) {
            int key1 = getCharKeyValue(i);
            int key2 = getCharKeyValue(j);
            int keypair = getPairCharKey(make_pair(i, j));
            G[key1].push_back(keypair);
            G[keypair].push_back(key1);
            G[key2].push_back(keypair);
            G[keypair].push_back(key2);
            C[key1][keypair] = oo;
            C[key2][keypair] = oo;
        }
}

inline bool BFs(const int &startNode) {
    Used.reset();
    Q.push(startNode);
    Used[startNode] = true;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[Node][*it] - F[Node][*it] > 0) {
                Q.push(*it);
                Used[*it] = true;
                Father[*it] = Node;
            }
    }
    return Used[Sink];
}

inline void doMaxFlow() { /// Ford fulkenson
    while(BFs(Source))
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!Used[*it] || C[*it][Sink] - F[*it][Sink] <= 0)
                continue;
            Father[Sink] = *it;
            int minFlow = oo;
            for(int i = Sink ; i != Source  && minFlow ; i = Father[i])
                minFlow = min(minFlow, C[Father[i]][i] - F[Father[i]][i]);
            if(!minFlow)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                F[Father[i]][i] += minFlow;
                F[i][Father[i]] -= minFlow;
            }
            maxFlow += minFlow;
        }
}

int main() {
    int keys = 0;
    for(int i = 0 ; i < 26 ; ++ i)
        for(int j = i ; j < 26 ; ++ j)
            key[i][j] = keys ++;
    Sink = 26 + 26 * 27 / 2 + 3;
    fin >> N >> M;
    fin >> (S + 1);
    for(int i = 1 ; i <= N ; ++ i)
        ++ fr1[S[i]];
    for(int i = 1 ; i <= N ; ++ i) {
        int key = getCharKeyValue(S[i]);
        G[key].push_back(Source);
        G[Source].push_back(key);
        C[Source][key] = fr1[S[i]];
    }
    for(int i = 0 ; i < M ; ++ i) {
        char a, b;
        fin >> a >> b;
        pairs.push_back(make_pair(a, b));
        ++ fr2[getPairCharKey(pairs[i])];
    }
    buildNetwork();
    doMaxFlow();
    vector <int> Ans[31];
    for(int i = 0 ; i < M ; ++ i) {
        pair<char, char> act = pairs[i];
        int key1 = getCharKeyValue(act.first);
        int key2 = getCharKeyValue(act.second);
        int keypair = getPairCharKey(act);
        if(F[key1][keypair] > 0) {
            Ans[key1].push_back(i);
            -- F[key1][keypair];
        }
        else {
            Ans[key2].push_back(i);
            -- F[key2][keypair];
        }
    }
    for(int i = 1 ; i <= N ; ++ i) {
        //if(Ans[getCharKeyValue(S[i])].empty())
        //    continue;
        int sol = Ans[getCharKeyValue(S[i])].back();
        Ans[getCharKeyValue(S[i])].pop_back();
        fout << sol + 1 << ' ';
    }
    fin.close();
    fout.close();
    return 0;
}
