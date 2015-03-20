#include <fstream>
#include <vector>
#include <bitset>
#include <set>

using namespace std;

const char infile[] = "zeap.in";
const char outfile[] = "zeap.out";

ifstream cin(infile);
ofstream cout(outfile);

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char op[5];
int x;
multiset <int> zeap, mindif;
multiset <int> :: iterator pos, pos1, pos2;

int main() {
    while(cin >> op) {
        if(op[0] == 'I') {
            cin >> x;
            if(zeap.find(x) == zeap.end()) {
                zeap.insert(x);
                pos = zeap.find(x);
                if(pos != zeap.begin()) {
                    pos1 = pos;
                    pos2 = pos;
                    -- pos1;
                    ++ pos2;
                    mindif.insert(x - *pos1);
                    if(pos2 != zeap.end()) {
                        mindif.erase(mindif.find(*pos2 - *pos1));
                        mindif.insert(*pos2 - x);
                    }
                }
                else {
                    pos2 = pos;
                    ++ pos2;
                    if(pos2 != zeap.end())
                        mindif.insert(*pos2 - x);
                }
            }
            continue;
        }
        if(op[0] == 'S') {
            cin >> x;
            if( (pos = zeap.find(x)) != zeap.end()) {
                pos1 = pos;
                pos2 = pos;
                if(pos != zeap.begin()) {
                    -- pos1;
                    mindif.erase(mindif.find(x - *pos1));
                }
                ++ pos2;
                if(pos2 != zeap.end())
                    mindif.erase(mindif.find(*pos2 - x));
                if(pos != zeap.begin() && pos2 != zeap.end())
                    mindif.insert(*pos2 - *pos1);
                zeap.erase(pos);
                continue;
            }
            cout << "-1\n";
            continue;
        }
        if(op[0] == 'C') {
            cin >> x;   cout << (zeap.find(x) != zeap.end()) << '\n';
            continue;
        }
        if(op[1] == 'A') {
            if(zeap.size() < 2)   { cout << "-1\n" ; continue; }
            pos = zeap.end();
            --pos;
            cout << *pos - *zeap.begin() << '\n';
            continue;
        }
        if(op[1] == 'I') {
            if(mindif.size())  cout << *mindif.begin() << '\n';
            else  cout << "-1\n";
            continue;
        }
    }
    cin.close();
    cout.close();
    return 0;
}
