#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<limits.h>

int main(int argc, char *argv[])
{
    int cur_max = atoi(argv[1]);
    int cur_min = atoi(argv[1]);
    for (int i = 2; i < argc; i++)
    {
        if (atoi(argv[i]) > cur_max)
        {
            cur_max = atoi(argv[i]);
        }
        if (atoi(argv[i]) < cur_min)
        {
            cur_min = atoi(argv[i]);
        }
        
    }
    printf("The max is %i\n", cur_max);
    printf("The min is %i\n", cur_min);
}