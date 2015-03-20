#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream fin("divmul.in");
    ofstream fout("divmul.out");
    int t;
    fin >> t;
    while(t -- ) {
        int x, y;
        fin >> x >> y;
        y /= x;
        int ans = 0;
        for(int d = 2 ; d * d <= y ; ++ d)
            if(y % d == 0) {
                ++ ans;
                while(y % d == 0)
                    y /= d;
            }
        if(y > 1)
            ++ ans;
        fout << (1LL << ans) << '\n';
    }
}
