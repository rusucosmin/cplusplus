#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;

const char infile[] = "seti.in";
const char outfile[] = "seti.out";
const int SIGMA = 52;

ifstream fin(infile);
ofstream fout(outfile);

string Txt, s;
vector <string> V;
int N, M, str;

class SuffixAutomation {
public:
    class Node {
    public:
        Node(const int &_length = 0, Node * const _link = 0, const int &_endings = 0) {
            length = _length;
            link = _link;
            endings = _endings;
            solved = false;
            memset(edges, 0, sizeof(edges));
        }
        int length, endings;
        bool solved;
        Node *link;
        Node *edges[SIGMA];
    };

    SuffixAutomation(const string &S = "") {
        start = finish = alloc.allocate(S.size() << 1);
        root = new Node();
        lastNode = root;
        for(string :: const_iterator it = S.begin(), fin = S.end(); it != fin ; ++ it) {
            int value = 0;
            if('a' <= *it && *it <= 'z')
                value = *it - 'a';
            else value = *it - 'A' + 26;
            extend(value);
        }
    }
    ~SuffixAutomation() {
        alloc.deallocate(start, finish - start);
    }
    void prepare() {
        for(Node *i = lastNode ; i != 0 ; i = i -> link)
            i -> endings = 1;
        getAnswer(root);
    }
    inline int many(string C) {
        Node *p = root;
        for(string::const_iterator it = C.begin(), fin = C.end(); it != fin ; ++ it) {
            int number = 0;
            if('a' <= *it && *it <= 'z')
                number = *it - 'a';
                else number = *it - 'A' + 26;
            if(!p -> edges[number])
                return 0;
            p = p -> edges[number];
        }
        return p -> endings;
    }
private:
    inline void extend(const int &value) {
        Node *now = new(finish) Node(lastNode -> length + 1);
        finish += 1;
        Node *aux;
        for(aux = lastNode ; aux != 0 && !aux -> edges[value] ; aux = aux -> link)
            aux -> edges[value] = now;

        lastNode = now;

        if(aux == 0) {
            now -> link = root;
            return ;
        }

        Node *nxt = aux -> edges[value];

        if(aux -> length + 1 == nxt -> length) {
            now -> link = nxt;
            return ;
        }

        Node *clone = new(finish) Node(aux -> length + 1, nxt -> link);
        finish += 1;

        memcpy(clone -> edges, nxt -> edges, sizeof(int) * 52);

        for( ; aux != 0 && aux -> edges[value] == nxt ; aux = aux -> link)
                aux -> edges[value] = clone;
        nxt -> link = now -> link = clone;
    }

    int getAnswer(Node * nod) {
        if(nod -> solved)
            return nod -> endings;
        for(int i = 0 ; i < 52 ; ++ i)
            if(nod -> edges[i])
                nod -> endings += getAnswer(nod -> edges[i]);
        nod -> solved = true;
        return nod -> endings;
    }
    allocator<Node> alloc;
    Node *start, *finish, *root, *lastNode;
};


int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> s;
        Txt += s;
    }
    SuffixAutomation suffixAutomation(Txt);
    suffixAutomation.prepare();
    int M;
    fin >> M;
    while(M --) {
        string C;
        fin >> C;
        fout << suffixAutomation.many(C) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}

/*#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string>

using namespace std;

const char infile[] = "seti.in";
const char outfile[] = "seti.out";

ifstream fin(infile);
ofstream fout(outfile);

string Txt, s;
vector <string> V;
int N, M, str;

struct classComp {
    inline bool operator () (const int &a, const int &b) const {
        return V[a] < V[b];
    }
};

inline int binarySearchRight(const string &S) {
    int li = 1, ls = str, mid, Ans = -1;
    int l = S.size();
    while(li <= ls) {
        mid = (li + ls) / 2;
        if(V[mid].substr(0, l) == S) {
            Ans = mid;
            li = mid + 1;
            continue;
        }
        if(V[mid].substr(0, l) < S)
            li = mid + 1;
        else ls = mid - 1;
    }
    return Ans + 1;
}

inline int binarySearchLeft(const string &S) {
    int li = 1, ls = str, mid, Ans = 0;
    int l = S.size();
    while(li <= ls) {
        mid = (li + ls) / 2;
        if(V[mid].substr(0, l) == S) {
            Ans = mid;
            ls = mid - 1;
            continue;
        }
        if(V[mid].substr(0, l) < S)
            li = mid + 1;
        else ls = mid - 1;
    }
    return Ans;
}

int main() {
    fin >> N;
    fin.get();
    for(int i = 1 ; i <= N ; ++ i) {
        getline(fin, s);
        //fin >> s;
        Txt += s;
    }
    V.push_back("");
    int l = Txt.size();
    for(int i = 0 ; i < l ; ++ i) {
        V.push_back(Txt.substr(i, min(16, l - i)));
        ++ str;
    }
    sort(V.begin(), V.end());
    fin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        fin >> s;
        fout << binarySearchRight(s) -  binarySearchLeft(s) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
*/
