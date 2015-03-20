#include <iostream>
#include <fstream>
#define nmax 1005
using namespace std;
 
int n, m, k, sol = 0;
int swaps[nmax][nmax], sum[nmax][nmax];
bool a[nmax][nmax], curr[nmax][nmax];
char c;
 
int main() {
    ifstream f("electrica.in");
    ofstream g("electrica.out");
 
    f>>n>>m>>k;
    for(int i=1; i<=n; i++) 
        for(int j=1; j<=m; j++) {
            f>>c;
            a[i][j] = c=='1'? true : false;
        }
 
    for(int i=1; i<=n-k+1; i++) {
        for(int j=1; j<=m-k+1; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + swaps[i][j];
            if(sum[i][j] % 2 == 1) curr[i][j] = !curr[i][j];
 
            if(curr[i][j] != a[i][j]) {
                curr[i][j] = !curr[i][j];
                sol++;
                swaps[i][j]++;
                swaps[i][j+k]--;
                swaps[i+k][j]--;
                swaps[i+k][j+k]++;
                sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + swaps[i][j]; //se recalculeaza suma
            }
        }
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + swaps[i][j];
            curr[i][j] = sum[i][j] % 2 == 1? true : false;
            if(curr[i][j] != a[i][j]) sol = -1;
        }
    }
 
    g<<sol<<"\n";
    return 0;
}
