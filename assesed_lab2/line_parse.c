#include <stdlib.h>
#include <string.h>
void line_parse(char *line) {

    int i = 0;
    char split_line[120];
    char *word = strtok(line, " ");

    while (word != NULL) {

        split_line[i] = *word;
        word = strtok(NULL, " ");
        i++;

    }

    char name = split_line[0];
    int priority = split_line[1];
    int total_time = split_line[2];
    int fault_count = split_line[3];
    int *fault_positions = malloc(fault_count * sizeof(int));
    
    for (int i = 4; i < (fault_count + 3); i++) {
        int j = i - 4;
        fault_positions[j] = split_line[i];
    }
}

int main() {
    line_parse("Program7 3 110 2 40 90\n");
    return 0;
}