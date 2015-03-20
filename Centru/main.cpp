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

#define x first
#define y second

using namespace std;

const char infile[] = "centru.in";
const char outfile[] = "centru.out";

ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

const int dx[] = {-1,  0, 1, 0 };
const int dy[] = { 0, -1, 0, 1 };

typedef pair<int, int> per;
typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

class Scanner {
  public:
    Scanner(string file, int buffer_size = 32768):
            buffer_size_(buffer_size) {
        file_ = fopen(file.c_str(), "r");
        buffer_ = new char[buffer_size];
        pointer_ = buffer_ + buffer_size_;
    }

    Scanner& operator>>(int &object) {
        object = 0;
        while (next() < '0' or next() > '9')
            advance();
        while (next() >= '0' and next() <= '9') {
            object = object * 10 + next() - '0';
            advance();
        }
        return *this;
    }

  private:
    char next() {
        if (pointer_ == buffer_ + buffer_size_) {
            pointer_ = buffer_;
            fread(buffer_, 1, buffer_size_, file_);
        }
        return *pointer_;
    }

    void advance() {
        ++pointer_;
    }

    FILE *file_;
    int buffer_size_;
    char *buffer_, *pointer_;
};
Scanner fin(infile);

queue < per > Q;
int N, K, dp[MAXN][MAXN];

inline bool inside(const int &x, const int &y) {
    return x >= 1 && x <= N && y >= 1 && y <= N;
}

inline bool isSquareIntersection(const vector <pair<per, per> > V) {
    int x1 = -oo, y1 = -oo, x2 = oo, y2 = oo;
    for(int i = 0 ; i < V.size() ; ++ i) {
        x1 = max(x1, V[i].x.x);
        y1 = max(y1, V[i].x.y);
        x2 = min(x2, V[i].y.x);
        y2 = min(y2, V[i].y.y);
    }
    if(x1 == x2 && y1 == y2 && (x1 & 1) == (y1 & 1))
        return true;
    if(x1 == x2 && y1 == y2)
        return false;
    if(x1 <= x2 && y1 <= y2)
        return true;
    return false;
}

inline bool check(int dist) {
    per P1, P2;
    vector < pair<per, per> > Square;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(dp[i][j] > dist) {
                P1.x = i - dist; P1.y = j;
                P2.x = i + dist; P2.y = j;
                P1.x = P1.x + P1.y;
                P1.y = P1.x - 2 * P1.y;
                P2.x = P2.x + P2.y;
                P2.y = P2.x - 2 * P2.y;
                Square.push_back(make_pair(P1, P2));
            }
    return isSquareIntersection(Square);
}

inline int binarySearch() {
    int li = 0, ls = (1 << 11), Ans = 0;
    while(li <= ls) {
        int mid = (li + ls) / 2;
        if(!check(mid)) {
            Ans = mid;
            li = mid + 1;
        }
        else ls = mid - 1;
    }
    return Ans + 1;
}

int main() {
    memset(dp, oo, sizeof(dp));
    fin >> N >> K;
    for(int i = 1 ; i <= K ; ++ i) {
        int x, y;
        fin >> x >> y;
        dp[x + 1][y + 1] = 0;
        Q.push(make_pair(x + 1, y + 1));
    }
    while(!Q.empty()) {
        int x = Q.front().x;
        int y = Q.front().y;
        Q.pop();
        for(int d = 0; d < 4 ; ++d) {
            int newx = x + dx[d];
            int newy = y + dy[d];
            if(inside(newx, newy) && dp[newx][newy] > dp[x][y] + 1) {
                dp[newx][newy] = dp[x][y] + 1;
                Q.push(make_pair(newx, newy));
            }
        }
    }
    fout << binarySearch() << '\n';
    return 0;
}
