#include <stdio.h>
#include "passwordchecker.h"  // Include the header file


int main() {
    FILE *file;
    char line[256]; // Buffer to store a line

    file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) { // Read line by line
        printf("%s", line);
    }

    fclose(file);
    return 0;
}
