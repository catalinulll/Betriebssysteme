#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

#define FILENAME "depot.txt"

void deliver_goods(const char* goods, int quantity) {
    printf("Delivering %d units of %s\n", quantity, goods);
    sleep(1); 
}

int main() {
    FILE* file;

    if ((file = fopen(FILENAME, "r")) == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    if (flock(fileno(file), LOCK_EX) == -1) {
        perror("Failed to lock file");
        exit(1);
    }

    char line[30];
    char goods[20];
    int quantity;

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%s %d", goods, &quantity);
        deliver_goods(goods, quantity);
    }

    if (flock(fileno(file), LOCK_UN) == -1) {
        perror("Failed to unlock file");
        exit(1);
    }

    fclose(file);

    return 0;
}

