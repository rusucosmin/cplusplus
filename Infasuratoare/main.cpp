#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

ifstream fin("infasuratoare.in");
ofstream fout("infasuratoare.out");

const int maxn = 120005;

int n, st[maxn], top;
pair<double, double> p[maxn];

inline long double crossproduct(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
    return 1LL * (b.first - a.first) * (c.second - a.second) - 1LL * (c.first - a.first) * (b.second - a.second);
}

struct classcomp {
    inline bool operator () (const pair<double, double> &a, const pair<double, double> &b) const {
        return crossproduct(p[1], a, b) > 0;
    }
};

int main() {
    fin >> n;
    int minpos = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fin >> p[i].first >> p[i].second;
        if(p[i] > p[minpos])
            minpos = i;
    }
    swap(p[1], p[minpos]);
    sort(p + 2, p + n + 1, classcomp());
    for(int i = 1 ; i <= n ; ++ i) {
        while(top >= 2 && crossproduct(p[i], p[st[top - 1]], p[st[top]]) < 0)
            -- top;
        st[++ top] = i;
    }
    fout << top << '\n';
    fout << fixed << setprecision(6);
    for(int i = 1 ; i <= top ; ++ i)
        fout << p[st[i]].first << ' ' << p[st[i]].second << '\n';
}
