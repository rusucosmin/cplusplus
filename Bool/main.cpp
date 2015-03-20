#include <fstream>

using namespace std;

ifstream in("bool.in");
ofstream out("bool.out");

char s[1100],z[1100];
int p=0,v[30];


bool expresie();
bool termen_sau();
bool termen_si();

bool expresie()
{
    bool val=termen_sau();
    while(z[p]=='|')
    {
        ++p;
        val|=termen_sau();
    }
    return val;
}
bool termen_sau()
{
    bool val=termen_si();
    while (z[p]=='&')
    {
        ++p;
        val&=termen_si();
    }
    return val;
}
bool termen_si()
{
    bool val,nt=false;
    while(z[p]=='~')
    {
        nt=!nt;
        ++p;
    }
    if(z[p]=='1')
    {
        val=1;
        ++p;
        if(nt)
            return !val;
        return val;
    }
    if(z[p]=='0')
    {
        val=0;
        ++p;
        if(nt)
            return !val;
        return val;
    }
    if(z[p]>='a' && z[p]<='z')
    {
        val=v[z[p]-'a'];
        ++p;
        if(nt)
            return !val;
        return val;
    }
    if(z[p]=='(')
    {
        ++p;
        val=expresie();
        ++p;
        if(nt)
            return !val;
        return val;
    }
}
int main()
{
    int nr,i,n;
    char c;
    in.getline(s,1100);
    nr=-1;
    while(s[p])
    {
        if(s[p]==' ')
        {
            ++p;
            continue;
        }
        if(s[p]=='T' && s[p+1]=='R' && s[p+2]=='U' && s[p+3]=='E')
        {
            z[++nr]='1';
            p+=4;
            continue;
        }
        if(s[p]=='F' && s[p+1]=='A' && s[p+2]=='L' && s[p+3]=='S' && s[p+4]=='E')
        {
            z[++nr]='0';
            p+=5;
            continue;
        }
        if(s[p]=='(' || s[p]==')')
        {
            z[++nr]=s[p];
            ++p;
            continue;
        }
        if(s[p]=='A' && s[p+1]=='N' && s[p+2]=='D')
        {
            z[++nr]='&';
            p+=3;
            continue;
        }
        if(s[p]=='N' && s[p+1]=='O' && s[p+2]=='T')
        {
            z[++nr]='~';
            p+=3;
            continue;
        }
        if(s[p]=='O' && s[p+1]=='R')
        {
            z[++nr]='|';
            p+=2;
            continue;
        }
        if(s[p]>='A' && s[p]<='Z')
        {
            z[++nr]=s[p]-'A'+'a';
            p++;
            continue;
        }
    }
    //for(i=0;z[i];++i)
     //   out<<z[i];
    p=0;
    in>>n;
    in.getline(s,1000);
    for(i=1;i<=n;++i)
    {
        p=0;
        in>>c;
        v[c-'A']=(v[c-'A']+1)%2;
        out<<expresie();
    }
    return 0;
}
