#include <iostream>

using namespace std;

const int maxn = 500005;

int n, p[maxn];

inline int getinversions() {
	int cnt = 0;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = i + 1 ; j <= n ; ++ j)
			cnt += (p[i] > p[j]);
	return cnt;
}

int main() {
	#ifdef HOME
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif

	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> p[i];
	int ans = getinversions();
	pair<int, int> per = make_pair(-1, -1);
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = i + 1 ; j <= n ; ++ j) {
			swap(p[i], p[j]);
			int aux = getinversions();
			if(ans > aux) {
				ans = aux;
				per = make_pair(i, j);
			}
			swap(p[i], p[j]);
		}
	}
	if(per == make_pair(-1, -1))
		cout << "Cool Array\n";
	else
		cout << per.first << ' ' << per.second << '\n';
}
