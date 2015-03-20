#include <iostream>
#include <fstream>
#include <bitset>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <bitset>

using namespace std;

const int maxn = 23;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = { 0,-1, 0, 1};
const int oo = 0x3f3f3f3f;

int n, m, males, females, r, c, t, edgecnt;
char s[maxn][maxn];
vector <pair<pair<int, int>, long long> > male, female; 
long long dp[maxn][maxn][maxn][maxn];
vector <long long> cost;
vector <int> cap;
unordered_map<int, vector <pair<int, int> > > g;
unordered_map<int, int> father, dadedge;
unordered_map<int, bool> used;
int source, sink, aux;

inline int geta(int x) {
	return x;
}

inline int getb(int x, int y) {
	return males + (x - 1) * m + y;
}

inline int in(int x, int y) {
	return getb(x, y);
}

inline int out(int x, int y) {
	return sink + (x - 1) * m + y;
}

inline int getc(int x) {
	return males + n * m + x;
}

inline bool inside(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

inline void addedge(int x, int y, long long dist) {
	g[x].push_back(make_pair(y, edgecnt));
	cost.push_back(dist);
	cap.push_back(1);
	++ edgecnt;
	g[y].push_back(make_pair(x, edgecnt));
	cost.push_back(dist);
	cap.push_back(0);
	++ edgecnt;
}

inline void bfs(pair<int, int> st, long long dist[maxn][maxn], long long t) {
	queue <pair<int, int> > q;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			dist[i][j] = -1;
	q.push(st);
	dist[st.first][st.second] = 0;
	while(!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for(int i = 0 ; i < 4 ; ++ i) {
			int newx = x + dx[i];
			int newy = y + dy[i];
			if(inside(newx, newy) && dist[newx][newy] == -1 && s[newx][newy] != '#') {
				dist[newx][newy] = dist[x][y] + t;	
				q.push(make_pair(newx, newy));
			}
		}
	}
}

inline bool bfs(int source, int sink, long long value) {
	queue <int> q;
	used.clear();
	q.push(source);
	used[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(!used[it->first] && cap[it->second] > 0 && cost[it->second] <= value) {
				used[it->first] = 1;
				father[it->first] = node;
				dadedge[it->first] = it->second;
				q.push(it->first);
			}
		}
	}
	return used[sink];
}

inline bool check(long long value) {
	for(int i = 0 ; i < aux ; ++ i)
		if(i % 2 == 0)
			cap[i] = 1;
		else
			cap[i] = 0;
	for(int i = aux ; i < cap.size() ; ++ i) {
		if((i - aux) % 2 == 0)
			cap[i] = 1;  
		else
			cap[i] = 0;
	}
	int maxflow = 0;
	while(bfs(source, sink, value)) {
		for(vector <pair<int, int> > :: iterator it = g[sink].begin() ; it != g[sink].end() ; ++ it) {
			if(!used[it->first] || cap[it->second ^ 1] <= 0 || cost[it->second ^ 1] > value)
				continue;
			father[sink] = it->first;
			dadedge[sink] = it->second ^ 1;
			int bottleneck = oo;
			for(int i = sink ; i != source ; i = father[i]) {
				bottleneck = min(bottleneck, cap[dadedge[i]]);
			}
			if(!bottleneck)
				continue;
			maxflow += bottleneck;
			for(int i = sink ; i != source ; i = father[i]) {
				cap[dadedge[i]] -= bottleneck;
				cap[dadedge[i] ^ 1] += bottleneck;
			}
		}
	}
	return maxflow >= males;
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	while(!isdigit(buff[pos])) {
		if( ++pos == lim) {
			pos = 0;
			fread(buff,1,lim, stdin);
		}
	}
	x = 0;
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

inline void getlonglong(long long &x) {
	x = 0;
	while(!isdigit(buff[pos])) {
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff,1,lim,stdin);
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("513f1.in","r", stdin);
	freopen("513f1.out", "w", stdout);
	#endif
	scanf("%d%d%d%d", &n, &m, &males, &females);
	if((males + females + 1) % 2) {
		cout << "-1\n";
		return 0;
	}
	source = 0;
	sink = males + n * m + females + 1 + 1;
	for(int i = 1 ; i <= n ; ++ i)
		scanf("%s", s[i] + 1);
	if(males < females)
		++ males;
	else {
		int x, y;
		long long z;
		getint(x);
		getint(y);
		getlonglong(z);
		cin >> x >> y >> z;
		++ females;
		female.push_back(make_pair(make_pair(x, y), z));
		bfs(make_pair(x, y), dp[x][y], z);
		addedge(getc(1), sink, 0);
		for(int a = 1 ; a <= n ; ++ a)
			for(int b = 1 ; b <= m ; ++ b)
				if(dp[x][y][a][b] != -1)
					addedge(out(a, b), getc(1), dp[x][y][a][b]);
	}
	for(int i = 0 ; i < males ; ++ i) {
		int x, y;
		long long z;
		getint(x);
		getint(y);
		getlonglong(z);
		male.push_back(make_pair(make_pair(x, y), z));
		bfs(make_pair(x, y), dp[x][y], z);
		addedge(source, geta(i + 1), 0);
		for(int a = 1 ; a <= n ; ++ a)
			for(int b = 1 ; b <= m ; ++ b)
				if(dp[x][y][a][b] != -1)
					addedge(geta(i + 1), in(a, b), dp[x][y][a][b]);
	}
	for(int i = female.size() ; i < females ; ++ i) {
		int x, y;
		long long z;
		getint(x);
		getint(y);
		getlonglong(z);
		female.push_back(make_pair(make_pair(x, y), z));
		bfs(make_pair(x, y), dp[x][y], z);
		addedge(getc(i + 1), sink, 0);
		for(int a = 1 ; a <= n ; ++ a)
			for(int b = 1 ; b <= m ; ++ b)
				if(dp[x][y][a][b] != -1)
					addedge(out(a, b), getc(i + 1), dp[x][y][a][b]);
	}
	aux = edgecnt;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			addedge(in(i, j), out(i, j), 0);
	long long ans = -1, st = 0LL, dr = (1LL << 62);
	while(st <= dr) {
		long long mid =  st + ((dr - st) / 2);
		if(check(mid)) {
			ans = mid;
			dr = mid - 1;
		}
		else
			st = mid + 1;
	}
	cout << ans << '\n';
}
