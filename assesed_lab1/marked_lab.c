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
        procs[i].complete = false;

        //check if the faults we read are the same as num_faults claims
        if (procs[i].num_faults != (matched - 4)) 
        {
            printf("format error\n");
            fclose(fp);
            return 1;
        }
        i++;
    }
    num_of_proceses = i;
    fclose(fp);
    return 0;
}

//return the index of the task with priority from a given array, 
int priority_decider(struct process tasks[])
{
    /*index of the process with the current highest priority, 
    start at -1 so we can return -1 if nothing needs processing*/
    int prio_index = -1; 
    
    int max_prio = 100; //intitalise the max priority delibratly higher than any real priority value 

    for (int i = 0; i < num_of_proceses; i++)
    {
        if (tasks[i].complete || tasks[i].ran_in_pass) 
        {
            continue; //skip this task if already ran or complete
        }
        if (tasks[i].priority < max_prio)
        {
            prio_index = i;
            max_prio = tasks[i].priority;
        }
    }
    return prio_index;
}

//return 1 if every task is complete, else return 0 and reset ran_in pass variable
int is_finished(struct process tasks[])
{

}

/* lets run this process!! 
given a array of processes and an index of a process, runs said process for up to 10 ms*/
void run_process(struct process tasks[], int proc_no)
{
    int local_progress = 0;
    
};



//main simulation
int main(int argc, char *argv[])
{
    struct process process_array[10];

    if (file_read(argv[1], process_array) == 1) //ensure file has been read correctly
    {
        return 1;
    }

    while(true) //main loop
    {
        int index = priority_decider(process_array);

        if (index == -1 && is_finished(process_array))
        {
            break;
        }

        run_process(process_array, index);
    } 

}
