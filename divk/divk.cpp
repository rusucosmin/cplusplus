#include<fstream> 
using namespace std; 

ifstream in("divk.in");
ofstream out("divk.out");

long long N, K, A, B, sol;
long long V[500010], app[100010];

int main()
{
	long long i, x;
	
	in >> N >> K >> A >> B;
	for(i = 1; i <= N; i++)
	{
		in >> x;
		V[i] = ( V[i-1] + x )%K;
	}
	for(i = 1; i <= N; i++)
		{
			if( i - A >= 0 )
			++app[V[i - A]];
			if( i - B > 0 )
				--app[V[i - B - 1]];
	
	sol += app[V[i]];
	}
	out << sol;
	return 0;
}
	
