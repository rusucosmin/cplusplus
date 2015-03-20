#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#define infile "markon.in"
#define outfile "markon.out"
#define nMax 500013

using namespace std;

vector <int> v[nMax];
vector <int> res;
int unmark[nMax];
int value[nMax];
bool vz[nMax];
bool q2[nMax];
int n, m, x;

void read() {

  int a, b;
  scanf("%d %d %d", &n, &m, &x);

  for(int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
    if(value[i] == 0) value[i] = n;
  }

  for(int i = 1; i <= m; ++i) {
    scanf("%d %d", &a, &b);
    v[a].push_back(b);
    v[b].push_back(a);
  }

}

void init() {
  for(int i = 1; i <= n; ++i) {
    unmark[i] = v[i].size();
  }
}

void solve() {

  queue <int> q;
  q.push(x);
  vz[x] = true;

  while(!q.empty()) {

    int x = q.front();
    res.push_back(x);
    q.pop();

    for(unsigned i = 0; i < v[x].size(); ++i) {
      --unmark[v[x][i]];
    }

    if(unmark[x] < value[x]) {
      for(unsigned i = 0; i < v[x].size(); ++i) {
        if(!vz[v[x][i]]) {
          q.push(v[x][i]);
          vz[v[x][i]] = true;
        }
      }
    } else {
      q2[x] = true;
    }

    for(unsigned i = 0; i < v[x].size(); ++i) {
      if(q2[v[x][i]] == true && unmark[v[x][i]] < value[v[x][i]]) {
        int y = v[x][i];
        q2[y] = false;
        for(unsigned j = 0; j < v[y].size(); ++j) {
          if(!vz[v[y][j]]) {
            q.push(v[y][j]);
            vz[v[y][j]] = true;
          }
        }
      }
    }

  }

}

void write() {
  printf("%d\n", res.size());
  for(unsigned i = 0; i < res.size(); ++i) {
    printf("%d\n", res[i]);
  }
}

int main() {
  freopen(infile, "r", stdin);
  freopen(outfile, "w", stdout);

  read();
  init();
  solve();
  write();

  fclose(stdin);
  fclose(stdout);
  return 0;
}
