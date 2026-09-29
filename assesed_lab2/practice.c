#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file = fopen("test_input_2.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 1. Initialize buffer variables ONCE before the loop
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 1;

    // 2. The loop runs until getline returns -1 (EOF or Error)
    while ((read = getline(&line, &len, file)) != -1) {
        
        // Strip trailing newline if present
        line[strcspn(line, "\n")] = '\0';
        
        // Process the line
        printf("Line %d [%zu bytes allocated]: %s\n", line_number, len, line);
        line_number++;

        // 2. If the allocated buffer is way bigger than the data we just read
        if (len > 128 && (size_t)read < (len / 2)) {
            // Shrink the buffer back down to a reasonable baseline (e.g., 128 bytes)
            char *temporary_pointer = realloc(line, 128);
            if (temporary_pointer != NULL) {
                line = temporary_pointer;
                len = 128; // Remember to update the size tracker!
            }
        }
    }

    // 3. CRITICAL: Free the buffer exactly ONCE after the loop finishes
    free(line);
    
    // 4. Close the file stream
    fclose(file);
    return 0;
}