#include <stdlib.h>
#include <stdio.h>

void line_parse(char *line) {

    char *name;

    int used;
    int ints;

    int priority;
    int exec_time;
    int num_faults;
    

    if (sscanf(line, "%ms%n", &name, &used) == 1) {
        char *cursor = line + used;
        
        if (sscanf(cursor, "%d %d %d%n",&priority, &exec_time, &num_faults, &ints) == 3) {
            char *faults = cursor + ints;
            int *fault_positions = malloc(num_faults * sizeof(int));

            int i = 0;
            while (i < num_faults) {

                if (sscanf(faults, "%d%n", &fault_positions[i], &used) != 1) {
                    break;
                }
                faults = faults + used;
                i++;

            }
        }
    }

printf("%s %d %d %d %d %d", name, priority, exec_time, num_faults, fault_positions[0], fault_positions[1]);


}

int main() {
    line_parse("Program7 3 110 2 40 90\n");
    
    return 0;
}