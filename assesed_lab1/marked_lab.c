/*CITS2002 Assesed Lab 1 
Code by Finlay Thomson, SID: 23953297 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//Define the structure to describe each process
struct process
{
    char name[10];
    int priority;
    int total_exec_time;
    int exec_prog;
    int num_faults;
    int fault_positions[8];
    bool ran_in_pass;
};

//Read file and save data to array
int file_read(char filename[], struct process data_array[])
{
    FILE *fp;
    fp=fopen("name_num.txt", "r");

    char line[1000];
    int i = 0;

    //read file and copy to array
    while(fgets(line, sizeof(line), fp))
    {
        
    }

    
}

int main(int argc, char *argv[])
{
    struct process proc_array[8];
    int cpuTime;

    file_read(argv[1], proc_array);

}
