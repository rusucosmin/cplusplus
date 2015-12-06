#include <iostream>
#include <queue>

using namespace std;

int n;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("534d.in", "r", stdin);
	freopen("534d.out", "w", stdout);
	#endif
	cin >> n;
	priority_queue <pair<int, int> > q;
	int cnt = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		int a[i];
		cin >> a[i];
		q.push(make_pair(-a[i], i));
	}
	vector <int> v;
	while(!q.empty()) {
		int act = -q.top().first;
		int ind = q.top().second;
		q.pop();
		if(act == 0) {
			v.push_back(ind);
			if(cnt) {
				cout << "Impossible\n";
//				return 0;
			}
			++ cnt;
			continue;
		}
		if(act > cnt) {
			cout << "Impossible\n";
			return 0;
		}
		int aux = cnt - act;
		if(aux == 0) {
			++ cnt;
			v.push_back(ind);
			continue;
		}
		if(aux % 3 == 0) {
			cnt -= aux;
			++ cnt;
			v.push_back(ind);
			continue;
		}
	//	cout << "Impossible\n";
	//	return 0;
	}
	cout << "Possible\n";
	for(auto it : v)
		cout << it << ' ';
}
