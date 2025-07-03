#include "user/user.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(2, "Pass one parameter, usage: sleep 10\n");
        exit(1);
    }

    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}