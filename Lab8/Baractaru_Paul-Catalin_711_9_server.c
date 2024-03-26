+#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

// Numele conductelor
#define FIFO1 "fifo1" 
#define FIFO2 "fifo2"
#define FIFO3 "fifo3"

void server(const char *fifo_name) {
    int fd = open(fifo_name, O_RDONLY); // Deschiderea conductei FIFO pentru citire

    char line[256];
    while (read(fd, line, sizeof(line)) > 0) { // Citesc din FIFO si verific daca s-a citit o linie intreaga
        printf("%s: %s", fifo_name, line); // Afișează liniile corespunzătoare FIFO-ului
    }

    close(fd); // Închide conducta FIFO
}

int main() {
    mkfifo(FIFO1, 0666); // Crearea conductei numite FIFO1
    mkfifo(FIFO2, 0666); // Crearea conductei numite FIFO2
    mkfifo(FIFO3, 0666); // Crearea conductei numite FIFO3

    pid_t pid1 = fork(); // Creez un nou proces copil
    if (pid1 == 0) { // Daca sunt in procesul copil 1
        server(FIFO1); // Procesul 2 - Server pentru FIFO1
        exit(0); // Termin procesul copil 1
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        server(FIFO2); // Procesul 3 - Server pentru FIFO2
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        server(FIFO3); // Procesul 4 - Server pentru FIFO3
        exit(0);
    }

    // Procesul părinte - Client
    execl("./client", "client", NULL); // Execută fișierul client

    waitpid(pid1, NULL, 0); // Așteaptă terminarea procesului 2
    waitpid(pid2, NULL, 0); // Așteaptă terminarea procesului 3
    waitpid(pid3, NULL, 0); // Așteaptă terminarea procesului 4

    unlink(FIFO1); // Șterge conducta FIFO1
    unlink(FIFO2); // Șterge conducta FIFO2
    unlink(FIFO3); // Șterge conducta FIFO3

    return 0;
}

