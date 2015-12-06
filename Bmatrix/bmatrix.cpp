#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
ifstream in("bmatrix.in");
ofstream out("bmatrix.out");

const int maxn = 205;
stack <int> st;
int stanga[maxn];
int dreapta[maxn];
int sp[maxn][maxn];
int M[maxn][maxn];
int aux[maxn][maxn];
int maxpartial1[maxn];
int maxpartial2[maxn];
int maxpartial3[maxn];
int maxpartial4[maxn];
int n, m;
char T[maxn];


void aflare_stanga(int linie)
{
    while(!st.empty())
        st.pop();
    sp[linie][0] = -1;
    st.push(0);
    for(int i = 1; i <= m; i++)
    {
        while(sp[linie][st.top()] >= sp[linie][i])
            st.pop();
        stanga[i] = st.top();
        st.push(i);
    }
}

void aflare_dreapta(int linie)
{
    while(!st.empty())
        st.pop();
    sp[linie][m+1] = -1;
    st.push(m+1);
    for(int i = m; i >= 1; i--)
    {
        while(sp[linie][st.top()] >= sp[linie][i])
            st.pop();
        dreapta[i] = st.top();
        st.push(i);
    }
}

void sump()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(M[i][j] == 1)
                sp[i][j] = 0;
            else
                sp[i][j] = sp[i-1][j] + 1;
        }
    }
}

void citire()
{
    in >> n >> m;
    in.getline(T,maxn);
    for(int i = 1; i <= n; i++)
    {
        in.getline(T + 1, maxn);
        for(int j = 1; j <= m; j++)
            M[i][j] = T[j] - '0';
    }
}

void rotire_90()
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            aux[j][n - i + 1] = M[i][j];
	swap(n, m);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            M[i][j] = aux[i][j];
}

int getmax(int linie) { /// maximul dreptungihului de pe linia i
    aflare_stanga(linie);
    aflare_dreapta(linie);
    int maxi = 0;
    for(int i = 1 ;i <= m ; ++ i)
        maxi = max(maxi, (dreapta[i] - 1 - stanga[i]) * sp[linie][i]);
    return maxi;
}

void solve(int maxpartial[])
{
    sump();
    for(int i = 1; i <= n; i++)
        maxpartial[i] = max(maxpartial[i-1], getmax(i));
}

void afisare() {
	for(int i = 1 ; i <= n ; ++ i, out << '\n')
		for(int j = 1 ; j <= m ; ++ j)
			out << M[i][j];
	out << '\n';
}

int main()
{
    citire();
    solve(maxpartial1);
    rotire_90();
   	solve(maxpartial3);
    rotire_90();
    solve(maxpartial2);
    rotire_90();
    solve(maxpartial4);
	rotire_90(); //// mai rotim odata ca sa avem aceleasi n si m, practic acum aducem matricea M in pozitia initiala
	/// am rttit de 4 * 90 = 360 de ori, deci ramane la fel
	///	afisare();
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i)
        ans = max(ans, maxpartial1[i] + maxpartial2[n - i]);
    for(int i = 1 ; i <= m ; ++ i)
        ans = max(ans, maxpartial3[i] + maxpartial4[m - i]);
	out << ans << '\n';
    return 0;
}

