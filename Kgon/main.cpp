    #include <fstream>
    #include <vector>
    #include <cmath>
    #include <algorithm>
    using namespace std;

    #define eps 0.00001

    int n, k; double r;
    double arce[100001];
    vector <bool> done;

    inline int eq(double a, double b) {
        if(fabs(a - b) < eps) return 0;
        else return (a < b ? -1 : 1);
    }

    int bin_src(double val) {
        int step, poz;
        for(step = 1; step <= n; step <<= 1);
        for(poz = -1; step != 0; step >>= 1)
            if(poz + step < n && eq(arce[poz + step], val) < 0)
                poz += step;
        if(poz == n - 1 || eq(arce[poz + 1], val) != 0)
            return -1;
        return poz + 1;
    }

    int main(void) {
        ifstream fin("kgon.in");
        fin >> n >> k >> r;
        for(int i = 0; i < n; ++i)
            fin >> arce[i];
        fin.close();
        sort(arce, arce + n);

        done.resize(n); int rasp = 0;
        double circ = r * M_PI *  2 , arc = circ / k;
        for(int i = 0; i < n && eq(circ, arc * (k - 1) + arce[i]) >= 0; ++i) {
            bool ok = true;
            for(int j = 0; j < k && ok; ++j) {
                int poz = (j == 0 ? i : bin_src(arce[i] + j * arc));
                if(poz == -1 || done[poz]) ok = false;
                else done[poz] = true;
            }
            rasp += ok;
        }

        ofstream fout("kgon.out");
        fout << rasp;
        fout.close();
    }
