








#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Stack {
private:
	int v[100];  /// vectorul
	int _top;     ///
public:
	Stack() {
		_top = 0;
		memset(v, 0, sizeof(v));
	}
	Stack(int N) {
		v.resize(N);	
	}
	void push(int value) {
		v[_top ++] = value;
	}
	void pop() {
		if(_top == 0)
			return ;
		-- _top;
	}
	int top() {
		if(_top == 0)
			return -1;
		return v[_top - 1];
	}
	bool empty() {
		return _top == 0;
	}
	int size() {
		return _top;
	}
};


int main() {
	Stack mStack;
	for(int i = 1 ; i <= 10 ; ++ i)
		mStack.push(i);
	while(!mStack.empty()) {
		cout << mStack.top() << '\n';
		mStack.pop();
	}
}
