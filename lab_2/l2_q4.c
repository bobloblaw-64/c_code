#include <stdio.h>


int main(int argc, char *argv[])
{
    //Pattern A
    printf("Pattern A:\n");
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    //Pattern B
    printf("\nPattern B:\n");
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 0; j < 5 - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    
    //Pattern C
    printf("\nPattern C:\n");
    for (int i = 5; i >= 1; i--)
    {
        for (int j = 0; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    //Pattern D
    printf("\nPattern D:\n");
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 0; j < 5 - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < (2 * i - 1); j++)
        {
            printf("*");
        }
        printf("\n");
    }
    

}