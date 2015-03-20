#include <vector>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int maxn = 100005;
const int maxlg = 18;

struct node {
	node *left, *right;	
	int count;
	node (int _count, node *_left, node *_right) {
		count = _count;
		right = _right;
		left = _left;
	}
	node *insert(int l, int r, int w);
};

node *null = new node(0, NULL, NULL);
node *root[maxn];


node * node::insert(int l, int r, int w) {
	if(l <= w && w <= r) {
		if(l == r)
			return new node(this->count+1, null, null);

		int m = ((l+r)>>1);
		return new node(this->count+1, this->left->insert(l, m, w), this->right->insert(m + 1, r, w));
	}
	return this;
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	x = 0;
	while(!('0' <= buff[pos] && buff[pos] <= '9')) {
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while('0' <= buff[pos] && buff[pos] <= '9') {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

int v[maxn], anc[maxlg][maxn], values, depth[maxn];
vector <int> g[maxn];
map <int, int> mp, rm;

inline void dfs(int nod, int father) {
	anc[0][nod] = father;
	depth[nod] = depth[father] + 1;
	root[nod] = root[father] -> insert(1, values, mp[v[nod]]);
	for(vector <int> :: iterator it = g[nod].begin() ; it != g[nod].end() ; ++ it)
		if(*it != father)
			dfs(*it, nod);
}

inline int lca(int x, int y) {
	if(depth[x] < depth[y])
		swap(x, y);
	int log1, log2;
	for(log1 = 1 ; (1 << log1) < depth[x] ; ++ log1);
	for(log2 = 1 ; (1 << log2) < depth[y] ; ++ log2);

	for(int k = log1 ; k >= 0 ; -- k)
		if(depth[x] - (1 << k) >= depth[y])
			x = anc[k][x];
	if(x == y)
		return x;
	for(int k = log2 ; k >= 0 ; -- k)
		if(anc[k][x] && anc[k][x] != anc[k][y]) {
			x = anc[k][x];
			y = anc[k][y];
		}
	return anc[0][x];
}

inline int query(node *a, node *b, node *c, node *d, int st, int dr, int k) {
	if(st == dr)
		return st;
	int sum = a->left->count + b->left->count - c->left->count - d->left->count;
	int mid = ((st + dr) >> 1);
	if(sum >= k)
		return query(a->left, b->left, c->left, d->left, st, mid, k);
	return query(a->right, b->right, c->right, d->right, mid + 1, dr, k - sum);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("cot.in", "r", stdin);
	freopen("cot.out", "w", stdout);
	#endif
	int n, m;
	getint(n);
	getint(m);
	for(int i = 1 ; i <= n ; ++ i) {
		getint(v[i]);
		mp[v[i]];
	}

	values = 0;
	for(map <int, int> :: iterator it = mp.begin() ; it != mp.end() ; ++ it) {
		++ values;
		mp[it->first] = values;
		rm[values] = it->first;
	}

	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		getint(x);
		getint(y);
		g[x].push_back(y);
		g[y].push_back(x);
	}

	null->left = null->right = null;
	root[0] = null;	
	dfs(1, 0);

	for(int lg = 1 ; (1 << lg) <= n ; ++ lg)
		for(int i = 1 ; i <= n ; ++ i)
			anc[lg][i] = anc[lg - 1][ anc[lg - 1][i] ];
	
	while(m --) {
		int x, y, k;
		getint(x);
		getint(y);
		getint(k);
		int LCA = lca(x, y);
		int ans = query(root[x], root[y], root[LCA], root[ anc[0][LCA] ], 1, values, k);
		printf("%d\n", rm[ans]);
	}
}
