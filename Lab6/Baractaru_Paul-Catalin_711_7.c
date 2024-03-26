#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
if (argc <= 1) {
printf("No numbers provided.\n");
return 1;
}
    int n = argc; // Number of elements in the array
    int *nums = (int *)malloc(n * sizeof(int)); // Dynamic array for numbers
    int sum = 0; // Variable to store the sum of cubes
    int i;
    int fd[2]; // File descriptors for pipe

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            // Child process
            close(fd[0]); // Close the read end of the pipe

            int num = atoi(argv[i]);
            int cube = num * num * num;
            write(fd[1], &cube, sizeof(cube)); // Write the cube value to the pipe

            close(fd[1]); // Close the write end of the pipe
            exit(0);
        } else if (pid < 0) {
            // Error handling
            perror("fork");
            exit(1);
        }
    }

    close(fd[1]); // Close the write end of the pipe

    for (i = 0; i < n; i++) {
        int cube;
        read(fd[0], &cube, sizeof(cube)); // Read the cube value from the pipe
        sum += cube;
    }

    close(fd[0]); // Close the read end of the pipe

    for (i = 0; i < n; i++) {
        wait(NULL); // Wait for all child processes to finish
    }

    printf("Sum of the cubes of the numbers: %d\n", sum);

    return 0;
}

