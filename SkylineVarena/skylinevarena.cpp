#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

const int maxn = 40005;

int n, h[maxn], w[maxn], _right[maxn], _left[maxn];
long long s[maxn];
stack<int> st;

int main() {
	ifstream fin("skyline.in");
	ofstream fout("skyline.out");

	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> h[i] >> w[i];
		s[i] = s[i - 1] + w[i];
	}
	h[0] = h[n + 1] = -1;	
	st.push(0);
	for(int i = 1 ; i <= n ; ++ i) {
		while(h[st.top()] >= h[i])
			st.pop();
		_left[i] = st.top();
		st.push(i);
	}
	st.push(n + 1);
	for(int i = n ; i ; -- i) {
		while(h[st.top()] >= h[i])
			st.pop();
		_right[i] = st.top() - 1;
		st.push(i);
	}
	long long ans = 0;
	for(int i = 1 ; i <= n ; ++ i)
		ans = max(ans, 1LL * h[i] * (s[_right[i]] - s[_left[i]]));
	fout << ans << '\n';
}
