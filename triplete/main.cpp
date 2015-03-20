#include <iostream>

using namespace std;

inline void triplete(int n) {
    for(int i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            int y = i;
            int sum = n / i;
            for(int x = 0 ; x <= sum ; ++ x) {
                int z = sum - x;
                if(x < y && y < z)
                    cerr << x << ' ' << y << ' ' << z << '\n';
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
   /* for(int i = 1 ; i <= n ; ++ i)
        for(int j = i + 1 ; j <= n ; ++ j)
            for(int k = j + 1 ; k <= n ; ++ j)
                if(i * j + j * k == n)
                    cout << i << ' ' << j << ' ' << k<< "\n";
    */
    triplete(n);
}
