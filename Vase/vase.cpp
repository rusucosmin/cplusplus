#include<fstream>
using namespace std;
ifstream fin("vase.in");
ofstream fout("vase.out");
long long s, st, dr;
int n, x, i, v[100001];//, st, dr;
char d[100001];
int main()
{
    fin>>n;
    for(i=1;i<=n;i++)
      fin>>v[i]>>d[i];
    fin>>x;
    for(i=1;i<=n;i++)
      s=s+v[i];
    s=s/2;
    long long ss=0;
	for(int i=1; i<x; ++i)
		ss += v[i];
	ss /= 2;
	int i=x;
	if(d[i]=='S')
		st = -ss-v[i]/2, dr = -ss + v[i]/2;
	else
		st = ss-v[i]/2, dr = ss + v[i]/2;
	for(i = x+1 ; i<=n ; ++i)
    {
		if(d[i]=='S')
			st = st+v[i]/2, dr = dr + v[i]/2;
		else
			st = st-v[i]/2, dr = dr - v[i]/2;
	}
	
	fout<<s<<endl;
	if(st>=0)
		fout<<dr<<" D\n"<<st<<" D";
	else
		if(dr<=0)
			fout<< -st <<" S\n"<< -dr <<" S";
		else
			fout<< -st <<" S\n"<< dr <<" D";
	
	return 0;
}
       
