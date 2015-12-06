#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

const int maxn = 500005;
const int oo = 0x3f3f3f3f;

int a[maxn], n, k, _st, _end;

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	x = 0;
	char sgn = '+';
	while(!isdigit(buff[pos])) {
		sgn = buff[pos];
		if(++pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	if(sgn == '-')
		x = -x;
}

int main() {
	freopen("secventa.in", "r", stdin);
	ofstream fout("secventa.out");
	getint(n);
	getint(k);
	int _bestmax = -oo;
	deque <int> dq;
	for(int i = 1 ; i <= n ; ++ i) {
		getint(a[i]);
		while(!dq.empty() && a[dq.back()] >= a[i])
			dq.pop_back();
		dq.push_back(i);
		if(dq.front() <= i - k)
			dq.pop_front();
		if(i >= k) {
			if(_bestmax < a[dq.front()]) {
				_bestmax = a[dq.front()];
				_st = dq.front();
				_end = i;
			}
		}
	}
	fout << _end - k + 1 << ' ' << _end << ' ' << _bestmax << "\n";
}
