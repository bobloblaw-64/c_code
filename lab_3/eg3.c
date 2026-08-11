#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char myfile[1000];
    fp=fopen("myfile", "r");
    while(fgets(myfile,100,fp))
    {
        printf("%s",myfile);
    }
}
