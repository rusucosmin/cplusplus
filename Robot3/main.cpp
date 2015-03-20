#include <fstream>
#include <algorithm>

using namespace std;

int N, M, L, C;
long long Enow;
char Com[5005];
int pos1[5005], pos2[5005];
int P[5005];
int size;

bool compare(const int& i1, const int& i2)
{
	if (pos1[i1] != pos1[i2])
		return pos1[i1] < pos1[i2];
	return pos2[i1] < pos2[i2];
}

int main()
{
	ifstream fin("robot3.in");
	ofstream fout("robot3.out");
	
	fin >> N >> M >> L >> C;
	for (int i = 1; i <= M; ++i)
		fin >> Com[i];
	
	int aL = L, aC = C;
	
	pos1[++size] = L, pos2[size] = C;
	P[size] = size;
	
	for (int i = 1; i <= M; ++i)
	{
		switch (Com[i])
		{
			case 'N':
				--L;
				break;
			case 'S':
				++L;
				break;
			case 'E':
				++C;
				break;
			case 'V':
				--C;
				break;
		}
		
		pos1[++size] = L, pos2[size] = C;
		P[size] = size;
	}
	
	sort(P + 1, P + size + 1, compare);
	
	int now = 1, value;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
		{
			fin >> value;
			if (now <= size && pos1[P[now]] == i && pos2[P[now]] == j)
			{
				pos1[P[now]] = value;
				++now;
			}
		}
	
	L = aL, C = aC;
	
	Enow = pos1[1];
	for (int i = 1; i <= M; ++i)
	{
		if (Enow == 0) break;
		--Enow;
		
		switch (Com[i])
		{
			case 'N':
				--L;
				break;
			case 'S':
				++L;
				break;
			case 'E':
				++C;
				break;
			case 'V':
				--C;
				break;
		}
		
		Enow += (long long) pos1[i + 1];
	}
	
	fout << L << ' ' << C;
	
	fin.close();
	fout.close();
}
