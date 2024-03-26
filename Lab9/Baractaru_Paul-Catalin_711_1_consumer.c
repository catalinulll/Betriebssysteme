#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

// Numele fisierului in care se afla bunurile depozitate
#define FILENAME "depot.txt"

void consume_goods(const char* goods, int quantity) { // un sir de caractere (bunurile) si o cantitate
    printf("Consuming %d units of %s\n", quantity, goods);
    // Contine actiuni specifice consumatorului
    sleep(1); // Simuleaza o actiune de consum(asteapta o secunda)
}

int main() {
    FILE* file; // Declar un pointer la fisier

    // Deschid fisierul "depot.txt" in modul citire
    if ((file = fopen(FILENAME, "r")) == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    // Blochez fisierul ca sa asigur acces exclusiv la el
    if (flock(fileno(file), LOCK_EX) == -1) {
        perror("Failed to lock file");
        exit(1);
    }

    // Variabile necesare pt linii, bunuri si cantitate
    char line[30];
    char goods[20];
    int quantity;

    while (fgets(line, sizeof(line), file) != NULL) { // Citesc linii din fisier
        sscanf(line, "%s %d", goods, &quantity); // Descompun linia in bunuri si cantitate
        consume_goods(goods, quantity); // Consum bunurile citite
    }

    // Deblochez fisierul
    if (flock(fileno(file), LOCK_UN) == -1) {
        perror("Failed to unlock file");
        exit(1);
    }

    // Inchid fisierul
    fclose(file);

    return 0;
}

