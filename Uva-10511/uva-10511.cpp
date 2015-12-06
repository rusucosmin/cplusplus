#include <iostream>
#include <vector>
#include <string.h>
#include <queue>
#include <bitset>
#include <sstream>
#include <unordered_map>
#include <bitset>
#include <algorithm>

using namespace std;

const int maxn = 3005;
const int oo = 0x3f3f3f3f;

struct edge {
	int x, flow, cap;
	edge(int _x, int _cap, int _flow) {
		x = _x;
		cap = _cap;
		flow = _flow;
	}
};

vector <int> c[maxn];
int t, names, clubs, parties, which[maxn], edgecnt, father[maxn], dadedge[maxn];
unordered_map<string, int> idname, idparty, idclub;
unordered_map<int, string> revname, revparty, revclub;
vector <int> g[maxn];
vector <edge> e;
bitset <maxn> used;
queue <int> q;

inline int geta(int x) {
	return x;
}

inline int getb(int x) {
	return x + clubs;
}

inline int getc(int x) {
	return x + clubs + names;
}

inline void addedge(int x, int y, int cap) {
	g[x].push_back(edgecnt);
	e.push_back(edge(y, cap, 0));
	++ edgecnt;

	g[y].push_back(edgecnt);
	e.push_back(edge(x, 0, 0));
	++ edgecnt;
}

inline bool bfs(int source, int sink) {
	used.reset();
	used[source] = 1;
	q.push(source);
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(auto it : g[node]) {
			edge nxt = e[it];	
			if(!used[nxt.x] && nxt.cap - nxt.flow > 0) {
				used[nxt.x] = 1;
				father[nxt.x] = node;
				dadedge[nxt.x] = it;
				q.push(nxt.x);
			}
		}
	}
	return used[sink];
}

inline int maxflow(int source, int sink) {
	int ret = 0;
	while(bfs(source, sink))
		for(auto it : g[sink]) {
			edge nxt = e[it];
			edge backedge = e[it ^ 1];
			if(!used[nxt.x] || backedge.cap - backedge.flow <= 0)
				continue;
			father[sink] = nxt.x;
			dadedge[sink] = it ^ 1;
			int bottleneck = oo;
			for(int i = sink ; i != source ; i = father[i])
				bottleneck = min(bottleneck, e[dadedge[i]].cap - e[dadedge[i]].flow);
			for(int i = sink ; i != source ; i = father[i]) {
				e[dadedge[i]].flow += bottleneck;
				e[dadedge[i] ^ 1].flow -= bottleneck;
			}
			ret += bottleneck;
		}
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-10511.in", "r", stdin);
	freopen("uva-10511.out", "w", stdout);
	#endif
	cin >> t;
	string s;
	getline(cin, s);
	getline(cin, s);
	while(t --) {
		names = parties = clubs = 0;
		while(getline(cin, s)) {
			if(s.size() == 0)
				break;
			istringstream get(s);
			string name, party, club;
			get >> name >> party;
			idname[name] = ++ names;
			revname[names] = name;
			if(!idparty[party]) {
				idparty[party] = ++ parties;
				revparty[parties] = party;
			}
			which[idname[name]] = idparty[party];
			while(get >> club) {
				if(!idclub[club]) {
					idclub[club] = ++ clubs;
					revclub[clubs] = club;
				}
				c[idname[name]].push_back(idclub[club]);
			}
		}
		int source = 0, sink = names + clubs + parties + 1;
		for(int i = 1 ; i <= clubs ; ++ i)
			addedge(source, geta(i), 1);
		for(int i = 1 ; i <= names ; ++ i) {
			addedge(getb(i), getc(which[i]), 1);
			for(auto it : c[i]) {
				addedge(geta(it), getb(i), 1);
			}
		}
		for(int i = 1 ; i <= parties ; ++ i) {
			addedge(getc(i), sink, (clubs - 1) / 2);
		}
		int mf = maxflow(source, sink);
		if(mf != clubs)
			cout << "Impossible.\n";
		else {
			vector <pair<string, string> > ans;
			for(int i = 1 ; i <= clubs  ; ++ i)
				for(auto it : g[geta(i)]) {
					edge nxt = e[it];
					if(nxt.cap == nxt.flow) {
						ans.push_back(make_pair(revname[nxt.x - clubs], revclub[i]));
						break;
					}
				}
			sort(ans.begin(), ans.end());
			for(auto it : ans)
				cout << it.first << ' ' << it.second << '\n';
		}
		if(t)
		cout << '\n';
		for(int i = 1 ; i <= names ; ++ i)
			c[i].clear();
		for(int i = source ; i <= sink ; ++ i)
			vector <int> ().swap(g[i]);
		vector <edge> ().swap(e);
		idname.clear();
		revname.clear();
		idclub.clear();
		revclub.clear();
		idparty.clear();
		revparty.clear();
		edgecnt = 0;
	}
}
