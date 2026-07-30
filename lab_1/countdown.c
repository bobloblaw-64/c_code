#include <stdio.h>
void countdown(int n)
{
	if (n == 0)
	{
	printf("Finished!\n");
	return;
	} 
	printf("%d\n", n);
	countdown(n - 1);
}

int main()
{
	countdown(16);
	return 0;
}
