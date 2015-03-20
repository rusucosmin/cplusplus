#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int maxn = 100005;

struct trio {
	int st, dr, ind;
	trio(int _st, int _dr, int _ind) {
		st = _st;
		dr = _dr;
		ind = _ind;
	}
};

int n, m, ans[maxn];
vector < trio > actor, part;

struct classcomp {
	inline bool operator () (const trio &a, const trio &b) const {
		return a.st < b.st || (a.st == b.st && a.dr > b.dr);
	}
};

multiset <pair<int, int> > s;
vector <int> k;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("496e.in", "r", stdin);
	#endif
	cin >> n;
	for(int i = 0 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		part.push_back(trio(x, y, i));
	}
	cin >> m;
	for(int i = 0 ; i < m ; ++ i) {
		int x, y, z;
		cin >> x >> y >> z;
		actor.push_back(trio(x, y, i));
		k.push_back(z);
	}
	sort(part.begin(), part.end(), classcomp());
	sort(actor.begin(), actor.end(), classcomp());
	
	int j = 0;
	for(int i = 0 ; i < n ; ++ i) {
		while(j < actor.size() && actor[j].st <= part[i].st) {
			s.insert(make_pair(actor[j].dr, actor[j].ind));
			++ j;
		}
		multiset<pair<int, int> > :: iterator it = s.lower_bound(make_pair(part[i].dr, 0));
		if(it == s.end()) {
			cout << "NO\n";
			return 0;
		}
		ans[part[i].ind] = it->second;
		-- k[it->second];
		if(!k[it->second])
			s.erase(it);
	}
	cout << "YES\n";
	for(int i = 0 ; i < n ; ++ i)
		cout << ans[i] + 1 << ' ';
}
