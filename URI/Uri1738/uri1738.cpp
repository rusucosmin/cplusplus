#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 205;

int t, n, m[maxn][maxn];

int main() {
	#ifndef ONLINE_JUDGE
		freopen("uri1738.in", "r", stdin);
		freopen("uri1738.out", "w", stdout);
	#endif
	while (true) {
		cin >> n;
		if(n == 0)
			break;
		memset(m, 0, sizeof(m));
		while(true) {
			int x, y;
			cin >> x >> y;
			if(!x && !y)
				break;
			string s;
			cin >> s;
			for(auto it : s)
				m[x][y] |= (1 << (it - 'a'));
		}
		for(int k = 1 ; k <= n ; ++ k)
			for(int i = 1 ; i <= n ; ++ i)
				for(int j = 1 ; j <= n ; ++ j)
					m[i][j] |= (m[i][k] & m[k][j]);
		while(true) {
			int x, y;
			cin >> x >> y;
			if(!x && !y)
				break;
			for(int i = 0 ; i < 26 ; ++ i)
				if(m[x][y] & (1 << i))
					cout <<(char)(i + 'a');
			if(!m[x][y])
				cout << "-";
			cout << "\n";
		}
		cout << '\n';
	}
	
	
	
}
