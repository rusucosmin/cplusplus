#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

ifstream fin("fibo.in");
ofstream fout("fibo.out");

const int maxn = 50;

unsigned long long fibo[maxn];
unsigned long long n, ans;
bool st[maxn];

inline bool updatesolution(int k) {
	int actans = ans;
	unsigned long long nr = 0;
	int aux = 0;
if(st[k] != 1) {
	for(int i = 1 ; i <= k ; ++ i) {
		nr = nr + st[i] * fibo[++ aux];		
		if(nr > n)
			return false;
	}
	for(int i = k ; i >= 1 ; -- i) {
		nr = nr + st[i] * fibo[++ aux];
		if(nr > n)
			return false;
	}
	if(nr <= n)
		++ ans;
	else
		return false;
}

	aux = 0;
	nr = 0;

	for(int i = 1 ; i <= k ; ++ i)
		nr = nr + st[i] * fibo[++ aux];

	unsigned long long bux = fibo[++ aux];

	for(int i = k ; i >= 1 ; -- i)
		nr = nr + st[i] * fibo[++ aux];

	if(nr <= n)
		++ ans;

	if(st[k] == 0) {
		nr = nr + bux;
		if(nr <= n) {
			++ ans;
		}
	}

	if(actans == ans)
		return false;
	return true;
}

inline void back(int k) { 
	if(!updatesolution(k - 1))
		return ;
	st[k] = 0;
	back(k + 1);
	if(st[k - 1] == 0) {
		st[k] = 1;
		back(k + 1);
	}
}

int main() {
	fin >> n;
	fibo[0] = fibo[1] = 1;
	for(int i = 2 ; i < maxn ; ++ i)
		fibo[i] = fibo[i - 1] + fibo[i - 2];

	if(n == 1) {
		cout << "1\n";
		return 0;
	}
	if(n == 2) {
		cout << "1\n";
		return 0;
	}
	if(n == 3) {
		cout << "1\n";
		return 0;
	}
	if(n == 4) {
		cout << "2\n";
		return 0;
	}
	++ ans;
	st[1] = 1;
	back(2);

	fout << ans << '\n';
}
