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
#include <stack>

using namespace std;

const char infile[] = "unique.in";
const char outfile[] = "unique.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

class DisjointSet {
public:
    DisjointSet(int _maxValue) {
        Father.resize(_maxValue + 2);
        for(int i = 1 ; i < _maxValue ; ++ i)
            Father[i] = i;
    }
    int Find(int Node) {
        if(Father[Node] != Node)
            Father[Node] = Find(Father[Node]);
        return Father[Node];
    }
    inline void Unite(int first_one, int second_one) {
        Father[Find(first_one)] = Find(second_one);
    }
    vector <int> Father;
};

int main() {
    cin.sync_with_stdio(false);
    int T;
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        int N;

        fin >> N;

        DisjointSet disjointSet(N + 2);
        vector <int> values(N + 2, oo);
        stack <int> St;
        vector <int> differentNumbers(N + 2);
        vector <int> lastPosition(N + 1, -1);


        for(int i = 1 ; i <= N ; ++ i)
            fin >> values[i];
        -- values.back();

        St.push(0);
        int Answer = 0;
        for(int i = 1 ; i <= N + 1 ; ++ i) {
            int currentValue = values[i];
            int currentDifferentNumbers = 0;
            while(values[St.top()] <= currentValue) {
                int possibleMaxPosition = St.top();
                int possibleMaxValue = values[St.top()];
                St.pop();
                currentDifferentNumbers += differentNumbers[disjointSet.Find(possibleMaxPosition)];
                if(currentDifferentNumbers == possibleMaxValue)
                    Answer = max(Answer, i - St.top() - 1);
                disjointSet.Unite(possibleMaxPosition, i);
            }
            St.push(i);
            if(i > N)
                continue;
            differentNumbers[disjointSet.Find(i)] = currentDifferentNumbers + 1;

            if(lastPosition[currentValue] > -1)
                -- differentNumbers[disjointSet.Find(lastPosition[currentValue])];
            lastPosition[currentValue] = i;
        }
        fout << Answer << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}
