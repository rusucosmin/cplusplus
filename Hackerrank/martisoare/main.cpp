#include <iostream>
#include<fstream>
using namespace std;

const int maxn = 100005;

int v[maxn];

int main()
{
    ifstream fin("martisoare.in");
    ofstream fout("martisoare.out");
    int n;
    fin>>n;
    for(int i = 1 ; i <= n ; ++ i)
        fin>>v[i];
    if(v[1] + 1 == v[2]) {
            bool afisat = false;
        /// inseamna ca v1 e bun, v2 e bun
        for(int i = 3 ; i <= n ; ++ i)
            if(v[i] != v[i - 1] + 1) {
                /// am aflat ca v[i] e un element care nu este bun
                int numar_bun = v[i - 1] + 1;
                //// trebuie sa determinam care sunt cifrele greiste
                while(v[i] > 0 && numar_bun > 0) {
                    if(v[i] % 10 != numar_bun % 10) {
                        afisat = true;
                        if(v[i] % 10 > numar_bun % 10)
                            fout << numar_bun % 10 << ' ' << v[i] % 10 << '\n';
                        else
                            fout << v[i] % 10 << ' ' << numar_bun % 10 << '\n';
                        break;
                    }
                    else {
                        v[i] = v[i] / 10;
                        numar_bun = numar_bun / 10;
                    }
                }
                if(afisat == true)
                    break;
            }
        if(afisat == false)
            fout << "0 0\n";
        fout << v[1] + n - 1 << '\n';
    }
    else if(v[2] + 1 == v[3]) /// v1 e cu buba
    {
        int nrbun = v[2] - 1;
        while(v[1] > 0 && nrbun > 0) {
            if(v[1]%10!=nrbun%10) {
                fout<<min(v[1] % 10, nrbun%10) << ' ' << max(v[1] % 10, nrbun % 10) << '\n';
                break;
            }
            else {
                v[1] /= 10;
                nrbun /= 10;
            }
        }
        fout << v[2] + n - 2 << '\n';
    }
    else if(v[1] + 2 == v[3]) {
           int nrbun = v[1] + 1;
            while(v[2] > 0 && nrbun > 0) {
                if(v[2]%10!=nrbun%10) {
                    fout<<min(v[2] % 10, nrbun%10) << ' ' << max(v[2] % 10, nrbun % 10) << '\n';
                    break;
                }
                else {
                    v[2] /= 10;
                    nrbun /= 10;
                }
            }
            fout << v[1] + n - 1 << '\n';
    }
    else {
        if(v[2] != v[4] - 2) {
            int nrbun = v[4] - 2;
            while(v[2] > 0 && nrbun > 0) {
                if(v[2]%10!=nrbun%10) {
                    fout<<min(v[2] % 10, nrbun%10) << ' ' << max(v[2] % 10, nrbun % 10) << '\n';
                    break;
                }
                else {
                    v[2] /= 10;
                    nrbun /= 10;
                }
            }
            fout << v[4] + n - 4 << '\n';
        }
        else {
            int nrbun = v[4] - 3;
            while(v[1] > 0 && nrbun > 0) {
                if(v[1]%10!=nrbun%10) {
                    fout<<min(v[1] % 10, nrbun%10) << ' ' << max(v[1] % 10, nrbun % 10) << '\n';
                    break;
                }
                else {
                    v[1] /= 10;
                    nrbun /= 10;
                }
            }
            fout << v[4] + n - 4 << '\n';
        }
    }

    return 0;
}
