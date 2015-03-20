#include <fstream>

using namespace std;

ifstream fin("aparitii.in");
ofstream fout("aparitii.out");

int N, K, dp[15][15], Ans;

int main() {
    fin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y = 0;
        fin >> x;
        while(x) {
            ++ y;
            int cif = x % 10;
            ++ dp[y][cif];
            x = x / 10;
        }
    }
    bool start = false;
    for(int i = 9 ; i >= 1 ; -- i) {
        bool ok = false;
        for(int j = 0 ; j <= 9 && !ok ; ++ j)
            if(dp[i][j] % K) {
                start = true;
                ok = true;
                fout << j;
            }
    }
    return 0;
}
