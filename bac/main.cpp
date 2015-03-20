#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("bac.txt");
ofstream fout("bac.out");

int n, cnt[10], x;

int main() {
    fin >> n;
    while(fin >> x) {
        int p = 0;
        while(x != 1) {
            ++ p;
            x /= 10;
        }
        ++ cnt[p];
    }
    int sum = 0, nr = 1;
    bool okay = false;
    for(int i = 0 ; i < 10 ; ++ i) {
        sum = sum + cnt[i];
        if(sum >= n) {
            cout << nr << '\n';
            okay = true;
            break;
        }
        nr = nr * 10;
    }
    if(!okay)
        cout << "Nu exista";
}
