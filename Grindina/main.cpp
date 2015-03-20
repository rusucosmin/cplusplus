#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "grindina.in";
const char outfile[] = "grindina.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int MAXP = 8;
const int oo = 0x3f3f3f3f;
const double eps = 0.00001;

#define x first
#define y second

pair<int, int> Lot[MAXN][MAXP];
int P[MAXN], G;
int howMany[MAXN];
int N;
double Area[MAXN];

inline double myAbs(double x) {
    if(x < 0)
        return -x;
    return x;
}

inline int intAbs(int x) {
    if(x < 0)
        return -x;
    return x;
}

inline double AreaPoligon(pair<int, int> Poligon[MAXP], int M) {
    double area = 0;
    for(int i = 1 ; i <= M ; ++ i)
        area = area + (Poligon[i].x * Poligon[i + 1].y - Poligon[i + 1].x * Poligon[i].y);
    return 0.5 * myAbs(area);
}

inline int Memory() {
    return sizeof(Lot) + sizeof(P) + sizeof(Area);
}

inline double triangleArea(int x1, int y1, int x2, int y2, int x3, int y3) {
    int area = (x1 * y2 + x2 * y3 + x3 * y1 - x3 * y2 - x2 * y1 - x1 * y3);
    return 0.5 * (double)intAbs(area);
}

inline bool insidePolygon(pair<int, int> Point, pair<int, int> Poligon[MAXP], int M, double AreaToCheck) {
    double totalTrianglesArea = 0;
    for(int i = 1 ; i <= M ; ++ i) {
        double actArea = triangleArea(Point.x, Point.y, Poligon[i].x, Poligon[i].y, Poligon[i + 1].x, Poligon[i + 1].y);
        if(actArea < eps)
            return 0;
        totalTrianglesArea += actArea;
    }
    if(myAbs(AreaToCheck - totalTrianglesArea) < eps)
        return 1;
    return 0;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> P[i];
        for(int j = 1 ; j <= P[i] ; ++ j)
            fin >> Lot[i][j].x >> Lot[i][j].y;
        Lot[i][P[i] + 1] = Lot[i][1];
        Area[i] = AreaPoligon(Lot[i], P[i]);
    }
    fin >> G;
    for(int i = 1 ; i <= G ; ++ i) {
        pair<int, int> X;
        fin >> X.x >> X.y;
        for(int j = 1 ; j <= N ; ++ j) {
            howMany[j] += (insidePolygon(X, Lot[j], P[j], Area[j]));
        }
    }
    int Ans = 0;
    vector <int> v, v2;
    for(int i = 1 ; i <= N ; ++ i) {
        if(Ans < howMany[i]) {
            Ans = howMany[i];
            v.clear();
        }
        if(Ans == howMany[i])
            v.push_back(i);
        if(!howMany[i])
            v2.push_back(i);
    }
    fout << v.size() << '\n';
    for(unsigned int i = 0 ; i < v.size() ; ++ i)
        fout << v[i] << ' ';
    fout << '\n';
    if(!v2.size()) {
        fout << "0\n0\n";
        return 0;
    }
    fout << v2.size() << '\n';
    for(unsigned int i = 0 ; i < v2.size() ; ++ i)
        fout << v2[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
