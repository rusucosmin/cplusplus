#include <fstream>
#include <vector>
#include <bitset>
#include <math.h>
#include <queue>
#include <iomanip>

using namespace std;

const char infile[] = "cablaj.in";
const char outfile[] = "cablaj.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 3005;
const int oo = 0x3f3f3f3f;

int N;
double totalCost, cmin[MAXN];
vector< pair<int, int> > p;

inline double eucDistance(pair<int, int> a, pair<int, int> b) {
    return sqrt(((double)b.first - (double)a.first)*((double)b.first - (double)a.first) + ((double)b.second - (double)a.second)*((double)b.second - (double)a.second));
}

inline void PRIM() {
    int remain = N - 1;
    int Node = 0;
    cmin[Node] = - 1;
    for(int i = 1 ; i < N ; ++ i)
        cmin[i] = eucDistance(p[Node], p[i]);
    for( ; remain ; ) {
        double minCost = 0x3f3f3f3f;
        int actNode;
        for(int i = 1 ; i < N ; ++ i)
            if(cmin[i] > 0 && ( cmin[i] < minCost ) ) {
                minCost = cmin[i];
                actNode = i;
            }
        cmin[actNode] = -1;
        if(minCost != (1 << 29))
            totalCost += minCost;
        for(int i = 1 ; i < N ; ++ i) {
            double t = 0;
            if(cmin[i] > (t = eucDistance(p[actNode], p[i])))
                cmin[i] = t;
        }
        -- remain;
    }
}

int main() {
    fin >> N;
    for(int i = 0 ; i < N ; ++ i) {
        int x, y;
        fin >> x >> y;
        p.push_back(make_pair(x, y));
    }
    PRIM();
    fout << fixed << setprecision(5) << totalCost << '\n';
    fin.close();
    fout.close();
    return 0;
}
