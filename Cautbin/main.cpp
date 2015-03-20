#include <fstream>
#include <vector>

using namespace std;

ifstream fin("cautbin.in");
ofstream fout("cautbin.out");

const int maxn = 100005;

int n, m, a[maxn];

int main() {
    fin >> n;
    for(int i = 1 ; i <= n ; ++ i)
        fin >> a[i];
    fin >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int op, x;
        fin >> op >> x;
        /*0 x - cea mai mare pozitie pe care se afla un element cu valoarea x sau -1 daca aceasta valoare nu se gaseste in sir
1 x - cea mai mare pozitie pe care se afla un element cu valoarea mai mica sau egala cu x in sir. Se garanteaza ca cel mai mic numar al sirului este mai mic sau egal decat x
2 x - cea mai mica pozitie pe care se afla un element cu valoarea mai mare sau egala cu x in sir. Se garanteaza ca cel mai mare numar din sir este mai mare sau egal decat x*/
        if(op == 0) {
            int st = 1, dr = n, ret = -1;
            while(st <= dr) {
                int mid = ((st + dr) >> 1);
                if(a[mid] == x)
                    ret = mid;
                if(a[mid] <= x)
                    st = mid + 1;
                else
                    dr = mid - 1;
            }
            fout << ret << '\n';
        }
        else if(op == 1) {
            int st = 1, dr = n, ret = -1;
            while(st <= dr) {
                int mid = ((st + dr) >> 1);
                if(a[mid] <= x) {
                    ret = mid;
                    st = mid + 1;
                }
                else
                    dr = mid - 1;
            }
            fout << ret << '\n';
        }
        else {
            int st = 1, dr = n, ret = -1;
            while(st <= dr) {
                int mid = ((st + dr) >> 1);
                if(a[mid] >= x) {
                    ret = mid;
                    dr = mid - 1;
                }
                else
                    st = mid + 1;
            }
            fout << ret << '\n';
        }
    }
}
