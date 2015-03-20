#include <set>
#include <math.h>
#include <fstream>

using namespace std;

ifstream fin("slidingwindow.in");
ofstream fout("slidingwindow.out");

const int maxn = 1000015;

int n, a[maxn], d;
multiset <int> s;
pair<multiset<int> :: iterator, multiset <int> :: iterator > p;

int main() {
	fin >> n >> d;
	int ans = ((1 << 30) - 1);
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> a[i];
		p = s.equal_range(a[i]);
		if((p.first == s.end() || (*p.first > a[i])) && p.first != s.begin())
			-- p.first;
		if(p.first != s.end())
			ans = min(ans, abs(a[i] - *p.first));
		if(p.second != s.end())
			ans = min(ans, abs(*p.second - a[i]));
		s.insert(a[i]);
		if(i - d >= 1)
			s.erase(s.find(a[i - d]));
	}
	fout << ans << '\n';
}
