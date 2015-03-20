#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector <string> data = {
	"+------------------------+",
	"|#.#.#.#.#.#.#.#.#.#.#.|D|)",
	"|#.#.#.#.#.#.#.#.#.#.#.|.|",
	"|#.......................|",
	"|#.#.#.#.#.#.#.#.#.#.#.|.|)",
	"+------------------------+"
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("475a.in", "r", stdin);
	freopen("475a.out", "w", stdout);
	#endif
	int k;	
	cin >> k;
	int actind = 1;
	for(int i = 1 ; i <= min(k, 4) ; ++ i)
		data[i][actind] = 'O';
	k -= min(k, 4);
	if(k > 0) {
		int full = k / 3;
		int other = k % 3;
		for(int i = 1 ; i <= full ; ++ i) {
			actind += 2;
			for(int j = 1 ; j <= 4 ; ++ j) {
				if(j == 3)
					continue;
				data[j][actind] = 'O';
			}
		}
		actind += 2;
		for(int j = 1 ; other ; ++ j) {
			if(j == 3)
				continue;
			data[j][actind] = 'O';
			-- other;
		}
	}

	for(int i = 0 ; i < data.size() ; ++ i)	
		cout << data[i] << '\n';
}
