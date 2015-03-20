#include <iostream>
#include <vector>

using namespace std;

vector<int> a, b; 
int n;

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	int ans = 0x3f3f3f3f;
	for(int i = 1 ; i < n - 1 ; ++ i) {
		b.clear();
		for(int j = 0 ; j < n ; ++ j) {
			if(i == j)
				continue;
			b.push_back(a[j]);
		}
		int actmax = -0x3f3f3f3f;
		for(int j = 0 ; j < b.size() - 1 ; ++ j)
			actmax = max(actmax, b[j + 1] - b[j]);
		ans = min(ans, actmax);
	}
	cout << ans << '\n';
	
}
