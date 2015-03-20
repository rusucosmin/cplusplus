#include <fstream>
 using namespace std;
 const int MOD = 10007;
 
int N, M;
int P[301][301];
int perm[301];
 
int main()
{
ifstream fin("permutari2.in");
ofstream fout("permutari2.out");
 
fin >> N >> M;
 
perm[1] = 1;
for (int i = 2; i <= N; ++i)
perm[i] = (perm[i - 1] * i) % MOD;
 
P[1][1] = 1;
for (int i = 2; i <= N; ++i)
{
int total = 0;
for (int j = 2; j <= N; ++j)
{
for (int k = i - 1; k >= j - 1; --k)
{
P[i][j] += (P[k][j - 1] * P[i - k][1]) % MOD;
P[i][j] %= MOD;
}
total += P[i][j], total %= MOD;
}
 
P[i][1] = (perm[i] - total + MOD) % MOD;
} 
fout << P[N][M]; 
fin.close();
fout.close();
}

