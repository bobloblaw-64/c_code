#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    printf("number of arguments=%i\n",argc);
    for(int i=0;i<argc;i++)
        printf("%s\n", argv[i]);
    printf("The fourth character of fifth argument=%c\n", argv[4][3]);
}