#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 4005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int main() {
    int A, B;
    cin >> A >> B;
    long long Ans = 0;
    Ans += A;
    while(A / B) {
        Ans += (A / B);
        A = A / B;
    }
    cout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
