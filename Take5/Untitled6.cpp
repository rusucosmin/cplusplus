#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define maxc 4000
#define baza 10
#define fwd 5
#define filein "aladdin2.in"
#define fileout "aladdin2.out"

typedef long int BigNum[maxc];

int compare(BigNum, BigNum);
void add(BigNum, BigNum, BigNum);
void sub(BigNum, BigNum, BigNum);
void dec(BigNum, BigNum);
void mult(long int, BigNum, BigNum);
void multbig(BigNum, BigNum, BigNum);

BigNum naux1, naux2, total;
long int M, N, i, x;

int main()
{
freopen(filein, "r", stdin);
scanf("%ld %ld", &M, &N);

memset(total, 0, sizeof(total));
memset(naux1, 0, sizeof(naux1));
naux1[0] = naux1[1] = 1;

if (M > N)
  {
    x = M; M = N; N = x;
  }

for (i = 1; i <= M; )
  {
    if (i + 11 <= M)
      x = 2048, i += 11;
    else
      x = 2, i++;

    mult(x, naux1, naux2);
    memmove(naux1, naux2, sizeof(BigNum));
  }
i--;

if (i == M)
  memmove(total, naux1, sizeof(BigNum));

if (i == N)
  {
    add(total, naux1, naux2);
    memmove(total, naux2, sizeof(BigNum));
  }

for (i = M+1; i <= N;)
  {
    if (i + 11 <= N)
      x = 2048, i += 11;
    else
      x = 2, i++;

    mult(x, naux1, naux2);
    memmove(naux1, naux2, sizeof(BigNum));

    if (i == N+1)
      {
        add(naux1, total, naux2);
        memmove(total, naux2, sizeof(BigNum));
      }
  }

dec(total, naux1);
dec(naux1, total);

freopen(fileout, "w", stdout);
printf("%ld", total[total[0]]);
for (i = total[0]-1; i >= 1; i--)
  printf("%ld", total[i]);

return 0;
}

/* 1 if n1 > n2 ; -1 if n1 < n2 ; 0 if n1 == n2 */
int compare(BigNum n1, BigNum n2)
{
int i, res;

if (n1[0] > n2[0]) return 1;
if (n1[0] < n2[0]) return -1;

for (res = 0, i = n1[0]; i >= 1; i--)
  if (n1[i] > n2[i])
    {
      res=1;
      break;
    }
  else
  if (n1[i] < n2[i])
    {
      res=-1;
      break;
    }

return res;
}

void add(BigNum n1, BigNum n2, BigNum rez)
{
int i, ndigits = n1[0];

if (n2[0] > ndigits)
  ndigits = n2[0];

memset(rez, 0, sizeof(BigNum));
for (i = 1; i <= ndigits; i++)
  rez[i] = n1[i]+n2[i];

for (i = 1 ;i <= (ndigits+fwd); i++)
  if (rez[i] >= baza)
    {
      rez[i+1] += (rez[i]/baza);
      rez[i] %= baza;
    }

for (i = (ndigits+fwd); i >= 1; i--)
  if (rez[i] > 0)
    {
      rez[0] = i;
      break;
    }
}

void sub(BigNum n1, BigNum n2, BigNum res)
{
int i, ndigits = n1[0];

memset(res, 0, sizeof(BigNum));
for (i = 1; i <= ndigits; i++)
  res[i] = n1[i] - n2[i];

for (i = 1; i <= ndigits; i++)
  while (res[i] < 0)
    {
      res[i] += baza;
      res[i+1]--;
    }

for (res[0] = 1, i = ndigits; i >= 1; i--)
  if (res[i])
    {
      res[0] = i;
      break;
    }
}

void dec(BigNum n, BigNum res)
{
int i, ndigits = n[0];

memset(res, 0, sizeof(BigNum));
for (i = 1; i <= ndigits; i++)
  res[i] = n[i];

for (res[1]--, i = 1; i <= ndigits; i++)
  if (res[i] < 0)
    {
      res[i] += baza;
      res[i+1]--;
    }

for (res[0] = 1, i = ndigits; i >= 1; i--)
  if (res[i])
    {
      res[0] = i;
      break;
    }
}

void mult(long int x, BigNum num, BigNum rez)
{
int i, ndigits = num[0];

memset(rez, 0, sizeof(BigNum));
for (i = 1; i <= ndigits; i++)
  rez[i] = num[i]*x;

for (i = 1; i <= (ndigits+fwd); i++)
  if (rez[i] >= baza)
    {
    rez[i+1] += (rez[i]/baza);
    rez[i] %= baza;
    }

for (i = (ndigits+fwd); i >= 1; i--)
  if (rez[i] > 0)
    {
    rez[0] = i;
    break;
    }
}

void multbig(BigNum n1, BigNum n2, BigNum rez)
{
int i, j, ndigits = n1[0]+n2[0]-1;

memset(rez, 0, sizeof(BigNum));
for (i = 1; i <= n1[0]; i++)
  for (j = 1; j <= n2[0]; j++)
    rez[i+j-1] += (n1[i]*n2[j]);

for (i = 1; i <= (ndigits+fwd); i++)
  if (rez[i] >= baza)
    {
      rez[i+1] += (rez[i]/baza);
      rez[i] %= baza;
    }

for (i = (ndigits+fwd); i >= 1; i--)
  if (rez[i] > 0)
    {
      rez[0] = i;
      break;
    }
}
