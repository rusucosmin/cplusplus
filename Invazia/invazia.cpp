#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int maxn = 400005;
const int oo = (1 << 30);

struct node {
	int mini;
	int lazy;
	node () {
		mini = oo;
		lazy = oo;
	}
} arb[maxn << 2];

int n, m, top;
vector <pair<int, int> > updates[maxn * 5];
vector <pair<int, int> > updateslazy[maxn * 5];

inline void update(int node, int st, int dr, int x, int y, int z) {
	if(x <= st && dr <= y) {
		updates[top].push_back(make_pair(node, arb[node].mini));
		updateslazy[top].push_back(make_pair(node, arb[node].lazy));
		arb[node].mini = min(arb[node].mini, z);
		arb[node].lazy = min(arb[node].lazy, z);
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(arb[node].lazy != oo) {
		updateslazy[top].push_back(make_pair(node, arb[node].lazy));
		update(node << 1, st, mid, st, mid, arb[node].lazy);
		update((node << 1) | 1, mid + 1, dr, mid + 1, dr, arb[node].lazy);
		arb[node].lazy = oo;
	}
	if(x <= mid)
		update(node << 1, st, mid, x, y, z);
	if(mid < y)
		update((node << 1) | 1, mid + 1, dr, x, y, z);
	updates[top].push_back(make_pair(node, arb[node].mini));
	arb[node].mini = min(arb[node << 1].mini, arb[(node << 1) | 1].mini);
}

inline int query(int node, int st, int dr, int x) {
	if(st == dr)
		return arb[node].mini;
	int mid = ((st + dr) >> 1);	
	if(arb[node].lazy != oo) {
		updateslazy[top].push_back(make_pair(node, arb[node].lazy));
		update(node << 1, st, mid, st, mid, arb[node].lazy);
		update((node << 1) | 1, mid + 1, dr, mid + 1, dr, arb[node].lazy);
		arb[node].lazy = oo;
	}
	if(x <= mid)
		return query(node << 1, st, mid, x);
	else
		return query((node << 1) | 1, mid + 1, dr, x);
}

int main() {
	ifstream fin("invazia.in");
	ofstream fout("invazia.out");
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		char op;
		int x, y, z;
		fin >> op;
		if(op == 'I') {
			++ top;
			fin >> x >> y >> z;
			update(1, 1, n, x, y, z);
			continue;
		}
		if(op == 'E') {	
for(vector <pair<int, int> > :: reverse_iterator it = updates[top].rbegin() ; it != updates[top].rend() ; ++ it)
				arb[it->first].mini = it->second;
for(vector <pair<int, int> > :: reverse_iterator it = updateslazy[top].rbegin() ; it != updateslazy[top].rend () ; ++ it)
				arb[it->first].lazy = it->second;
			updates[top].clear();
			updateslazy[top].clear();
			-- top;
			continue;
		}
		if(op == 'R') {
			fin >> x;
			int ans = query(1, 1, n, x);
			if(ans == (1 << 30))
				fout << "GUITZZZ!\n";
			else
				fout << ans << '\n';
		}
	}
}
