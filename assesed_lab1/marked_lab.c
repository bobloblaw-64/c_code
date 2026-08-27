/*CITS2002 Assesed Lab 1 
Code by Finlay Thomson, 
SID: 23953297 */

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

struct process process_array[10];

//Read file and save data to array
int file_read(char filename[])
{
    FILE *fp;
    fp=fopen("name_num.txt", "r");

    char line[50];
    int i = 0;

    //read file and copy to array
    while(fgets(line, sizeof(line), fp))
    {
        int matched = sscanf(line, "%s %d %d %d %d %d %d %d %d %d %d %d",
             process_array[i].name, &process_array[i].priority, 
             &process_array[i].total_exec_time, &process_array[i].num_faults, 
             &process_array[i].fault_positions[0], &process_array[i].fault_positions[1],
             &process_array[i].fault_positions[2], &process_array[i].fault_positions[3],
             &process_array[i].fault_positions[4], &process_array[i].fault_positions[5],
             &process_array[i].fault_positions[6],&process_array[i].fault_positions[7]);

        i++;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int cpuTime;

    file_read(argv[1]);

}
