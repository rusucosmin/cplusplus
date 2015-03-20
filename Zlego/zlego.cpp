#include <fstream>
#include <vector>

using namespace std;

const int maxn = 250005;

int height[maxn];
int t, n, pi[maxn];
long long sum[maxn];

int main() {
    ifstream fin("zlego.in");
    ofstream fout("zlego.out");
    fin >> t;
    while(t -- ) {
        fin >> n;
        for(int i = 1 ; i <= n ; ++ i)
            fin >> height[i];
        for(int i = 1 ; i <= n ; ++ i)
            fin >> sum[i];
        int k = 0;
        pi[1] = 0;
        for(int i = 2 ; i <= n ; ++ i) {
            while(k > 0 && height[k + 1] != height[i])
                k = pi[k];
            if(height[k + 1] == height[i])
                ++ k;
            pi[i] = k;
        }
        for(int i = n ; i >= 1 ; -- i)
            sum[pi[i]] += sum[i];
        for(int i = 1 ; i <= n ; ++ i)
            fout << sum[i] << '\n';
    }
}
