#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{

    char names[5][50];
    int numbers[5];
    
    for (int i = 0; i < 5; i++)
    {
        printf("enter student name \n");
        scanf("%s", names[i]);

        printf("enter student number \n");
        scanf("%i", &numbers[i]);
    }
    
    for (int i = 0; i < 5; i++)
    {
        printf("name: %s number: %i\n", names[i], numbers[i] );
    } 

}    

    
