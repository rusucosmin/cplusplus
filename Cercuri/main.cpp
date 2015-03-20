#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream cin("cercuri.in");
ofstream cout("cercuri.out");

inline double distance(const double x1, const double y1, const double x2, const double y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

inline double area(const double l1, const double l2, const double l3){
    double p = (l1 + l2 + l3)/2.0;
    return sqrt(p*(p-l1)*(p-l2)*(p-l3));
}

inline double solve(const double x1, const double y1, const double r1, const double x2, const double y2, const double r2){
    int d = distance(x1, y1, x2, y2);
    if(x1 == x2 && y1 == y2 && r1 == r2)
        return -1;
    if(r1 + r2 < d || abs(r1 - r2) > d)
        return -2;
    if( r1 + r2 == d || abs(r1 - r2) == d)
        return -3;
    double Ar = area(r1, r2, d);   // A = (b*h)/2 => h = 2*A / b;
    double H =

}

int main()
{
    int t;
    double x1, x2, y1 , y2, r1, r2;
    cin >> t;
    for(int i = 1 ; i <= t ; ++ i){
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        cout << solve(x1, y1, r1, x2, y2, r2);
    }
    cin.close();
    cout.close();
    return 0;
}
