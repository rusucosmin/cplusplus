#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 2000005;

string a, b, whole;
int z[maxn << 1], n, m;

inline int extend2(int i, int j) {
    int sum;
    for(sum = 0 ; j + sum < a.size() ; ++ sum)
        if(a[i + sum] != a[j + sum])
            return sum;
    return sum;
}

inline int extend(int i, int j) {
    int cnt = 0;
    for(int x = i, y = j ; y < a.size() ; ++ y, ++ x) {
        if(a[x] != a[y])
            return cnt;
        ++ cnt;
    }
    return cnt;
}


inline void buildz() {
    int l = -1, r = -1;
    for(int i = 1 ; i < a.size() ; ++ i) {
        if(i > r) {
            z[i] = extend(0, i);
            if(z[i] != 0) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        else {
            int lasti = i - l;
            if(z[lasti] < r - i + 1)
                z[i] = z[lasti];
            else {
                z[i] = r - i + 1 + extend(r - i + 1, r + 1);
                if(r < i + z[i] - 1) {
                    l = i;
                    r = i + z[i] - 1;
                }
            }
        }
    }
}

int main() {
    ifstream fin("strmatch.in");
    ofstream fout("strmatch.out");
    getline(fin, a);
    getline(fin, b);
    int aux = a.size();
    a += b;
    buildz();
    int ans = 0;
    vector <int> matches;
    for(int i = aux ; i < a.size() ; ++ i)
        if(z[i] >= aux) {
            ++ ans;
            if(ans <= 1000)
                matches.push_back(i - aux);
        }
    fout << ans << '\n';
    for(auto it : matches)
        fout << it << ' ';
}
