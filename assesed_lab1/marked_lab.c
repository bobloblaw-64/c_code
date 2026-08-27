/*CITS2002 Assesed Lab 1 
Code by Finlay Thomson, 
SID: 23953297 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int global_time = 0;
int num_of_proceses;

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
    bool complete;
};

//Read file and save data to array
int file_read(char filename[], struct process procs[])
{
    FILE *fp;
    fp=fopen(filename, "r");
    if (fp == NULL)
    {
        printf("file error\n");
        fclose(fp);
        return 1;
    }

    char line[200];
    int i = 0;

    //read file, copy data to array and initialise values
    while(fgets(line, sizeof(line), fp))
    {
        int matched = sscanf(line, "%s %d %d %d %d %d %d %d %d %d %d %d",
             procs[i].name, &procs[i].priority, 
             &procs[i].total_exec_time, &procs[i].num_faults, 
             &procs[i].fault_positions[0], &procs[i].fault_positions[1],
             &procs[i].fault_positions[2], &procs[i].fault_positions[3],
             &procs[i].fault_positions[4], &procs[i].fault_positions[5],
             &procs[i].fault_positions[6],&procs[i].fault_positions[7]);
        
        procs[i].exec_prog = 0;
        procs[i].ran_in_pass = false;
        procs[i].complete = true;

        //check if the faults we read are the same as num_faults claims
        if (procs[i].num_faults != (matched - 4)) 
        {
            printf("format error\n");
            fclose(fp);
            return 1;
        }
        i++;
    }
    num_of_proceses = i + 1;
    fclose(fp);
    return 0;
}

int priority_decider(struct process tasks[])
{
    int prio_index = -1; //index of the process with the current highest priority
    int max_prio = 100; //intitalise the max priority as the first priority value

    for (int i = 0; i < num_of_proceses; i++)
    {
        if (tasks[i].complete || tasks[i].ran_in_pass) continue; //skip this task if already ran or complete 

        if (tasks[i].priority < max_prio)
        {
            prio_index = i;
            max_prio = tasks[i].priority;
        }
    }
    return prio_index;
}

//main simulation
int main(int argc, char *argv[])
{
    struct process process_array[10];

    if (file_read(argv[1], process_array) == 1)
    {
        return 1;
    }

}
