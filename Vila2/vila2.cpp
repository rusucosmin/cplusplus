#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <deque>

using namespace std;

const int maxn = 100005;
const int oo = 0x3f3f3f3f;

int n, k, a[maxn];

int main() {
	ifstream fin("vila2.in");
	ofstream fout("vila2.out");
	fin >> n >> k;
	++ k;
	deque <int> dqmin, dqmax;
	int ans = -oo;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> a[i];
		while(!dqmin.empty() && a[dqmin.back()] >= a[i])
			dqmin.pop_back();
		while(!dqmax.empty() && a[dqmax.back()] <= a[i])
			dqmax.pop_back();
		dqmin.push_back(i);
		dqmax.push_back(i);
		while(dqmin.front() <= i - k)
			dqmin.pop_front();
		while(dqmax.front() <= i - k)
			dqmax.pop_front();
		ans = max(ans, a[dqmax.front()] - a[dqmin.front()]);
	}
	fout << ans << '\n';
}
