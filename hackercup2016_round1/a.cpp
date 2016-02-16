#include <iostream>
#include <fstream>

using namespace std;
const int maxn = 100005;

int t, n, a[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif

	cin >> t;
	for(int test = 1 ; test <= t ; ++ test) {
		cin >> n;
		for(int i = 1 ; i <= n ; ++ i)
			cin >> a[i];
		int per = 1;
		int rasp = 0;
		for(int i = 2 ; i <= n ; ++ i) {
			if(a[i] - a[i - 1] <= 10  && a[i] - a[i - 1] > 0) 
				per = (per + 1) % 4;
			else if(a[i] - a[i - 1] <= 0) {
				if(per)
					rasp = rasp + 4 - per;
				per = 1;
			}
			else {
				while(a[i] - a[i - 1] > 10 && per) {
					a[i - 1] += 10;
					per = (per + 1) % 4;
					++ rasp;
				}
				per = (per + 1) % 4;
			}
		}
		if(per)
			rasp += 4 - per;
		cout << "Case #" << test << ": " << rasp  << '\n';
	}
}
