#include <stdio.h>

int fib (int n)
{
	if (n <= 1)
		return 1;
	else
		return fib(n-1) + fib(n-2);
}

int main()
{
	int i, result;
	puts("Enter a positive number: ");
	scanf("%d", &i);
	result = fib(i);
	printf("\nElement %d of the Fibbionacci Sequence is %d.\n",i, result);
	return 0;
}
