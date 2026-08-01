#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    for(int i=1;i<argc;i++)
        printf("%i\n", atoi(argv[i]));
}