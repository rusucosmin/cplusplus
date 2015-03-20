#include <fstream>

using namespace std;

ifstream fin("subsiruri2.in");
ofstream fout("subsiruri2.out");

const int maxn = 21;

int n, a[51], b[51], _hasha[1 << maxn], _hashb[1 << maxn];
char s[50];

inline long long getAns() {
	int m = (n >> 1);
	for(int conf = 0 ; conf < (1 << m) ; ++ conf) {
		a[0] = b[0] = 0;
		for(int i = 0, j = m - 1 ; j >= 0 ; ++ i, -- j)
			if(conf & (1 << j))
				a[ ++ a[0] ] = s[i];
			else
				b[ ++ b[0] ] = s[i];
		
		int k = min(a[0], b[0]);
		bool ok = true;
		for(int i = 1 ; i <= k && ok ; ++ i)
			if(a[i] != b[i])
				ok = false;
		if(!ok)
			continue;
		if(a[0] == b[0])
			++ _hasha[0];
		if(a[0] > b[0]) {
			int t = 1;
			for(int i = b[0] + 1 ; i <= a[0] ; ++ i)
				t = (t << 1) + a[i];
			++ _hasha[t];
		}
		if(b[0] > a[0]) {
			int t = 1;
			for(int i = a[0] + 1 ; i <= b[0] ; ++ i)
				t = (t << 1) + b[i];
			++ _hashb[t];
		}
	}
	long long ans = 0;
	for(int conf = 0 ; conf < (1 << m) ; ++ conf) {
		a[0] = b[0] = 0;
		for(int i = n - 1, j = 0 ; j < m ; ++ j,-- i)
			if(conf & (1 << j))
				a[ ++ a[0] ] = s[i];
			else
				b[ ++ b[0] ] = s[i];
		
		int k = min(a[0], b[0]);
		bool ok = true;
		for(int i = 1 ; i <= k && ok ; ++ i)
			if(a[i] != b[i])
				ok = false;
		if(!ok)
			continue;
		if(a[0] == b[0])
			ans = ans + _hasha[0];
		if(a[0] > b[0]) {
			int t = 1;
			for(int i = a[0] ; i > b[0] ; -- i)
				t = (t << 1) + a[i];
			ans += _hashb[t];
		}
		if(b[0] > a[0]) {
			int t = 1;
			for(int i = b[0] ; i > a[0] ; -- i)
				t = (t << 1) + b[i];
			ans += _hasha[t];
		}
	}
	return ans;
}

int main() {
	fin >> n >> s;
	for(int i = 0 ; i < n ; ++ i)
		s[i] -= 'a';
	fout << getAns() << '\n';	
}
