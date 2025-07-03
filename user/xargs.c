#include "user/user.h"
#include "kernel/param.h"

int readLine(char *buf, int maxLength) {
    for (int i = 0; i < maxLength - 1; i += 1) {
        if (read(0, buf + i, 1) != 1) {
            return i;
        }

        if (buf[i] == '\n') {
            buf[i] = 0;
            return i;
        }
    }

    buf[maxLength - 1] = 0;
    return maxLength - 1;
}

int main(int argc, char *argv[]) {
    char *args[MAXARG];
    char buf[1024];

    if (argc < 2) {
        fprintf(2, "Usage: xargs command args\n");
        exit(1);
    }

    while (readLine(buf, 1024) > 0) {
        int index = 0;
        for (int i = 1; i < argc && index < MAXARG - 1; i += 1) {
            args[index] = argv[i];
            index += 1;
        }
        args[index] = buf;
        args[index + 1] = 0;

        if (fork() == 0) {
            exec(args[0], args);
        } else {
            wait(0);
        }
    }

    exit(0);
}

