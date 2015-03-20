#include <fstream>
#include <algorithm>
#include <cassert>

using namespace std;

int T, N = 49, v[55];

vector <int> check(int gcd) {
	vector <int> ret;
	for(int i = 1 ; i <= N ; ++ i) 
		if(v[i] % gcd == 0) {
			ret.push_back(v[i]);
			if(ret.size() >= 6)
				return ret;
		}
	return ret;
}

int main() {
	ifstream fin("sase49.in");
	ofstream fout("sase49.out");

	fin >> T;
	while (T --) {
		for(int i = 1 ; i <= N ; ++ i)
			fin >> v[i];
		sort(v + 1, v + N + 1);
		int st = 1, dr = 17;
		vector <int> ans, act;
		int ret = -1;
		for(ret = 16 ; ret >= 1 ; -- ret) {
			ans = check(ret);
			if(ans.size() == 6)
				break;
		}
		fout << ret << '\n';
		for(auto it : ans)
			fout << it << ' ';
		fout << '\n';
	}
}
