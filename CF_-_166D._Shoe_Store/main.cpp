/*#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, Father[MAXN];
int dp[MAXN];
map<pair<int, int>, int> C, F;
bitset <MAXN> inQ;
queue <int> Q;
Graph G;

inline bool BF(Graph &G, int Source, int Sink) {
    memset(dp, oo, sizeof(dp));
    Q.push(Source);
    dp[Source] = 0;
    inQ[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = 0;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(C[make_pair(Node, it->first)] - F[make_pair(Node, it->first)] > 0 && dp[it->first] > dp[Node] + it->second) {
                dp[it->first] = dp[Node] + it->second;
                Father[it->first] = Node;
                if(inQ[it->first])
                    continue;
                inQ[it->first] = 1;
                Q.push(it->first);
            }
    }
    return dp[Sink] != oo;
}

inline pair<int, long long> getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    long long minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        for(int i = Sink ; i != Source ; i = Father[i]) {
            ++ F[make_pair(Father[i], i)];
            -- F[make_pair(i, Father[i])];
        }
        ++ maxFlow;
        minCostMaxFlow += 1LL * dp[Sink];
    }
    return make_pair(maxFlow, minCostMaxFlow);
}

const int kBufferSize = 50;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (cin.read(Buffer, kBufferSize), BufferInd = 0) : (0))
#define BufferC (Buffer[BufferInd])
#define char_ok (((BufferC >= '0' and BufferC <= '9') or BufferC == '-') ? (1) : (0))

inline void cit(int &n) {
	verf;
	for (; not char_ok; verf)
		;

	bool sign = false;
	if (BufferC == '-') {
		verf;
		sign = true;
	}

	n = 0;
	for (; char_ok; verf) {
		n *= 10;
		n += BufferC - '0';
	}
	if (sign)
		n *= -1;
}


int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    vector <pair<int, int> > A, B;
    A.push_back(make_pair(0, 0));
    B.push_back(make_pair(0, 0));
    cit(N);
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        cit(x);
        cit(y);
        A.push_back(make_pair(x, y));
    }
    cit(M);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cit(x);
        cit(y);
        B.push_back(make_pair(x, y));
    }
    int Source = 0, Sink = N + M + 1;
    for(int i = 1 ; i <= N ; ++ i) {
        G[Source].push_back(make_pair(i, 0));
        G[i].push_back(make_pair(Source, 0));
        C[make_pair(Source, i)] = 1;
        for(int j = 1 ; j <= M ; ++ j) {
            int c = A[i].first;
            int s = A[i].second;
            int d = B[j].first;
            int l = B[j].second;
            if(c <= d && (l == s || l == s - 1)) {
                G[i].push_back(make_pair(j + N, -c));
                G[j + N].push_back(make_pair(i,  c));
                C[make_pair(i, j + N)] = 1;
            }
        }
    }
    for(int ii = 1 ; ii <= M ; ++ ii) {
        G[ii + N].push_back(make_pair(Sink, 0));
        G[Sink].push_back(make_pair(ii + N, 0));
        C[make_pair(ii + N, Sink)] = 1;
    }
    pair<int, long long> minCostMaxFlow = getMinCostMaxFlow(G, Source, Sink);
    cout << -minCostMaxFlow.second << '\n' << minCostMaxFlow.first << '\n';
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            if(F[make_pair(i, j + N)])
                cout << j << ' ' << i << '\n';
    return 0;
}
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#define N 100000
using namespace std;

typedef long long ll;
struct obj
{
	int s, c, n;
	obj()
	{ s = c = 0; }
	obj(int price, int size, int num = 0)
	{ c = price, s = size, n = num; }
}a[N + 1], c;
vector <int> q[N + 1];
int n, m, i, j, p[N + 1], k = 0, x, y;
ll ans = 0;
bool v[N + 1];

inline bool cmp(obj a, obj b)
{ return a.s < b.s; }
inline bool cmp2(obj a, obj b)
{ return a.c > b.c; }

bool find(int s)
{
	int i, x;
	for (i = 0; i < q[s].size(); ++i)
		if (!v[x = q[s][i]])
		{
			v[x] = true;
			if (!p[x] || find(p[x]))
			{
				p[x] = s;
				return true;
			}
		}
	return false;
}

int main()
{
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) scanf("%d%d", &x, &y), a[i] = obj(x, y, i);
	sort(a + 1, a + n + 1, cmp);
	scanf("%d", &m);
	for (i = 1; i <= m; ++i)
	{
		scanf("%d%d", &x, &y);
		c = obj(x, y);
		for (j = lower_bound(a + 1, a + n + 1, c, cmp) - a; c.s + 1 == a[j].s || c.s == a[j].s; ++j)
			if (c.c >= a[j].c) q[a[j].n].push_back(i);
	}
	sort(a + 1, a + n + 1, cmp2);
	for (i = 1; i <= n; ++i)
	{
		memset(v, 0, sizeof v);
		if (find(a[i].n)) ++k, ans += (ll)a[i].c;
	}
	printf("%I64d\n%d\n", ans, k);
	for (i = 1; i <= m; ++i)
		if (p[i]) printf("%d %d\n", i, p[i]);
	return 0;
}
