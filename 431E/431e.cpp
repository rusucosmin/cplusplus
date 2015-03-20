#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

const int maxn = 201005;

long long aib[2][maxn];
int n, m, a[maxn], uniq;
map<long long, int> ind;
map<int, long long> rev;

struct input {
	int op, p, x;
	long long v;
};

inline int lsb(int x) {
	return x & (-x);
}

inline void update(int type, int node, int value) {
	for(int i = node ; i <= uniq ; i += lsb(i))
		aib[type][i] += value;
}

inline long long query(int type, int node) {
	long long sum = 0;
	for(int i = node ; i > 0 ; i -= lsb(i))
		sum += aib[type][i];
	return sum;
}

vector <input> q;

inline long long check(int d) {
	long long t = query(1, d - 1);
	long long v1 = t * rev[d] - query(0, d - 1);
	return v1;
}

inline int getans(long long v) {
	int st = 1, dr = uniq, ans = uniq;
	while(st <= dr) {
		int mid = ((st + dr) >> 1);
		if(check(mid) >= v) {
			ans = mid;
			dr = mid - 1;
		}
		else
			st = mid + 1;
	}
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("431e.in", "r", stdin);
	freopen("431e.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		ind[a[i]];
	}
	for(int i = 1 ; i <= m ; ++ i) {
		input act;
		cin >> act.op;
		if(act.op == 1) {
			cin >> act.p >> act.x;
			ind[act.x];	
		}
		else
			cin >> act.v;
		q.push_back(act);
	}
	for(map<long long, int> :: iterator it = ind.begin() ; it != ind.end() ; ++ it) {
		ind[it->first] = ++ uniq;
		rev[uniq] = it->first;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		update(0, ind[a[i]], a[i]);
		update(1, ind[a[i]], 1);
	}
	for(vector <input> :: iterator it = q.begin() ; it != q.end() ; ++ it) {
		input act = *it;
		if(act.op == 1) {
			int i = act.p;
			update(0, ind[a[i]], -a[i]);
			update(1, ind[a[i]], -1);
			a[i] = act.x;
			update(0, ind[a[i]], a[i]);
			update(1, ind[a[i]], 1);
		}
		else {
			int ans = getans(act.v);
			long long t = query(1, ans - 1);
			long long v1 = rev[ans] * t - query(0, ans - 1);
			if(v1 >= act.v && t) 
				cout << ((long double)rev[ans] - (long double)(v1 - act.v) / t) << '\n';
			else
				cout << (long double)(rev[ans] + (long double)(act.v - v1) / n) << '\n';
				
		}
	}
}
