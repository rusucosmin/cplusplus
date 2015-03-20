#include <vector>
#include <queue>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int maxn = 100005;
const int bt = 31;

int t, n, m, first[maxn], a[maxn], last[maxn], h, euler[maxn];
vector <int> g[maxn];

struct trie {
	int cnt;
	trie *sons[2];
	trie() {
		cnt = 0;
		memset(sons, 0, sizeof(sons));
	}
	~trie() {
		for(int i = 0 ; i < 2 ; ++ i)
			if(sons[i])
				delete sons[i];
	}
} *arb[maxn << 2];

inline void dfs(int node, int father) {
	first[node] = ++ h;
	euler[h] = node;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(*it != father)
			dfs(*it, node);
	last[node] = h;
}

const int lim = (1 << 20);
int pos;
char buff[lim];

inline void getint(int &x) {
	x = 0;
	while(!isdigit(buff[pos])) {
		if(++ pos == lim) {
			fread(buff, 1, lim, stdin);
			pos = 0;
		}
	}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			fread(buff, 1, lim, stdin);
			pos = 0;
		}
	}
}

inline void add(trie *&node, int value, int cnt, int bit) {
	if(bit == -1) {
		node->cnt += cnt;
		return;
	}
	bool son = (value & (1 << bit));
	if(!node->sons[son])
		node->sons[son] = new trie();
	add(node->sons[son], value, cnt, bit - 1);
	node->cnt = 0;
	for(int i = 0 ; i < 2 ; ++ i)
		if(node->sons[i])
			node->cnt += node->sons[i]->cnt;
}
 
inline void build(int node, int st, int dr) {
	if(st == dr) {
		if(arb[node])
			delete arb[node];
		arb[node] = new trie();
		add(arb[node], a[euler[st]], 1, bt);
		return ;
	}
	int mid = ((st + dr) >> 1);
	build(node << 1, st, mid);
	build((node << 1) | 1, mid + 1, dr);
	if(arb[node])
		delete arb[node];
	arb[node] = new trie();
	for(int i = st ; i <= dr ; ++ i)
		add(arb[node], a[euler[i]], 1, bt);
}

vector <trie *> v, nxt[2];

inline void query(int node, int st, int dr, int x, int y) {
	if(x <= st && dr <= y) {
		v.push_back(arb[node]);
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(x <= mid)
		query(node << 1, st, mid, x, y);
	if(mid < y)
		query((node << 1) | 1, mid + 1, dr, x, y);
}

inline int solve(int k) {
	int ret = 0;
	for(int bit = bt ; bit >= 0 ; -- bit) {
		int sum = 0;
		for(vector <trie *> :: iterator it = v.begin() ; it != v.end() ; ++ it) {
			if(*it && (*it)->sons[0])
				sum += (*it)->sons[0]->cnt;
			if(*it && (*it)->sons[0])
				nxt[0].push_back((*it)->sons[0]);
			if(*it && (*it)->sons[1])
				nxt[1].push_back((*it)->sons[1]);
		}
		bool son = 0;
		if(k > sum) {
			k -= sum;
			son = 1;
		}
		ret = ret * 2 + son;
		v.clear();
		v = nxt[son];
		nxt[0].clear();
		nxt[1].clear();
	}
	assert(ret <= 1000000000);
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1695.in", "r", stdin);
	freopen("uri1695.out", "w", stdout);
	#endif

	getint(t);

	while (t--) {
		h = 0;
		getint(n);
		getint(m);
		for(int i = 1 ; i <= n ; ++ i) {
			getint(a[i]);
			g[i].clear();
		}	
		for(int i = 1 ; i < n ; ++ i) {
			int x, y;

			getint(x);
			getint(y);
			
			g[x].push_back(y);
			g[y].push_back(x);
		}

		dfs(1, 0);

		build(1, 1, n);

		for(int i = 1 ; i <= m ; ++ i) {
			int x, k;
			getint(x);
			getint(k);
			v.clear();
			query(1, 1, n, first[x], last[x]);
			printf("%d ", solve(k));
		}

		printf("\n");
	}
}
