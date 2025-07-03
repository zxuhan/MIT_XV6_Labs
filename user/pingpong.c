#include "user/user.h"

int main(int argc, char *argv[]) {
    int p1[2]; // parent to child
    int p2[2]; // child to parent
    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        char buf[1];
        close(p1[1]);
        close(p2[0]);

        if (read(p1[0], buf, 1) != 1) {
            fprintf(2, "child read error.\n");
            exit(1);
        }

        printf("%d: received ping\n", getpid());

        if (write(p2[1], buf, 1) != 1) {
            fprintf(2, "child write error.\n");
            exit(1);
        }

        close(p1[0]);
        close(p2[1]);

        exit(0);
    } else {
        char buf[1];
        close(p1[0]);
        close(p2[1]);

        if (write(p1[1], "a", 1) != 1) {
            fprintf(2, "parent write error.\n");
            exit(1);
        }

        wait(0);

        if (read(p2[0], buf, 1) != 1)
        {
            fprintf(2, "parent read error.\n");
            exit(1);
        }

        printf("%d: received pong\n", getpid());
        
        close(p1[1]);
        close(p2[0]);

        exit(0);
    }
}