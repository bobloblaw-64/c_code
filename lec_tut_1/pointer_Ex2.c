#include<stdio.h>

int main()
{
    int alpha;
    int *ptr;

    alpha = 99;
    ptr = &alpha;

    printf("the adress of alpha is %p.\n",&alpha);
    //printf("the value stored in ptr is %p.\n",ptr);
    printf("the value at location ptr %p is %d.\n", ptr, *ptr);
    printf("the value of alpha is %d.\n", alpha);
    *ptr = 16;
    printf("the value of alpha is %d.\n", alpha);


}