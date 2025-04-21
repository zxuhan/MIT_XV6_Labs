#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

    if (argc > 1) {
        fprintf(2, "No arguments!\n");
        exit(1);
    }

    int p1[2];
    int p2[2];
    char buf[1];

    pipe(p1); // parent->child
    pipe(p2); // child->parent

    if (fork() == 0) {
        close(p1[1]); // close write parent->child
        close(p2[0]); // close read child->parent

        read(p1[0], buf, 1);
        printf("%d: received ping\n", getpid());

        write(p2[1], "p", 1);

        close(p1[0]);
        close(p2[1]);

        exit(0);
    } else {
        close(p1[0]); // close read parent->child
        close(p2[1]); // close write child->parent

        write(p1[1], "p", 1);
        read(p2[0], buf, 1);

        printf("%d: received pong\n", getpid());

        wait(0);

        close(p1[1]);
        close(p2[0]);
    }

    exit(0);
}