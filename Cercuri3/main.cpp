#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>
#include <cmath>
#define _USE_MATH_DEFINES

using namespace std;

ifstream cin("cercuri3.in");
ofstream cout("cercuri3.out");

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

double T, x1, y11, r1, x2, y2, r2, A;

inline double area(double l1, double l2, double l3){
    double  p = (l1+l2+l3)/2.0;
    return sqrt(p*(p-l1)*(p-l2)*(p-l3));
}

inline double Solve(){
    cin >> x1 >> y11 >> r1 >> x2 >> y2 >> r2 >> A;
    double d = (x1 - x2)*(x1 - x2) + (y11 - y2)*(y11 - y2);
    if((r1-r2)*(r1-r2) >= d){
        double r = min(r1, r2);
        cout << "min";
        return (double)M_PI * r * r;
    }
    if((r1+r2)*(r1+r2) <= d)
        return 0;
    d = sqrt(d);
    double Area = area(r1, r2, d);
    double H = 2.0*Area/d;
    double sin1 = H/r1;
    double sin2 = H/r2;
    double alfa = asin(sin1) * 180.0 / M_PI;
    double beta = asin(sin2) * 180.0 / M_PI;
    alfa = alfa*2.0;
    beta = beta*2.0;
    cout << alfa << " " << beta << " ";
    double firstpizza = M_PI * r1 * r1 * alfa / 360.0;
    double secondpizza = M_PI * r2 * r2 * beta / 360.0;
    Area *= 2;
    return (firstpizza + secondpizza - Area);
}

int main(){
    cin >> T;
    while(T--){
        double ArREAAA = Solve();
        cout << ArREAAA << " ";
        if(ArREAAA > A ) cout << "DA\n";
        else cout << "NU\n";
    }
    cin.close();
    cout.close();
    return 0;
}
