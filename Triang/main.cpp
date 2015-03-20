#include <fstream>
#include <vector>
#include <bitset>
#include <math.h>
#include <algorithm>

using namespace std;

const char infile[] = "triang.in";
const char outfile[] = "triang.out";

ifstream cin(infile);
ofstream cout(outfile);

const int oo = 0x3f3f3f3f;
const double SIGMA = 1e-5;
const double sqrt_3 = sqrt(3.0);

typedef pair<double, double> point;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

vector< point > a;
int N, Ans = 0;

struct classComp {
    inline bool operator () (const point &a, const point &b) const {
        if( fabs(a.first - b.first) < SIGMA ) {
            if(fabs(a.second - b.second) < SIGMA)   return 0;
            return a.second < b.second;
        }
        return a.first < b.first;
    }
};

inline pair<point, point> getPoint(const point &a, const point &b) {
    point ret1, ret2;

    ret1.first = 0.5 * (a.first + b.first) - 0.5 * sqrt_3 * (b.second - a.second);
    ret1.second = 0.5 * (a.second + b.second) + 0.5 * sqrt_3 * (b.first - a.first);
    ret2.first = 0.5 * (a.first + b.first) + 0.5 * sqrt_3 * (b.second - a.second);
    ret2.second = 0.5 * (a.second + b.second) - 0.5 * sqrt_3 * (b.first - a.first);

    return make_pair(ret1, ret2);
}

inline int searchPoints(pair<point, point> toSearch) {
    return binary_search(a.begin(), a.end(), toSearch.first, classComp()) + binary_search(a.begin(), a.end(), toSearch.second, classComp());
}

int main() {
    cin >> N;
    for(int i = 0 ; i < N ; ++ i) {
        double x, y;
        cin >> x >> y;
        a.push_back(make_pair(x, y));
    }
    sort(a.begin(), a.end(), classComp());
    for(int i = 0 ; i < N ; ++ i)
        for(int j = i + 1 ; j < N ; ++ j)
            Ans += searchPoints(getPoint(a[i], a[j]));
    cout << Ans / 3 << '\n';
    cin.close();
    cout.close();
    return 0;
}
