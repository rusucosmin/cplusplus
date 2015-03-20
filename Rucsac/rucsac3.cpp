#include <fstream>
using namespace std;
 
ifstream fin("rucsac2.in");
ofstream fout("rucsac.out");
 
int n, g, i, j, nr, gr, p, sol, sum[10001];
 
int main() {
    fin >> nr >> gr;
    for (; i < nr; ++i) {
        fin >> g >> p;
        for (j = gr - g; j >= 0; --j)
            if (sum[j + g] < sum[j] + p) {
                sum[j + g] = sum[j] + p;
                if (sum[j + g] > sol)
                    sol = sum[j + g];
            }
    }
    fout << sol;
    fout.close();
    return 0;
}
