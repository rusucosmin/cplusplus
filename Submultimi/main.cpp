#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    ifstream fin("submultimi.in");
    ofstream fout("submultimi.out");
    int n;
    fin >> n;
    for(int i = 1 ; i < (1 << n ) ; ++ i) {
        for(int j = 0 ; j < n ; ++ j)
            if(i & (1 << j))
                fout << j + 1 << ' ';
        fout << '\n';
    }

}
