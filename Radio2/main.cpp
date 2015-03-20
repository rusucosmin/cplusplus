#include <fstream>
#include <vector>
#include <bitset>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

const char infile[] = "radio2.in";
const char outfile[] = "radio2.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 1000010;
const int MOD = 71582857;
const int BASE = 29;
const int MAXL = 2510;

int N, M, L, K;
unordered_map <int, vector <int> > Hash;
char wordGiven[MAXN], word[MAXL];

inline void buildHash(const int &l) {
    int hashVal = 0;
    int b = 1;
    for(int i = 1 ; i <= l ; ++ i) {
        hashVal = (1LL * hashVal * BASE + (wordGiven[i] - 'a')) % MOD;
        if(i < l)
            b = (1LL * b * BASE) % MOD;
    }
    Hash[hashVal].push_back(1);
    for(int i = l + 1 ; i <= N ; ++ i) {
        hashVal = (hashVal - (b * (wordGiven[i - l] - 'a'))) % MOD;
        if(hashVal < 0)
            hashVal += MOD;
        hashVal = (1LL * hashVal * BASE + (wordGiven[i] - 'a')) % MOD;
        Hash[hashVal].push_back(i - l);
    }
}

inline bool Search(const int &value) {
    if(value < 0 || value + L > N)
        return false;
    int cnt = 0;
    for(int i = 1 ; i <= L ; ++ i)
        if(wordGiven[value + i] != word[i]) {
            ++ cnt;
            if(cnt > K)
                return false;
        }
    return true;
}

int main() {
    cin >> N >> M >> L >> K;
    cin >> (wordGiven + 1);
    int l = L / ( K + 1 );
    buildHash(l);
    for(int i = 1 ; i <= M ; ++ i) {
        cin >> (word + 1);
        bool found = false;
        for(int j = 0 ; j <= K && !found ; ++ j) {
            int hashVal = 0;
            for(int pos = 1 ; pos <= l ; ++ pos)
                hashVal = (hashVal * BASE + (word[j * l + pos] - 'a')) % MOD;
            if(Hash.find(hashVal) != Hash.end())
                for(unsigned int sz = 0 ; sz < Hash[hashVal].size() && !found ; ++ sz)
                    found |= Search(Hash[hashVal][sz] - j * l);
        }
        cout << found << '\n';
    }
    cin.close();
    cout.close();
    return 0;
}
