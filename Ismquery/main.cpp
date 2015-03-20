#include<fstream>
#include<vector>
#include<algorithm>
#include<cstring>
#define pii pair<int,int>
using namespace std;
int n,m,v[400100],G,H;
vector <pii> Q[400100];
int aib[400100],poz[6],sol[1200100];
bool viz[400100];
struct Element{int val,ind;};
int vsort[400100];
char sir[5000100];

inline bool Sortare(int A,int B)
{
    if(v[A]==v[B])
		return A<B;
	return v[A]>v[B];
}

inline void Aduna(int poz)
{
	while(poz<=n)
	{
		aib[poz]++;
		poz+=(poz & -poz);
	}
}

inline int Suma(int poz)
{
	int sum=0;
	while(poz)
	{
		sum+=aib[poz];
		poz-=(poz & -poz);
	}
	return sum;
}

inline int CautareBinara(int s,int st)
{
	/*int dr,mij,S;
	dr=n;
	while(st<=dr)
	{
		mij=(st+dr)/2;
		S=Suma(mij);
		if(S>s)
			dr=mij-1;
		else
		{
			if(S<s)
				st=mij+1;
			else
			{
				if(viz[mij])
					return mij;
				dr=mij-1;
			}
		}
	}
	return 0;*/

	//st e pozitia de inceput
	int ind = ( 1<< 15 );
    int rez=0, act=0;
    for ( ; ind; ind>>=1 ){
		if (rez + ind <= n)
		{
			if ( aib[rez+ind]+act < s ){
				act+=aib[ind+rez];
				rez+=ind;
			}
		}
    }
    return rez+1;
}

int main()
{
	int i,j,p,k,s,size,ind,ns,semn,x;
	ifstream fin("ismquery.in");
	fin>>n>>m;
	fin.get();
	fin.getline(sir,5000000);
	ns=strlen(sir);
	j=0;
	for(i=1;i<=n;i++)
	{
		while(sir[j]==' ')
			j++;
		if(sir[j]=='-')
		{
			semn=-1;
			j++;
		}
		else
			semn=1;
		x=0;
		while(j<ns && sir[j]!=' ')
			x=x*10+sir[j++]-'0';
		v[i]=x*semn;
		//fin>>v[i];
		vsort[i]=i;
	}
	fin>>G>>H;
	fin.close();

	p=k=1;
	for(i=1;i<=m;i++)
	{
		p=1+(i+p*G)%n;
		k=1+(i+k*H)%5;
		Q[p].push_back(make_pair(i,k));
	}
	sort(vsort+1,vsort+n+1,Sortare);
	for(i=1;i<=n;i++)
	{
		ind=vsort[i];
		size=Q[ind].size();
		if(size)
		{
			s=Suma(ind);
			poz[0]=ind;
			for(k=1;k<=5;k++)
			{
				poz[k]=CautareBinara(s+k,poz[k-1]+1);
				if(poz[k]==0)
				{
					k++;
					while(k<=5)
					{
						poz[k]=0;
						k++;
					}
				}
			}
			for(j=size-1;j>=0;j--)
			{
				k=Q[ind][j].second;
				sol[Q[ind][j].first]=poz[k];
			}
		}
		Aduna(ind);
		viz[ind]=true;
	}

	ofstream fout("ismquery.out");
	for(i=1;i<=m;i++)
		fout<<sol[i]<<"\n";
	fout.close();
	return 0;
}
