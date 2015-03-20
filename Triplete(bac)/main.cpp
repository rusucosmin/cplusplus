#include <iostream>

using namespace std;

inline void triplete(int n) {
    for(int i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            cerr << i << ' ' << n / i << '\n';
        }
    }
}

int main() {
    int n;
    cin >> n;
    //triplete(n);
}
