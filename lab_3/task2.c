#include<stdio.h>
#include<string.h>

int main(void)
{
    FILE *fp;
    char filearray[1000][1000];
    char myfile[1000];

    fp=fopen("myfile", "r");

    int i = 0;
    while(fgets(myfile,1000,fp))
    {
        strcpy(filearray[i], myfile);
        i++;
    }

    fclose(fp);

    for (int j = 0; j < i; j++) 
    {
        printf("Line %d: %s", j + 1, filearray[j]);
    }

    return 0;
}