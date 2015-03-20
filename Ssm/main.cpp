#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("ssm.in");
ofstream fout("ssm.out");

const int oo = 0x3f3f3f3f;

int main() {
    int n, ind_beg, best_sum = -oo, best_st, best_end;
    int sum = -1;
    fin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        int x;
        fin >> x;
        if(sum < 0) {
            sum = x;
            ind_beg = i;
        }
        else
            sum += x;
        if(best_sum < sum) {
            best_sum = sum;
            best_st = ind_beg;
            best_end = i;
        }
    }
    fout << best_sum << ' ' << best_st << ' ' << best_end << '\n';
}
