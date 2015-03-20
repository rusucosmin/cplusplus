#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream fin("politic.in");
	ofstream fout("politic.out");
	int n;
	vector <int> v, s;
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		v.push_back(x);
	}
	s.push_back(0);
	for(int i = 0 ; i < n ; ++ i) {
		int sum = 1;
		while(i + 1 < n && v[i] + 1 == v[i + 1])
			++i, ++ sum;
		s.push_back(s.back() + sum);
	}
	int majority = n / 2 + 1;
	fout << s.size() - 1 << '\n';
	long long ret = 0;
	for(int i = 1 ; i < s.size() ; ++ i) {
		if(s[i] >= majority) {
			int st = 1;
			int dr = i;
			int ans = 1;
			while(st <= dr) {
				int mid = ((st + dr) >> 1);
				if(s[i] - s[mid - 1] >= majority) {
					st = mid + 1;
					ans = mid;
				}
				else
					dr = mid - 1;
			}
			ret = ret + ans;
		}
	}
	fout << ret << '\n';
}
