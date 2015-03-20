#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <queue>
#include <bitset>
#include <fstream>
#include <time.h>

using namespace std;

#define in_file "jmenoasa.in"
#define out_file "jmenoasa.out"

#define VI vector <int>
#define FORN(i,n) for(int i=0;i<n;++i)
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define SZ size()
#define B begin()
#define E end()
#define X first
#define Y second
#define PB push_back
#define MP make_pair
#define ALL(x) x.begin(),x.end()
#define repeat do{
#define until(x) }while(!(x));

char buf[12000];
int n,m,ind,solution,limit=CLOCKS_PER_SEC*0.55;
vector <VI> a;
clock_t start=clock();

int ReadNr()
{
        int ans=0;
        while (isdigit(buf[ind]))
        {
                ans=ans*10 + buf[ind] - '0';
                ++ind;
        }
        ++ind;
        return ans;
}

void solve()
{
        solution=1;
        FOR(i1,1,n)
        {
                FOR(j1,1,m)
                {
                        int area;
                        int j2=j1+1;
                        while (j2<=m && a[i1][j2]>a[i1][j2-1]) ++j2;
                        --j2;
                        int     minCol=j2-j1+1;
                        area=minCol;
                        solution=max(solution, area);
                        FOR(i2,i1+1,n)
                        {
                                if (a[i2][j1]<=a[i2-1][j1]) break;
                                j2=j1+1;
                                while (j2<=m && a[i2][j2]>a[i2][j2-1] && a[i2][j2]>a[i2-1][j2])
                                {
                                        ++j2;
                                        if ((j2-j1)>=minCol) break;
                                }
                                --j2;
                                minCol=min(minCol,j2-j1+1);
                                area=minCol * (i2 - i1 + 1);
                                solution=max(solution, area);
                        }

                }
                if (clock()-start>limit) return ;
        }
}

int main() {
        FILE* fin=fopen(in_file,"r");
        fscanf(fin,"%d%d\n",&n,&m);
        a.resize(n+1, VI (m+1, -1));
        FOR(i,1,n)
        {
                fgets(buf,12000,fin);
                ind=0;
                FOR(j,1,m) a[i][j]=ReadNr();
        }
        fclose(fin);

        solve();

        FILE* fout=fopen(out_file,"w");
        fprintf(fout,"%d",solution);
        fclose(fout);

        return 0;
}
