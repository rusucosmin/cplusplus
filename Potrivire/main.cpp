#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("potrivire.in");
ofstream fout("potrivire.out");

const int maxn = 10005;

int n, m, pi[maxn];
char a[maxn], b[maxn];

int main() {
    fin >> n >> m;
    fin.get();
    fin.getline(a + 1, maxn);
    fin.getline(b + 1, maxn);

    int _left = -1, _right = 0;

    int first = 1;
    while(first <= m && b[first] == '*')
        ++ first;
    if(first > m) {
        fout << "1 1\n";
        return 0;
    }
    for( ; ; ) {
        int second = first;
        int k = first - 1;
        pi[first] = first - 1;
        while(second + 1 <= m && b[second + 1] != '*') {
            ++ second;
            while(k != first - 1 && b[k + 1] != b[second])
                k = pi[k];
            if(b[k + 1] == b[second])
                ++ k;
            pi[second] = k;
        }
        k = first - 1;
        int sz = second - first + 1;
        bool found = 0;
        for(int i = _right + 1 ; i <= n ; ++ i) {
            while(k != first - 1 && b[k + 1] != a[i])
                k = pi[k];
            if(b[k + 1] == a[i])
                ++ k;
            if(k == second) {
                if(_left == -1)
                    _left = i - sz + 1;
                _right = i;
                found = 1;
                break;
            }
        }
        if(!found) {
            fout << "-1\n";
            return 0;
        }
        first = second + 1;
        while(first <= m && b[first] == '*')
            ++ first;
        if(first > m || second > m) {
            fout << _left << ' ' << _right << '\n';
            return 0;
        }
    }
}
