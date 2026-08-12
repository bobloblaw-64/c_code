#include<stdio.h>
#include<stdlib.h>

//define data type
struct People
{
    char name[50];
    int number;
};

int main(void)
{
    //declare array opf max size 20
    struct People people_array[20];

    //open file
    FILE *fp;
    fp=fopen("name_num.txt", "r");
    if (fp == NULL)
    {
        printf("error\n");
        return 1;
    }

    char line[1000];
    int i = 0;

    //read file and copy to array
    while(fgets(line, sizeof(line), fp) && i < 20)
    {
        if (sscanf(line, "%49s %d", people_array[i].name, &people_array[i].number) == 2)
        {
            i++;
        }
    }

    fclose(fp);

    //find max and min
    int max_index =0;
    int min_index =0;

    for (int j = 1; j < i; j++)
    {
        if (people_array[j].number > people_array[max_index].number)
        {
            max_index = j;
        }

        if (people_array[j].number < people_array[min_index].number)
        {
            min_index = j;
        }
    }

    printf("Maximum= %s %i\n", people_array[max_index].name, people_array[max_index].number);
    printf("Minimum= %s %i\n", people_array[min_index].name, people_array[min_index].number);

    return 0;

}