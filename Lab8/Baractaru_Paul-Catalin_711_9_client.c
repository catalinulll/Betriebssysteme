#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

// Numele conductelor
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define FIFO3 "fifo3"

int main() {
    int fd1 = open(FIFO1, O_WRONLY); // Deschiderea conductei FIFO1 pentru scriere
    int fd2 = open(FIFO2, O_WRONLY); // Deschiderea conductei FIFO2 pentru scriere
    int fd3 = open(FIFO3, O_WRONLY); // Deschiderea conductei FIFO3 pentru scriere

    char line[256];
    while (fgets(line, sizeof(line), stdin)) { // Citesc linii de la intreare pana cand se ajunge la sfarsitul fisierului de intrare
        if (isalpha(line[0])) { // Daca primul caracter din linie e o litera
            write(fd1, line, strlen(line) + 1); // Scrie liniile care încep cu o literă în FIFO1
        } else if (isdigit(line[0])) { // Daca primul caracter din linie e o cifra
            write(fd2, line, strlen(line) + 1); // Scrie liniile care încep cu un număr în FIFO2
        } else { // Daca primul caracter din linie e altceva
            write(fd3, line, strlen(line) + 1); // Scrie restul liniilor în FIFO3
        }
    }

    close(fd1); // Închide conducta FIFO1
    close(fd2); // Închide conducta FIFO2
    close(fd3); // Închide conducta FIFO3

    return 0;
}

