#include "user/user.h"

void primes(int) __attribute__((noreturn)); 

void primes(int fd) {
    int k;
    
    if (read(fd, &k, 4) <= 0) {
        close(fd);
        exit(0);
    }

    int prime = k;
    printf("prime %d\n", prime);

    int p[2];
    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        close(fd); 

        primes(p[0]);
    } else {
        close(p[0]);
        
        while (read(fd, &k, 4) > 0) {
            if (k % prime != 0) {
                write(p[1], &k, 4);
            }
        }
    }

    close(p[1]);
    close(fd);

    wait(0);
    exit(0);
}

int main(int argc, char *argv[]) {
    
    if (argc != 1) {
        fprintf(2, "Usage: primes\n");
        exit(1);
    }

    int p[2];
    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        
        primes(p[0]);
        
    } else {
        close(p[0]);

        printf("prime %d\n", 2);

        for (int i = 3; i <= 280; i += 2) {
            write(p[1], &i, 4);
        }
        close(p[1]);

        wait(0);

        exit(0);
    }
}