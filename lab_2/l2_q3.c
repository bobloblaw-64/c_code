#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    for(int i=1;i<argc;i++)
    {
        size_t len = strlen(argv[i]);
        char last_digit = argv[i][len - 1];

        if (atoi(argv[i]) == 11 || atoi(argv[i]) == 12 || atoi(argv[i]) == 13)
        {
            printf("%sth\n", argv[i]);
        }
        else if (last_digit == '1')
        {
            printf("%sst\n", argv[i]);
        }
        else if (last_digit == '2')
        {
            printf("%snd\n", argv[i]);
        }
        else if (last_digit == '3')
        {
            printf("%srd\n", argv[i]);
        }
        else
        {
            printf("%sth\n", argv[i]);
        }
        
        
    }
    

}