#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long int Module (long long int a)
{
	if (a < 0) return -a;
	else return a;
}

int main ()
{
	int N;
	long long int A, B, C, B2, res, res2;
	scanf("%d",&N);
	int i;
	for (i = 0; i < N; i++)
	{
		scanf("%I64i %I64i",&A,&C);
		B = C / A;
		B2 = B + 1;
		res = Module(A * B - C);
		res2 = Module(A * B2 - C);
		if (res < res2) printf("%I64i\n",B);
		else printf("%I64i\n",B2);
	}
	return 0;
}
