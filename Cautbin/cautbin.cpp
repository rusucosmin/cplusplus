#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;

int n, m, a[maxn];

inline int type0(int x) {
	int st = 1, dr = n, ans = -1;	
	while(st <= dr) {
		int mid = ((st + dr) >> 1);
		if(a[mid] <= x) {
			st = mid + 1;
			if(a[mid] == x)
				ans = mid;
		}
		else
			dr = mid - 1;
	}
	return ans;
}

inline int type1(int x) {
	int st = 1, dr = n, ans = -1;
	while(st <= dr) {
		int mid = ((st + dr) >> 1);
		if(a[mid] <= x) {
			ans = mid;
			st = mid + 1;
		}
		else
			dr = mid - 1;
	}
	return ans;
}

inline int type2(int x) {
	int st = 1, dr = n, ans = -1;
	while(st <= dr) {
		int mid = ((st + dr) >> 1);
		if(a[mid] >= x) {
			dr = mid - 1;
			ans = mid;
		}
		else
			st = mid + 1;
	}
	return ans;
}

int main() {
	ifstream fin("cautbin.in");
	ofstream fout("cautbin.out");
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> a[i];
	fin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int type, x;
		fin >> type >> x;
		if(type == 0)	
			fout << type0(x) << '\n';
		if(type == 1)
			fout << type1(x) << '\n';
		if(type == 2)
			fout << type2(x) << '\n';
	}

}
