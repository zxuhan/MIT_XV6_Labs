#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

    if (argc <= 1 || argc >= 3) {
        fprintf(2, "Pass one argument for sleep!\n");
        exit(1);
    }

    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}