#include <fstream>
#include <vector>

using namespace std;

ifstream fin("elmaj.in");
ofstream fout("elmaj.out");

const int maxn = 1000005;

int n, a[maxn];

int main() {
	fin >> n;
	int last, cnt = -1;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> a[i];
		if(cnt == -1) {
			last = a[i];
			cnt = 1;
		}
		else if(last == a[i])
			++ cnt;
		else
			-- cnt;
	}
	cnt = 0;
	for(int i = 1 ; i <= n ; ++ i)
		cnt += (a[i] == last);
	if(cnt >= n / 2 + 1)
		fout << last << ' ' << cnt << '\n';
	else
		fout << "-1\n";
}
