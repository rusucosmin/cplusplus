#include <fstream>
#include <vector>

using namespace std;

ifstream fin("elmaj.in");
ofstream fout("elmaj.out");

int main() {
	int n, last = -1, cnt = 0;
	vector <int> v;
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		v.push_back(x);
		if(last == -1)
			last = x;
		if(x == last)
			++ cnt;
		else
			-- cnt;
		if(cnt <= 0)
			last = -1;
	}
	cnt = 0;
	for(vector <int> :: iterator it = v.begin() ; it != v.end() ; ++ it)
		if(*it == last)
			++ cnt;
	if(cnt > (n / 2))
		fout << last << ' ' << cnt << '\n';
	else
		fout << "-1\n";
}
