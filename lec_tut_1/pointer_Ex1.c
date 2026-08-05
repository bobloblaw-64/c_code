#include<stdio.h>

int main()
{
    int alpha;

    alpha = 27;
    printf("Integer variable alpha holds the value %d\n", alpha);
    printf("variable alpha occupies %lu bytes of storage\n",sizeof(alpha));
    printf("and sits at adress %p\n",&alpha);
}