/*CITS2002 Assesed Lab 2
Code by Finlay Thomson, 
SID: 23953297 */

#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

int global_time = 0;
int num_of_proceses;

//Define the structure to describe each process
struct process
{
    char *name;
    int priority;
    int total_exec_time;
    int exec_prog;
    int num_faults;
    int *fault_positions;
    bool ran_in_pass;
    bool complete;
};

//open a file
FILE* open_file(char filename[]) {
    FILE *fp;
    fp=fopen(filename, "r");
    if (fp == NULL) {
        printf("file error\n");
        return NULL;
    }
    return fp;
}

//given a line and process structure, will write that line to the struct
int line_parse(char *line, struct process *dest) {
    
    int used;//bit of the line already parsed
    int ints;//all the int values that arent the name or fault positions

    //first assign name
    if (sscanf(line, "%ms%n", &dest->name, &used) == 1) { 
        char *cursor = line + used;
        /*
        then prio, total exec time and num of faults are defined. Followed
         by the dynamic array that is fault positions
         */
        if (sscanf(cursor, "%d %d %d%n",&dest->priority, &dest->total_exec_time, &dest->num_faults, &ints) == 3) {
            int num_faults = dest->num_faults;
            char *faults = cursor + ints;
            dest->fault_positions = malloc(num_faults * sizeof(int));

            //loop through the faults and add to the array we allocated earlier
            int i = 0;
            while (i < num_faults) {
                if (sscanf(faults, "%d%n", &dest->fault_positions[i], &used) != 1) {
                    free(dest->fault_positions);
                    return 1;
                }
                faults = faults + used;
                i++;
            }
            return 0;
        }
    }
    free(dest->name);
    return 1;
}



//Read file and save data to array
int file_read(char filename[], struct process **procs_out) {

    int capacity = 2;
    struct process *procs = malloc(capacity * sizeof(struct process));
    if (procs == NULL) return 1;

    //get a pointer to file
    FILE *file = open_file(filename);
    if (file == NULL) return 1;  

    //initialise variables
   
    char *line = NULL;
    size_t len = 0;
    ssize_t amount_read;
    int i = 0; 
    
    //read file, copy data to array and initialise values
    while((amount_read = getline(&line, &len, file)) != -1) {

        if (i == capacity) {

            capacity *= 2;
            struct process *tmp = realloc(procs, capacity * sizeof(struct process));
            if (tmp == NULL) {
                free(procs);
                return 1;
            }
            
            procs = tmp;
        }

        if (line_parse(line, &procs[i]) == 1) return 1;

        procs[i].exec_prog = 0;
        procs[i].ran_in_pass = false;
        procs[i].complete = false;
        
        i++;
    }
    num_of_proceses = i;
    free(line);
    fclose(file);
    *procs_out = procs;
    return 0;
}

//return the index of the task with priority from a given array, 
int priority_decider(struct process tasks[])
{
    /*index of the process with the current highest priority, 
    start at -1 so we can return -1 if nothing needs processing*/
    int prio_index = -1; 
    
    int max_prio = INT_MAX; //intitalise the max priority delibratly higher than any real priority value 

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

//return true if every task is complete, else return false 
bool is_finished(struct process tasks[])
{
    for (int i = 0; i < num_of_proceses; i++)
    {
        if (!tasks[i].complete)
        {
            return false;
        }
    }
    return true;
}

//reset ran_in pass varriables
void reset(struct process tasks[])
{
    for (int i = 0; i < num_of_proceses; i++)
    {
        tasks[i].ran_in_pass = false;
    }
}

//helper function to return minimum of two integers
int min(int x, int y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

/* lets run this process!! 
given a array of processes and an index of a process, runs said process for up to 10 ms*/
void run_process(struct process tasks[], int x)
{
    int remaining_time = tasks[x].total_exec_time - tasks[x].exec_prog;
    int local_progress = min(10, remaining_time);

    //what faults trigger in this pass?
    for(int i = 0; i < tasks[x].num_faults; i++)
    {
        if (tasks[x].exec_prog <= tasks[x].fault_positions[i] && 
            tasks[x].fault_positions[i] < tasks[x].exec_prog + local_progress)
        {
            global_time += 4;
        } 
    }

    tasks[x].ran_in_pass = true;
    tasks[x].exec_prog += local_progress;
    global_time += local_progress;

    if(remaining_time <= 10)//this is true iff the process is complete in this pass
    {
        tasks[x].complete = true;
        printf("%s %d\n", tasks[x].name, global_time);
    }
};



//main simulation
int main(int argc, char *argv[])
{
    
    struct process *process_array = NULL;

    //ensure correct number of arguments
    if(argc != 2) {
        printf("incorrect number of arguments\n");
        return 1;
    }
    //ensure file has been read correctly
    if (file_read(argv[1], &process_array) == 1) {
        return 1;
    }

    while(true) //main loop
    {
        int index = priority_decider(process_array);

        if (index == -1)
        {
            if (is_finished(process_array))
            {
                break;
            }
            else
            {
                reset(process_array);
                continue;
            }
        }

        run_process(process_array, index);
    } 

    return 0;
}
