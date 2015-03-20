#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "abc2.in";
const char outfile[] = "abc2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int BASE = 3;
const int oo = 0x3f3f3f3f;
const int MOD = 99991;

typedef unsigned int ulol;

template <class T>
class Hash {
private:
    vector <T> _hash[MOD + 10];
    inline T key(const T &value) {
        return value % MOD;
    }
public:
    inline void add(const T &value) {
        _hash[key(value)].push_back(value);
    }
    inline int find(const T &value) {
        T keyy = key(value);
        for(typename vector < T> :: iterator it = _hash[keyy].begin(), fin = _hash[keyy].end(); it != fin ; ++ it)
            if(*it == value)
                return 1;
        return 0;
    }
};

inline ulol getInt(const char &c) {
    return c - 'a';
}

string Text, s;
ulol sigma;

inline ulol getValue(const string &p) {
    ulol value = 0;
    ulol i = 0;
    for(i = 0, sigma = p.size() ; i < sigma ; ++ i)
        value = value * BASE + getInt(p[i]);
    return value;
}

Hash <ulol> _hash;

int main() {
    fin >> Text;
    while(fin >> s) {
        ulol val = getValue(s);
        if(!_hash.find(val))
            _hash.add(val);
    }
    ulol value = 0;
    ulol _base = 1;
    for(ulol i = 0 ; i < sigma ; ++ i) {
        value = value * BASE + getInt(Text[i]);
        _base = _base * BASE;
    }
    ulol Ans = 0;
    Ans += _hash.find(value);
    for(ulol i = sigma , sz = Text.size() ; i < sz ; ++ i) {
        value = value * BASE + getInt(Text[i]);
        value = value - _base * getInt(Text[i - sigma]);
        Ans += _hash.find(value);
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
