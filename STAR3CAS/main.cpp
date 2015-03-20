#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 105;


int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> t;
    while(t -- ) {
        cin >> n;
        for(int i = 0 ; i < n ; ++ i)
            cin >> x[i];
        bfs(0);

    }


}
