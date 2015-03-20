#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <cassert>
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

const char infile[] = "dreapta.in";
const char outfile[] = "dreapta.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;
const long double eps = 0.0001;

typedef long double lol;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

typedef pair<double, double> Point;

#define x first
#define y second

Point P[MAXN];
Point M[MAXN];
Point maxP = make_pair(-oo, -oo);
Point minP = make_pair(oo, oo);
int N, Q;

inline pair<double, pair<double, double> > Equation(double x1, double y1, double x2, double y2) {
    double a = (y1 - y2);
    double b = (x2 - x1);
    double c = (x1 * y2 - x2 * y1);
    return make_pair(a, make_pair(b, c));
}

#define a first
#define b second.first
#define c second.second

inline Point Intersection(pair<double, pair<double, double> > d1, pair<double, pair<double, double> > d2) {
    double det = d1.a * d2.b - d2.a * d1.b;
    if(det == 0){
        return make_pair(oo, oo);
        //assert(false);
    }else{
        double x = (d2.b * d1.c - d1.b * d2.c) / det;
        double y = (d1.a * d2.c - d2.a * d1.c) / det;
        return make_pair(-x, -y);
    }
}

inline bool Check(Point A, Point B, Point C) {
    return min(B.x,C.x) <= A.x && A.x <= max(B.x, C.x) && min(B.y,C.y) <= A.y && A.y <= max(B.y, C.y);
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> P[i].x >> P[i].y;
    }
    P[N + 1] = P[1];
    fin >> Q;
    for(int i = 1 ; i <= Q; ++ i) {
        fin >> M[i].x >> M[i].y;
        maxP = max(maxP, M[i]);
        minP = min(minP, M[i]);
    }
    pair<double, pair<double, double> > eq = Equation(M[1].x, M[1].y, M[2].x, M[2].y);
    vector <Point> X;
    for(int i = 1 ; i <= N ; ++ i) {
        Point act = Intersection(eq, Equation(P[i].x, P[i].y, P[i + 1].x, P[i + 1].y));
        //fout << i << ' ' << act.x << ' ' << act.y << '\n';
        if(Check(act, P[i], P[i + 1])) {
            X.push_back(act);
        }
    }
    //fout << X.size() << '\n';
    if(!X.size()) {
            for(int i = 1 ; i <= Q ; ++ i)
                fout << "0\n";
            return 0;
        }
    sort(X.begin(), X.end());
    for(int i = 1 ; i <= Q ; ++ i) {
        Point act = M[i];
        int pos = lower_bound(X.begin(), X.end(), act) - X.begin();
        fout << (pos & 1) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
