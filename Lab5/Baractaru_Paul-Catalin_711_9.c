#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a constant for the maximum line length
#define MAX_LINE_LENGTH 1000

// Define the main function, which takes command line arguments
int main(int argc, char *argv[]) {
    // Check if the program was called with the correct number of arguments
    if (argc != 3) {
        return 1;
    }

    // Get the names of the two input files from the command line arguments
    char *filename1 = argv[1];
    char *filename2 = argv[2];

    // Open the first input file for reading
    FILE *file1 = fopen(filename1, "r");
    // Check if the file was opened successfully
    if (file1 == NULL) {
        return 1;
    }

    // Open the second input file for reading
    FILE *file2 = fopen(filename2, "r");
    // Check if the file was opened successfully
    if (file2 == NULL) {
        fclose(file1);
        return 1;
    }

    // Declare two character arrays to store the lines read from each file
    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];

    // Read lines from both files and compare them until one of the files is exhausted
    while (fgets(line1, MAX_LINE_LENGTH, file1) != NULL && fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
        // Remove the newline character from the end of each line
        line1[strcspn(line1, "\n")] = '\0';
        line2[strcspn(line2, "\n")] = '\0';

        // Compare the two lines and print them in sorted order
        if (strcmp(line1, line2) < 0) {
            printf("%s\n%s\n", line1, line2);
        } else {
            printf("%s\n%s\n", line2, line1);
        }
    }

    // Print any remaining lines from the first file
    while (fgets(line1, MAX_LINE_LENGTH, file1) != NULL) {
        // Remove the newline character from the end of the line
        line1[strcspn(line1, "\n")] = '\0';
        printf("%s\n", line1);
    }

    // Print any remaining lines from the second file
    while (fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
        // Remove the newline character from the end of the line
        line2[strcspn(line2, "\n")] = '\0';
        printf("%s\n", line2);
    }

    // Close both input files
    fclose(file1);
    fclose(file2);

    return 0;
}

