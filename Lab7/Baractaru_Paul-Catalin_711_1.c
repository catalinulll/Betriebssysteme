#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

void process_1() { // Functie responsabila pentru citirea, procesarea si transmiterea datelor in procese
    char line[256];  // Buffer pentru linia citită
    char digits[256];  // Buffer pentru cifre
    char letters[256];  // Buffer pentru litere
    int digits_index = 0;  // Index pentru buffer-ul de cifre
    int letters_index = 0;  // Index pentru buffer-ul de litere

    while (fgets(line, sizeof(line), stdin)) { // Citesc linii 
        if (strlen(line) <= 30) { // Daca au lungime mai mica sau egala cu 30
            for (int i = 0; line[i] != '\0'; i++) { // Iau fiecare caracter
                if (isdigit(line[i])) { // Daca e cifra
                    digits[digits_index++] = line[i];  // Adaugă cifra în buffer-ul de cifre
                } else if (isalpha(line[i])) { // Daca e litera
                    letters[letters_index++] = line[i];  // Adaugă litera în buffer-ul de litere
                }
            }
        }
    }

    digits[digits_index] = '\0';  // Setează sfârșitul de șir pentru buffer-ul de cifre
    letters[letters_index] = '\0';  // Setează sfârșitul de șir pentru buffer-ul de litere

    int pipe_1[2];  // Declarațiile pentru primul pipe (capetele de citire și scriere)
    int pipe_2[2];  // Declarațiile pentru al doilea pipe (capetele de citire și scriere)

    pipe(pipe_1);  // Creează primul pipe
    pipe(pipe_2);  // Creează al doilea pipe

    pid_t pid_2 = fork();  // Creează procesul copil 2

    if (pid_2 == 0) { // Proces copil 2
        close(pipe_1[1]);  // Închide capătul de scriere al primului pipe
        char buffer[256];
        ssize_t read_bytes = read(pipe_1[0], buffer, sizeof(buffer) - 1);  // Citește datele din capătul de citire al primului pipe
        if (read_bytes > 0) { // Daca s-a citit cel putin 1 byte de date(daca s-au primit date valide in buffer)
            buffer[read_bytes] = '\0';  // Setează sfârșitul de șir pentru buffer
            printf("%s ", buffer);  // Afișează conținutul buffer-ului
        }
        close(pipe_1[0]);  // Închide capătul de citire al primului pipe
        exit(0);  // Termină procesul copil 2
    } else {
        pid_t pid_3 = fork();  // Creează procesul copil 3

        if (pid_3 == 0) {
            // Child process 3
            close(pipe_2[1]);  // Închide capătul de scriere al al doilea pipe
            char buffer[256];
            ssize_t read_bytes = read(pipe_2[0], buffer, sizeof(buffer) - 1);  // Citește datele din capătul de citire al al doilea pipe
            if (read_bytes > 0) { // Daca s-a citit cel putin 1 byte de date(daca s-au primit date valide in buffer)
                buffer[read_bytes] = '\0';  // Setează sfârșitul de șir pentru buffer
                for (int i = 0; buffer[i] != '\0'; i++) {
                    if (islower(buffer[i])) {
                        buffer[i] = toupper(buffer[i]);  // Converteste literele mici in litere mari
                    }
                }
                printf("%s", buffer);  // Afișează conținutul buffer-ului
            }
            close(pipe_2[0]);  // Închide capătul de citire al al doilea pipe
            exit(0);  // Termină procesul copil 3
        } else {
            // Parent process
            close(pipe_1[0]);  // Închide capătul de citire al primului pipe
            close(pipe_2[0]);  // Închide capătul de citire al al doilea pipe
            write(pipe_1[1], digits, strlen(digits));  // Scrie conținutul buffer-ului de cifre în primul pipe
            write(pipe_2[1], letters, strlen(letters));  // Scrie conținutul buffer-ului de litere în al doilea pipe
            close(pipe_1[1]);  // Închide capătul de scriere al primului pipe
            close(pipe_2[1]);  // Închide capătul de scriere al al doilea pipe

            wait(NULL);  // Așteaptă ca procesul copil 3 să se termine
            wait(NULL);  // Așteaptă ca procesul copil 2 să se termine
        }
    }
}

int main() {
    pid_t pid_1 = fork();  // Creează procesul copil 1

    if (pid_1 == 0) {
        // Child process 1
        process_1();  // Execută funcția process_1()
    } else {
        wait(NULL);  // Așteaptă ca procesul copil 1 să se termine
    }

    return 0;
}

