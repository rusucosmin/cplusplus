#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

const int maxn = 5000005;

int n, k, a[maxn];

int main() {
	ifstream fin("deque.in");
	ofstream fout("deque.out");
	fin >> n >> k;
	deque <int> dq;
	long long sum = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> a[i];
		while(!dq.empty() && a[dq.back()] >= a[i])
			dq.pop_back();
		dq.push_back(i);
		if(dq.front() <= i - k)
			dq.pop_front();
		if(i >= k)
			sum += a[dq.front()];
	}
	fout << sum << '\n';
}
