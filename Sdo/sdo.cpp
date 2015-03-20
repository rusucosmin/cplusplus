#include <fstream>
#include <algorithm>

using namespace std;

const int maxn = 3000005;

int n, k, a[maxn];

int main() {
	ifstream cin("sdo.in");
	ofstream cout("sdo.out");
	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	nth_element(a + 1, a + k, a + n + 1);
	cout << a[k] << '\n';
}
