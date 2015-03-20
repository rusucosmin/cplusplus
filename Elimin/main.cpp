#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "elimin.in";
const char outfile[] = "elimin.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 900;
const int oo = 0x3f3f3f3f;

int M, N, R, C;
short a[MAXN][MAXN];
short st[MAXN];
int sum[MAXN], ans;
bitset <MAXN> used;

void backLine(const int k) {
    if(k == R + 1) {
        for(int i = 1 ; i <= N ; ++ i) {
            sum[i] = 0;
            for(int j = 1 ; j <= M ; ++ j)
                    sum[i] += (!used[j])*a[j][i];
        }
        nth_element(sum + 1, sum + C, sum + N + 1);
        int actsum = 0;
        for(int i = C + 1 ; i <= N ; ++ i)
            actsum += sum[i];
        ans = max(ans, actsum);
        return;
    }
    for(int i = st[k - 1] + 1 ; i <= M ; ++ i){
        st[k] = i;
        used[i] = 1;
        backLine(k + 1);
        used[i] = 0;
    }
}

void backRow(const int k) {
    if(k == C + 1) {
        bool ok = true;
        for(int i = 1 ; i <= M ; ++ i) {
            sum[i] = 0;
            for(int j = 1 ; j <= N ; ++ j)
                sum[i] += (!used[j] * a[i][j]);
        }
        nth_element(sum + 1, sum + R, sum + M + 1);
        int actsum = 0;
        for(int i = R + 1 ; i <= M ; ++ i)
            actsum += sum[i];
        ans = max(ans, actsum);
        return;
    }
    for(int i = st[k - 1] + 1 ; i <= N ; ++ i){
        st[k] = i;
        used[i] = 1;
        backRow(k + 1);
        used[i] = 0;
    }
}

int main() {
    int Ans = 0;
    fin >> M >> N >> R >> C;
    for(int i = 1 ; i <= M ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            fin >> a[i][j], Ans += a[i][j];
    if(M <= N)
       backLine(1);
        else
            backRow(1);
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
