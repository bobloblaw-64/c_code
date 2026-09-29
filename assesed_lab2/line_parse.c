#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

int line_parse(char *line, struct process *dest) {
    int used;
    int ints;
    if (sscanf(line, "%ms%n", &dest->name, &used) == 1) {
        char *cursor = line + used;
        
        if (sscanf(cursor, "%d %d %d%n",&dest->priority, &dest->total_exec_time, &dest->num_faults, &ints) == 3) {
            int num_faults = dest->num_faults;
            char *faults = cursor + ints;
            dest->fault_positions = malloc(num_faults * sizeof(int));

            int i = 0;
            while (i < num_faults) {
                if (sscanf(faults, "%d%n", &dest->fault_positions[i], &used) != 1) {
                    return 1;
                }
                faults = faults + used;
                i++;
            }
            return 0;
        }
    }
    return 1;
}

int main() {
    struct process process_array[1];
    line_parse("Program7 3 110 2 40 90\n", process_array);
    
    return 0;
}