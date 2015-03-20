#include <fstream>
#include <vector>
#include <memory>

using namespace std;

const int maxn = 50005;

int arb[maxn * 4], n, m;

class Reader {
  public:
    Reader(const string& filename):
            m_stream(filename),
            m_pos(kBufferSize - 1),
            m_buffer(new char[kBufferSize]) {
        next();
    }
  
    Reader& operator>>(int& value) {
        value = 0;
        while (current() < '0' || current() > '9')
            next();
        while (current() >= '0' && current() <= '9') {
            value = value * 10 + current() - '0';
            next();
        }
        return *this;
    }
  
  private:
    const int kBufferSize = 32768;
  
    char current() {
        return m_buffer[m_pos];
    }
  
    void next() {
        if (!(++m_pos != kBufferSize)) {
            m_stream.read(m_buffer.get(), kBufferSize);
            m_pos = 0;
        }
    }
  
    ifstream m_stream;
    int m_pos;
    unique_ptr<char[]> m_buffer;
};
  

inline void update(int node, int st, int dr, int pos, int value) {
	if(st == dr) {
		arb[node] = value;
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(pos <= mid)
		update(node << 1, st, mid, pos, value);
	else
		update((node << 1)|1, mid + 1, dr, pos, value);
	arb[node] = max(arb[node << 1], arb[(node << 1) | 1]);
}

inline int query(int node, int st, int dr, int a, int b) {
	if(a <= st && dr <= b)
		return arb[node];
	int mid = ((st + dr)>>1);
	int ans = -0x3f3f3f3f;
	if(a <= mid)
		ans = max(ans, query(node << 1, st, mid, a, b));
	if(mid < b)
		ans = max(ans, query((node << 1) | 1, mid + 1, dr, a, b));
	return ans;
}

int main() {
	Reader fin("saracsaurege.in");
	ofstream fout("saracsaurege.out");
	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		update(1, 1, n, i, x);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int a, b;
		fin >> a >> b;
		fout << query(1, 1, n, a, b) << '\n';
	}
	

	
}
