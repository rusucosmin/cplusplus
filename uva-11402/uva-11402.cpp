#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 1024050;

struct Node {
	int a, b;
	int pending;
	Node () : a(0), b(0), pending(0) {}
	Node (int _a) : a(_a), b(0), pending(0) {}
	Node(int _a, int _b) : a(_a), b(_b), pending(0) {}
	Node clear() {
		a = b = 0;
		pending = 0;
	}
	Node lazy(int which) {
		if(which == 1) {
			b += a;
			a = 0;
			pending = 1;
		}
		else if(which == 2) {
			a += b;
			b = 0;
			pending = 2;
		}
		else if(which == 3) {
			swap(a, b);
			pending = 3 - pending;
		}
		return *this;
	}
	Node operator + (Node x) {
		return Node(a + x.a, b + x.b);
	}
} arb[3000100];

int n, m, t;
string act;

inline Node build(int node, int st, int dr) {
	if(st == dr) {
		return arb[node] = Node(1-(act[st - 1] - '0'), act[st - 1] - '0');
	}
	int mid = ((st + dr) >> 1);
	return arb[node] = build(node << 1, st, mid) +
	build((node << 1) | 1, mid + 1, dr);
}

inline Node update(int node, int st, int dr, int a, int b, int carry, int pending) {
	arb[node].lazy(carry);
	if(a > dr || b < st)
		return Node(0);
	if(a <= st && dr <= b)
		return arb[node].lazy(pending);
	int mid = ((st + dr) >> 1);
	Node answer = update(node << 1, st, mid, a, b, arb[node].pending, pending) +
		update((node << 1) | 1, mid + 1, dr, a, b, arb[node].pending, pending);
	arb[node] = arb[node << 1] + arb[(node << 1) | 1];
	return answer;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-11402.in", "r", stdin);
	freopen("uva-11402.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);
	cin >> t;
	int testcnt = 0;
	while(t -- ) {
		cin >> m;
		for(int i = 1 ; i <= m ; ++ i) {
			int cnt; string s;
			cin >> cnt >> s;
			for(int j = 1 ; j <= cnt ; ++ j)
				act = act + s;	
		}
		n = act.size();
		build(1, 1, n);
		cin >> m;
		cout << "Case " << ++ testcnt << ":\n";
		int qcnt = 0;
		for(int i = 1 ; i <= m ; ++ i) {
			char op; int x, y;
			cin >> op >> x >> y;
			++ x; ++ y;
			if(op == 'F')
				update(1, 1, n, x, y, 0, 1);
			else if(op == 'E')
				update(1, 1, n, x, y, 0, 2);
			else if(op == 'I')
				update(1, 1, n, x, y, 0, 3);
			else if(op == 'S') {
				cout << "Q" << ++qcnt << ": ";
				cout << update(1, 1, n, x, y, 0, 0).b << '\n';
			}
		}
	}
}

