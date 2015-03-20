#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100005;

char s[maxn], *p;

inline int getint() {
	int nr = 0;
	while(*p && '0' <= *p && *p <= '9') {
		nr = nr * 10 + *p - '0';	
		++ p;
	}
	return nr;
}

inline vector <int> termen() {
	vector <int> ret;
	++ p;
	if(*p == '}')
		return ret;
	while(true) {
		int aux = getint();
		ret.push_back(aux);
		if(*p == '}')
			return ret;
		++ p;
	}
}


inline vector <int> eval() {
	vector <int> ret;
	if(*p == '(') {
		++ p;
		ret = eval();
		++ p;
	}
	else
		ret = termen();
	
	while(*p != ')' && *p) {
		if(*p == '-' || *p == '+' || *p == '*' || *p == '%') {
			char op = *p;
			++ p;
				
			vector <int> nxt;

			if(*p == '(') {
				++ p;
				nxt = eval();
			}
			else
				nxt = termen();

			vector <int> aux (ret.size() + nxt.size());
			vector <int> :: iterator it;

			if(op == '+')
				it = set_union(ret.begin(), ret.end(), nxt.begin(), nxt.end(), aux.begin());
			if(op == '-')
				it = set_difference(ret.begin(), ret.end(), nxt.begin(), nxt.end(), aux.begin());
			if(op == '*')
				it = set_intersection(ret.begin(), ret.end(), nxt.begin(), nxt.end(), aux.begin());
			if(op == '%')
				it = set_symmetric_difference(ret.begin(), ret.end(), nxt.begin(), nxt.end(), aux.begin());
			aux.resize(it - aux.begin());
			ret = aux;
		}
		++ p;
	}
	return ret;
}

int main() {
	ifstream fin("expr.in");
	ofstream fout("expr.out");
	
	fin >> s;
	p = s;

	vector <int> ans = eval();
	fout << '{';
	if(ans.size() > 0) {
		fout << ans[0];
		for(int i = 1 ; i < ans.size() ; ++ i)
			fout << ',' << ans[i];
	}
	fout << "}\n";

}
