#include <fstream>
#include <bitset>

using namespace std;

const char infile[] = "noname.in";
const char outfile[] = "noname.out";

ofstream fout(outfile);

const short MAXN = 1002;;

short N, whereLine[MAXN], whereCol[MAXN];
bitset<MAXN> used[MAXN];
bitset<MAXN> vis[MAXN];

ifstream fin(infile);

int main() {
    fin >> N;
    int x;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> x;
        whereLine[x] = i;
    }
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> x;
        whereCol[x] = i;
    }
    for(int i = N ; i ; -- i) {
        for(int k = 1 ; k <= N ; ++ k) {
            if(!vis[whereLine[i]][k])
                used[whereLine[i]][k] = 1, vis[whereLine[i]][k] = 1;
            if(!vis[k][whereCol[i]])
                used[k][whereCol[i]] = 1, vis[k][whereCol[i]] = 1;
        }
        for(int k = 1 ; k <= N ; ++ k) {
            if(!vis[whereLine[N - i + 1]][k])
                used[whereLine[N - i + 1]][k] = 0, vis[whereLine[N - i + 1]][k] = 1;
            if(!vis[k][whereCol[N - i + 1]])
                used[k][whereCol[N - i + 1]] = 0, vis[k][whereCol[N - i + 1]] = 1;
        }
    }
    fout << 1 << '\n';
    for(int i = 1 ; i <= N ; ++ i, fout << '\n') {
        string s = "";
        for(int j = 1 ; j <= N ; ++ j)
            if(used[i][j])
                s = s + "1 ";
            else
                s = s + "0 ";
        fout << s;
    }
    fout.close();
    return 0;
}
