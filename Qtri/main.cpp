#include<iostream>
#include<fstream>
#include<math.h>
#include<iomanip>
using namespace std;

double area(int x1, int y1, int x2, int y2, int x3, int y3) {
    int p=x1*y2+x2*y3+x3*y1-x3*y2-x1*y3-x2*y1;
    return 0.5*fabs(p);
}

int main() {
    int n, x1, y1, x2, y2, x3, y3, x4, y4;
    ifstream fin("qtri.in");
    ofstream fout("qtri.out");
    fin>>n;
    for(int i=1; i<=n; ++i) {
        fin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
        double a = area(x1, y1, x2, y2, x3, y3);
        double a1 = area(x1, y1, x2, y2, x4, y4);
        double a2 = area(x1, y1, x3, y3, x4, y4);
        double a3 = area(x2, y2, x3, y3, x4, y4);
        if(a==(a1+a2+a3))
            fout<<"DA\n";
        else
            fout<<"NU\n";
    }
    return 0;
}
